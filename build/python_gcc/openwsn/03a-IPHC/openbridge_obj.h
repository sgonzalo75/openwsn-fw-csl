/**
DO NOT EDIT DIRECTLY!!

This file was 'objectified' by SCons as a pre-processing
step for the building a Python extension module.

This was done on 2014-10-04 20:14:38.683097.
*/
#ifndef __OPENBRIDGE_H
#define __OPENBRIDGE_H

/**
\addtogroup LoWPAN
\{
\addtogroup OpenBridge
\{
*/

//=========================== define ==========================================

//=========================== typedef =========================================

//=========================== variables =======================================

#include "openwsnmodule_obj.h"
typedef struct OpenMote OpenMote;

//=========================== prototypes ======================================

void openbridge_init(OpenMote* self);
void openbridge_triggerData(OpenMote* self);
void openbridge_sendDone(OpenMote* self, OpenQueueEntry_t* msg, owerror_t error);
void openbridge_receive(OpenMote* self, OpenQueueEntry_t* msg);

/**
\}
\}
*/

#endif
