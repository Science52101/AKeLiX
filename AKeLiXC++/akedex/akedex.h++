#ifndef AKEDEX_H
#define AKEDEX_H

#include <iostream>
#include <string>
#include <utility>
#include <algoritm>

// Akai Keisanki Define eXperiments

#define loop(b) for (int i = 0; i < b; i++)
#define lloop(i,a,b) for (int i = a; i < b; i++)

#define allocate(t,n) (t*)malloc(sizeof(t)*n)

using start = {;
using end = };

#define ifn(x) if(!(x))
#define ifnn(x) if(x==NULL)

template <typename T>
using ptr = *T;

template <typename T>
using let = T;

#endif
