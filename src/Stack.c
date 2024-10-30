#include <stdbool.h>
#include <raylib.h>
#include "./libs/klib/kvec.h"
#include "Stack.h"



void InitCellStack(CellStack *stack) {
  kv_init(*stack);
}

void FreeCellStack(CellStack *stack) {
  kv_destroy(*stack);
}

void CellStackPush(CellStack *stack, Cell value) {
  kv_push(Cell, *stack, value);
}

Cell CellStackPop(CellStack *stack) {
  if (kv_size(*stack) > 0) {
    return kv_A(*stack, --kv_size(*stack));
  } else {
    return (Cell){0, CELL_TYPE_EMPTY};
  }
}

bool IsCellStackEmpty(CellStack *stack) {
  return kv_size(*stack) == 0;
}

size_t CellStackSize(CellStack *stack) {
  return kv_size(*stack);
}

Cell CellStackPeek(CellStack *stack, size_t index) {
  if (index < kv_size(*stack)) {
    return kv_A(*stack, index);
  } else {
    return (Cell){0, CELL_TYPE_EMPTY};
  }
}

const char *CellTypeToName(CellType cellType) {
  switch (cellType) {
  #define X(name) case CELL_TYPE_##name: return #name;
    CELL_TYPE_LIST
  #undef X
  default:
    return "UNKNOWN";
  }
}

