#include <stddef.h>
#include <stdbool.h>

typedef _Bool bool;


struct secure_st
{
  void* ptr = NULL ;
  bool  avl = false;
}

#include "../AKeDeX/AKeSaX.h"


Secure* s_wrap (void* p)
{
  Secure* s = (Secure) malloc(sizeof(struct secure_st));
  
  s->ptr = p   ;
  s->avl = true;

  return s;
}


bool s_check (Secure* s)
{
  return s->avl;
}

void* s_uwrap (Secure* s)
{
  if (s_check(s)) return s->ptr;
  return NULL;
}


void* s_del (Secure* s)
{
  void* aux = s->ptr;

  s->ptr = NULL ;
  s->avl = false;

  return aux;
}

void* s_ass (Secure* s, void* p)
{
  s->ptr = p   ;
  s->avl = true;

  return s->ptr;
}
