#include "Sys.h"

void FreeSys(Cell *cell) {
  switch (cell->type) {
    case CELL_TYPE_COLON_SYS:
      FreeColonSys((ColonSys *)cell->value);
      break;
    case CELL_TYPE_LOOP_SYS:
      FreeLoopSys((LoopSys *)cell->value);
      break;
    case CELL_TYPE_DO_SYS:
      FreeDoSys((DoSys *)cell->value);
      break;
    case CELL_TYPE_ORIG_SYS:
      FreeOrigSys((OrigSys *)cell->value);
      break;
    default:
      fprintf(stderr, "FreeSys: Unknown type: %s\n", CellTypeToName(cell->type));
  }
}
