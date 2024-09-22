#ifndef THREADSTATE_H
#define THREADSTATE_H

#include "./Dictionary.h"

typedef struct {
  Dictionary *dict;
  void *dataStack;
  void *returnSack;
} ThreadState;

#endif // THREADSTATE_H
