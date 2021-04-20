/*
 *  @file       gd_mirror.h
 *
 *  @brief      header file for GD-mirroring, used by application
 *
 *  @section    history
 *
 *  2016-03-03 / florian.koppers.ruecker@agcocorp.com
 *  			 - created
 *  2016-03-16 / florian.koppers.ruecker@agcocorp.com
 *  			 [MISC] added comments
 */

#ifndef MODULE_GD_MIRROR_H_
#define MODULE_GD_MIRROR_H_



typedef struct	// one entry in index-list contains a 16bit-variable with index-number
{
	uint16 indexToMirror_u16;
} gdMirrorEntry_ts;



typedef struct
{
	uint16 canIDRequester_u16;					// CAN-ID for requests / commands to mirror
	uint16 canIDResponse_u16;					// CAN-ID, the responses from mirror should have
	uint8 canBusNumber_u8;						// on this CAN-interface, mirror is listing/responding
	uint8 ecuNumber_u8;                   		// (( segment << 4 ) | phy. node number )
	uint8 numberOfPersistentEntries_u8;			// number of persistent entries (that are stored in EEPROM) = GD_MIRROR_ENTRIES_EEPROM;
	uint8 numberOfTemporaryEntries_u8;			// number of temporary entries. On start = 0, max = GD_MIRROR_ENTRIES_RAM
	bool mirroringActive_b;						// mirroring is only active, if this bit is set
	bool writeEEPROMnow_b;						// library sets this flag, to order application task an EEPROM-write
	gdMirrorEntry_ts *gdMirrorIndexEntries_ps;	// pointer to list of entries. list has size [(GD_MIRROR_ENTRIES_EEPROM + GD_MIRROR_ENTRIES_RAM)];
	uint64 gdMirrorNodeEntries_u64;				// bitfield, that contains a bit for every possible logical node. if bit is set, node gets mirrored
	uint64 gdMirrorNodeEntriesPersistent_u64;	// same as above. But this bitfield is stored in EEPROM when writeEEPROMnow_b-bit is set. So this bitfield gets recovered on next ignition on
}gdMirrorManagement_ts;


#endif /* MODULE_GD_MIRROR_H_ */
