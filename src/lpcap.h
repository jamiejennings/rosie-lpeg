/*
** $Id: lpcap.h,v 1.2 2015/02/27 17:13:17 roberto Exp $
*/

#if !defined(lpcap_h)
#define lpcap_h

#include "lptypes.h"

/* kinds of captures -- 16 at most, since the kind must fit into 4 bits! */
typedef enum CapKind {
  Cclose, Cposition, /* Cconst, */ Cbackref, Carg, Csimple, Ctable, Cfunction,
  Cquery, Cstring, Cnum, /* Csubst, */ Cfold, Cruntime, Cgroup,
  Crosiecap, Crosieconst, Cfinal /* rosie */
} CapKind;


typedef struct Capture {
  const char *s;  /* subject position */
/*   unsigned short idx;  /\* extra info (group name, arg index, etc.) *\/ */
  capidx_t idx;  /* extra info (group name, arg index, etc.) */
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
capidx_t finddyncap (Capture *cap, Capture *last);

#define isfinalcap(cap)	(captype(cap) == Cfinal)
#define isclosecap(cap)	(captype(cap) == Cclose)
#define isfullcap(cap)	((cap)->siz != 0)
#define captype(cap)	((cap)->kind)

/* Rosie additions */

#define isopencap(cap)	((captype(cap) != Cclose) && ((cap)->siz == 0))

#include "rbuf.h"

/* Two arrays are STATICALLY ALLOCATED with R_MAXDEPTH elements
 * in lpcap.c, where it is used by caploop().
 *
 * FUTURE: Allocate a small number of entries that will accomodate
 * many use cases, perhaps 30 or so.  Dynamically allocate more when
 * needed, up to R_MAXDEPTH at most.
 */
#define R_MAXDEPTH USHRT_MAX	/* max nesting depth for patterns (was 200) */

typedef struct {  
  int (*Open)(CapState *cs, rBuffer *buf, int count);
  int (*Fullcapture)(CapState *cs, rBuffer *buf, int count);
  int (*Close)(CapState *cs, rBuffer *buf, int count, const char *start);
} encoder_functions;
 
typedef enum r_status { 
     /* OK must have the value 0 */ 
     ROSIE_HALT = -1, ROSIE_OK, ROSIE_OPEN_ERROR, ROSIE_CLOSE_ERROR, ROSIE_FULLCAP_ERROR
} r_status;

int r_match (lua_State *L);
int r_getcaptures(lua_State *L, const char *s, const char *r, int ptop, int etype, size_t len);
int r_lua_decode (lua_State *L);

#endif


