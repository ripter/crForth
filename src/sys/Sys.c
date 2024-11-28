#include "Sys.h"

// Frees any type of Sys struct.
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

// Ends the stream of any type of Sys struct.
void EndSysStream(Cell *cell) {
  switch (cell->type) {
    case CELL_TYPE_COLON_SYS:
      fseek(((OrigSys *)cell->value)->stream, 0, SEEK_END);
      break;
    case CELL_TYPE_LOOP_SYS:
      fseek(((LoopSys *)cell->value)->stream, 0, SEEK_END);
      break;
    case CELL_TYPE_DO_SYS:
      fseek(((DoSys *)cell->value)->stream, 0, SEEK_END);
      break;
    case CELL_TYPE_ORIG_SYS:
      fseek(((OrigSys *)cell->value)->stream, 0, SEEK_END);
      break;
    default:
      fprintf(stderr, "EndSysStream: Unknown type: %s\n", CellTypeToName(cell->type));
  }
}
