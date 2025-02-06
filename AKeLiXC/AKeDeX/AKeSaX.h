#ifndef AKEDEX_SAX
#define AKEDEX_SAX

#include <stdbool.h>

typedef secure_st* Secure;

Secure s_wrap (void *);

bool   s_check (Secure);
void * s_uwrap (Secure);

void * s_del (Secure        );
void * s_ass (Secure, void *);

#endif
