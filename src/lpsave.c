/*  -*- Mode: C/l; -*-                                                      */
/*                                                                          */
/*  lpsave.c                                                                */
/*                                                                          */
/*  © Copyright Jamie A. Jennings 2018.                                     */
/*  LICENSE: MIT License (https://opensource.org/licenses/mit-license.html) */
/*  AUTHOR: Jamie A. Jennings                                               */


#include <limits.h>
#include <ctype.h>
#include <stdio.h>

#include "lptypes.h"
#include "lpcode.h"

#include "lpsave.h"

void saveCharset(const byte *st) {
  int i;
  for (i = 0; i <= UCHAR_MAX; i++) {
    int first = i;
    while (testchar(st, i) && i <= UCHAR_MAX) i++;
    if (i - 1 == first)  /* unary range? */
      printf("%02x ", first);
    else if (i - 1 > first)  /* non-empty range? */
      printf("(%02x %02x) ", first, i - 1);
  }
}

static void saveCapKind(int kind) {
  const char *const modes[] = {
    "close", "position", "constant", "backref",
    "argument", "simple", "table", "function",
    "query", "string", "num", "substitution", "fold",
    "runtime", "group"};
  printf("%s", modes[kind]);
}


static void saveJMP(const Instruction *op, const Instruction *p) {
  printf("-> %d", (int)(p + (p + 1)->offset - op));
}


void saveInstruction(const Instruction *op, const Instruction *p) {
  const char *const names[] = {
    "any", "char", "set",
    "testany", "testchar", "testset",
    "span", "behind",
    "ret", "end",
    "choice", "jmp", "call", "open_call",
    "commit", "partial_commit", "back_commit", "failtwice", "fail", "giveup",
    "fullcapture", "opencapture", "closecapture", "closeruntime", "halt"
  };
  printf("%02ld: %s ", (long)(p - op), names[p->i.code]);
  switch ((Opcode)p->i.code) {
    case IChar: {
      printf("'%c'", p->i.aux);
      break;
    }
    case ITestChar: {
      printf("'%c'", p->i.aux); saveJMP(op, p);
      break;
    }
    case IFullCapture: {
      saveCapKind(getkind(p));
      printf(" (size = %d)  (idx = %d)", getoff(p), p->i.key);
      break;
    }
    case IOpenCapture: {
      saveCapKind(getkind(p));
      printf(" (idx = %d)", p->i.key);
      break;
    }
    case ISet: {
      saveCharset((p+1)->buff);
      break;
    }
    case ITestSet: {
      saveCharset((p+2)->buff); saveJMP(op, p);
      break;
    }
    case ISpan: {
      saveCharset((p+1)->buff);
      break;
    }
    case IOpenCall: {
      printf("-> %d", (p + 1)->offset);
      break;
    }
    case IBehind: {
      printf("%d", p->i.aux);
      break;
    }
    case IJmp: case ICall: case ICommit: case IChoice:
    case IPartialCommit: case IBackCommit: case ITestAny: {
      saveJMP(op, p);
      break;
    }
    default: break;
  }
  printf("\n");
}

void saveInstructions(Instruction *p, int n) {
  Instruction *op = p;
  while (p < op + n) {
    saveInstruction(op, p);
    p += sizei(p);
  }
}

static const char *tagnames[] = {
  "char", "set", "any",
  "true", "false",
  "rep",
  "seq", "choice",
  "not", "and",
  "call", "opencall", "rule", "grammar",
  "behind",
  "capture", "run-time",
  "halt"
};

void saveTree(TTree *tree) {
  int i;
  printf("(%s ", tagnames[tree->tag]);
  switch (tree->tag) {
    case TChar: {
      int c = tree->u.n;
      if (isprint(c))
        printf("'%c')", c);
      else
        printf("%02X)", c);
      break;
    }
    case TSet: {
      saveCharset(treebuffer(tree));
      printf(")");
      break;
    }
    case TOpenCall: case TCall: {
      printf("key: %d)", tree->key);
      break;
    }
    case TBehind: {
      printf("%d ", tree->u.n);
      saveTree(sib1(tree));
      printf(")");
      break;
    }
    case TCapture: {
      printf("kind: %d  key: %d ", tree->cap, tree->key);
      saveTree(sib1(tree));
      printf(")");
      break;
    }
    case TRule: {
      printf("n: %d  key: %d ", tree->cap, tree->key);
      saveTree(sib1(tree));
      printf(")");
      break;  /* do not print next rule as a sibling */
    }
    case TGrammar: {
      TTree *rule = sib1(tree);
      printf("%d ", tree->u.n);  /* number of rules */
      for (i = 0; i < tree->u.n; i++) {
        saveTree(rule);
        rule = sib2(rule);
      }
      assert(rule->tag == TTrue);  /* sentinel */
      printf(")");
      break;
    }
    default: {
      int sibs = numsiblings[tree->tag];
      if (sibs >= 1) {
        saveTree(sib1(tree));
        if (sibs >= 2)
          saveTree(sib2(tree));
      }
      printf(")");
      break;
    }
  }
}

void saveKTable(lua_State *L, int idx) {
  int n, i;
  lua_getuservalue(L, idx);
  if (lua_isnil(L, -1))  /* no ktable? */
    return;
  n = lua_rawlen(L, -1);
  printf("(ktable ");
  for (i = 1; i <= n; i++) {
    lua_rawgeti(L, -1, i);
    if (lua_isstring(L, -1))
      printf("%s ", lua_tostring(L, -1));
    else
      printf("(error %s) ", lua_typename(L, lua_type(L, -1)));
    lua_pop(L, 1);
  }
  printf(")\n");
}

