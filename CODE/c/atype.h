#ifndef ATYPE_H_INCLUDED
#define ATYPE_H_INCLUDED
#include <stdio.h>
#define N 32
#define M 32
#include <math.h>
#include <stdlib.h>
#include <time.h>
int fatherfind(int x,int y);
void setgraph(int vertical,int horizontal);
void printG();
void printS();
int estimate(int v);
int expand(int v);
void pseudoexpand(int v);
void SAA(int v,float T,float r,float Tmin);
int deal(int o,int p,int c[],int vertical,int horizontal);
#endif
