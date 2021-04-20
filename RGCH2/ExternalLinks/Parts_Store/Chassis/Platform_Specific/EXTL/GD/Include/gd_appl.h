/**
 *  @file       gd_appl.h
 *
 *  @brief      Application module of GENERIC DRIVER (GD).
 *
 *
 *  @section    History
 *
 *  2009-07-03 / werner.unsinn@xfendt.de
 *  - erstellt
 *
 *  2012-07-05 / werner.unsinn@agcocorp.com
 *  - Typedefs fuer Pointer auf Strukturen entfernt
 *
 *  2013-10-01 / rainer.eberhardt@agcocorp.com
 *  - comments translated to English
 *
 *  2015-10-09 / mattis.kornelius@agcocorp.com
 *  - [PB-10478] replaced bool by boolean
 *
 *  2015-12-17 / florian.koppers.ruecker@agcocorp.com
 *  - [PB-11430] immediate write callback has now a third parameter (logical sender node)
 */

#ifndef __GD_APPL_H
#define __GD_APPL_H


/// Internal structure for local list management (Data basis)
typedef struct
{
    uint16      index_u16;  ///< Index number to public list
    uint8       status_u8;  ///< Availability
    boolean     toSend_b;   ///< send or don't send
    GdData_ts   data_s;     ///< data of last cycle
} GdLocList_ts;

/// Internal structure for application interface of GD
typedef struct
{
    boolean         (*requestIndexData_pf)(uint16, GdData_ts*);

    void            (*signalDataResponse_pf)(uint16, GdData_ts*);
    void            (*signalRequestError_pf)(uint16, GdData_ts*);
    void            (*signalHandshake_pf)(uint16, GdData_ts*);
    void            (*signalImmediateWrite_pf)(uint16, GdData_ts*, uint8);
    void            (*signalImmediateWriteError_pf)(uint16);

    uint16          serviceCount_u16;

    uint16          loclistSize_u16;
    uint16          loclistNumber_u16;
    GdLocList_ts   *loclist_as;

} GdApplStruct_ts;



/**
 *  @brief Initialize the GD application interface for own participant.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param loclist_as   Pointer to first item for local list management
 *  @param size_u16     Number of items for local list management
 */
void gdInitApplStruct (GdApplStruct_ts *appl_ps, GdLocList_ts *loclist_as, uint16 size_u16);

/**
 *  @brief Add an index to local list management.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param index_u16    Index number
 *  @return             0 if index was added, otherwise no free element
 */
sint32 gdAddIndexToApplStruct_s32 (GdApplStruct_ts *appl_ps, uint16 index_u16);

/**
 *  @brief Insert the function to request indices to own participant.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for index requests
 */
void gdConnectIndexData (GdApplStruct_ts *appl_ps, boolean (*fu_pf)(uint16, GdData_ts*));

/**
 *  @brief Insert the function to receive answers to previous requests.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for indication of received answers
 */
void gdConnectDataResponse (GdApplStruct_ts *appl_ps, void (*fu_pf)(uint16, GdData_ts*));

/**
 *  @brief Insert the function to receive request errors.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for indication of received errors
 */
void gdConnectRequestError (GdApplStruct_ts *appl_ps, void (*fu_pf)(uint16, GdData_ts*));

/**
 *  @brief Insert the function to receive handshakes.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for indication of received handshakes
 */
void gdConnectHandshake (GdApplStruct_ts *appl_ps, void (*fu_pf)(uint16, GdData_ts*));

/**
 *  @brief Insert the function to receive immediate write access.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for indication of immediate write access
 */
void gdConnectImmediateWrite (GdApplStruct_ts *appl_ps, void (*fu_pf)(uint16, GdData_ts*, uint8));

/**
 *  @brief Insert the function to receive immediate write errors.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param fu_pf        Pointer to function for indication of immediate write errors
 */
void gdConnectImmediateWriteError (GdApplStruct_ts *appl_ps, void (*fu_pf)(uint16));



/**
 *  @brief Evaluate GD messages.
 *
 *  @param appl_ps      Pointer to structure of application interface
 *  @param msg_pps      Pointer to the message
 */
void gdProcessMessage (GdApplStruct_ts *appl_ps, PxMsg_t *msg_pps);

/**
 *  @brief Operate the local list of the participant.
 *
 *  Cyclic database update of REQ's to GD.
 *  Fill the items from application side.
 *
 *  @param appl_ps      Pointer to structure of application interface
 */
void gdServeLoclist (GdApplStruct_ts *appl_ps);

/**
 *  @brief Transmit the number of active requests in local list.
 *
 *  @return             Number of active requests
 */
uint32 gdGetLoclistCount_u32 (GdApplStruct_ts *appl_ps);

#endif // __GD_APPL_H
