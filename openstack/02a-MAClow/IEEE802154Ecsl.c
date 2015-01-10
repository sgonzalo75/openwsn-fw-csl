#include "IEEE802154Ecsl.h"

#include "opendefs.h"
#include "radio.h"
#include "radiotimer.h"
#include "IEEE802154.h"
#include "openqueue.h"
#include "idmanager.h"
#include "openserial.h"
#include "schedule.h"
#include "packetfunctions.h"
#include "scheduler.h"
#include "leds.h"
#include "neighbors.h"
#include "debugpins.h"
#include "sixtop.h"
#include "adaptive_sync.h"
#include "processIE.h"

//======================================================================
//=========================== VARIABLES ================================
//======================================================================

ieee154e_vars_t	   ieee154e_vars;
ieee154e_stats_t   ieee154e_stats;
ieee154e_dbg_t     ieee154e_dbg;

//======================================================================
//========================== PROTOTYPES ================================
//======================================================================

// [CSL]: FSM activities prototypes.

// TX-MODE: CSL Frame sending activities prototypes
void    activity_csl_wakeup_ti1(void);
void    activity_csl_wakeup_ti2(void);
void    activity_csl_wakeup_tie1(void);
void    activity_csl_wakeup_ti3(void);
void    activity_csl_wakeup_tie2(void);
void    activity_csl_wakeup_ti4(PORT_RADIOTIMER_WIDTH capturedTime);
void    activity_csl_wakeup_tie3(void);
void    activity_csl_wakeup_ti5(PORT_RADIOTIMER_WIDTH capturedTime);

void    activity_csl_data_ti1(void);
void    activity_csl_data_ti2(void);
void    activity_csl_data_tie1(void);
void    activity_csl_data_ti3(void);
void    activity_csl_data_tie2(void);
void    activity_csl_data_ti4(PORT_RADIOTIMER_WIDTH capturedTime);
void	activity_csl_data_tie3(void);
void    activity_csl_data_ti5(PORT_RADIOTIMER_WIDTH capturedTime);
void    activity_csl_data_ti6(void);
void    activity_csl_data_tie4(void);
void	activity_csl_data_ti7(void);
void    activity_csl_data_tie5(void);
void    activity_csl_data_ti8(PORT_RADIOTIMER_WIDTH capturedTime);
void    activity_csl_data_tie6(void);
void    activity_csl_data_ti9(PORT_RADIOTIMER_WIDTH capturedTime);

// RX-MODE: CSL Sampling activities prototypes
void 	activity_csl_wakeup_ri1(void);
void 	activity_csl_wakeup_ri2(void);
void    activity_csl_wakeup_rie1(void);
void    activity_csl_wakeup_ri3(void);
void    activity_csl_wakeup_rie2(void);
void    activity_csl_wakeup_ri4(PORT_RADIOTIMER_WIDTH capturedTime);
void    activity_csl_wakeup_rie3(void);
void    activity_csl_wakeup_ri5(PORT_RADIOTIMER_WIDTH capturedTime);
void    activity_csl_wakeup_rie4(void);

void    activity_csl_data_ri2(void);
void    activity_csl_data_rie1(void);
void    activity_csl_data_ri3(void);
void    activity_csl_data_rie2(void);
void    activity_csl_data_ri4(PORT_RADIOTIMER_WIDTH capturedTime);
void	activity_csl_data_rie3(void);
void    activity_csl_data_ri5(PORT_RADIOTIMER_WIDTH capturedTime);
void    activity_csl_data_ri6(void);
void    activity_csl_data_rie4(void);
void	activity_csl_data_ri7(void);
void    activity_csl_data_rie5(void);
void    activity_csl_data_ri8(PORT_RADIOTIMER_WIDTH capturedTime);
void    activity_csl_data_rie6(void);
void    activity_csl_data_ri9(PORT_RADIOTIMER_WIDTH capturedTime);

// frame validity check
bool     isValidRxFrame(ieee802154_header_iht* ieee802514_header);
bool     isValidAck(ieee802154_header_iht*     ieee802514_header,
                    OpenQueueEntry_t*          packetSent);
void     changeIsSync(bool newIsSync);

// statistics
void     resetStats(void);
void     updateStats(PORT_SIGNED_INT_WIDTH timeCorrection);

// notifying upper layer
void     notif_sendDone(OpenQueueEntry_t* packetSent, owerror_t error);
void     notif_receive(OpenQueueEntry_t* packetReceived, uint8_t action);

// IEs Handling
bool     ieee154e_processIEs(OpenQueueEntry_t* pkt, uint16_t* lenIE);

// ASN handling
void     incrementAsnOffset(void);
void     asnStoreFromAdv(uint8_t* asn);
void     joinPriorityStoreFromAdv(uint8_t jp);

// misc
void     changeState(ieee154e_state_t newstate);
void     endOps(void);
bool     debugPrint_asn(void);
bool     debugPrint_isSync(void);

// CSL Sampling interrupts
void     isr_ieee154ecsl_newChannelSample(void);
void     isr_ieee154ecsl_timer(void);

// [CSL]: queue checking for local transmissions
void 	 isr_ieee154ecsl_txtimer_cb(void);

// [CSL-TEST]: Testing callback to put a packet on queue for testing CSL Tx mode.
void     isr_ieee154ecsl_addPacketToQueueForTestingCslTx_cb (void);

// [CSL]: Wake-up frames prototypes (create and retrieve methods).
void 	ieee802154_retrieveWakeUpFrame(OpenQueueEntry_t* msg, ieee802154_header_iht* ieee802514_header, uint16_t* rztime);
void    ieee802154_createWakeUpFrame(OpenQueueEntry_t* msg, uint8_t sequenceNumber, open_addr_t* nextHop, uint16_t rztime);


//======================================================================
//========================== INITIALIZATION ============================
//======================================================================

/**
  \brief This function initializes this module.

  Call this function once before any other function in this module, possibly during boot-up.
*/
// [CSL]: Modificaciones sobre método inicial referidas a los temporizadores y al estado inicial.
void ieee154e_init() {
   
   // initialize variables
   memset(&ieee154e_vars,0,sizeof(ieee154e_vars_t));
   memset(&ieee154e_dbg,0,sizeof(ieee154e_dbg_t));
   
   if (idmanager_getIsDAGroot()==TRUE) {
      changeIsSync(TRUE);
   } else {
      changeIsSync(FALSE);
   }
   
   resetStats();
   ieee154e_stats.numDeSync                 = 0;
   
   // [CSL]: update CSL Mode to SLEEP in order to allow RX o TX.
   ieee154e_vars.cslMode = CSL_SLEEP_MODE;
   // [CSL]: Set initial DSN counter for wake-up sequence frames.
   ieee154e_vars.cslDSN	 = 0;

   // switch radio on - Does this function really do anything?. Its contents are commented...
   radio_rfOn();
   
   // set callback functions for the radio
   radio_setOverflowCb(isr_ieee154ecsl_newChannelSample); // CSL - Fires every macCSLPeriod for sampling.
   radio_setCompareCb(isr_ieee154ecsl_timer);             // CSL - Fires for FSM state changing.
   radio_setStartFrameCb(ieee154ecsl_startOfFrame);       // CSL – Fires on start of frame detected on radio
   radio_setEndFrameCb(ieee154ecsl_endOfFrame);           // CSL – Fires on end of frame detected on radio

   // [CSL]: set timer for checking frames on local queue to transmit.
   ieee154e_vars.txTimer = opentimers_start(macCSLTxChkFreq, TIMER_PERIODIC, TIME_TICS, isr_ieee154ecsl_txtimer_cb);

   // [CSL-TEST]: set timer for callback to add packet to queue for testing CSL TX (every 5 seconds)
   ieee154e_vars.cslTxTestTimer = opentimers_start(2000, TIMER_PERIODIC, TIME_MS, isr_ieee154ecsl_addPacketToQueueForTestingCslTx_cb);

   // [CSL]: have the radio start its timer for channel sampling (macCSLPeriod)
   radio_startTimer(macCSLPeriod);
}

//=========================== public ==========================================

//======================================================================
//======================  EVENTS & CALLBACKS ===========================
//======================================================================

/**
\brief Indicates a new CSL Channel Sample has just started.

This function executes in ISR mode, when the new CSÑ Channel Sample timer fires.
*/
// [CSL]: Callback indicating the start of a new CSL channel sample.
void isr_ieee154ecsl_newChannelSample() {
   // Establish the new timer for the next channel sample
   radio_setTimerPeriod(macCSLPeriod);

   // Verificamos que no estamos ya en un proceso de TX o RX previo.
   if(ieee154e_vars.cslMode == CSL_SLEEP_MODE) {
	  // We call the first activity on FSM for channel sampling (CSL FSM RX mode)
	  activity_csl_wakeup_ri1();
   } else {
	  // log the info about a operation in progress
	  openserial_printInfo(COMPONENT_IEEE802154E,ERR_MAC_OPERATION_IN_PROGRESS,
						  (errorparameter_t)ieee154e_vars.cslMode, (errorparameter_t)ieee154e_dbg.num_cslSamples);
   }

   // Increment the number of cslSamples.
   ieee154e_dbg.num_cslSamples++;
}

/**
\brief Indicates the FSM timer has fired.

This function executes in ISR mode, when the FSM timer fires.
*/
// [CSL]: Callback to select the next FSM action.
void isr_ieee154ecsl_timer() {
   if (ieee154e_vars.cslMode == CSL_RX_MODE)  { // Current CSL operation mode is channel sampling and possible frame RX.
	   switch (ieee154e_vars.state) {
	      // RX-MODE
		  case S_CSLRXWAKEUPOFFSET:      activity_csl_wakeup_ri2();  break;
		  case S_CSLRXWAKEUPPREPARE:     activity_csl_wakeup_rie1(); break;
		  case S_CSLRXWAKEUPREADY:       activity_csl_wakeup_ri3();  break;
		  case S_CSLRXWAKEUPLISTEN:      activity_csl_wakeup_rie2(); break;
		  case S_CSLRXWAKEUP:			 activity_csl_wakeup_rie3(); break;
		  case S_CSLRXWAKEUPVALIDATE: 	 activity_csl_wakeup_rie4(); break;

		  case S_CSLRXDATAOFFSET:    	 activity_csl_data_ri2();    break;
		  case S_CSLRXDATAPREPARE:       activity_csl_data_rie1();   break;
		  case S_CSLRXDATAREADY:         activity_csl_data_ri3();    break;
		  case S_CSLRXDATALISTEN:        activity_csl_data_rie2();   break;
		  case S_CSLRXDATA:			     activity_csl_data_rie3();   break;

		  case S_CSLTXACKOFFSET: 	     activity_csl_data_ri6();    break;
		  case S_CSLTXACKPREPARE:        activity_csl_data_rie4();   break;
		  case S_CSLTXACKREADY:          activity_csl_data_ri7();    break;
		  case S_CSLTXACKDELAY:          activity_csl_data_rie5();   break;
		  case S_CSLTXACK:               activity_csl_data_rie6();   break;
		  default:
			 // log the error
			 openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_CSL_TIMERFIRES,
								   (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_dbg.num_cslSamples);
			 // abort
			 endOps();
			 break;
	   }
   } else if (ieee154e_vars.cslMode == CSL_TX_MODE)  { // Current CSL operation mode is frame TX.
	   switch (ieee154e_vars.state) {
	      // TX-MODE
	      case S_CSLTXWAKEUPOFFSET:		 activity_csl_wakeup_ti2();  break;
	      case S_CSLTXWAKEUPPREPARE:	 activity_csl_wakeup_tie1(); break;
	      case S_CSLTXWAKEUPREADY:	     activity_csl_wakeup_ti3();  break;
	      case S_CSLTXWAKEUPDELAY:	     activity_csl_wakeup_tie2(); break;
	      case S_CSLTXWAKEUP: 	         activity_csl_wakeup_tie3(); break;

	      case S_CSLTXDATAPREOFFSET:	 activity_csl_data_ti1();	 break;
	      case S_CSLTXDATAOFFSET:        activity_csl_data_ti2();    break;
	      case S_CSLTXDATAPREPARE:	     activity_csl_data_tie1(); 	 break;
	      case S_CSLTXDATAREADY:	     activity_csl_data_ti3(); 	 break;
	      case S_CSLTXDATADELAY:	     activity_csl_data_tie2(); 	 break;
	      case S_CSLTXDATA: 	         activity_csl_data_tie3();	 break;

	      case S_CSLRXACKOFFSET: 	     activity_csl_data_ti6();	 break;
	      case S_CSLRXACKPREPARE:	     activity_csl_data_tie4(); 	 break;
	      case S_CSLRXACKREADY: 	     activity_csl_data_ti7(); 	 break;
	      case S_CSLRXACKLISTEN: 	     activity_csl_data_tie5(); 	 break;
	      case S_CSLRXACK:     	         activity_csl_data_tie6(); 	 break;

		  default:
			 // log the error
			 openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_CSL_TIMERFIRES,
								   (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_dbg.num_cslSamples);
			 // abort
			 endOps();
			 break;
	   }
   }
   ieee154e_dbg.num_timer++;
}

// [CSL] – Callback fired after receive a start of frame on radio.
void ieee154ecsl_startOfFrame(PORT_RADIOTIMER_WIDTH capturedTime) {
	if(ieee154e_vars.cslMode == CSL_RX_MODE)  { // Current CSL operation mode is channel sampling and possible frame RX.
	   switch (ieee154e_vars.state) {
		  // RX MODE
          /*
		   It is possible to receive in this state for radio where there is no way of differentiated between "ready to listen" and "listening"
		   (e.g. CC2420). We must therefore expect to the start of a packet in this "ready" state.
		  */
		  case S_CSLRXWAKEUP:    			 // no break!
		  case S_CSLRXWAKEUPLISTEN:	 	     activity_csl_wakeup_ri4(capturedTime); break;

		  case S_CSLRXDATAREADY:		     // no break!
		  case S_CSLRXDATALISTEN:            activity_csl_data_ri4(capturedTime);   break;

		  case S_CSLTXACKDELAY:              activity_csl_data_ri8(capturedTime);   break;
		  default:
			// log the error
			//openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_CSL_SAMPLE,
			//					  (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_dbg.num_cslSamples);
			// abort
			endOps();
			break;
		}
	} else if (ieee154e_vars.cslMode == CSL_TX_MODE)  { // Current CSL operation mode is frame TX.
	   switch (ieee154e_vars.state) {
		  // TX MODE

          /*
          It is possible to receive in this state for radio where there is no way of differentiated between "ready to listen" and "listening"
          (e.g. CC2420). We must therefore expect to the start of a packet in this "ready" state.
          */
	      case S_CSLRXACKREADY:               // no break!
	      case S_CSLRXACKLISTEN:              activity_csl_data_ti8(capturedTime);  break;

	      case S_CSLTXWAKEUPDELAY:            activity_csl_wakeup_ti4(capturedTime); break;
	      case S_CSLTXDATADELAY:              activity_csl_data_ti4(capturedTime);   break;

          default:
   			// log the error
   			openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_CSL_SAMPLE,
   								  (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_dbg.num_cslSamples);
   			// abort
   			endOps();
   			break;
   		}
	}
  ieee154e_dbg.num_startOfFrame++;
}

// [CSL] – Callback fired after receive a end of frame on radio.
void ieee154ecsl_endOfFrame(PORT_RADIOTIMER_WIDTH capturedTime) {
	if(ieee154e_vars.cslMode == CSL_RX_MODE)  { // Current CSL operation mode is channel sampling and possible frame RX.
	   switch (ieee154e_vars.state) {
		 // RX MODE
		 case S_CSLRXWAKEUP:           activity_csl_wakeup_ri5(capturedTime);  break;
		 case S_CSLRXDATA:             activity_csl_data_ri5(capturedTime);    break;
		 case S_CSLTXACK:              activity_csl_data_ri9(capturedTime);    break;
		 default:
			// log the error
			openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_CSL_ENDOFFRAME,
								  (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_dbg.num_cslSamples);
			// abort
			endOps();
			break;
	   }
	} else if (ieee154e_vars.cslMode == CSL_TX_MODE)  { // Current CSL operation mode is frame TX.
	  switch (ieee154e_vars.state) {
        // TX MODE
	    case S_CSLTXWAKEUP:            activity_csl_wakeup_ti5(capturedTime); break;
        case S_CSLTXDATA:              activity_csl_data_ti5(capturedTime);   break;
	    case S_CSLRXACK:               activity_csl_data_ti9(capturedTime);   break;
	    default:
           // log the error
		   openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_CSL_ENDOFFRAME,
			   				    (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_dbg.num_cslSamples);
    	   // abort
		   endOps();
		   break;
	  }
	}
   ieee154e_dbg.num_endOfFrame++;
}

// tx timer interrupt callbacks

// [CSL]: Callback to check pending data to be sent.
void isr_ieee154ecsl_txtimer_cb() {

	// Verificamos que no estamos ya en un proceso de TX o RX previo.
   if(ieee154e_vars.cslMode == CSL_SLEEP_MODE) {
	  // We call the first activity on FSM for channel sampling (CSL FSM RX mode)
      activity_csl_wakeup_ti1();
   }
   else {
	  // log the info about a operation in progress
	  openserial_printInfo(COMPONENT_IEEE802154E,ERR_MAC_OPERATION_IN_PROGRESS,
						  (errorparameter_t)ieee154e_vars.cslMode, (errorparameter_t)ieee154e_dbg.num_cslSamples);
   }
}

// [CST-TEST]: test timer interrupt callback to put a new packet on queue for testing CSL TX mode.

void isr_ieee154ecsl_addPacketToQueueForTestingCslTx_cb () {

  OpenQueueEntry_t* pkt;
  open_addr_t neighbor;

  // Simulate a ficticious address for CSL testing.
  neighbor.addr_64b[0]=0x00;
  neighbor.addr_64b[1]=0x11;
  neighbor.addr_64b[2]=0x22;
  neighbor.addr_64b[3]=0x33;
  neighbor.addr_64b[4]=0x44;
  neighbor.addr_64b[5]=0x55;
  neighbor.addr_64b[6]=0x66;
  neighbor.addr_64b[7]=0x77;

  neighbor.type=ADDR_64B;

  // Switch off all the leds.
  leds_all_off();

  // CREATE DATA PACKET ONLY IF NOT ALREADY EXISTS ON QUEUE.

  if (openqueue_macGetDataPacket(&neighbor) == NULL) {

	  // get freebuffer.
	  pkt = openqueue_getFreePacketBuffer(COMPONENT_IEEE802154E);
	  if(pkt==NULL) {
		// registro del error & fin de operaciones.
		openserial_printError(COMPONENT_IEEE802154E,ERR_NO_FREE_PACKET_BUFFER, (errorparameter_t)0, (errorparameter_t)0);
		endOps();
		return;
	  }

	  // Declaración de propiedad sobre el paquete.
	  pkt->creator = COMPONENT_SIXTOP_TO_IEEE802154E;
	  pkt->owner   = COMPONENT_SIXTOP_TO_IEEE802154E;

	  // Frame type (data frame).
	  pkt->l2_frameType=IEEE154_TYPE_DATA;

	  // Neighbor address.
	  memcpy(&(pkt->l2_nextORpreviousHop),&neighbor,sizeof(open_addr_t));

	  // TX retries
	  pkt->l2_retriesLeft = TXRETRIES;

	  // record this packet's dsn (for matching the ACK)
	  pkt->l2_dsn = ieee154e_vars.cslDSN++;

	  // this is a new packet which I never attempted to send
	  pkt->l2_numTxAttempts = 0;

	  // transmit with the default TX power
	  pkt->l1_txPower = TX_POWER;

	  // add a IEEE802.15.4 header
	  ieee802154_prependHeader(pkt,
							   pkt->l2_frameType,
							   IEEE154_IELIST_NO,
							   IEEE154_FRAMEVERSION,
							   IEEE154_SEC_NO_SECURITY,
							   pkt->l2_dsn,
							   &(pkt->l2_nextORpreviousHop)
							   );

	  // reserve space for 2-byte CRC
	  packetfunctions_reserveFooterSize(pkt,2);
  }

  return;
}


//======================================================================
//========================== CSL TX MODE ===============================
//======================================================================

/**
 \brief Activity for CSL TX stage [wake-up ti1].

 This method is invoked in ISR-mode from "isr_ieee154ecsl_txtimer_cb" function when TX Timer is fired (every "macCSLTxChkFreq" time).

*/
port_INLINE void activity_csl_wakeup_ti1() {
	   cellType_t  cellType;
	   open_addr_t neighbor;

	   // update CSL Mode to TX in order to avoid problems in FSM.
	   ieee154e_vars.cslMode = CSL_TX_MODE;

	   // Las acciones que realizaremos son las siguientes:
	   //  - Avanzar el schedule para posicionar la siguiente posición en éste, el cual marcará la dirección a quien enviar.
	   //  - Verificar el estado actual dentro de la FSM para comprobar que efectivamente nos encontramos en un estado SLEEP.
	   //  - Si no hay problema en ambos, verificamos el tipo de slot en el schedule y preparamos un paquete para enviar al
	   //    destino asociado a dicho slot.

	   // increment ASN (do this first so debug pins are in sync)
	   incrementAsnOffset();

	   // wiggle debug pins
	   debugpins_slot_toggle();
	   if (ieee154e_vars.slotOffset==0) {
	      debugpins_frame_toggle();
	   }

       // if the previous slot took too long, we will not be in the right state
	   if (ieee154e_vars.state!=S_SLEEP) {
	      // log the error
	      openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_STARTSLOT,
	                            (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_dbg.num_cslSamples);
	      // abort
	      endOps();
	      return;
	   }

	   // advance the schedule
       schedule_advanceSlot();

       // stop using serial
       openserial_stop();

       // check the schedule to see what type of slot this is
       cellType = schedule_getType();

       // check whether we can send
	   if (schedule_getOkToSend()) {
	       schedule_getNeighbor(&neighbor);
	       ieee154e_vars.dataToSend = openqueue_macGetDataPacket(&neighbor);
	   } else {
	       ieee154e_vars.dataToSend = NULL;
	   }
	   if((ieee154e_vars.dataToSend!=NULL) && (cellType == CELLTYPE_TX)) {   // If I have a packet to send and slot is TX, then we start FSM TX mode.
	       // change state to start sending CSL preamble before send the data packet.
	       changeState(S_CSLTXWAKEUPOFFSET);

           // record that I will attempt to transmit this packet
	       ieee154e_vars.dataToSend->l2_numTxAttempts++;

	       // arm tt1
	       radiotimer_schedule(DURATION_tt1);
	   } else {
	       // abort because slot is not TX or there is no data to send, so we reset TX Mode state
		   ieee154e_vars.cslMode = CSL_SLEEP_MODE;
	   }
}


/**
 \brief Activity for CSL TX stage [wake-up ti2].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt1") while state = S_CSLTXWAKEUPOFFSET.
  The functionality is to prepare the radio for sending packets.
*/
port_INLINE void activity_csl_wakeup_ti2() {

   open_addr_t neighbor;

   // El tiempo de rendezvous que será necesario esperar será macCSLMaxPeriod al tratarse de
   // una comunicación en modo TX no sincronizado.

   // Calculamos el valor del rz-time en cada trama wake-up de la secuencia dado que debe ir reduciéndose para notificar
   // al extemo remoto el tiempo restante hasta el envío de la trama de datos.

   // El tiempo lastCapturedTime se ve incrementado tras el envio de cada trama wake-up por lo que cada vez tendrá un
   // valor más proximo al macCSLMaxPeriod.

   ieee154e_vars.remainingRzTime = macCSLMaxPeriod - ieee154e_vars.lastCapturedTime;

   if (MaxWakeUpTxTime < ieee154e_vars.remainingRzTime) { // Si da tiempo a enviar una nueva trama de wake-up antes de la finalización del ciclo...

	   // change state
	   changeState(S_CSLTXWAKEUPPREPARE);

	   //
	   // Construimos el paquete Wake-Up con su valor RZTime asociado en caso de no existir ya.
	   //

	   if (ieee154e_vars.wakeupToSend == NULL) { // first time

		   // obtenemos un buffer en el cual poder guardar los datos recibidos.
		   ieee154e_vars.wakeupToSend = openqueue_getFreePacketBuffer(COMPONENT_IEEE802154E);
		   if (ieee154e_vars.wakeupToSend == NULL) {
			  // registro del error & fin de operaciones.
			  openserial_printError(COMPONENT_IEEE802154E,ERR_NO_FREE_PACKET_BUFFER, (errorparameter_t)0, (errorparameter_t)0);
			  endOps();
			  return;
		   }

		   // Declaración de propiedad sobre el paquete.
		   ieee154e_vars.wakeupToSend->creator = COMPONENT_IEEE802154E;
		   ieee154e_vars.wakeupToSend->owner   = COMPONENT_IEEE802154E;

		   // El tipo de trama es Multipurpose.
		   ieee154e_vars.wakeupToSend->l2_frameType = IEEE154_TYPE_MULTIPURPOSE;

		   // El dsn del paquete lo obtenemos a partir del actual DSN incrementado en cada paquete de la secuencia wake-up.
		   ieee154e_vars.wakeupToSend->l2_dsn = ieee154e_vars.cslDSN++;

		   // El destinatario es el mismo que el destinatario del mensaje de datos indicado en el schedule.
		   schedule_getNeighbor(&neighbor);

		   // Verificamos que se trata de una dirección corta (short address). En caso contrario generamos un mensaje de advertencia.
		   if(neighbor.type != ADDR_16B) {
			   // CSL: This is an invalid address because address in wake-up frame must be short address.
			   // We do not finish operations but we will use later short address getting it from long address.
			   openserial_printInfo(COMPONENT_IEEE802154,ERR_IEEE154_UNSUPPORTED, (errorparameter_t)1, (errorparameter_t)(neighbor.type));
		   }

		   // create frame header.
		   ieee802154_createWakeUpFrame(ieee154e_vars.wakeupToSend,
										ieee154e_vars.wakeupToSend->l2_dsn,
										&neighbor,
										ieee154e_vars.remainingRzTime);

		   // space for 2-byte CRC
		   packetfunctions_reserveFooterSize(ieee154e_vars.wakeupToSend,2);
	   }
	   else {
		   // update rztime in header.
		   // Se posiciona 8 posiciones antes dado que estamos escribiendo el paquete de atras hacia delante y antes tenemos:
		   // - 1 byte FCF
		   // - 1 byte SEQ
		   // - 2 bytes PANID
		   // - 2 bytes DEST ADDR
		   // - 2 bytes RZTIME IE HEADER
		   // - 2 bytes RZTIME (el cual se sobrescribirá con el nuevo valor).
		   *((uint16_t*)(ieee154e_vars.wakeupToSend->payload+8)) = ieee154e_vars.remainingRzTime;
	   }

	   // load the packet in the radio's Tx buffer
	   radio_loadPacket(ieee154e_vars.wakeupToSend->payload, ieee154e_vars.wakeupToSend->length);

	   // enable the radio in Tx mode. This does not send the packet.
	   radio_txEnable();
	   ieee154e_vars.radioOnInit=radio_getTimerValue();
	   ieee154e_vars.radioOnThisSlot=TRUE;

	   // arm tt2
       radiotimer_schedule(DURATION_tt2);

	   // change state
	   changeState(S_CSLTXWAKEUPREADY);
   }
   else {
	   // Si no da tiempo a enviar una nueva trama, simplemente esperamos un tiempo igual a remainingRzTime que será
	   // el tiempo que queda pendiente hasta el envío de la trama de datos y actualizamos directamente el estado para
	   // pasar a la transmisión de los datos, a través del estado CSLTXDATAPREOFFSET.

	   // change state
	   changeState(S_CSLTXDATAPREOFFSET);

	   // arm remaining rendezvous time.
	   radiotimer_schedule(ieee154e_vars.remainingRzTime);
   }
}

/**
 \brief Activity for CSL TX stage [wake-up tie1].

  This is triggered by #tt2 expiring, i.e. timer fires while state = S_CSLTXWAKEUPPREPARE. This is really an error state which indicates that #ti2
  did not have enough time to execute. Chances are to set maxTxDataPrepare too small. The implemented behaviour is to log the error and finish.
*/
port_INLINE void activity_csl_wakeup_tie1() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_MAXTXDATAPREPARE_OVERFLOW,
                         (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_vars.slotOffset);

   // abort
   endOps();
}

/**
 \brief Activity for CSL TX stage [wake-up ti3].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt2") while state = S_CSLTXWAKEUPREADY.
  The radio is configured and this interrupt gives it the "go" signal to start listening.
*/

port_INLINE void activity_csl_wakeup_ti3() {
   // change state
   changeState(S_CSLTXWAKEUPDELAY);

   // arm tt3
   radiotimer_schedule(DURATION_tt3);

   // give the 'go' to transmit
   radio_txNow();
}

/**
 \brief Activity for CSL TX stage [wakeup tie2].

  This is triggered by #tt3 expiring, i.e. timer fires while state = S_CSLTXWAKEUPDELAY. If no packet is sent by this time, this timer expires.
*/
port_INLINE void activity_csl_wakeup_tie2() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDRADIO_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_vars.slotOffset);
   // abort
   endOps();
}

/**
 \brief Activity for CSL TX stage [wake-up ti4].

  This method is invoked from ISR-mode "ieee154ecsl_startOfFrame" function when a start of frame event fires while state = S_CSLRXWAKEUPDELAY.
  The functionality is to capture the time, cancel #tt3 and arm #tt4 (max time to send all the packet).
*/
port_INLINE void activity_csl_wakeup_ti4(PORT_RADIOTIMER_WIDTH capturedTime) {

   // cancel tt3
   radiotimer_cancel();

   // record the captured time
   ieee154e_vars.lastCapturedTime = capturedTime;

   // change state
   changeState(S_CSLTXWAKEUP);

   // arm tt4
   radiotimer_schedule(DURATION_tt4);
}

/**
 \brief Activity for CSL TX stage [wake-up tie3].

  This is triggered by #tt4 expiring, i.e. timer fires while state = S_CSLTXWAKEUP. This is an error state which indicates the radio
  took too long to transmit the data packet. The implemented behaviour is to log the error and finish.
*/
port_INLINE void activity_csl_wakeup_tie3() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDDATADURATION_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_vars.slotOffset);
   // abort
   endOps();
}


/**
 \brief Activity for CSL RX Sampling stage [wake-up ri5].

  This method is invoked from ISR-mode "ieee154ecsl_endOfFrame" function when a end of frame event fires while state = S_CSLTXWAKEUP.
  The functionality is to change state, cancel #rt4, and start sending data frame and wait for ACK.
*/
port_INLINE void activity_csl_wakeup_ti5(PORT_RADIOTIMER_WIDTH capturedTime) {

	// record the captured time
	ieee154e_vars.lastCapturedTime = capturedTime;

	// Mientras el tiempo capturado en el envío de la ultima trama wake-up de la trama wake-up sequence
	// sea inferior al tiempo de la duración del rztime inicial, debemos seguir enviando tramas wake-up.
	// En caso contrario, enviamos la trama de datos.

	//if((macCSLMaxPeriod - ieee154e_vars.lastCapturedTime) < ieee154e_vars.remainingRzTime) {
	//	changeState(S_CSLTXWAKEUPOFFSET);
	//}
	//else {
    //   changeState(S_CSLTXDATAOFFSET);
    //}

	changeState(S_CSLTXWAKEUPOFFSET);

    // arm tt1 (enviemos de nuevo una trama de wake-up o de datos, el tiempo será tt1).
    radiotimer_schedule(DURATION_tt1);
}

/**
 \brief Activity for CSL TX stage [data ti1].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires after expire remainingRzTime while state = S_CSLTXWAKEUPVALIDATE.
  The functionality is to prepare the data to be sent.
*/

port_INLINE void activity_csl_data_ti1() {

	// change state
	changeState(S_CSLTXDATAOFFSET);

    // arm tt1 (enviemos de nuevo una trama de wake-up o de datos, el tiempo será tt1).
    radiotimer_schedule(DURATION_tt1);
}



/**
 \brief Activity for CSL TX stage [data ti2].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt1") while state = S_CSLTXDATAOFFSET.
  The functionality is to prepare the radio for sending packets.
*/
port_INLINE void activity_csl_data_ti2() {
   // change state
   changeState(S_CSLTXDATAPREPARE);

   // load the packet in the radio's Tx buffer
   radio_loadPacket(ieee154e_vars.dataToSend->payload,
                    ieee154e_vars.dataToSend->length);

   // enable the radio in Tx mode. This does not send the packet.
   radio_txEnable();
   ieee154e_vars.radioOnInit=radio_getTimerValue();
   ieee154e_vars.radioOnThisSlot=TRUE;

   // arm tt2
   radiotimer_schedule(DURATION_tt2);

   // change state
   changeState(S_CSLTXDATAREADY);

}

/**
 \brief Activity for CSL TX stage [data tie1].

  This is triggered by #tt2 expiring, i.e. timer fires while state = S_CSLTXDATAPREPARE. This is really an error state which indicates that #ti2
  did not have enough time to execute. Chances are to set maxTxDataPrepare too small. The implemented behaviour is to log the error and finish.
*/
port_INLINE void activity_csl_data_tie1() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_MAXTXDATAPREPARE_OVERFLOW,
                         (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_vars.slotOffset);
   // abort
   endOps();
}

/**
 \brief Activity for CSL TX stage [data ti3].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt2") while state = S_CSLTXDATAREADY.
  The radio is configured and this interrupt gives it the "go" signal to start listening.
*/
port_INLINE void activity_csl_data_ti3() {
   // change state
   changeState(S_CSLTXDATADELAY);

   // arm tt3
   radiotimer_schedule(DURATION_tt3);

   // give the 'go' to transmit
   radio_txNow();
}


/**
 \brief Activity for CSL TX Sampling error [data tie2].

  This is triggered by #tt3 expiring, i.e. timer fires while state = S_CSLTXDATADELAY. If no packet is received by the time, this timer expires, then
  none will be sent and it is safe to switch off the radio. This timer is set such that the radio will be on during two consecutive windows of
  duration (#TsLongGT).
*/
port_INLINE void activity_csl_data_tie2() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDRADIO_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_vars.slotOffset);

   // abort
   endOps();
}


/**
 \brief Activity for CSL TX stage [data ti4].

  This method is invoked from ISR-mode "ieee154ecsl_startOfFrame" function when a start of frame event fires while state = S_CSLTXDATADELAY.
  The functionality is to change state, cancel #tt3 and arm #tt4 (max time to sent all the packet).
*/
port_INLINE void activity_csl_data_ti4(PORT_RADIOTIMER_WIDTH capturedTime) {
   // change state
   changeState(S_CSLTXDATA);

   // cancel tt3
   radiotimer_cancel();

   // record the captured time
   ieee154e_vars.lastCapturedTime = capturedTime;

   // arm tt4
   radiotimer_schedule(DURATION_tt4);
}

/**
 \brief Activity for CSL TX stage [data tie3].

  This is triggered by #tt4 expiring, i.e. timer fires while state = S_CSLTXDATA. This is an error state which indicates the radio took too long
  to transmit the data packet. The implemented behaviour is to log the error and finish.
*/
port_INLINE void activity_csl_data_tie3() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDDATADURATION_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_vars.slotOffset);
   // abort
   endOps();
}

/**
 \brief Activity for CSL TX stage [data ri5].

  This method is invoked from ISR-mode "ieee154ecsl_endOfFrame" function when a end of frame event fires while state = S_CSLTXDATA.
  The functionality is to change state, cancel #tt4, and notify upper layer and schedule about successful TX. In case ACK required,
  start process for receive ACK frame (arm #tt5).
*/
port_INLINE void activity_csl_data_ti5(PORT_RADIOTIMER_WIDTH capturedTime) {
   bool listenForAck;

   // change state
   changeState(S_CSLRXACKOFFSET);

   // cancel tt4
   radiotimer_cancel();

   // turn off the radio
   radio_rfOff();
   ieee154e_vars.radioOnTics+=(radio_getTimerValue()-ieee154e_vars.radioOnInit);

   // record the captured time
   //ieee154e_vars.lastCapturedTime = capturedTime;

   // decides whether to listen for an ACK
   if (packetfunctions_isBroadcastMulticast(&ieee154e_vars.dataToSend->l2_nextORpreviousHop)==TRUE) {
      listenForAck = FALSE;
   } else {
      listenForAck = TRUE;
   }

   // [CSL-TEST]: testing code for toggling orange led to indicate OK TX.

   if((ieee154e_vars.dataToSend->l2_frameType == IEEE154_TYPE_DATA) &&
	  (ieee154e_vars.dataToSend->owner == COMPONENT_SIXTOP_TO_IEEE802154E)) {
	 leds_sync_blink();
	 listenForAck = FALSE;
   }
   // [CSL-TEST]: end test code


   if (listenForAck==TRUE) {
      // arm tt5
      radiotimer_schedule(DURATION_tt5);
   } else {
      // indicate succesful Tx to schedule to keep statistics
      schedule_indicateTx(&ieee154e_vars.asn,TRUE);

      // [CSL-TEST]: comment notification

      // indicate to upper later the packet was sent successfully
      //notif_sendDone(ieee154e_vars.dataToSend,E_SUCCESS);

      // reset local variable
      //ieee154e_vars.dataToSend = NULL;

      // [CSL-TEST]: end test code

      // abort
      endOps();
   }
}

/**
 \brief Activity for CSL TX stage [data ti6].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt5") while state = S_CSLRXACKOFFSET.
   The functionality is to prepare the radio for ACK reception.
*/
port_INLINE void activity_csl_data_ti6() {
   // change state
   changeState(S_CSLRXACKPREPARE);

   // enable the radio in Rx mode. The radio is not actively listening yet.
   radio_rxEnable();

   //caputre init of radio for duty cycle calculation
   ieee154e_vars.radioOnInit=radio_getTimerValue();
   ieee154e_vars.radioOnThisSlot=TRUE;

   // arm tt6
   radiotimer_schedule(DURATION_tt6);

   // change state
   changeState(S_CSLRXACKREADY);
}

/**
 \brief Activity for CSL TX stage [data tie4].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt6") while state = S_CSLRXACKPREPARE.
   The functionality is to prepare the radio for ACK sending.
*/
port_INLINE void activity_csl_data_tie4() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_MAXRXACKPREPARE_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state, (errorparameter_t)ieee154e_vars.slotOffset);
   // abort
   endOps();
}

/**
 \brief Activity for CSL TX stage [data ti7].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt6") while state = S_CSLRXACKREADY.
  The radio is configured and this interrupt gives it the "go" signal to start listening.
*/
port_INLINE void activity_csl_data_ti7() {
   // change state
   changeState(S_CSLRXACKLISTEN);

   // start listening
   radio_rxNow();

   // arm tt7
   radiotimer_schedule(DURATION_tt7);
}

/**
 \brief Activity for CSL TX stage [data tie5].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_tt7") while state = S_CSLRXACKLISTEN.
  The functionality is to notify upper level, updating the number of remaining retries of the packet.
*/
port_INLINE void activity_csl_data_tie5() {
   // indicate transmit failed to schedule to keep stats
   schedule_indicateTx(&ieee154e_vars.asn,FALSE);

   // decrement transmits left counter
   ieee154e_vars.dataToSend->l2_retriesLeft--;

   if (ieee154e_vars.dataToSend->l2_retriesLeft==0) {
      // indicate tx fail if no more retries left
      notif_sendDone(ieee154e_vars.dataToSend,E_FAIL);
   } else {
      // return packet to the virtual COMPONENT_SIXTOP_TO_IEEE802154E component
      ieee154e_vars.dataToSend->owner = COMPONENT_SIXTOP_TO_IEEE802154E;
   }

   // reset local variable
   ieee154e_vars.dataToSend = NULL;

   // abort
   endOps();
}

/**
 \brief Activity for CSL TX stage [data ti8].

  This method is invoked from ISR-mode "ieee154ecsl_startOfFrame" function when a start of frame event fires while state = S_CSLRXACKLISTEN.
  The functionality is to change the state, cancel #tt7 and arm #tt8 (max time to receive the ack packet).
*/
port_INLINE void activity_csl_data_ti8(PORT_RADIOTIMER_WIDTH capturedTime) {
   // change state
   changeState(S_CSLRXACK);

   // cancel tt7
   radiotimer_cancel();

   // record the captured time
   //ieee154e_vars.lastCapturedTime = capturedTime;

   // arm tt8
   radiotimer_schedule(DURATION_tt8);
}

/**
 \brief Activity for CSL TX stage [data tie6].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt8") while state = S_CSLRXACK.
  The functionality is to finish and clean registers.
*/
port_INLINE void activity_csl_data_tie6() {
   // abort
   endOps();
}


/**
 \brief Activity for CSL TX stage [data ti9].

  This method is invoked from ISR-mode "ieee154ecsl_endOfFrame" function when a end of frame event fires while state = S_CSLRXACK.
  The functionality is to change the state, cancel #tt8, analyze ack packet and notify upper layer.
*/
port_INLINE void activity_csl_data_ti9(PORT_RADIOTIMER_WIDTH capturedTime) {
   ieee802154_header_iht     ieee802514_header;
   uint16_t                  lenIE;

   // change state
   changeState(S_CSLTXPROC);

   // cancel tt8
   radiotimer_cancel();

   // turn off the radio
   radio_rfOff();
   //compute tics radio on.
   ieee154e_vars.radioOnTics+=(radio_getTimerValue()-ieee154e_vars.radioOnInit);

   // record the captured time
   //ieee154e_vars.lastCapturedTime = capturedTime;

   // get a buffer to put the (received) ACK in
   ieee154e_vars.ackReceived = openqueue_getFreePacketBuffer(COMPONENT_IEEE802154E);
   if (ieee154e_vars.ackReceived==NULL) {
      // log the error
      openserial_printError(COMPONENT_IEEE802154E,ERR_NO_FREE_PACKET_BUFFER,
                            (errorparameter_t)0,
                            (errorparameter_t)0);
      // abort
      endOps();
      return;
   }

   // declare ownership over that packet
   ieee154e_vars.ackReceived->creator = COMPONENT_IEEE802154E;
   ieee154e_vars.ackReceived->owner   = COMPONENT_IEEE802154E;

   /*
   The do-while loop that follows is a little parsing trick.
   Because it contains a while(0) condition, it gets executed only once.
   Below the do-while loop is some code to cleans up the ack variable.
   Anywhere in the do-while loop, a break statement can be called to jump to
   the clean up code early. If the loop ends without a break, the received
   packet was correct. If it got aborted early (through a break), the packet
   was faulty.
   */

   do { // this "loop" is only executed once

      // retrieve the received ack frame from the radio's Rx buffer
      ieee154e_vars.ackReceived->payload = &(ieee154e_vars.ackReceived->packet[FIRST_FRAME_BYTE]);
      radio_getReceivedFrame(       ieee154e_vars.ackReceived->payload,
                                   &ieee154e_vars.ackReceived->length,
                             sizeof(ieee154e_vars.ackReceived->packet),
                                   &ieee154e_vars.ackReceived->l1_rssi,
                                   &ieee154e_vars.ackReceived->l1_lqi,
                                   &ieee154e_vars.ackReceived->l1_crc);

      // break if wrong length
      if (ieee154e_vars.ackReceived->length<LENGTH_CRC || ieee154e_vars.ackReceived->length>LENGTH_IEEE154_MAX) {
         // break from the do-while loop and execute the clean-up code below
        openserial_printError(COMPONENT_IEEE802154E,ERR_INVALIDPACKETFROMRADIO,
                            (errorparameter_t)1,
                            ieee154e_vars.ackReceived->length);

         break;
      }

      // toss CRC (2 last bytes)
      packetfunctions_tossFooter(   ieee154e_vars.ackReceived, LENGTH_CRC);

      // break if invalid CRC
      if (ieee154e_vars.ackReceived->l1_crc==FALSE) {
         // break from the do-while loop and execute the clean-up code below
         break;
      }

      // parse the IEEE802.15.4 header (RX ACK)
      ieee802154_retrieveHeader(ieee154e_vars.ackReceived,&ieee802514_header);

      // break if invalid IEEE802.15.4 header
      if (ieee802514_header.valid==FALSE) {
         // break from the do-while loop and execute the clean-up code below
         break;
      }

      // store header details in packet buffer
      ieee154e_vars.ackReceived->l2_frameType  = ieee802514_header.frameType;
      ieee154e_vars.ackReceived->l2_dsn        = ieee802514_header.dsn;
      memcpy(&(ieee154e_vars.ackReceived->l2_nextORpreviousHop),&(ieee802514_header.src),sizeof(open_addr_t));

      // toss the IEEE802.15.4 header
      packetfunctions_tossHeader(ieee154e_vars.ackReceived,ieee802514_header.headerLength);

      // break if invalid ACK
      if (isValidAck(&ieee802514_header,ieee154e_vars.dataToSend)==FALSE) {
         // break from the do-while loop and execute the clean-up code below
         break;
      }
      //hanlde IEs --xv poipoi
      if (ieee802514_header.ieListPresent==FALSE){
         break; //ack should contain IEs.
      }

      if (ieee154e_processIEs(ieee154e_vars.ackReceived,&lenIE)==FALSE){
        // invalid IEs in ACK
        break;
      }

      // toss the IEs
      packetfunctions_tossHeader(ieee154e_vars.ackReceived,lenIE);

      // inform schedule of successful transmission
      schedule_indicateTx(&ieee154e_vars.asn,TRUE);

      // inform upper layer
      notif_sendDone(ieee154e_vars.dataToSend,E_SUCCESS);

      ieee154e_vars.dataToSend = NULL;

      // in any case, execute the clean-up code below (processing of ACK done)
   } while (0);

   // free the received ack so corresponding RAM memory can be recycled
   openqueue_freePacketBuffer(ieee154e_vars.ackReceived);

   // clear local variable
   ieee154e_vars.ackReceived = NULL;

   // official end of Tx
   endOps();
}

//======================================================================
//========================== CSL RX MODE ===============================
//======================================================================


/**
 \brief Activity for CSL RX Sampling stage [wake-up ri1].

 This method is invoked in ISR-mode from "isr_ieee154ecsl_newChannelSample" function when a new CSL Channel Sample is fired (every "macCSLPeriod" time).
 
 \note The FSM state should be S_SLEEP (initial state), raising an error in otherwise.
*/
port_INLINE void activity_csl_wakeup_ri1() { // Activity for stage [ri1] on CSL RX Sampling.

	   // if the previous sample took too long or the state is incorrect, we will not be in the right state.
	   // we register an error indicating the number of CSL sample where the problem have been detected since sampling startup.
	   if (ieee154e_vars.state!=S_SLEEP) {
		  // log the error
		  openserial_printError(COMPONENT_IEEE802154E,ERR_WRONG_STATE_IN_START_CSL_SAMPLING,
								(errorparameter_t)ieee154e_vars.state,
								(errorparameter_t)ieee154e_dbg.num_cslSamples);

		  // Abort in case of error. The signature of the function has been changed (instead of endSlot()) in order to be more representative to its
		  // functionality. However, this function is equal for CSL and not-CSL.
		  endOps();
		  return;
	   }

	   // stop using serial
	   openserial_stop();

	   // change state --> Next State will be S_CSLRXWAKEUPOFFSET in order to prepare for CSL Rx wake-up.
	   changeState(S_CSLRXWAKEUPOFFSET);

	   // update CSL Mode to RX in order to avoid problems in FSM.
	   ieee154e_vars.cslMode = CSL_RX_MODE;

	   // arm rt1
	   radiotimer_schedule(DURATION_rt1);
}


/**
 \brief Activity for CSL RX Sampling stage [wake-up ri2].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt1") while state = S_CSLRXWAKEUPOFFSET.
  The functionality is to prepare the radio for receiving packets.
*/
port_INLINE void activity_csl_wakeup_ri2() { // Activity for stage [ri2] on CSL RX Sampling.
   // change state
   changeState(S_CSLRXWAKEUPPREPARE);

   // We use always the same frequency so it is not necessary to change it on radio.
   // Enable the radio in Rx mode. The radio does not actively listen yet.
   radio_rxEnable();
   ieee154e_vars.radioOnInit=radio_getTimerValue();
   ieee154e_vars.radioOnThisSlot=TRUE;

   // arm rt2
   radiotimer_schedule(DURATION_rt2);

   // Change state.
   // If this action is not performed before rt2 has expired, we need to manage the error in activity_csl_rie1. This means that radio
   // prepare has exceeded the maximum allowed time (duration_rt2).
   changeState(S_CSLRXWAKEUPREADY);
}


/**
 \brief Activity for CSL RX Sampling error [wake-up rie1].

  This is triggered by #rt2 expiring, i.e. timer fires while state = S_CSLRXWAKEUPPREPARE. This is really an error state which indicates that #ri2
  did not have enough time to execute. Chances are to set maxRxDataPrepare too small. The implemented behaviour is to log the error and move on the
  next CSL sample.
*/
port_INLINE void activity_csl_wakeup_rie1() {  // Activity for error event [rie1] on CSL RX Sampling.
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_MAXRXWAKEUPPREPARE_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state,
                         (errorparameter_t)ieee154e_dbg.num_cslSamples);
   // abort
   endOps();
}


/**
 \brief Activity for CSL RX Sampling stage [wake-up ri3].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt2") while state = S_CSLRXWAKEUPREADY.
  The radio is configured and this interrupt gives it the "go" signal to start listening.
*/
port_INLINE void activity_csl_wakeup_ri3() { // Activity for stage [ri3] on CSL RX Sampling.
   // change state
   changeState(S_CSLRXWAKEUPLISTEN);

   // give the 'go' to receive
   radio_rxNow();

   // arm rt3
   radiotimer_schedule(DURATION_rt3);
}


/**
 \brief Activity for CSL RX Sampling error [wake-up rie2].

  This is triggered by #rt3 expiring, i.e. timer fires while state = S_CSLRXWAKEUPLISTEN. If no packet is received by the time, this timer expires, then
  none will be received ever and it is safe to switch of the radio. This timer is set such that the radio will be on during two consecutive windows of
  duration (#TsLongGT).
*/
port_INLINE void activity_csl_wakeup_rie2() { // Activity for error event [rie2] on CSL RX Sampling.
   // change state --> Next State will be S_CSLRXWAKEUPOFFSET in order to prepare for CSL Rx wake-up.
   changeState(S_CSLRXWAKEUPOFFSET);

   // arm rt1
   radiotimer_schedule(DURATION_rt1);

   // abort
   endOps();
}


/**
 \brief Activity for CSL RX Sampling stage [wake-up ri4].

  This method is invoked from ISR-mode "ieee154ecsl_startOfFrame" function when a start of frame event fires while state = S_CSLRXWAKEUPLISTEN.
  The functionality is to capture the time, cancel #rt3 and arm #rt4 (max time to receive all the packet).
*/
port_INLINE void activity_csl_wakeup_ri4(PORT_RADIOTIMER_WIDTH capturedTime) {  // Activity for stage [ri4] on CSL RX Sampling.

   // change state
   changeState(S_CSLRXWAKEUP);

   // cancel rt3
   radiotimer_cancel();

   // record the captured time
   ieee154e_vars.lastCapturedTime = capturedTime;

   // record the captured time to sync
   ieee154e_vars.syncCapturedTime = capturedTime;

   radiotimer_schedule(DURATION_rt4);
}


/**
 \brief Activity for CSL RX Sampling error [wake-up rie3].

  This is triggered by #rt4 expiring, i.e. timer fires while state = S_CSLRXWAKEUP. This is an error state which indicates the radio took too long to
  transmit the data packet. The implemented behaviour is to log the error and move on the next CSL sample.
*/
port_INLINE void activity_csl_wakeup_rie3() {

   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDWAKEUPDURATION_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state,
                         (errorparameter_t)ieee154e_dbg.num_cslSamples);
   // abort
   endOps();
}


/**
 \brief Activity for CSL RX Sampling stage [wake-up ri5].

  This method is invoked from ISR-mode "ieee154ecsl_endOfFrame" function when a end of frame event fires while state = S_CSLRXWAKEUP.
  The functionality is to change state, cancel #rt4, validate wake-up frame and destination, and arm #rt4 (rztime).
*/
port_INLINE void activity_csl_wakeup_ri5(PORT_RADIOTIMER_WIDTH capturedTime) {

	ieee802154_header_iht ieee802514_header;
	open_addr_t myID, myID16b;
	uint16_t rztime = 0;

	// [CSL-TEST]: hard-code mac address to match dest address on schedule in tx activity.

    myID.addr_64b[0]=0x00;
	myID.addr_64b[1]=0x11;
	myID.addr_64b[2]=0x22;
	myID.addr_64b[3]=0x33;
	myID.addr_64b[4]=0x44;
	myID.addr_64b[5]=0x55;
	myID.addr_64b[6]=0x66;
	myID.addr_64b[7]=0x77;

	myID.type=ADDR_64B;

	// [CSL-TEST]: end test code

	// En este punto ya hemos recibido la trama por lo que hay que hacer las siguientes validaciones:
	//   1.- Cambiar el estado a S_CSLRXWAKEUPVALIDATE y cancelar el temporizador rt4.
	//   2.- Apagar la radio.
	//   3.- Analizar el mensaje recibido y parsear su cabecera.
	//   4.- Verificar que se trata de una trama de tipo wake-up.
	//   5.- Comprobar que el destinatario soy yo mismo.
	//
	// En caso afirmativo, utilizamos el Rendezvous time recibido para saber cuánto tiempo hay que dormir hasta recibir la trama de datos.
	// En caso negativo, desactivamos la radio e iniciamos de nuevo el proceso de channel sampling.

   // actualizamos el estado.
   changeState(S_CSLRXWAKEUPVALIDATE);

   // cancelamos el timer #rt4
   radiotimer_cancel();

   // apagamos la radio
   radio_rfOff();

   // obtenemos un buffer en el cual poder guardar los datos recibidos.
   ieee154e_vars.wakeupReceived = openqueue_getFreePacketBuffer(COMPONENT_IEEE802154E);
   if (ieee154e_vars.wakeupReceived==NULL) {
      // registro del error & fin de operaciones.
      openserial_printError(COMPONENT_IEEE802154E,ERR_NO_FREE_PACKET_BUFFER, (errorparameter_t)0, (errorparameter_t)0);
      endOps();
      return;
   }

   // Declaración de propiedad sobre el paquete.
   ieee154e_vars.wakeupReceived->creator = COMPONENT_IEEE802154E;
   ieee154e_vars.wakeupReceived->owner   = COMPONENT_IEEE802154E;

   /*
   The do-while loop that follows is a little parsing trick.
   Because it contains a while(0) condition, it gets executed only once.
   The behavior is:
   - if a break occurs inside the do{} body, the error code below the loop gets executed. This indicates something is wrong with the packet being parsed.
   - if a return occurs inside the do{} body, the error code below the loop does not get executed. This indicates the received packet is correct.
   */
   do { // Este "loop" es ejecutado sólo en una ocasión.

      // Obtenemos la trama con los datos recibidos desde el buffer de recepción de la radio.
      ieee154e_vars.wakeupReceived->payload = &(ieee154e_vars.wakeupReceived->packet[FIRST_FRAME_BYTE]);
      radio_getReceivedFrame(      ieee154e_vars.wakeupReceived->payload,
                                   &ieee154e_vars.wakeupReceived->length,
                             sizeof(ieee154e_vars.wakeupReceived->packet),
                                   &ieee154e_vars.wakeupReceived->l1_rssi,
                                   &ieee154e_vars.wakeupReceived->l1_lqi,
                                   &ieee154e_vars.wakeupReceived->l1_crc);

      // Finalizamos si la longitud no es correcta.
      if (ieee154e_vars.wakeupReceived->length<LENGTH_CRC || ieee154e_vars.wakeupReceived->length>LENGTH_IEEE154_MAX ) {
        openserial_printError(COMPONENT_IEEE802154E,ERR_INVALIDPACKETFROMRADIO, (errorparameter_t)2, ieee154e_vars.wakeupReceived->length);
        break;
      }

      // toss CRC (2 últimos bytes)
      packetfunctions_tossFooter(ieee154e_vars.wakeupReceived, LENGTH_CRC);

      // si CRC no es válido, finalizamos el proceso.
      if (ieee154e_vars.wakeupReceived->l1_crc==FALSE) { break; }

      // parseamos la trama IEEE802.15.4 WAKE-UP y su cabecera.
      ieee802154_retrieveWakeUpFrame(ieee154e_vars.wakeupReceived,&ieee802514_header,&rztime);

      // En el caso de que no sea una cabecera IEEE802.15.4 válida, finalizamos el proceso.
      if (ieee802514_header.valid==FALSE) { break; }

      // Verificamos que se trata de una trama WAKE-UP, perteneciente a la misma PAN ID, y dirigida a mi.
      if(ieee802514_header.frameType==IEEE154_TYPE_MULTIPURPOSE) {

    	  // [CSL-TEST]: comment and substituted due to mac address is hard-coded in tx and rx for testing.

    	  //if(packetfunctions_sameAddress(&ieee802514_header.dest,idmanager_getMyID(ADDR_16B)) &&
   	      //   packetfunctions_sameAddress(&ieee802514_header.panid,idmanager_getMyID(ADDR_PANID))) {

    	  packetfunctions_mac64bToMac16b(&myID,&myID16b);
    	  if(packetfunctions_sameAddress(&ieee802514_header.dest, &myID16b) &&
    	     packetfunctions_sameAddress(&ieee802514_header.panid,idmanager_getMyID(ADDR_PANID))) {

   		  // [CSL-TEST]: end test code

    	   // En este caso, debemos dormir el tiempo indicado por RZ Time, estableciendo el estado a S_CSLRXDATAOFFSET
 	       changeState(S_CSLRXDATAOFFSET);

    	   // registro del tiempo de captura
           ieee154e_vars.lastCapturedTime = capturedTime;

    	   // Tratamos el caso en el cual rztime_ie.time sea cero, es decir, sea la ultima trama wake-up antes del envío de la trama de datos.
    	   if (rztime == 0) {
    	     // Establecemos el timer rt1 (consideramos el mismo tiempo de offset para la recepción de la trama wake-up que para la de datos).
    	     radiotimer_schedule(DURATION_rt1);
    	   } else {
    	     // Establecemos el timer al valor rt1 pero desplazado el tiempo indicado por rendezvous-time.
        	 radiotimer_schedule(DURATION_rt1 + rztime);
           }

           // Descartamos el paquete una vez recibido y tratado.

           openqueue_freePacketBuffer(ieee154e_vars.wakeupReceived);

           // clear local variable
           ieee154e_vars.wakeupReceived = NULL;

           // retornamos para no ejecutar el codigo inferior y finalizar el proceso.
           return;
    	 }
    	 // En el caso que sea una trama dentro de mi PANID pero no dirigida a mi, entonces dormimos un tiempo igual a:
    	 //   - RZ time + Maximum length payload frame + secure ack frame (consideraremos un tiempo igual a RZ time + TsSlotDuration)
    	 // dado que TsSlotDuration es el tiempo utilizado en OpenWSN-TSCH para enviar y recibir una trama de datos + ack. Se requiere
    	 // en cualquier caso revisar estos timings mediante medidas y mecanismos más precisos (osciloscopio).

    	 else if( ! packetfunctions_sameAddress(&ieee802514_header.dest,idmanager_getMyID(ADDR_16B)) &&
    	   		    packetfunctions_sameAddress(&ieee802514_header.panid,idmanager_getMyID(ADDR_PANID))) {

    	     // La limpieza del paquete y los datos recibidos será realizada en el metodo activity_csl_wakeup_rie4
    		 radiotimer_schedule(rztime + TsSlotDuration);

    	     // Descartamos el paquete una vez recibido y tratado.

    	     openqueue_freePacketBuffer(ieee154e_vars.wakeupReceived);

    	     // clear local variable
    	     ieee154e_vars.wakeupReceived = NULL;

    	     return;
    	 }
      }
      else {
    	  break; // cualquier otro tipo de trama recibida en este punto de la FSM es descartada.
      }

   } while(0);

   // En cualquier otro caso, descartamos el paquete e iniciamos de nuevo el proceso de channel sampling.

   openqueue_freePacketBuffer(ieee154e_vars.wakeupReceived);

   // clear local variable
   ieee154e_vars.wakeupReceived = NULL;

   // abort
   endOps();
}


/**
 \brief Activity for CSL RX Sampling error [wake-up rie4].

  This is triggered by rztime+TsSlotDuration expiring, i.e. timer fires while state = S_CSLRXWAKEUPVALIDATE because the wake-up frame is not for me.
  The behaviour is to free mem used and restart CSL sampling.
*/
port_INLINE void activity_csl_wakeup_rie4() {
   // abort
   endOps();
}


/**
 \brief Activity for CSL RX Sampling stage [data ri2].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt1") while state = S_CSLRXDATAOFFSET.
  The functionality is to prepare the radio for receiving packets.
*/

port_INLINE void activity_csl_data_ri2() {
   // change state
   changeState(S_CSLRXDATAPREPARE);

   // We use always the same frequency so it is not necessary to change it on radio.
   // Enable the radio in Rx mode. The radio does not actively listen yet.
   radio_rxEnable();
   ieee154e_vars.radioOnInit=radio_getTimerValue();
   ieee154e_vars.radioOnThisSlot=TRUE;

   // arm rt2
   radiotimer_schedule(DURATION_rt2);

   // change state
   // If this action is not performed before rt2 has expired, we need to manage the error in activity_csl_data_rie1. This means that radio
   // prepare has exceeded the maximum allowed time (duration_rt2).
   changeState(S_CSLRXDATAREADY);
}


/**
 \brief Activity for CSL RX Sampling error [data_rie1].

  This is triggered by #rt2 expiring, i.e. timer fires while state = S_CSLRXDATAPREPARE. This is really an error state which indicates that #ri2
  did not have enough time to execute. Chances are to set maxRxDataPrepare too small. The implemented behaviour is to log the error and move on the
  next CSL sample.
*/
port_INLINE void activity_csl_data_rie1() {  // Activity for error event [rie1] on CSL RX Sampling.
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_MAXRXDATAPREPARE_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state,
                         (errorparameter_t)ieee154e_dbg.num_cslSamples);
   // abort
   endOps();
}


/**
 \brief Activity for CSL RX Sampling stage [data ri3].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt2") while state = S_CSLRXDATAREADY.
  The radio is configured and this interrupt gives it the "go" signal to start listening.
*/
port_INLINE void activity_csl_data_ri3() { // Activity for stage [data ri3] on CSL RX Sampling.
   // change state
   changeState(S_CSLRXDATALISTEN);

   // give the 'go' to receive
   radio_rxNow();

   // arm rt3
   radiotimer_schedule(DURATION_rt3);
}


/**
 \brief Activity for CSL RX Sampling error [data rie2].

  This is triggered by #rt3 expiring, i.e. timer fires while state = S_CSLRXDATALISTEN. If no packet is received by the time, this timer expires, then
  none will be received ever and it is safe to switch of the radio. This timer is set such that the radio will be on during two consecutive windows of
  duration (#TsLongGT).
*/
port_INLINE void activity_csl_data_rie2() { // Activity for error event [data rie2] on CSL RX Sampling.
   // abort
   endOps();
}

/**
 \brief Activity for CSL RX Sampling stage [data ri4].

  This method is invoked from ISR-mode "ieee154ecsl_startOfFrame" function when a start of frame event fires while state = S_CSLRXDATALISTEN.
  The functionality is to capture the time, cancel #rt3 and arm #rt4 (max time to receive all the packet).
*/
port_INLINE void activity_csl_data_ri4(PORT_RADIOTIMER_WIDTH capturedTime) {  // Activity for stage [data ri4] on CSL RX Sampling.

   // change state
   changeState(S_CSLRXDATA);

   // cancel rt3
   radiotimer_cancel();

   // record the captured time
   ieee154e_vars.lastCapturedTime = capturedTime;

   // record the captured time to sync
   ieee154e_vars.syncCapturedTime = capturedTime;

   radiotimer_schedule(DURATION_rt4);
}


/**
 \brief Activity for CSL RX Sampling error [data rie3].

  This is triggered by #rt4 expiring, i.e. timer fires while state = S_CSLRXDATA. This is an error state which indicates the radio took too long to
  transmit the data packet. The implemented behaviour is to log the error and move on the next CSL sample.
*/
port_INLINE void activity_csl_data_rie3() {

   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDDATADURATION_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state,
                         (errorparameter_t)ieee154e_dbg.num_cslSamples);

   // abort
   endOps();
}

/**
 \brief Activity for CSL RX Sampling stage [data ri5].

  This method is invoked from ISR-mode "ieee154ecsl_endOfFrame" function when a end of frame event fires while state = S_CSLRXDATA.
  The functionality is to change state, cancel #rt4, validate data frame, and transmit ACK.
*/
port_INLINE void activity_csl_data_ri5(PORT_RADIOTIMER_WIDTH capturedTime) {
   ieee802154_header_iht ieee802514_header;
   uint16_t lenIE=0;

   // change state
   changeState(S_CSLTXACKOFFSET);

   // cancel rt4
   radiotimer_cancel();

   // turn off the radio
   radio_rfOff();
   ieee154e_vars.radioOnTics+=radio_getTimerValue()-ieee154e_vars.radioOnInit;
   // get a buffer to put the (received) data in
   ieee154e_vars.dataReceived = openqueue_getFreePacketBuffer(COMPONENT_IEEE802154E);
   if (ieee154e_vars.dataReceived==NULL) {
      // log the error
      openserial_printError(COMPONENT_IEEE802154E,ERR_NO_FREE_PACKET_BUFFER,
                            (errorparameter_t)0,
                            (errorparameter_t)0);
      // abort
      endOps();
      return;
   }

   // declare ownership over that packet
   ieee154e_vars.dataReceived->creator = COMPONENT_IEEE802154E;
   ieee154e_vars.dataReceived->owner   = COMPONENT_IEEE802154E;

   /*
   The do-while loop that follows is a little parsing trick.
   Because it contains a while(0) condition, it gets executed only once.
   The behavior is:
   - if a break occurs inside the do{} body, the error code below the loop
     gets executed. This indicates something is wrong with the packet being
     parsed.
   - if a return occurs inside the do{} body, the error code below the loop
     does not get executed. This indicates the received packet is correct.
   */

   do { // this "loop" is only executed once

      // retrieve the received data frame from the radio's Rx buffer
      ieee154e_vars.dataReceived->payload = &(ieee154e_vars.dataReceived->packet[FIRST_FRAME_BYTE]);
      radio_getReceivedFrame(       ieee154e_vars.dataReceived->payload,
                                   &ieee154e_vars.dataReceived->length,
                             sizeof(ieee154e_vars.dataReceived->packet),
                                   &ieee154e_vars.dataReceived->l1_rssi,
                                   &ieee154e_vars.dataReceived->l1_lqi,
                                   &ieee154e_vars.dataReceived->l1_crc);

      // break if wrong length
      if (ieee154e_vars.dataReceived->length<LENGTH_CRC || ieee154e_vars.dataReceived->length>LENGTH_IEEE154_MAX ) {
         // jump to the error code below this do-while loop
        openserial_printError(COMPONENT_IEEE802154E,ERR_INVALIDPACKETFROMRADIO,
                            (errorparameter_t)2,
                            ieee154e_vars.dataReceived->length);
         break;
      }

      // toss CRC (2 last bytes)
      packetfunctions_tossFooter(   ieee154e_vars.dataReceived, LENGTH_CRC);

      // if CRC doesn't check, stop
      if (ieee154e_vars.dataReceived->l1_crc==FALSE) {
         // jump to the error code below this do-while loop
         break;
      }

      // parse the IEEE802.15.4 header (RX DATA)
      ieee802154_retrieveHeader(ieee154e_vars.dataReceived,&ieee802514_header);

      // break if invalid IEEE802.15.4 header
      if (ieee802514_header.valid==FALSE) {
         // break from the do-while loop and execute the clean-up code below
         break;
      }

      // store header details in packet buffer
      ieee154e_vars.dataReceived->l2_frameType      = ieee802514_header.frameType;
      ieee154e_vars.dataReceived->l2_dsn            = ieee802514_header.dsn;
      ieee154e_vars.dataReceived->l2_IEListPresent  = ieee802514_header.ieListPresent;
      memcpy(&(ieee154e_vars.dataReceived->l2_nextORpreviousHop),&(ieee802514_header.src),sizeof(open_addr_t));

      // toss the IEEE802.15.4 header
      packetfunctions_tossHeader(ieee154e_vars.dataReceived,ieee802514_header.headerLength);

      // handle IEs xv poipoi
      // reset join priority
      // retrieve IE in sixtop
      if ((ieee802514_header.valid==TRUE &&
          ieee802514_header.ieListPresent==TRUE &&
          ieee802514_header.frameType==IEEE154_TYPE_BEACON && // if it is not a beacon and have ie, the ie will be processed in sixtop
          packetfunctions_sameAddress(&ieee802514_header.panid,idmanager_getMyID(ADDR_PANID)) &&
          ieee154e_processIEs(ieee154e_vars.dataReceived,&lenIE))==FALSE) {
          //log  that the packet is not carrying IEs
      }

      // toss the IEs including Synch
      packetfunctions_tossHeader(ieee154e_vars.dataReceived,lenIE);

      // record the captured time
      ieee154e_vars.lastCapturedTime = capturedTime;

      // if I just received an invalid frame, stop
      if (isValidRxFrame(&ieee802514_header)==FALSE) {
         // jump to the error code below this do-while loop
         break;
      }

      // [CSL-TEST]: Force to not send ack packet

      ieee802514_header.ackRequested = 0;

      // [CSL-TEST]: end test code

      // check if ack requested
      if (ieee802514_header.ackRequested==1) {
         // arm rt5
         radiotimer_schedule(DURATION_rt5);
      } else {
         // [CSL-TEST]: comment synchronization
         // synchronize to the received packet if I'm not a DAGroot and this is my preferred parent
         //if (idmanager_getIsDAGroot()==FALSE && neighbors_isPreferredParent(&(ieee154e_vars.dataReceived->l2_nextORpreviousHop))) {
         //   synchronizePacket(ieee154e_vars.syncCapturedTime);
         //}
         // [CSL-TEST]: end test code

    	 // indicate reception to upper layer (no ACK asked)
         notif_receive(ieee154e_vars.dataReceived, 1);
         // reset local variable
         ieee154e_vars.dataReceived = NULL;
         // abort
         endOps();
      }

      // everything went well, return here not to execute the error code below
      return;

   } while(0);

   // free the (invalid) received data so RAM memory can be recycled
   openqueue_freePacketBuffer(ieee154e_vars.dataReceived);

   // clear local variable
   ieee154e_vars.dataReceived = NULL;

   // abort
   endOps();
}

/**
 \brief Activity for CSL RX Sampling stage [data ri6].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt5") while state = S_CSLTXACKOFFSET.
   The functionality is to prepare the radio for ACK sending.
*/
port_INLINE void activity_csl_data_ri6() {
   PORT_SIGNED_INT_WIDTH timeCorrection;
   header_IE_ht header_desc;
   
   // change state
   changeState(S_CSLTXACKPREPARE);
   
   // get a buffer to put the ack to send in
   ieee154e_vars.ackToSend = openqueue_getFreePacketBuffer(COMPONENT_IEEE802154E);
   if (ieee154e_vars.ackToSend==NULL) {
      // log the error
      openserial_printError(COMPONENT_IEEE802154E,ERR_NO_FREE_PACKET_BUFFER, (errorparameter_t)0, (errorparameter_t)0);
      // indicate we received a packet anyway (we don't want to loose any)
      notif_receive(ieee154e_vars.dataReceived,0);
      // free local variable
      ieee154e_vars.dataReceived = NULL;
      // abort
      endOps();
      return;
   }
   
   // declare ownership over that packet
   ieee154e_vars.ackToSend->creator = COMPONENT_IEEE802154E;
   ieee154e_vars.ackToSend->owner   = COMPONENT_IEEE802154E;
   
   // calculate the time timeCorrection (this is the time when the packet arrive w.r.t the time it should be.
   timeCorrection = (PORT_SIGNED_INT_WIDTH)((PORT_SIGNED_INT_WIDTH)ieee154e_vars.syncCapturedTime-(PORT_SIGNED_INT_WIDTH)TsTxOffset);
    
   // add the payload to the ACK (i.e. the timeCorrection)
   packetfunctions_reserveHeaderSize(ieee154e_vars.ackToSend,sizeof(timecorrection_IE_ht));
   timeCorrection  = -timeCorrection;
   timeCorrection *= US_PER_TICK;
   ieee154e_vars.ackToSend->payload[0] = (uint8_t)((((uint16_t)timeCorrection)   ) & 0xff);
   ieee154e_vars.ackToSend->payload[1] = (uint8_t)((((uint16_t)timeCorrection)>>8) & 0xff);
   
   // add header IE header -- xv poipoi -- pkt is filled in reverse order..
   packetfunctions_reserveHeaderSize(ieee154e_vars.ackToSend,sizeof(header_IE_ht));
   //create the header for ack IE
   header_desc.length_elementid_type=(sizeof(timecorrection_IE_ht)<< IEEE802154E_DESC_LEN_HEADER_IE_SHIFT)|
                                     (IEEE802154E_ACK_NACK_TIMECORRECTION_ELEMENTID << IEEE802154E_DESC_ELEMENTID_HEADER_IE_SHIFT)|
                                     IEEE802154E_DESC_TYPE_SHORT; 
   memcpy(ieee154e_vars.ackToSend->payload,&header_desc,sizeof(header_IE_ht));
   
   // prepend the IEEE802.15.4 header to the ACK
   ieee154e_vars.ackToSend->l2_frameType = IEEE154_TYPE_ACK;
   ieee154e_vars.ackToSend->l2_dsn       = ieee154e_vars.dataReceived->l2_dsn;
   ieee802154_prependHeader(ieee154e_vars.ackToSend,
                            ieee154e_vars.ackToSend->l2_frameType,
                            IEEE154_IELIST_YES,//ie in ack
                            IEEE154_FRAMEVERSION,//enhanced ack
                            IEEE154_SEC_NO_SECURITY,
                            ieee154e_vars.dataReceived->l2_dsn,
                            &(ieee154e_vars.dataReceived->l2_nextORpreviousHop)
                            );
   
   // space for 2-byte CRC
   packetfunctions_reserveFooterSize(ieee154e_vars.ackToSend,2);
   
   // load the packet in the radio's Tx buffer
   radio_loadPacket(ieee154e_vars.ackToSend->payload,
                    ieee154e_vars.ackToSend->length);
   
   // enable the radio in Tx mode. This does not send that packet.
   radio_txEnable();
   ieee154e_vars.radioOnInit=radio_getTimerValue();
   ieee154e_vars.radioOnThisSlot=TRUE;
   // arm rt6
   radiotimer_schedule(DURATION_rt6);
   
   // change state
   changeState(S_CSLTXACKREADY);
}

/**
 \brief Activity for CSL RX Sampling stage [data rie4].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt5") while state = S_CSLTXACKOFFSET.
   The functionality is to prepare the radio for ACK sending.
*/
port_INLINE void activity_csl_data_rie4() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_MAXTXACKPREPARE_OVERFLOWS,
		                 (errorparameter_t)ieee154e_vars.state,
						 (errorparameter_t)ieee154e_dbg.num_cslSamples);

   // abort
   endOps();
}

/**
 \brief Activity for CSL RX Sampling stage [data ri7].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt2") while state = S_CSLRXDATAREADY.
  The radio is configured and this interrupt gives it the "go" signal to start listening.
*/
port_INLINE void activity_csl_data_ri7() {
   // change state
   changeState(S_CSLTXACKDELAY);
   
   // arm rt7
   radiotimer_schedule(DURATION_rt7);
   
   // give the 'go' to transmit
   radio_txNow(); 
}

/**
 \brief Activity for CSL RX Sampling stage [data rie5].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt7") while state = S_CSLTXACKDELAY.
   The functionality is to prepare the radio for ACK sending.
*/
port_INLINE void activity_csl_data_rie5() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDRADIOTX_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state,
						 (errorparameter_t)ieee154e_dbg.num_cslSamples);
   // abort
   endOps();
}

/**
 \brief Activity for CSL RX Sampling stage [data ri8].

  This method is invoked from ISR-mode "ieee154ecsl_startOfFrame" function when a start of frame event fires while state = S_CSLTXACKDELAY.
  The functionality is to change the state to set transmission, cancel #rt7 and arm #rt8 (max time to sent the ack packet).
*/
port_INLINE void activity_csl_data_ri8(PORT_RADIOTIMER_WIDTH capturedTime) {
   // change state
   changeState(S_CSLTXACK);
   
   // cancel rt7
   radiotimer_cancel();
   
   // record the captured time
   ieee154e_vars.lastCapturedTime = capturedTime;
   
   // arm rt8
   radiotimer_schedule(DURATION_rt8);
}

/**
 \brief Activity for CSL RX Sampling stage [data rie6].

  This method is invoked from ISR-mode "isr_ieee154ecsl_timer" function when FSM timer fires (expiring "duration_rt8") while state = S_CSLTXACK.
  The functionality is to register an error when timer for sent ACK has expired.
*/
port_INLINE void activity_csl_data_rie6() {
   // log the error
   openserial_printError(COMPONENT_IEEE802154E,ERR_WDACKDURATION_OVERFLOWS,
                         (errorparameter_t)ieee154e_vars.state,
                         (errorparameter_t)ieee154e_dbg.num_cslSamples);
   // abort
   endOps();
}

/**
 \brief Activity for CSL RX Sampling stage [data ri9].

  This method is invoked from ISR-mode "ieee154ecsl_endOfFrame" function when a end of frame event fires while state = S_CSLTXACK.
  The functionality is to change the state, cancel #rt8, free ack packet and notify upper layer.
*/
port_INLINE void activity_csl_data_ri9(PORT_RADIOTIMER_WIDTH capturedTime) {
   // change state
   changeState(S_CSLRXPROC);
   
   // cancel rt8
   radiotimer_cancel();
  
   // record the captured time
   ieee154e_vars.lastCapturedTime = capturedTime;
   
   // free the ack we just sent so corresponding RAM memory can be recycled
   openqueue_freePacketBuffer(ieee154e_vars.ackToSend);
   
   // clear local variable
   ieee154e_vars.ackToSend = NULL;
   
   // synchronize to the received packet
   //if (idmanager_getIsDAGroot()==FALSE && neighbors_isPreferredParent(&(ieee154e_vars.dataReceived->l2_nextORpreviousHop))) {
   //   synchronizePacket(ieee154e_vars.syncCapturedTime);
   //}
   
   // inform upper layer of reception (after ACK sent)
   notif_receive(ieee154e_vars.dataReceived,1);
   
   // clear local variable
   ieee154e_vars.dataReceived = NULL;
   
   // official end of Rx slot
   endOps();
}


//======================================================================
//======================= WAKE-UP FRAMES ===============================
//======================================================================

/**
\brief Prepend the IEEE802.15.4 MAC Wake-Up header to a (to be transmitted) packet.

Note that we are writing the field from the end of the header to the beginning.

\param[in,out] msg              The message to append the header to.
\param[in]     sequenceNumber   Sequence number of this frame.
\param[in]     nextHop          Address of the next hop
\param[in]     rztime           Rendezvoud time
*/

// [CSL]: Prepend  a wake-up header to a packet.
void ieee802154_createWakeUpFrame(OpenQueueEntry_t*		msg,
                                  uint8_t           	sequenceNumber,
                                  open_addr_t*        	nextHop,
							      uint16_t				rz_time) {

    open_addr_t	nextHop16b;

	// La estructura de una trama Wake-Up es la siguiente:
	//
	//   - FRAME CONTROL: 1 byte
	//   - SEQ NUMBER (macDSN): 1 byte
	//   - PAN ID: 2 bytes
	//   - DEST ADDR: 2 bytes
	//   - RZ TIME IE: 2 bytes (header) + 2 bytes (body)
	//   - IE LIST TERMINATOR: 2 bytes
	//
	//  | FRAME   |  SEQ   | PAN | DEST | RZ TIME  | IE LIST    |
	//  | CONTROL | NUMBER |  ID | ADDR |  HDR IE  | TERMINATOR |
	//

	// Empezamos a escribir el payload de la trama wake-up empezando del final hacia adelante.

	// IE LIST TERMINATOR, formado por 2 bytes con la siguiente estructura (0x3F80 o 0x3F00)
    //  - b0-b6 (Length) = 0
    //  - b7-b14 (Element ID) = 0x7e o 0x7f
    //  - b15 (Type) = 0
    //
    //  b15 | b14 | b13 | b12 | b11 | b10 | b9 | b8 | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
    //   0  |  0  |  1  |  1  |  1  |  1  | 1  | 1  |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |
	packetfunctions_reserveHeaderSize(msg,sizeof(uint16_t));
	*((uint16_t*)(msg->payload)) = 0x3F00;  // Element ID = 0x7e

	// RZ TIME IE, formado por 4 bytes con la siguiente estructura (0x0E82). La cabecera es igual a:
    //  - b0-b6 (Length) = 2
    //  - b7-b14 (Element ID) = 0x1D
    //  - b15 (Type) = 0
    //  - b16-b31 (IE Content) = time (2 bytes)
    //
    //  b15 | b14 | b13 | b12 | b11 | b10 | b9 | b8 | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
    //   0  |  0  |  0  |  0  |  1  |  1  |  1 |  0 |  1 |  0 |  0 |  0 |  0 |  0 |  1 |  0 |

 	// rz time ie body (time)
	packetfunctions_reserveHeaderSize(msg,sizeof(uint16_t));
	*((uint16_t*)(msg->payload)) = rz_time;

	// rz time ie header
	packetfunctions_reserveHeaderSize(msg,sizeof(uint16_t));
	*((uint16_t*)(msg->payload)) = 0x0E82;

	// DEST ADDR
	if (nextHop->type == ADDR_16B) {
  	   packetfunctions_writeAddress(msg,nextHop,OW_LITTLE_ENDIAN);
    } else if (nextHop->type == ADDR_64B) {
	   packetfunctions_mac64bToMac16b(nextHop, &nextHop16b);
	   packetfunctions_writeAddress(msg,&nextHop16b,OW_LITTLE_ENDIAN);
	}

	// PAN ID
	packetfunctions_writeAddress(msg,idmanager_getMyID(ADDR_PANID),OW_LITTLE_ENDIAN);

	// SEQ NUMBER
	packetfunctions_reserveHeaderSize(msg,sizeof(uint8_t));
	*((uint8_t*)(msg->payload)) = sequenceNumber;

	// La estructura del FCF en la trama de wake-up es 0x55 = 01010101b:
	// b0-b2 -- Frame Type (debe ser 101 para trama wake-up)
	// b3 ----- Long Frame Control (debe ser 0 para indicar que se trata de un FCF de 1 byte como es en el caso de tramas wake-up).
	// b4-b5 -- Dest Addr Mode (en este caso, short address por lo que tiene que valer 10).
	// b6-b7 -- Src Addr Mode (en este caso, short address por lo que tiene que valer 10).

	//  b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
	//   0 |  1 |  0 |  1 |  0 |  1 |  0 |  1 |

	// FCF
	packetfunctions_reserveHeaderSize(msg,sizeof(uint8_t));
	*((uint8_t*)(msg->payload)) = 0x55;

}

/**
\brief Retrieve the IEEE802.15.4 MAC Wake-Up Frame header from a (just received) packet.

Note We are writing the fields from the beginning of the header to the end.

\param[in,out] msg            The message just received.
\param[out] ieee802514_header The internal header to write the data to.
\param[out] rztime  		  Rendezvous time to wait for data packet.
*/

// [CSL]: Retrieve a wake-up header from the received packet.
void ieee802154_retrieveWakeUpFrame(OpenQueueEntry_t*      msg,
                                    ieee802154_header_iht* ieee802514_header,
									uint16_t* rztime) {
   uint8_t temp_8b, temp_8b1, temp_8b2;
   uint8_t src_addr_mode, dst_addr_mode;
   uint16_t temp_16b;


   // La estructura de una trama Wake-Up es la siguiente:
   //
   //   - FRAME CONTROL: 1 byte
   //   - SEQ NUMBER (macDSN): 1 byte
   //   - PAN ID: 2 bytes
   //   - DEST ADDR: 2 bytes
   //   - RZ TIME IE: 2 bytes
   //   - IE LIST TERMINATOR: 2 bytes
   //
   //  | FRAME   |  SEQ   | PAN | DEST | RZ TIME  | IE LIST    |
   //  | CONTROL | NUMBER |  ID | ADDR |  HDR IE  | TERMINATOR |
   //

   // Por defecto, se asume que la cabecera no es válida en el caso de
   // abandonar la función al ser el paquete más corto que la cabecera.
   ieee802514_header->valid=FALSE;
   ieee802514_header->headerLength = 0;

   // Validamos la existencia de datos que leer.
   if (ieee802514_header->headerLength > msg->length) { return; }

   // Frame Control Field (1 byte)
   temp_8b = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);

   // La estructura del FCF en la trama de wake-up es 0x55 = 01010101b:
   // b0-b2 -- Frame Type (debe ser 101 para trama wake-up)
   // b3 ----- Long Frame Control (debe ser 0 para indicar que se trata de un FCF de 1 byte como es en el caso de tramas wake-up).
   // b4-b5 -- Dest Addr Mode (en este caso, short address por lo que tiene que valer 10).
   // b6-b7 -- Src Addr Mode (en este caso, short address por lo que tiene que valer 10).

   //  b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
   //   0 |  1 |  0 |  1 |  0 |  1 |  0 |  1 |

   ieee802514_header->frameType = (temp_8b >> IEEE154_FCF_FRAME_TYPE) & 0x07;//3b

   // Comprobamos que efectivamente se trata de una trama de tipo MULTIPURPOSE.
   if (ieee802514_header->frameType != IEEE154_TYPE_MULTIPURPOSE) {return; }

   // Verificamos que efectivamente el campo Long Frame Control tiene valor cero para indicar que el FCF solo tiene 1 byte.
   if ((temp_8b >> 3) & 0x01) { return; }

   // Recuperamos los Destination y Source Address Mode

   // Destination Address Mode
   dst_addr_mode = (temp_8b >> 4) & 0x03;
   if(dst_addr_mode == 1) { // 01 en binario en bits b5-b4
     // Debería ser siempre este caso en las tramas wake-up por lo que se trata como error cualquier otra opción.
     ieee802514_header->dest.type = ADDR_16B;
   }
   else {
	 openserial_printError(COMPONENT_IEEE802154,ERR_IEEE154_UNSUPPORTED, (errorparameter_t)1, (errorparameter_t)(dst_addr_mode));
     return; // this is an invalid packet, return
   }

   // Source Address Mode
   src_addr_mode = (temp_8b >> 6) & 0x03;
   if(src_addr_mode == 1) { // 01 en binario en bits b7-b6
      // Debería ser siempre este caso en las tramas wake-up por lo que se trata como error cualquier otra opción.
      ieee802514_header->src.type = ADDR_16B;
   }
   else {
	  openserial_printError(COMPONENT_IEEE802154,ERR_IEEE154_UNSUPPORTED, (errorparameter_t)2, (errorparameter_t)src_addr_mode);
      return; // this is an invalid packet, return
   }

   //
   // En este punto ya hemos analizado el contenido del primer byte de la cabecera correspondiente al Frame Control Field (FCF)
   //

   // A partir de este punto, la estructura del paquete es la siguiente:
   //   - SEQ NUMBER (macDSN): 1 byte
   //   - PAN ID: 2 bytes
   //   - DEST ADDR: 2 bytes
   //   - RZ TIME IE: 2 bytes
   //   - IE LIST TERMINATOR: 2 bytes
   //

   // Avanzamos 1 byte en el procesamiento de la cabecera.
   ieee802514_header->headerLength += 1;

   // Posicionamos dentro del paquete para leer el resto de elementos.

   // 1.- SequenceNumber
   if (ieee802514_header->headerLength > msg->length) { return; } // no more to read!
   ieee802514_header->dsn  = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);
   ieee802514_header->headerLength += 1;

   // 2.- panID
   if (ieee802514_header->headerLength > msg->length) { return; } // no more to read!
   packetfunctions_readAddress(((uint8_t*)(msg->payload)+ieee802514_header->headerLength), ADDR_PANID, &ieee802514_header->panid, OW_LITTLE_ENDIAN);
   ieee802514_header->headerLength += 2;

   // 3.- Dest Addr
   if (ieee802514_header->headerLength > msg->length) { return; } // no more to read!

   // En este punto ya sabemos que el tipo de dirección tiene que ser ADDR_16B dado que cualquier otro caso ya fue tratado antes
   // en la lectura del frame control field por lo que leemos los 2 bytes de la dirección del destino.
   packetfunctions_readAddress(((uint8_t*)(msg->payload)+ieee802514_header->headerLength), ADDR_16B, &ieee802514_header->dest, OW_LITTLE_ENDIAN);
   ieee802514_header->headerLength += 2;

   // 4.- RZ Time Header IE, formado por 4 bytes con la siguiente estructura (0x0E82)
   //  - b0-b6 (Length) = 2
   //  - b7-b14 (Element ID) = 0x1D
   //  - b15 (Type) = 0
   //  - b16-b31 (IE Content) = time (2 bytes)
   //
   //  b15 | b14 | b13 | b12 | b11 | b10 | b9 | b8 | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
   //   0  |  0  |  0  |  0  |  1  |  1  |  1 |  0 |  1 |  0 |  0 |  0 |  0 |  0 |  1 |  0 |

   if (ieee802514_header->headerLength > msg->length) {  return; } // no more to read!

   // Verificamos longitud a valor 2 y el elementID a valor 0x1D. Lo hacemos leyendo los primeros 2 bytes del RZ Time IE, uno a uno.
   temp_8b1 = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);
   ieee802514_header->headerLength += 1;

   temp_8b2 = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);
   ieee802514_header->headerLength += 1;

   temp_16b = (temp_8b2 << 8) | temp_8b1;

   // Comprobación de longitud a valor 2.
   if ((temp_16b & 0x007f) != 2) { return; }

   // Comprobación de element ID = 0x1D.
   if ((temp_16b >> 7) != 0x001d) { return; }

   // Comprobación del type = 0.
   if ((temp_16b >> 15) & 0x0001) { return; }

   // Obtención del IE Content (rztime).
   if (ieee802514_header->headerLength > msg->length) { return; } // no more to read!

   temp_8b1 = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);
   ieee802514_header->headerLength += 1;

   temp_8b2 = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);
   ieee802514_header->headerLength += 1;

   (*rztime) = (temp_8b2 << 8) | temp_8b1;

   // 5.- IE List Terminator, formado por 2 bytes con la siguiente estructura (0x3F80 o 0x3F00)
   //  - b0-b6 (Length) = 0
   //  - b7-b14 (Element ID) = 0x7e o 0x7f
   //  - b15 (Type) = 0
   //
   //  b15 | b14 | b13 | b12 | b11 | b10 | b9 | b8 | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
   //   0  |  0  |  1  |  1  |  1  |  1  | 1  | 1  |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |

   if (ieee802514_header->headerLength > msg->length) { return; } // no more to read!

   // Verificamos longitud a valor 0 y el elementID a valor 0x7E o 0x7F. Lo hacemos leyendo los 2 bytes IE.
   temp_8b1 = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);
   ieee802514_header->headerLength += 1;

   temp_8b2 = *((uint8_t*)(msg->payload)+ieee802514_header->headerLength);
   ieee802514_header->headerLength += 1;

   temp_16b = (temp_8b2 << 8) | temp_8b1;

   // Comprobación de longitud a valor 0.
   if (temp_16b & 0x007f) { return; }

   // Comprobación de element ID = 0x7E o 0x7F.
   if (((temp_16b >> 7) != 0x7e) && ((temp_16b >> 7) != 0x7f)) { return; }

   // Comprobación del type = 0.
   if ((temp_16b >> 15) & 0x0001) { return; }

   // Por ultimo y en el caso de haber llegado aquí, consideramos la cabecera como válida.
   ieee802514_header->valid=TRUE;
}

//======================================================================
//====================  FRAME VALIDITY CHECK ===========================
//======================================================================

/**
\brief Decides whether the packet I just received is valid received frame.

A valid Rx frame satisfies the following constraints:
- its IEEE802.15.4 header is well formatted
- it's a DATA of BEACON frame (i.e. not ACK and not COMMAND)
- it's sent on the same PANid as mine
- it's for me (unicast or broadcast)

\param[in] ieee802514_header IEEE802.15.4 header of the packet I just received

\returns TRUE if packet is valid received frame, FALSE otherwise
*/
port_INLINE bool isValidRxFrame(ieee802154_header_iht* ieee802514_header) {
   return ieee802514_header->valid==TRUE                                                           && \
          (
             ieee802514_header->frameType==IEEE154_TYPE_DATA                   ||
             ieee802514_header->frameType==IEEE154_TYPE_BEACON
          )                                                                                        && \
          packetfunctions_sameAddress(&ieee802514_header->panid,idmanager_getMyID(ADDR_PANID))     && \
          (
             idmanager_isMyAddress(&ieee802514_header->dest)                   ||
             packetfunctions_isBroadcastMulticast(&ieee802514_header->dest)
          );
}

/**
\brief Decides whether the packet I just received is a valid ACK.

A packet is a valid ACK if it satisfies the following conditions:
- the IEEE802.15.4 header is valid
- the frame type is 'ACK'
- the sequence number in the ACK matches the sequence number of the packet sent
- the ACK contains my PANid
- the packet is unicast to me
- the packet comes from the neighbor I sent the data to

\param[in] ieee802514_header IEEE802.15.4 header of the packet I just received
\param[in] packetSent points to the packet I just sent

\returns TRUE if packet is a valid ACK, FALSE otherwise.
*/
port_INLINE bool isValidAck(ieee802154_header_iht* ieee802514_header, OpenQueueEntry_t* packetSent) {
   /*
   return ieee802514_header->valid==TRUE                                                           && \
          ieee802514_header->frameType==IEEE154_TYPE_ACK                                           && \
          ieee802514_header->dsn==packetSent->l2_dsn                                               && \
          packetfunctions_sameAddress(&ieee802514_header->panid,idmanager_getMyID(ADDR_PANID))     && \
          idmanager_isMyAddress(&ieee802514_header->dest)                                          && \
          packetfunctions_sameAddress(&ieee802514_header->src,&packetSent->l2_nextORpreviousHop);
   */
   // poipoi don't check for seq num
   return ieee802514_header->valid==TRUE                                                           && \
          ieee802514_header->frameType==IEEE154_TYPE_ACK                                           && \
          packetfunctions_sameAddress(&ieee802514_header->panid,idmanager_getMyID(ADDR_PANID))     && \
          idmanager_isMyAddress(&ieee802514_header->dest)                                          && \
          packetfunctions_sameAddress(&ieee802514_header->src,&packetSent->l2_nextORpreviousHop);
}

//======================================================================
//========================  ASN HANDLING ===============================
//======================================================================

port_INLINE void incrementAsnOffset() {
   // increment the asn
   ieee154e_vars.asn.bytes0and1++;
   if (ieee154e_vars.asn.bytes0and1==0) {
      ieee154e_vars.asn.bytes2and3++;
      if (ieee154e_vars.asn.bytes2and3==0) {
         ieee154e_vars.asn.byte4++;
      }
   }
   // increment the offsets: Comment slot offset update.
   ieee154e_vars.slotOffset  = (ieee154e_vars.slotOffset+1)%schedule_getFrameLength();
   ieee154e_vars.asnOffset   = (ieee154e_vars.asnOffset+1)%16;
}

//from upper layer that want to send the ASN to compute timing or latency
port_INLINE void ieee154e_getAsn(uint8_t* array) {
   array[0]         = (ieee154e_vars.asn.bytes0and1     & 0xff);
   array[1]         = (ieee154e_vars.asn.bytes0and1/256 & 0xff);
   array[2]         = (ieee154e_vars.asn.bytes2and3     & 0xff);
   array[3]         = (ieee154e_vars.asn.bytes2and3/256 & 0xff);
   array[4]         =  ieee154e_vars.asn.byte4;
}

//======================================================================
//======================  SYNCHRONIZATION ==============================
//======================================================================

void synchronizeAck(PORT_SIGNED_INT_WIDTH timeCorrection) {
   PORT_RADIOTIMER_WIDTH newPeriod;
   PORT_RADIOTIMER_WIDTH currentPeriod;
   
   // calculate new period
   currentPeriod                  =  radio_getTimerPeriod();
   newPeriod                      =  (PORT_RADIOTIMER_WIDTH)((PORT_SIGNED_INT_WIDTH)currentPeriod-timeCorrection);

   // resynchronize by applying the new period
   radio_setTimerPeriod(newPeriod);
   
   // reset the de-synchronization timeout
   ieee154e_vars.deSyncTimeout    = DESYNCTIMEOUT;
   
   // indicate time correction to adaptive sync module
   adaptive_sync_indicateTimeCorrection((-timeCorrection),ieee154e_vars.ackReceived->l2_nextORpreviousHop);
   
   // log a large timeCorrection
   if (
         ieee154e_vars.isSync==TRUE &&
         (
            timeCorrection<-LIMITLARGETIMECORRECTION ||
            timeCorrection> LIMITLARGETIMECORRECTION
         )
      ) {
      openserial_printError(COMPONENT_IEEE802154E,ERR_LARGE_TIMECORRECTION,
                            (errorparameter_t)timeCorrection,
                            (errorparameter_t)1);
   }
   // update the stats
   ieee154e_stats.numSyncAck++;
   updateStats(timeCorrection);
   
#ifdef OPENSIM
   debugpins_syncAck_set();
   debugpins_syncAck_clr();
#endif
}

void changeIsSync(bool newIsSync) {
   ieee154e_vars.isSync = newIsSync;
   
   if (ieee154e_vars.isSync==TRUE) {
      leds_sync_on();
      resetStats();
   } else {
      leds_sync_off();
      schedule_resetBackoff();
   }
}

//======================================================================
//=====================  NOTIFY UPPER LAYER  ===========================
//======================================================================

void notif_sendDone(OpenQueueEntry_t* packetSent, owerror_t error) {
   // record the outcome of the trasmission attempt
   packetSent->l2_sendDoneError   = error;
   // record the current ASN
   memcpy(&packetSent->l2_asn,&ieee154e_vars.asn,sizeof(asn_t));
   // associate this packet with the virtual component
   // COMPONENT_IEEE802154E_TO_RES so RES can knows it's for it
   packetSent->owner              = COMPONENT_IEEE802154E_TO_SIXTOP;
   // post RES's sendDone task
   scheduler_push_task(task_sixtopNotifSendDone,TASKPRIO_SIXTOP_NOTIF_TXDONE);
   // wake up the scheduler
   SCHEDULER_WAKEUP();
}

// Modified notif_receive signature to add action for CSL testing purposes.
// Packet is removed on endOps in order to not fill all the slots on queue due
// to no sixtop action is defined for receive and process incoming packets.
// Then, we comment this actions here and add remove packet on endOps method.
void notif_receive(OpenQueueEntry_t* packetReceived, uint8_t action) {

   // [CSL-TEST]: comment and add led (orange) blink if OK or led (red) toggle if KO.

   // record the current ASN
   //memcpy(&packetReceived->l2_asn, &ieee154e_vars.asn, sizeof(asn_t));

   // indicate reception to the schedule, to keep statistics
   //schedule_indicateRx(&packetReceived->l2_asn);

   // associate this packet with the virtual component
   // COMPONENT_IEEE802154E_TO_SIXTOP so sixtop can knows it's for it
   //packetReceived->owner          = COMPONENT_IEEE802154E_TO_SIXTOP;

   // post RES's Receive task
   //scheduler_push_task(task_sixtopNotifReceive,TASKPRIO_SIXTOP_NOTIF_RX);

   if (action == 1)
	leds_sync_blink();
   else
    leds_error_toggle();

   // [CSL-TEST]: end test code

   // wake up the scheduler
   SCHEDULER_WAKEUP();
}

//======================================================================
//============================== STATS =================================
//======================================================================

port_INLINE void resetStats() {
   ieee154e_stats.numSyncPkt      =    0;
   ieee154e_stats.numSyncAck      =    0;
   ieee154e_stats.minCorrection   =  127;
   ieee154e_stats.maxCorrection   = -127;
   ieee154e_stats.numTicsOn       =    0;
   ieee154e_stats.numTicsTotal    =    0;
   // do not reset the number of de-synchronizations
}

void updateStats(PORT_SIGNED_INT_WIDTH timeCorrection) {
   // update minCorrection
   if (timeCorrection<ieee154e_stats.minCorrection) {
     ieee154e_stats.minCorrection = timeCorrection;
   }
   // update maxConnection
   if(timeCorrection>ieee154e_stats.maxCorrection) {
     ieee154e_stats.maxCorrection = timeCorrection;
   }
}

//======================================================================
//============================== MISC ==================================
//======================================================================

/**
\brief Changes the state of the IEEE802.15.4e FSM.

Besides simply updating the state global variable,
this function toggles the FSM debug pin.

\param[in] newstate The state the IEEE802.15.4e FSM is now in.
*/
void changeState(ieee154e_state_t newstate) {
   // update the state
   ieee154e_vars.state = newstate;
   // wiggle the FSM debug pin
   switch (ieee154e_vars.state) {
      case S_CSLTXWAKEUPOFFSET:
      case S_CSLTXDATAPREOFFSET:
      case S_CSLTXDATAOFFSET:
         debugpins_fsm_set();
         break;
      case S_SLEEP:
      case S_CSLRXDATAOFFSET:
      case S_CSLRXWAKEUPOFFSET:
         debugpins_fsm_clr();
         break;

      // ------- TX STATES -------

      // Estados usados para la transmisión de tramas WAKE-UP previas a la trama de datos (Wake-Up Sequence).
      case S_CSLTXWAKEUPPREPARE:
      case S_CSLTXWAKEUPREADY:
      case S_CSLTXWAKEUPDELAY:
      case S_CSLTXWAKEUP:

      // Estados usados para la transmisión del paquete de datos y la recepción del ACK.
      case S_CSLTXDATAPREPARE:
      case S_CSLTXDATAREADY:
      case S_CSLTXDATADELAY:
      case S_CSLTXDATA:

      case S_CSLRXACKOFFSET:
      case S_CSLRXACKPREPARE:
      case S_CSLRXACKREADY:
      case S_CSLRXACKLISTEN:
      case S_CSLRXACK:
      case S_CSLTXPROC:

      // ------- RX STATES -------

      // Estados usados para la recepción y tratamiento de la trama de WAKE-UP.
      case S_CSLRXWAKEUPPREPARE:
      case S_CSLRXWAKEUPREADY:
      case S_CSLRXWAKEUPLISTEN:
      case S_CSLRXWAKEUP:
      case S_CSLRXWAKEUPVALIDATE:

      // Estados usados para la recepción del paquete de datos y la transmisión del ACK.
      case S_CSLRXDATAPREPARE:
      case S_CSLRXDATAREADY:
      case S_CSLRXDATALISTEN:
      case S_CSLRXDATA:

      case S_CSLTXACKOFFSET:
      case S_CSLTXACKPREPARE:
      case S_CSLTXACKREADY:
      case S_CSLTXACKDELAY:
      case S_CSLTXACK:
      case S_CSLRXPROC:
         debugpins_fsm_toggle();
         break;
   }
}

/**
\brief Trigger this module to print status information, over serial.

debugPrint_* functions are used by the openserial module to continuously print
status information about several modules in the OpenWSN stack.

\returns TRUE if this function printed something, FALSE otherwise.
*/
bool debugPrint_asn() {
   asn_t output;
   output.byte4         =  ieee154e_vars.asn.byte4;
   output.bytes2and3    =  ieee154e_vars.asn.bytes2and3;
   output.bytes0and1    =  ieee154e_vars.asn.bytes0and1;
   openserial_printStatus(STATUS_ASN,(uint8_t*)&output,sizeof(output));
   return TRUE;
}

/**
\brief Trigger this module to print status information, over serial.

debugPrint_* functions are used by the openserial module to continuously print
status information about several modules in the OpenWSN stack.

\returns TRUE if this function printed something, FALSE otherwise.
*/
bool debugPrint_isSync() {
   uint8_t output=0;
   output = ieee154e_vars.isSync;
   openserial_printStatus(STATUS_ISSYNC,(uint8_t*)&output,sizeof(uint8_t));
   return TRUE;
}

/**
\brief Trigger this module to print status information, over serial.

debugPrint_* functions are used by the openserial module to continuously print
status information about several modules in the OpenWSN stack.

\returns TRUE if this function printed something, FALSE otherwise.
*/
bool debugPrint_macStats() {
   // send current stats over serial
   openserial_printStatus(STATUS_MACSTATS,(uint8_t*)&ieee154e_stats,sizeof(ieee154e_stats_t));
   return TRUE;
}


/**
\brief Housekeeping tasks to do at the end of each slot.

This functions is called once in each slot, when there is nothing more
to do. This might be when an error occured, or when everything went well.
This function resets the state of the FSM so it is ready for the next slot.

Note that by the time this function is called, any received packet should already
have been sent to the upper layer. Similarly, in a Tx slot, the sendDone
function should already have been done. If this is not the case, this function
will do that for you, but assume that something went wrong.
*/

//[CSL] – Modificación de firma del método endSlot.
void endOps() {

   // turn off the radio
   radio_rfOff();

   // clear any pending timer
   radiotimer_cancel();

   // reset capturedTimes
   ieee154e_vars.lastCapturedTime = 0;
   ieee154e_vars.syncCapturedTime = 0;

   //clear vars for duty cycle on this slot
   ieee154e_vars.radioOnTics=0;
   ieee154e_vars.radioOnThisSlot=FALSE;

   // clean up dataToSend
   if (ieee154e_vars.dataToSend!=NULL) {
      // if everything went well, dataToSend was set to NULL in ti9
      // getting here means transmit failed

      // indicate Tx fail to schedule to update stats
      schedule_indicateTx(&ieee154e_vars.asn,FALSE);

      //decrement transmits left counter
      ieee154e_vars.dataToSend->l2_retriesLeft--;

      if (ieee154e_vars.dataToSend->l2_retriesLeft==0) {
    	 // indicate tx fail if no more retries left
         // [CSL-TEST]: comment to avoid led error blinking
    	 //notif_sendDone(ieee154e_vars.dataToSend,E_FAIL);
    	 // [CSL-TEST]: end test code
      } else {
         // return packet to the virtual COMPONENT_SIXTOP_TO_IEEE802154E component
         ieee154e_vars.dataToSend->owner = COMPONENT_SIXTOP_TO_IEEE802154E;
      }

      // CSL - Remove packet for testing because no high entity for packet processing.
      openqueue_freePacketBuffer(ieee154e_vars.dataToSend);

      // reset local variable
      ieee154e_vars.dataToSend = NULL;
   }

   // clean up dataReceived
   if (ieee154e_vars.dataReceived!=NULL) {
      // assume something went wrong. If everything went well, dataReceived
      // would have been set to NULL in ri9.
      // indicate  "received packet" to upper layer since we don't want to loose packets
      notif_receive(ieee154e_vars.dataReceived,0);

      // CSL - Remove packet for testing because no high entity for packet processing.
      openqueue_freePacketBuffer(ieee154e_vars.dataReceived);

      // reset local variable
      ieee154e_vars.dataReceived = NULL;
   }

   // clean up ackToSend
   if (ieee154e_vars.ackToSend!=NULL) {
      // free ackToSend so corresponding RAM memory can be recycled
      openqueue_freePacketBuffer(ieee154e_vars.ackToSend);
      // reset local variable
      ieee154e_vars.ackToSend = NULL;
   }

   // clean up ackReceived
   if (ieee154e_vars.ackReceived!=NULL) {
      // free ackReceived so corresponding RAM memory can be recycled
      openqueue_freePacketBuffer(ieee154e_vars.ackReceived);
      // reset local variable
      ieee154e_vars.ackReceived = NULL;
   }

   // clean up wakeupSend
   if (ieee154e_vars.wakeupToSend!=NULL) {
      // free wakeupToSend so corresponding RAM memory can be recycled
      openqueue_freePacketBuffer(ieee154e_vars.wakeupToSend);
      // reset local variable
      ieee154e_vars.wakeupToSend = NULL;
   }

   // clean up wakeupReceived
   if (ieee154e_vars.wakeupReceived !=NULL) {
      // free wakeupReceived so corresponding RAM memory can be recycled
      openqueue_freePacketBuffer(ieee154e_vars.wakeupReceived);
      // reset local variable
      ieee154e_vars.wakeupReceived = NULL;
   }

   // change state
   changeState(S_SLEEP);

   // update CSL Mode to SLEEP in order to allow new TX or RX.
   ieee154e_vars.cslMode = CSL_SLEEP_MODE;

}

bool ieee154e_isSynch(){
   return ieee154e_vars.isSync;
}

port_INLINE bool ieee154e_processIEs(OpenQueueEntry_t* pkt, uint16_t* lenIE) {
   uint8_t               ptr;
   uint8_t               byte0;
   uint8_t               byte1;
   uint8_t               temp_8b;
   uint8_t               gr_elem_id;
   uint8_t               subid;
   uint16_t              temp_16b;
   uint16_t              len;
   uint16_t              sublen;
   PORT_SIGNED_INT_WIDTH timeCorrection;

   ptr=0;

   //===== header or payload IE header

   //candidate IE header  if type ==0 header IE if type==1 payload IE
   temp_8b    = *((uint8_t*)(pkt->payload)+ptr);
   ptr++;

   temp_16b   = temp_8b + ((*((uint8_t*)(pkt->payload)+ptr))<< 8);
   ptr++;

   *lenIE     = ptr;

   if ((temp_16b & IEEE802154E_DESC_TYPE_PAYLOAD_IE) == IEEE802154E_DESC_TYPE_PAYLOAD_IE){
      // payload IE

      len          = (temp_16b & IEEE802154E_DESC_LEN_PAYLOAD_IE_MASK)>>IEEE802154E_DESC_LEN_PAYLOAD_IE_SHIFT;
      gr_elem_id   = (temp_16b & IEEE802154E_DESC_GROUPID_PAYLOAD_IE_MASK)>>IEEE802154E_DESC_GROUPID_PAYLOAD_IE_SHIFT;
   } else {
      // header IE

      len          = (temp_16b & IEEE802154E_DESC_LEN_HEADER_IE_MASK)>>IEEE802154E_DESC_LEN_HEADER_IE_SHIFT;
      gr_elem_id   = (temp_16b & IEEE802154E_DESC_ELEMENTID_HEADER_IE_MASK)>>IEEE802154E_DESC_ELEMENTID_HEADER_IE_SHIFT;
   }

   *lenIE         += len;

   //===== sub-elements

   switch(gr_elem_id){

      case IEEE802154E_MLME_IE_GROUPID:
         // MLME IE

         do {

            //read sub IE header
            temp_8b     = *((uint8_t*)(pkt->payload)+ptr);
            ptr         = ptr + 1;
            temp_16b    = temp_8b  +(*((uint8_t*)(pkt->payload)+ptr) << 8);
            ptr         = ptr + 1;

            len         = len - 2; //remove header fields len

            if ((temp_16b & IEEE802154E_DESC_TYPE_LONG) == IEEE802154E_DESC_TYPE_LONG){
               // long sub-IE

               sublen   = (temp_16b & IEEE802154E_DESC_LEN_LONG_MLME_IE_MASK)>>IEEE802154E_DESC_LEN_LONG_MLME_IE_SHIFT;
               subid    = (temp_16b & IEEE802154E_DESC_SUBID_LONG_MLME_IE_MASK)>>IEEE802154E_DESC_SUBID_LONG_MLME_IE_SHIFT;
            } else {
               // short sub-IE

               sublen   = (temp_16b & IEEE802154E_DESC_LEN_SHORT_MLME_IE_MASK)>>IEEE802154E_DESC_LEN_SHORT_MLME_IE_SHIFT;
               subid    = (temp_16b & IEEE802154E_DESC_SUBID_SHORT_MLME_IE_MASK)>>IEEE802154E_DESC_SUBID_SHORT_MLME_IE_SHIFT;
            }

            switch(subid){

               case IEEE802154E_MLME_SYNC_IE_SUBID:
                  // Sync IE: ASN and Join Priority

                  if (idmanager_getIsDAGroot()==FALSE) {
                     // ASN
                     asnStoreFromAdv((uint8_t*)(pkt->payload)+ptr);
                     ptr = ptr + 5;
                     // join priority
                     joinPriorityStoreFromAdv(*((uint8_t*)(pkt->payload)+ptr));
                     ptr = ptr + 1;
                  }
                  break;

               case IEEE802154E_MLME_SLOTFRAME_LINK_IE_SUBID:
                  processIE_retrieveSlotframeLinkIE(pkt,&ptr);
                  break;

               case IEEE802154E_MLME_TIMESLOT_IE_SUBID:
                  // to do
                  break;

               default:
                  return FALSE;
                  break;
            }

            len = len - sublen;
         } while(len>0);

         break;

      case IEEE802154E_ACK_NACK_TIMECORRECTION_ELEMENTID:
         // timecorrection IE

         if (
               idmanager_getIsDAGroot()==FALSE &&
               neighbors_isPreferredParent(&(pkt->l2_nextORpreviousHop))
            ) {

            byte0 = *((uint8_t*)(pkt->payload)+ptr);
            ptr++;
            byte1 = *((uint8_t*)(pkt->payload)+ptr);
            ptr++;

            timeCorrection  = (int16_t)((uint16_t)byte1<<8 | (uint16_t)byte0);
            timeCorrection  = (timeCorrection / (PORT_SIGNED_INT_WIDTH)US_PER_TICK);
            timeCorrection  = -timeCorrection;

            synchronizeAck(timeCorrection);
         }
         break;

      default:
         *lenIE = 0; //no header or not recognized.
         return FALSE;
   }

   if(*lenIE>127) {
      // log the error
      openserial_printError(
         COMPONENT_IEEE802154E,
         ERR_HEADER_TOO_LONG,
         (errorparameter_t)*lenIE,
         (errorparameter_t)1
      );
   }
   return TRUE;
}

port_INLINE void joinPriorityStoreFromAdv(uint8_t jp){
  ieee154e_vars.dataReceived->l2_joinPriority = jp;
  ieee154e_vars.dataReceived->l2_joinPriorityPresent = TRUE;
}

port_INLINE void asnStoreFromAdv(uint8_t* asn) {

   // store the ASN
   ieee154e_vars.asn.bytes0and1   =     asn[0]+
                                    256*asn[1];
   ieee154e_vars.asn.bytes2and3   =     asn[2]+
                                    256*asn[3];
   ieee154e_vars.asn.byte4        =     asn[4];

   // determine the current slotOffset
   /*
   Note: this is a bit of a hack. Normally, slotOffset=ASN%slotlength. But since
   the ADV is exchanged in slot 0, we know that we're currently at slotOffset==0
   */
   ieee154e_vars.slotOffset       = 0;
   schedule_syncSlotOffset(ieee154e_vars.slotOffset);
   ieee154e_vars.nextActiveSlotOffset = schedule_getNextActiveSlotOffset();

   /*
   infer the asnOffset based on the fact that
   ieee154e_vars.freq = 11 + (asnOffset + channelOffset)%16
   */
   ieee154e_vars.asnOffset = ieee154e_vars.freq - 11 - schedule_getChannelOffset();
}



/**
/brief Difference between some older ASN and the current ASN.

\param[in] someASN some ASN to compare to the current

\returns The ASN difference, or 0xffff if more than 65535 different
*/
PORT_RADIOTIMER_WIDTH ieee154e_asnDiff(asn_t* someASN) {
   PORT_RADIOTIMER_WIDTH diff;
   INTERRUPT_DECLARATION();
   DISABLE_INTERRUPTS();
   if (ieee154e_vars.asn.byte4 != someASN->byte4) {
      ENABLE_INTERRUPTS();
      return (PORT_RADIOTIMER_WIDTH)0xFFFFFFFF;;
   }

   diff = 0;
   if (ieee154e_vars.asn.bytes2and3 == someASN->bytes2and3) {
      ENABLE_INTERRUPTS();
      return ieee154e_vars.asn.bytes0and1-someASN->bytes0and1;
   } else if (ieee154e_vars.asn.bytes2and3-someASN->bytes2and3==1) {
      diff  = ieee154e_vars.asn.bytes0and1;
      diff += 0xffff-someASN->bytes0and1;
      diff += 1;
   } else {
      diff = (PORT_RADIOTIMER_WIDTH)0xFFFFFFFF;;
   }
   ENABLE_INTERRUPTS();
   return diff;
}

