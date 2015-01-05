
    #include "opendefs.h"
    #include "c6t.h"
#include "cinfo.h"
#include "cleds.h"
#include "cwellknown.h"
#include "techo.h"
#include "uecho.h"

    void openapps_init(void) {
       c6t_init();
   cinfo_init();
   cleds__init();
   cwellknown_init();
   techo_init();
   uecho_init();
    }
    