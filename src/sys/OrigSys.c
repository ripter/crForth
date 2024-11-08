#include <raylib.h>
#include "Sys.h"


OrigSys *CreateOrigSys(void) {
  OrigSys *origSys = MemAlloc(sizeof(OrigSys));
  origSys->flag = false;
  origSys->src = CreateString("");
  return origSys;
}


void FreeOrigSys(OrigSys *origSys) {
  FreeString(origSys->src);
  MemFree(origSys);
}
