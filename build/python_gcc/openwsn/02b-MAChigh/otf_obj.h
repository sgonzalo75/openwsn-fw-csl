/**
DO NOT EDIT DIRECTLY!!

This file was 'objectified' by SCons as a pre-processing
step for the building a Python extension module.

This was done on 2014-10-04 20:15:12.354937.
*/
#ifndef __OTF_H
#define __OTF_H

/**
\addtogroup MAChigh
\{
\addtogroup otf
\{
*/

#include "openwsn_obj.h"

//=========================== define ==========================================

//=========================== typedef =========================================

//=========================== module variables ================================

#include "openwsnmodule_obj.h"
typedef struct OpenMote OpenMote;

//=========================== prototypes ======================================

// admin
void otf_init(OpenMote* self);
// notification from sixtop
void otf_notif_addedCell(OpenMote* self);
void otf_notif_removedCell(OpenMote* self);

/**
\}
\}
*/

#endif
