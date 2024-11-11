#include <raylib.h>
#include "Sys.h"

DoSys *CreateDoSys(void) {
  DoSys *this = MemAlloc(sizeof(DoSys));
  this->src = CreateString("");
  this->limit = 0;
  this->index = 0;
  this->isNested = false;
  this->stream = NULL;
  return this;
}

void FreeDoSys(DoSys *doSys) {
  FreeString(doSys->src);
  MemFree(doSys);
}

