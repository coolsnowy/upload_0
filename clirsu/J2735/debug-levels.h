#ifndef __DEBUG_LEVELS_H__
#define __DEBUG_LEVELS_H__

#define D_MASTER !0

#ifndef D_LOCAL
  #define D_LOCAL D_ALL
//#define D_LOCAL D_WARN
#endif

#include "linux/cohda/debug.h"

// Some other handy levels
#define D_API    (D_INFO)
#define D_INTERN (D_DEBUG)
#define D_DBG    (D_DEBUG)
#define D_TST    (D_VERBOSE)
//#define D_TST   (D_WARN)

#endif //__DEBUG_LEVELS_H__

