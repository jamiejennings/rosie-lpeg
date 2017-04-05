/*
** $Id: lpcap.h,v 1.2 2015/02/27 17:13:17 roberto Exp $
*/

#if !defined(lpcap_h)
#define lpcap_h

#include "lptypes.h"

/* kinds of captures -- 16 at most, since the kind must fit into 4 bits! */
typedef enum CapKind {
  Cclose, Cposition, Cconst, Cbackref, Carg, Csimple, Ctable, Cfunction,
  Cquery, Cstring, Cnum, Csubst, Cfold, Cruntime, Cgroup, Crosiecap
} CapKind;


typedef struct Capture {
  const char *s;  /* subject position */
  unsigned short idx;  /* extra info (group name, arg index, etc.) */
  unsigned short flags;		/* rosie extension */
  byte kind;  /* kind of capture */
  byte siz;  /* size of full capture + 1 (0 = not a full capture) */
} Capture;


typedef struct CapState {
  Capture *cap;  /* current capture */
  Capture *ocap;  /* (original) capture list */
  lua_State *L;
  int ptop;  /* index of last argument to 'match' */
  const char *s;  /* original string */
  int valuecached;  /* value stored in cache slot */
} CapState;


int runtimecap (CapState *cs, Capture *close, const char *s, int *rem);
int getcaptures (lua_State *L, const char *s, const char *r, int ptop);
int finddyncap (Capture *cap, Capture *last);

#define isclosecap(cap)	(captype(cap) == Cclose)
#define isfullcap(cap)	((cap)->siz != 0)
#define captype(cap)	((cap)->kind)

/* Rosie additions */

/* #include "rbuf.h" */
#include "lauxlib.h"

typedef struct {  
  int (*Open)(CapState *cs, luaL_Buffer *buf, int count);
  int (*Fullcapture)(CapState *cs, luaL_Buffer *buf, int count);
  int (*Close)(CapState *cs, luaL_Buffer *buf, int count);
} encoder_functions;
 
typedef enum r_status { 
     /* OK must be first so that its value is 0 */ 
     ROSIE_OK, ROSIE_OPEN_ERROR, ROSIE_CLOSE_ERROR, ROSIE_FULLCAP_ERROR
} r_status;

int r_match (lua_State *L);
int r_getcaptures(lua_State *L, const char *s, const char *r, int ptop, int encoding);
int r_lua_decode (lua_State *L);

#endif


