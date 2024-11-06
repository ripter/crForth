#include "Sys.h"


ColonSys *CreateColonSys(const char* newName, String *src) {
  ColonSys *colonSys = (ColonSys *)MemAlloc(sizeof(ColonSys));
  colonSys->name = CreateString(newName);
  colonSys->src = src;
  return colonSys;
}

void FreeColonSys(ColonSys *colonSys) {
  if (colonSys == NULL) { return; }
  FreeString(colonSys->name);
  MemFree(colonSys);
}
