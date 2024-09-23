#include <stdbool.h>
#include "./libs/klib/kvec.h"
#include "Stack.h"


void InitCellStack(CellStack *stack) {
  kv_init(*stack);
}

void FreeCellStack(CellStack *stack) {
  kv_destroy(*stack);
}

void PushCellStack(CellStack *stack, cell_t value) {
  kv_push(cell_t, *stack, value);
}

cell_t PopCellStack(CellStack *stack) {
  if (kv_size(*stack) > 0) {
    return kv_A(*stack, --kv_size(*stack));
  } else {
    TraceLog(LOG_WARNING, "Stack underflow");
    return (cell_t){0}; /* Return zero-initialized value */
  }
}

bool IsCellStackEmpty(CellStack *stack) {
  return kv_size(*stack) == 0;
}
