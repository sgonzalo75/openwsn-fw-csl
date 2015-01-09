#ifndef __IEEE802154E_H
#define __IEEE802154E_H

/**
\addtogroup MAClow
\{
\addtogroup IEEE802154E
\{
*/

#include "opendefs.h"
#include "board.h"
#include "schedule.h"
#include "processIE.h"
#include "opentimers.h"

//=========================== debug define ====================================

//=========================== define ==========================================

#define SYNCHRONIZING_CHANNEL       20 // channel the mote listens on to synchronize
#define TXRETRIES                    3 // number of MAC retries before declaring failed
#define TX_POWER                    31 // 1=-25dBm, 31=0dBm (max value)
#define RESYNCHRONIZATIONGUARD       5 // in 32kHz ticks. min distance to the end of the slot to successfully synchronize
#define US_PER_TICK                 30 // number of us per 32kHz clock tick
#define ADVTIMEOUT                  30 // in seconds: sending ADV every 30 seconds
#define MAXKAPERIOD               2000 // in slots: @15ms per slot -> ~30 seconds. Max value used by adaptive synchronization.
#define DESYNCTIMEOUT             2333 // in slots: @15ms per slot -> ~35 seconds. A larger DESYNCTIMEOUT is needed if using a larger KATIMEOUT.
#define LIMITLARGETIMECORRECTION     5 // threshold number of ticks to declare a timeCorrection "large"
#define LENGTH_IEEE154_MAX         128 // max length of a valid radio packet  
#define DUTY_CYCLE_WINDOW_LIMIT    (0xFFFFFFFF>>1) // limit of the dutycycle window

//15.4e information elements related
#define IEEE802154E_PAYLOAD_DESC_LEN_SHIFT                 0x04
#define IEEE802154E_PAYLOAD_DESC_GROUP_ID_MLME             (1<<1)
#define IEEE802154E_DESC_TYPE_LONG                         0x01
#define IEEE802154E_DESC_TYPE_SHORT                        0x00

#define IEEE802154E_DESC_TYPE_HEADER_IE                    0x00
#define IEEE802154E_DESC_TYPE_PAYLOAD_IE                   0x01
//len field on PAYLOAD/HEADER DESC
#define IEEE802154E_DESC_LEN_HEADER_IE_MASK                0xFE00
#define IEEE802154E_DESC_LEN_PAYLOAD_IE_MASK               0xFFE0

#define IEEE802154E_DESC_LEN_HEADER_IE_SHIFT               9
#define IEEE802154E_DESC_LEN_PAYLOAD_IE_SHIFT              5

//groupID/elementID field on PAYLOAD/HEADER DESC
#define IEEE802154E_DESC_ELEMENTID_HEADER_IE_MASK          0x01FE
#define IEEE802154E_DESC_GROUPID_PAYLOAD_IE_MASK           0x001E

#define IEEE802154E_DESC_ELEMENTID_HEADER_IE_SHIFT         1
#define IEEE802154E_DESC_GROUPID_PAYLOAD_IE_SHIFT          1

//MLME Sub IE LONG page 83
#define IEEE802154E_DESC_LEN_LONG_MLME_IE_MASK             0xFFE0
#define IEEE802154E_DESC_SUBID_LONG_MLME_IE_MASK           0x001E

#define IEEE802154E_DESC_LEN_LONG_MLME_IE_SHIFT            5
#define IEEE802154E_DESC_SUBID_LONG_MLME_IE_SHIFT          1

//MLME Sub IE SHORT page 82
#define IEEE802154E_DESC_LEN_SHORT_MLME_IE_MASK            0xFF00
#define IEEE802154E_DESC_SUBID_SHORT_MLME_IE_MASK          0x00FE

#define IEEE802154E_DESC_LEN_SHORT_MLME_IE_SHIFT           8
#define IEEE802154E_DESC_SUBID_SHORT_MLME_IE_SHIFT         1

#define IEEE802154E_MLME_SYNC_IE_SUBID                     0x1A
#define IEEE802154E_MLME_SYNC_IE_SUBID_SHIFT               1
#define IEEE802154E_MLME_SLOTFRAME_LINK_IE_SUBID           0x1B
#define IEEE802154E_MLME_SLOTFRAME_LINK_IE_SUBID_SHIFT     1
#define IEEE802154E_MLME_TIMESLOT_IE_SUBID                 0x1c
#define IEEE802154E_MLME_TIMESLOT_IE_SUBID_SHIFT           1

#define IEEE802154E_MLME_IE_GROUPID                        0x01
#define IEEE802154E_ACK_NACK_TIMECORRECTION_ELEMENTID      0x1E

/**
When a packet is received, it is written inside the OpenQueueEntry_t->packet
buffer, starting at the byte defined below. When a packet is relayed, it
traverses the stack in which the MAC and IPHC headers are parsed and stripped
off, then put on again. During that process, the IPv6 hop limit field is
decremented. Depending on the new value of the hop limit, the IPHC header
compression algorithm might not be able to compress it, and hence has to carry
it inline, adding a byte to the header. To avoid having to move bytes around
inside OpenQueueEntry_t->packet buffer, we start writing the received packet a
bit after the start of the packet.
*/
#define FIRST_FRAME_BYTE             1

// the different states of the IEEE802.15.4e state machine
typedef enum {
   S_SLEEP                   = 0x00,   // ready for next slot

   // [CSL]: TX MODE States.
   S_CSLTXWAKEUPOFFSET       = 0x1a,   // waiting to prepare for CSL Tx wake-up
   S_CSLTXWAKEUPPREPARE		 = 0x1b,   // preparing for Tx wake-up
   S_CSLTXWAKEUPREADY	     = 0x1c,   // ready to Rx wake-up, waiting for 'go'
   S_CSLTXWAKEUPDELAY        = 0x1d,   // 'go' signal given, waiting for SFD Tx Wake-up
   S_CSLTXWAKEUP             = 0x1e,   // Tx data SFD received, sending bytes

   S_CSLTXDATAPREOFFSET		 = 0x1f,   // waiting remainingRzTime and starting data frame Tx process
   S_CSLTXDATAOFFSET         = 0x20,   // waiting to prepare for Tx data
   S_CSLTXDATAPREPARE        = 0x21,   // preparing for Tx data
   S_CSLTXDATAREADY          = 0x22,   // ready to Tx data, waiting for 'go'
   S_CSLTXDATADELAY          = 0x23,   // 'go' signal given, waiting for SFD Tx data
   S_CSLTXDATA               = 0x24,   // Tx data SFD received, sending bytes

   S_CSLRXACKOFFSET          = 0x25,   // Tx data done, waiting to prepare for Rx ACK
   S_CSLRXACKPREPARE         = 0x26,   // preparing for Rx ACK
   S_CSLRXACKREADY           = 0x27,   // ready to Rx ACK, waiting for 'go'
   S_CSLRXACKLISTEN          = 0x28,   // idle listening for ACK
   S_CSLRXACK                = 0x29,   // Rx ACK SFD received, receiving bytes
   S_CSLTXPROC               = 0x2a,   // processing sent data


   // [CSL]: RX MODE - IDLE LISTENING States.
   S_CSLRXWAKEUPOFFSET       = 0x2b,   // waiting to prepare for CSL Rx wake-up
   S_CSLRXWAKEUPPREPARE      = 0x2c,   // preparing for Rx wake-up
   S_CSLRXWAKEUPREADY        = 0x2d,   // ready to Rx wake-up, waiting for 'go'
   S_CSLRXWAKEUPLISTEN       = 0x2e,   // idle listening for wake-up
   S_CSLRXWAKEUP	         = 0x2f,   // idle listening for wake-up
   S_CSLRXWAKEUPVALIDATE     = 0x30,   // validate received wake-up frame.

   S_CSLRXDATAOFFSET         = 0x31,   // waiting to prepare for CSL Rx data.
   S_CSLRXDATAPREPARE        = 0x32,   // preparing for Rx data
   S_CSLRXDATAREADY          = 0x33,   // ready to Rx data, waiting for 'go'
   S_CSLRXDATALISTEN         = 0x34,   // idle listening for data
   S_CSLRXDATA   	         = 0x35,   // idle listening for data

   S_CSLTXACKOFFSET          = 0x36,   // waiting to prepare for Tx ACK
   S_CSLTXACKPREPARE         = 0x37,   // preparing for Tx ACK
   S_CSLTXACKREADY           = 0x38,   // Tx ACK ready, waiting for 'go'
   S_CSLTXACKDELAY           = 0x39,   // 'go' signal given, waiting for SFD Tx ACK
   S_CSLTXACK                = 0x3a,   // Tx ACK SFD received, sending bytes
   S_CSLRXPROC               = 0x3b,   // processing received data

} ieee154e_state_t;

// Atomic durations
// expressed in 32kHz ticks:
//    - ticks = duration_in_seconds * 32768
//    - duration_in_seconds = ticks / 32768
enum ieee154e_atomicdurations_enum {

   // [CSL]: timing related
   macCSLPeriod 			 = PORT_macCSLPeriod,	  // CSL - 200000us (200ms) by default.
   macCSLMaxPeriod			 = PORT_macCSLMaxPeriod,  // CSL - By default equal to macCSLPeriod.
   macCSLTxChkFreq			 = PORT_macCSLTxChkFreq,  // CSL - 60000us (60ms) by default. How often should we check if it is something pending on queue to transmit?.

   // time-slot related
   TsTxOffset                =  131,                  //  4000us
   TsLongGT                  =   43,                  //  1300us
   TsTxAckDelay              =  151,                  //  4606us
   TsShortGT                 =   16,                  //   500us
   TsSlotDuration            =  PORT_TsSlotDuration,  // 15000us
   // execution speed related
   maxTxDataPrepare          =  PORT_maxTxDataPrepare,
   maxRxAckPrepare           =  PORT_maxRxAckPrepare,
   maxRxDataPrepare          =  PORT_maxRxDataPrepare,
   maxTxAckPrepare           =  PORT_maxTxAckPrepare,
   // radio speed related
   delayTx                   =  PORT_delayTx,         // between GO signal and SFD
   delayRx                   =  PORT_delayRx,         // between GO signal and start listening
   // radio watchdog
   wdRadioTx                 =   33,                  //  1000us (needs to be >delayTx)
   wdDataDuration            =  164,                  //  5000us (measured 4280us with max payload)
   wdAckDuration             =   98,                  //  3000us (measured 1000us)
};

//shift of bytes in the linkOption bitmap
enum ieee154e_linkOption_enum {
   FLAG_TX_S                 = 7,
   FLAG_RX_S                 = 6,
   FLAG_SHARED_S             = 5,
   FLAG_TIMEKEEPING_S        = 4,   
};

// FSM timer durations (combinations of atomic durations)
// TX
#define DURATION_tt1 ieee154e_vars.lastCapturedTime+TsTxOffset-delayTx-maxTxDataPrepare
#define DURATION_tt2 ieee154e_vars.lastCapturedTime+TsTxOffset-delayTx
#define DURATION_tt3 ieee154e_vars.lastCapturedTime+TsTxOffset-delayTx+wdRadioTx
#define DURATION_tt4 ieee154e_vars.lastCapturedTime+wdDataDuration
#define DURATION_tt5 ieee154e_vars.lastCapturedTime+TsTxAckDelay-TsShortGT-delayRx-maxRxAckPrepare
#define DURATION_tt6 ieee154e_vars.lastCapturedTime+TsTxAckDelay-TsShortGT-delayRx
#define DURATION_tt7 ieee154e_vars.lastCapturedTime+TsTxAckDelay+TsShortGT
#define DURATION_tt8 ieee154e_vars.lastCapturedTime+wdAckDuration

// [CSL]: tiempo limite de transmisión de una trama wake-up CSL
#define MaxWakeUpTxTime TsTxOffset-delayTx+wdRadioTx+wdDataDuration

// RX
#define DURATION_rt1 ieee154e_vars.lastCapturedTime+TsTxOffset-TsLongGT-delayRx-maxRxDataPrepare
#define DURATION_rt2 ieee154e_vars.lastCapturedTime+TsTxOffset-TsLongGT-delayRx

// [CSL]: El tiempo de duración de la operación LISTEN debe ser igual al tiempo
// máximo de TX de una trama para asegurar su recepción.
//#define DURATION_rt3 ieee154e_vars.lastCapturedTime+TsTxOffset+TsLongGT
#define DURATION_rt3 MaxWakeUpTxTime

#define DURATION_rt4 ieee154e_vars.lastCapturedTime+wdDataDuration
#define DURATION_rt5 ieee154e_vars.lastCapturedTime+TsTxAckDelay-delayTx-maxTxAckPrepare
#define DURATION_rt6 ieee154e_vars.lastCapturedTime+TsTxAckDelay-delayTx
#define DURATION_rt7 ieee154e_vars.lastCapturedTime+TsTxAckDelay-delayTx+wdRadioTx
#define DURATION_rt8 ieee154e_vars.lastCapturedTime+wdAckDuration

//=========================== typedef =========================================

// [CSL]: CSL Working Mode (CWM)
typedef enum {
   CSL_SLEEP_MODE,               // CSL - State where mote is sleeping or idle and it is not involved in a current RX o TX.
   CSL_RX_MODE,                  // CSL - State where mote is performing a channel sampling and a (possible) frame RX.
   CSL_TX_MODE,                  // CSL - State where mote is performing a frame TX.
} ieee154ecsl_mode_t;

// IEEE802.15.4E acknowledgement (ACK)
typedef struct {
   PORT_SIGNED_INT_WIDTH timeCorrection;
} IEEE802154E_ACK_ht;

// includes payload header IE short + MLME short Header + Sync IE
#define ADV_PAYLOAD_LENGTH sizeof(payload_IE_ht) + \
                           sizeof(mlme_IE_ht)     + \
                           sizeof(sync_IE_ht)

//=========================== module variables ================================

typedef struct {
   // misc
   asn_t                     asn;                     // current absolute slot number

   slotOffset_t              slotOffset;              // current slot offset
   slotOffset_t              nextActiveSlotOffset;    // next active slot offset
   PORT_RADIOTIMER_WIDTH     deSyncTimeout;           // how many slots left before looses sync
   bool                      isSync;                  // TRUE if mote is synchronized to network
   // as shown on the chronogram
   ieee154e_state_t          state;                   // state of the FSM
   OpenQueueEntry_t*         dataToSend;              // pointer to the data to send
   OpenQueueEntry_t*         dataReceived;            // pointer to the data received
   OpenQueueEntry_t*         ackToSend;               // pointer to the ack to send
   OpenQueueEntry_t*         ackReceived;             // pointer to the ack received
   PORT_RADIOTIMER_WIDTH     lastCapturedTime;        // last captured time
   PORT_RADIOTIMER_WIDTH     syncCapturedTime;        // captured time used to sync
   // channel hopping
   uint8_t                   freq;                    // frequency of the current slot
   uint8_t                   asnOffset;               // offset inside the frame
   
   PORT_RADIOTIMER_WIDTH     radioOnInit;             // when within the slot the radio turns on
   PORT_RADIOTIMER_WIDTH     radioOnTics;             // how many tics within the sample the radio is on
   bool                      radioOnThisSlot;         // to control if the radio has been turned on in a schedule slot.

   // [CSL]: Variables CSL
   OpenQueueEntry_t*	     wakeupToSend;			  // CSL - Pointer to the wakeup to send.
   OpenQueueEntry_t*	     wakeupReceived;		  // CSL - Pointer to the wakeup received.
   uint8_t					 cslDSN;				  // CSL - DSN for wake-up sequence frames.
   ieee154ecsl_mode_t		 cslMode;				  // CSL - Csl mode (sleep, transmission o reception).
   opentimer_id_t			 txTimer;				  // CSL - Timer for checking frames on local queue to transmit.
   opentimer_id_t			 cslTxTestTimer;          // [CSL-TEST] - Timer for periodic add packet to queue for testing CSL TX.
   uint16_t					 remainingRzTime;		  // CSL - Used for checking if we should stop to sending wake-up and start to sending data.

} ieee154e_vars_t;

BEGIN_PACK
typedef struct {
   uint8_t                   numSyncPkt;              // how many times synchronized on a non-ACK packet
   uint8_t                   numSyncAck;              // how many times synchronized on an ACK
   int16_t                   minCorrection;           // minimum time correction
   int16_t                   maxCorrection;           // maximum time correction
   uint8_t                   numDeSync;               // number of times a desync happened
   uint32_t                  numTicsOn;               // mac dutyCycle
   uint32_t                  numTicsTotal;            // total tics for which the dutycycle is computed
} ieee154e_stats_t;
END_PACK

// [CSL]: debugging info
typedef struct {
   PORT_RADIOTIMER_WIDTH     num_newSample;            // CSL - commented and renamed slot reference.
   PORT_RADIOTIMER_WIDTH     num_timer;
   PORT_RADIOTIMER_WIDTH     num_startOfFrame;
   PORT_RADIOTIMER_WIDTH     num_endOfFrame;
   PORT_RADIOTIMER_WIDTH     num_cslSamples;  		   // CSL - counter of CSL Samples
} ieee154e_dbg_t;

//=========================== prototypes ======================================

// admin
void               ieee154e_init(void);
// public
PORT_RADIOTIMER_WIDTH   ieee154e_asnDiff(asn_t* someASN);
bool               ieee154e_isSynch(void);
void               ieee154e_getAsn(uint8_t* array);
// events
void               ieee154ecsl_startOfFrame(PORT_RADIOTIMER_WIDTH capturedTime);
void               ieee154ecsl_endOfFrame(PORT_RADIOTIMER_WIDTH capturedTime);
// misc
bool               debugPrint_asn(void);
bool               debugPrint_isSync(void);
bool               debugPrint_macStats(void);

/**
\}
\}
*/

#endif
