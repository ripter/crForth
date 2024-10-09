#include <stdbool.h>
#include "raylib.h"
#include "./libs/klib/kvec.h"
#include "Stack.h"


// void InitCell(cell_t value, CellType type, Cell *cell) {
//   cell->value = value;
//   cell->type = type;
// }

// void FreeCell(Cell *cell) {

// }


void InitCellStack(CellStack *stack) {
  kv_init(*stack);
}

void FreeCellStack(CellStack *stack) {
  kv_destroy(*stack);
}

void PushToCellStack(CellStack *stack, Cell value) {
  kv_push(Cell, *stack, value);
}

Cell PopFromCellStack(CellStack *stack) {
  if (kv_size(*stack) > 0) {
    return kv_A(*stack, --kv_size(*stack));
  } else {
    TraceLog(LOG_WARNING, "Stack underflow");
    return (Cell){0}; /* Return zero-initialized value */
  }
}

bool IsCellStackEmpty(CellStack *stack) {
  return kv_size(*stack) == 0;
}

size_t CellStackSize(CellStack *stack) {
  return kv_size(*stack);
}

Cell ViewCellStack(CellStack *stack, size_t index) {
  if (index < kv_size(*stack)) {
    return kv_A(*stack, index);
  } else {
    TraceLog(LOG_WARNING, "Index out of bounds");
    return (Cell){0}; /* Return zero-initialized value */
  }
}
