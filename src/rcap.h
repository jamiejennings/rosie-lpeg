/*  -*- Mode: C/l; -*-                                                       */
/*                                                                           */
/*  rcap.h                                                                   */
/*                                                                           */
/*  © Copyright IBM Corporation 2017.                                        */
/*  LICENSE: MIT License (https://opensource.org/licenses/mit-license.html)  */
/*  AUTHOR: Jamie A. Jennings                                                */


#if !defined(rcap_h)
#define rcap_h


int debug_Fullcapture(CapState *cs, luaL_Buffer *buf, int count);
int debug_Close(CapState *cs, luaL_Buffer *buf, int count);
int debug_Open(CapState *cs, luaL_Buffer *buf, int count);

int json_Fullcapture(CapState *cs, luaL_Buffer *buf, int count);
int json_Close(CapState *cs, luaL_Buffer *buf, int count);
int json_Open(CapState *cs, luaL_Buffer *buf, int count);

int byte_Fullcapture(CapState *cs, luaL_Buffer *buf, int count);
int byte_Close(CapState *cs, luaL_Buffer *buf, int count);
int byte_Open(CapState *cs, luaL_Buffer *buf, int count);


#endif
