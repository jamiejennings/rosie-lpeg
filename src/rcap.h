/*  -*- Mode: C/l; -*-                                                       */
/*                                                                           */
/*  rcap.h                                                                   */
/*                                                                           */
/*  © Copyright IBM Corporation 2017.                                        */
/*  LICENSE: MIT License (https://opensource.org/licenses/mit-license.html)  */
/*  AUTHOR: Jamie A. Jennings                                                */


#if !defined(rcap_h)
#define rcap_h


int debug_Fullcapture(CapState *cs, rBuffer *buf, int count);
int debug_Close(CapState *cs, rBuffer *buf, int count, const char *start);
int debug_Open(CapState *cs, rBuffer *buf, int count);

int json_Fullcapture(CapState *cs, rBuffer *buf, int count);
int json_Close(CapState *cs, rBuffer *buf, int count, const char *start);
int json_Open(CapState *cs, rBuffer *buf, int count);

int byte_Fullcapture(CapState *cs, rBuffer *buf, int count);
int byte_Close(CapState *cs, rBuffer *buf, int count, const char *start);
int byte_Open(CapState *cs, rBuffer *buf, int count);


#endif
