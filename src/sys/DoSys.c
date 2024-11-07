#include <raylib.h>
#include "Sys.h"

DoSys *CreateDoSys(void) {
  DoSys *doSys = MemAlloc(sizeof(DoSys));
  doSys->src = CreateString("");
  doSys->limit = 0;
  doSys->index = 0;
  doSys->isNested = false;
  return doSys;
}

void FreeDoSys(DoSys *doSys) {
  FreeString(doSys->src);
  MemFree(doSys);
}

