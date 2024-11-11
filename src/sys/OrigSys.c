#include <raylib.h>
#include "Sys.h"


OrigSys *CreateOrigSys(void) {
  OrigSys *this = MemAlloc(sizeof(OrigSys));
  this->flag = false;
  this->src = CreateString("");
  this->stream = NULL;
  return this;
}


void FreeOrigSys(OrigSys *origSys) {
  FreeString(origSys->src);
  MemFree(origSys);
}
