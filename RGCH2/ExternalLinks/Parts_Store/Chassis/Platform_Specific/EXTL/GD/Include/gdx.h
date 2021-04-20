/**
 *  @file       gdx.h
 *
 *  @brief      Extended access to GENERIC DRIVER (GD).
 *
 *
 *  @section    History
 *
 *  2009-07-03 / werner.unsinn@xfendt.de
 *  - erstellt
 *
 *  2011-03-21 / werner.unsinn@xfendt.de
 *  - Funktion gdxTestRequestData_b() eingefuegt
 *
 *  2012-07-05 / werner.unsinn@agcocorp.com
 *  - Typedefs fuer Pointer auf Strukturen entfernt
 *
 *  2013-01-17 / werner.unsinn@agcocorp.com
 *  - Funktion gdxKillRequest_s32() eingefuegt [PB-3991]
 *    (notwendig wenn fuer Anfrage gdxSendRequest*RR_s32() verwendet wird)
 *
 *  2013-10-01 / rainer.eberhardt@agcocorp.com
 *  - comments translated to English
 *
 *  2014-01-24 / werner.unsinn@agcocorp.com
 *  - Funktionen fuer ECRR Requests mit absoluter Hysterese hinzugefuegt [PB-6108]
 *
 *  2015-10-09 / mattis.kornelius@agcocorp.com
 *  - [PB-10478] replaced bool by boolean
 */

#ifndef __GDX_H
#define __GDX_H


///> Zustandsstruktur zur Erfassung externer Groessen (Signale, Zustaende) ueber GENERIC DRIVER
typedef struct
{
    GdData_ts   data_s;         ///< GD data
    uint32      timestamp_u32;  ///< timestamp
} GdXRequestData_ts;


/**
 *  @brief Reset status structure for external values.
 *
 *  @param xzust_ps     Pointer to status structure
 */
void gdxResetRequestData (GdXRequestData_ts *xdat_ps);

/**
 *  @brief Check if status structure contains valid values.
 *
 *  @param xzust_ps     Pointer to status structure
 *  @return             TRUE if valid values exist, otherwise FALSE
 */
boolean gdxTestRequestData_b (GdXRequestData_ts *xdat_ps);


/**
 *  @brief Send a SRR Request.
 *
 *  Extension: the return value is transferred through data structure
 *
 *  @param tn_u8        Own participant number
 *  @param xdat_ps      Pointer to data structure for return value
 *  @param index_u16    Request index
 *  @param hs_b         Flag for Handshake
 *  @return             0 if the request was successful transmitted
 */
sint32 gdxSendRequestSRR_s32 (uint8 tn_u8, GdXRequestData_ts *xdat_ps, uint16 index_u16, boolean hs_b);

/**
 *  @brief Send an ECRR Request with relative hysteresis.
 *
 *  Extension: the return value is transferred through data structure
 *
 *  @param tn_u8                Own participant number
 *  @param xdat_ps              Pointer to data structure for return value
 *  @param index_u16            Request index
 *  @param hs_b                 Flag for Handshake
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdxSendRequestECRR_s32 (uint8 tn_u8, GdXRequestData_ts *xdat_ps, uint16 index_u16, boolean hs_b, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @brief Send an ECRR Request with absolut hysteresis.
 *
 *  Extension: the return value is transferred through data structure
 *
 *  @param tn_u8                Own participant number
 *  @param xdat_ps              Pointer to data structure for return value
 *  @param index_u16            Request index
 *  @param hs_b                 Flag for Handshake
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdxSendRequestAbsECRR_s32 (uint8 tn_u8, GdXRequestData_ts *xdat_ps, uint16 index_u16, bool hs_b, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @brief Send an AECRR Request with relativ hysteresis.
 *
 *  Extension: the return value is transferred through data structure
 *
 *  @param tn_u8                Own participant number
 *  @param xdat_ps              Pointer to data structure for return value
 *  @param index_u16            Request index
 *  @param period_u16           Cycle duration
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdxSendRequestAECRR_s32 (uint8 tn_u8, GdXRequestData_ts *xdat_ps, uint16 index_u16, uint16 period_u16, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @return Send an AECRR Request with absolut hysteresis.
 *
 *  Extension: the return value is transferred through data structure
 *
 *  @param tn_u8                Own participant number
 *  @param xdat_ps              Pointer to data structure for return value
 *  @param index_u16            Request index
 *  @param period_u16           Cycle duration
 *  @param hysteresisUp_u16     Upper hysteresis for event control
 *  @param hysteresisDown_u16   Lower hysteresis for event control
 *  @return                     0 if the request was successful transmitted
 */
sint32 gdxSendRequestAbsAECRR_s32 (uint8 tn_u8, GdXRequestData_ts *xdat_ps, uint16 index_u16, uint16 period_u16, uint16 hysteresisUp_u16, uint16 hysteresisDown_u16);

/**
 *  @return Send a TCRR Request.
 *
 *  Extension: the return value is transferred through data structure
 *
 *  @param tn_u8        Own participant number
 *  @param xdat_ps      Pointer to data structure for return value
 *  @param index_u16    Request index
 *  @param period_u16   Cycle duration
 *  @return             0 if the request was successful transmitted
 */
sint32 gdxSendRequestTCRR_s32 (uint8 tn_u8, GdXRequestData_ts *xdat_ps, uint16 index_u16, uint16 period_u16);


/**
 *  @brief Cancel a Request.
 *
 *  @param tn_u8        Own participant number
 *  @param xdat_ps      Pointer to data structure for return value
 *  @param index_u16    Index of request to be canceled
 *  @return             0 if the request was successful transmitted
 */
sint32 gdxKillRequest_s32 (uint8 tn_u8, GdXRequestData_ts *xdat_ps, uint16 index_u16);


/**
 *  @brief Send an immediate write.
 *
 *  Erweiterung: bei Signalisierung eines Fehlers vom GD, wird das angegebene Flagbyte auf 0xFF gesetzt
 *
 *  @param tn_u8        Own participant number
 *  @param send_pu8     Pointer to flag byte
 *  @param index_u16    Index of immediate write
 *  @param hs_b         Flag for handshake
 *  @param data_s16     Data bytes
 *  @param stbit_b      Status bit
 *  @param diag_u8      Diagnose byte
 *  @return             0 if the immediate write was successful transmitted
 */
sint32 gdxSendImmediateWrite_s32 (uint8 tn_u8, uint8 *send_pu8, uint16 index_u16, bool hs_b, sint16 data_s16, bool stbit_b, uint8 diag_u8);

#endif // __GDX_H
