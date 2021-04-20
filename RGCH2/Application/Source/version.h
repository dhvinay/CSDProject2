/**
 *  @file   version.h
 */

#define version_bootloader	"AGCO"			// Needs to be "AGCO" for EXT and EXTLT
#define version_project		"RgChs2T"		// 8 chars max, '_' and '.' not allowed" 
#define version_major		"01"			// 2 chars, 00 - 99
#define version_minor		"00"			// 2 chars, 00 - 99
#define version_revision	"01"			// 2 chars, 00 - 99

// applVersion_value without period '.' between major/minor/revision - length 18 characters
#define applVersion_value	version_bootloader "_" version_project "_" version_major version_minor version_revision

// applVersion_valueVT with period '.' between major/minor/revision - length 21 characters
#define applVersion_valueVt	version_bootloader "_" version_project "_" version_major "." version_minor "." version_revision

#define applGNumber_value	"G000.000.000.000"
#define applDate_value		{ 0x23, 0x02, 0x21 }    // BCD in this format:  0xDD, 0xMM, 0xYY.  So, { 0x24, 0x10, 0x13 } is October 24, 2013
#define applTime_value		{ 0x17, 0x04, 0x52 }    // BCD in this format:  0xHH, 0xMM, 0xSS.  So, { 0x15, 0x22, 0x46 } is 15:22:46 (3:22:46 PM)

#if defined SYSTEM_C2C
# define applVersion_ecuType "C2C"
#elif defined SYSTEM_ESX
# define applVersion_ecuType "ESX"
#elif defined SYSTEM_ESXu
# define applVersion_ecuType "ESXu"
#elif defined EXT
# define applVersion_ecuType "EXT"
#elif defined EXT_LIGHT
# define applVersion_ecuType "EXTLT"
#elif defined WIN32
# define applVersion_ecuType "WIN32"
#else
# define applVersion_ecuType ""
#endif

#define applVersion_buildText	".lb"

