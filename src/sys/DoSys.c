#include <raylib.h>
#include "Sys.h"

DoSys *CreateDoSys(void) {
  DoSys *doSys = MemAlloc(sizeof(DoSys));
  doSys->loopSrc = CreateString("");
  doSys->limit = 0;
  doSys->index = 0;
  doSys->isNested = false;
  return doSys;
}

void FreeDoSys(DoSys *doSys) {
  FreeString(doSys->loopSrc);
  MemFree(doSys);
}

