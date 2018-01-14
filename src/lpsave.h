/*  -*- Mode: C/l; -*-                                                      */
/*                                                                          */
/*  lpsave.h                                                                */
/*                                                                          */
/*  © Copyright Jamie A. Jennings 2018.                                     */
/*  LICENSE: MIT License (https://opensource.org/licenses/mit-license.html) */
/*  AUTHOR: Jamie A. Jennings                                               */



#if !defined(lpsave_h)
#define lpsave_h


#include "lptree.h"
#include "lpvm.h"


void saveTree(TTree *tree);
void saveKTable(lua_State *L, int idx);
void saveCharset(const byte *st);
void saveInstruction(const Instruction *op, const Instruction *p);
void saveInstructions(Instruction *p, int n);


#endif

