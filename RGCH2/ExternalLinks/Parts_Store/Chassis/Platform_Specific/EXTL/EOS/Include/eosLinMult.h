/**
 *  \file       eosLinMult.h
 *
 *  \brief      Public eos header file for application tasks using more
 *              one LIN bus.
 *
 *  \par    history
 *
 *  2010-09-06 / Christian Pischulti
 *  - draft
 *
 *  2011-03-08 / Christian.Pischulti@xfendt.de
 *  - New flags and free selectable framelength for LIN 2.X compatibility
 *    in struct LinFrameCfg_ts.
 *
 *  2012-04-17 / Christian.Pischulti@xfendt.de
 *  - Added defines for diagnostic interface like commands, timings and other
 *    things.
 *  - Added property const for data pointer parameter of function
 *    eosLinSetData_s32().
 *  - New function eosLinStartRead_s32() for read of one time frames like slave
 *    response to diagnostic requests.
 *
 *  2014-10-14 / Christian.Pischulti@AGCOcorp.com
 *  - [PB-8563] Improved comments for doxygen.
 */
#ifndef __EOSLINMULT_H
    #define __EOSLINMULT_H

    /**
     * \defgroup _lin_mult LIN
     * \{
     */

    /// \brief flags for frame status
    #define LIN_STS_RESP        0x01    ///< \brief send message response field ( internal slave ).
    #define LIN_STS_DATAVALID   0x02    ///< \brief Content of datafield is valid.
                                        ///< \brief Read: Data was read and checked (checksum)
                                        ///< \brief Write: Valid data was written by application task to dataField
    #define LIN_STS_FAULT       0x04    ///< \brief Read: Last read was finished by any kind of error. Data field
                                        ///< \brief may contain old but still valid data from previous read.
                                        ///< \brief Write: Data still valid but lastt write attempt failed.
    #define LIN_STS_TXPROG      0x10    ///< \brief New write data was set but not written until now.
    #define LIN_STS_EXCHKSUM    0x20    ///< \brief Calculate checksum with PROT_ID field.
    #define LIN_STS_TXONETIME   0x40    ///< \brief Transmit frame only one time ( but repeat it until we had success )
    #define LIN_STS_NOTTX       0x80    ///< \brief Data was updated and not sent until now

    /// \brief Macro for build time calculation of P1 and P0 for protected LIN identifier.
    #define LIN_PROT_ID( _linId_ )  (  (_linId_ & 0x3F) ^ \
                                    (  (_linId_ & 0x01) << 6 ) ^ \
                                    (  (_linId_ & 0x02) << 5 ) ^ \
                                    (  (_linId_ & 0x04) << 4 ) ^ \
                                    (  (_linId_ & 0x10) << 2 ) ^ \
                                    (  (_linId_ & 0x02) << 6 ) ^ \
                                    (  (_linId_ & 0x08) << 4 ) ^ \
                                    (  (_linId_ & 0x10) << 3 ) ^ \
                                    (  (_linId_ & 0x20) << 2 ) ^ \
                                       0x80  )

    ///\brief timing defines for diagnostic interface
    #define P2_MIN_MS           50          ///< \brief minimum time after which a slave node should be able to answer response
    #define P2_MAX_MS           500         ///< \brief maximum time between a request and the slave response.

    ///\brief Reserved frame ids
    #define MASTER_REQ_PID      (LIN_PROT_ID( 0x3C ))   ///< \brief diag frame master request id
    #define SLAVE_RESP_PID      (LIN_PROT_ID( 0x3D ))   ///< \brief diag frame slave response id
    #define DIAG_MSG_LENGTH     8                       ///< \brief diag frames always has a data field with 8 bytes

    ///\brief Service Ids (SID) for diagnostic interface
    #define SID_RD_DATA_BY_ID   0x22        ///< \brief read data by identifier
    #define SID_ASSIGN_NAD      0xB0        ///< \brief assign nad for a slave node
    #define SID_READ_BY_ID_REQ  0xB2        ///< \brief read by identifier request.
        #define ID_PRODUCT_ID       0x00    ///< \brief Identifier for getting Supplier and Function ID
    #define SID_ASSIGN_FRAMEID  0xB7        ///< \brief assign frame id range for a slave node


    /// \brief  Lin cluster/node identifiers
    typedef enum
    {
        LIN_1,      ///< \brief cluster 1
        LIN_2,      ///< \brief cluster 2
        LIN_3,      ///< \brief cluster 3
        LIN_4       ///< \brief cluster 4
    } LinBus_te;

    /// \brief scheduler table row
    typedef struct
    {
        uint8   linId_u8;               ///< \brief Id of message which should be sent.
        uint8   delaySchedTicks_u8;     ///< \brief delay to next message in scheduler ticks
    } LinSchedRow_ts;

    /// \brief Message descriptor for setting of schedule table (only configuration data) --
    typedef struct
    {
        uint8   protlinId_u8;           ///< \brief lin message id with parity bits P0 and P1
        uint8   cfgFlags_u8;            ///< \brief Only LIN_STS_RESP for send msg resp and LIN_STS_EXCHKSUM/LIN_STS_TXONETIME
        uint8   frameLength_u8;         ///< \brief Number of data bytes. 0: use old 1.2 scheme 1-8: frame length
    } LinFrameCfg_ts;

    /// \brief LIN bus number schedule main struct ( setSchedule ) --
    typedef struct
    {
        LinFrameCfg_ts const *  frameTable_ps;      ///< \brief pointer to frame configuration table
        LinSchedRow_ts const *  schedTable_ps;      ///< \brief pointer to schedule table
        uint8                   nofFrames_u8;       ///< \brief length of frame descriptor table
        uint8                   nofSchedRows_u8;    ///< \brief length of scheduler table
        uint8                   schedulerTickMs_u8; ///< \brief scheduler tick in milli seconds
    } LinSchedule_ts;

    /// \brief Lin cluster states
    typedef enum
    {
        LIN_CLST_SLEEP,             ///< \brief lin cluster is in sleep state
        LIN_CLST_WAKEUP,            ///< \brief lin cluster wake up started ( txd low pulse )
        LIN_CLST_AWAKE,             ///< \brief lin cluster is awake state ( wake and scheduler running )
        LIN_CLST_GOSLEEP,           ///< \brief lin cluster is receiving go to sleep command from master node
        LIN_CLST_FAULT              ///< \brief unrecoverable fault detected
    } LinClusterState_te;

    // schedule functions
    sint32  eosLinSetSchedule_s32( LinBus_te linBus_e, LinSchedule_ts * linSchedule_ps );
    sint32  eosLinStartStopSchedule_s32( LinBus_te linBus_e, bool start_b );
    sint32  eosLinScheduleStarted( LinBus_te linBus_e, boolean * schedStarted_pb );    // Returns TRUE if a schedule has been started for this cluster.

    // bus status functions
    sint32  eosLinSetClusterSleepWake_s32( LinBus_te linBus_e, bool setWake_b );                // TRUE: wake up lin cluster (bus); FALSE: set to sleep
    sint32  eosLinGetClusterStatus_s32( LinBus_te linBus_e, LinClusterState_te * linClstState_pe );

    // data functions
    sint32  eosLinReadData_s32( LinBus_te linBus_e, uint8 linId_u8, uint8 * dataField_pu8, uint8 * frameSts_pu8 );      // returns last read or written data
    sint32  eosLinSetData_s32( LinBus_te linBus_e, uint8 linId_u8, uint8 const * dataField_pu8, uint8 frameLength_u8 ); // set new data field for internal slave ( write message )

    // Start new read of LIN non response frames that should only be transmitted one time.
    sint32  eosLinStartRead_s32( LinBus_te linBus_e, uint8 linId_u8 );

    /**
     * \}
     */

#endif // __EOSLIN_H
