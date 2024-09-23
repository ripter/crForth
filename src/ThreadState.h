#ifndef THREADSTATE_H
#define THREADSTATE_H

#include "./Dictionary.h"
#include "./Stack.h"

typedef struct {
  Dictionary *dict;
  CellStack *dataStack;
  CellStack *returnSack;
} ThreadState;

#endif // THREADSTATE_H
