#include <raylib.h>
#include "Sys.h"

LoopSys *CreateLoopSys(CellValue limit, CellValue index) {
  LoopSys *this = MemAlloc(sizeof(LoopSys));
  this->src = CreateString("");
  this->limit = limit;
  this->index = index;
  this->stream = NULL;
  return this;
}

void FreeLoopSys(LoopSys *this) {
  if (this->stream != NULL) {
    fclose(this->stream);
  }
  FreeString(this->src);
  MemFree(this);
}
