/**
DO NOT EDIT DIRECTLY!!

This file was 'objectified' by SCons as a pre-processing
step for the building a Python extension module.

This was done on 2014-10-04 20:16:04.893327.
*/
/**
\brief Webpages for Ohlone

\author Ankur Mehta <mehtank@eecs.berkeley.edu>, September 2010
*/

#ifndef __OHLONEWEBPAGES_H
#define __OHLONEWEBPAGES_H

//=========================== define ==========================================

#define HTTP_LINE(str) {                         \
  if (chunk == ++current_line) {                 \
    memcpy(packet, str, sizeof(str)-1);          \
    len = sizeof(str)-1;                         \
  }                                              \
}

#define HTTP_LINE_REPLACE16(offset, value) {     \
  if (chunk == current_line)                     \
    ohlone_line_replace16(packet+offset, value); \
}

//=========================== typedef =========================================

//=========================== variables =======================================

#include "openwsnmodule_obj.h"
typedef struct OpenMote OpenMote;

//=========================== prototypes ======================================

void     ohlone_webpages_init(void);
uint8_t  ohlone_webpage(uint8_t *getRequest, uint16_t chunk, uint8_t *packet);

#endif
