/**
DO NOT EDIT DIRECTLY!!

This file was 'objectified' by SCons as a pre-processing
step for the building a Python extension module.

This was done on 2014-10-04 20:14:15.366054.
*/
#ifndef __SCHEDULER_H
#define __SCHEDULER_H

/**
\addtogroup kernel
\{
\addtogroup Scheduler
\{
*/

#include "openwsn_obj.h"

//=========================== define ==========================================

typedef enum {
   TASKPRIO_NONE                   = 0x00,
   // tasks trigger by radio
   TASKPRIO_SIXTOP_NOTIF_RX        = 0x01,
   TASKPRIO_SIXTOP_NOTIF_TXDONE    = 0x02,
   // tasks triggered by timers
   TASKPRIO_SIXTOP                 = 0x03,
   TASKPRIO_RPL                    = 0x04,
   TASKPRIO_TCP_TIMEOUT            = 0x05,
   TASKPRIO_COAP                   = 0x06,
   TASKPRIO_ADAPTIVE_SYNC          = 0x07, 
   TASKPRIO_OTF                    = 0x08,
   // tasks trigger by other interrupts
   TASKPRIO_BUTTON                 = 0x09,
   TASKPRIO_SIXTOP_TIMEOUT         = 0x0a,
   TASKPRIO_MAX                    = 0x0b,
} task_prio_t;

#define TASK_LIST_DEPTH      10

//=========================== typedef =========================================

typedef void (*task_cbt)(OpenMote* self);

typedef struct task_llist_t {
   task_cbt             cb;
   task_prio_t          prio;
   void*                next;
} taskList_item_t;

//=========================== module variables ================================

typedef struct {
   taskList_item_t      taskBuf[TASK_LIST_DEPTH];
   taskList_item_t*     task_list;
   uint8_t              numTasksCur;
   uint8_t              numTasksMax;
} scheduler_vars_t;

typedef struct {
   uint8_t              numTasksCur;
   uint8_t              numTasksMax;
} scheduler_dbg_t;

#include "openwsnmodule_obj.h"
typedef struct OpenMote OpenMote;

//=========================== prototypes ======================================

// public functions
void scheduler_init(OpenMote* self);
void scheduler_start(OpenMote* self);
void scheduler_push_task(OpenMote* self, task_cbt task_cb, task_prio_t prio);

// interrupt handlers
void isr_ieee154e_newSlot(OpenMote* self);
void isr_ieee154e_timer(OpenMote* self);
void isr_adc(void);
#ifdef ISR_GYRO
void isr_gyro(void);
#endif
#ifdef ISR_LARGE_RANGE_ACCEL
void isr_large_range_accel(void);
#endif
#ifdef ISR_BUTTON
void isr_button(void);
#endif

/**
\}
\}
*/

#endif
