#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "./libs/klib/kvec.h"

// Define the possible types of values in the stack.
typedef enum {
  CELL_TYPE_NUMBER,
  CELL_TYPE_WORD,
  CELL_TYPE_ADDRESS,
  CELL_TYPE_BOOL,
  CELL_TYPE_VARIABLE,
  CELL_TYPE_DOSYS,
} CellType;

// Define the type for the cell, the basic data type for the stack.
typedef intptr_t cell_t;

// Define a struct to hold both the value and its type.
typedef struct {
  cell_t value;       // The actual value.
  CellType type;     // The type of the value.
} Cell;

// Define the type for the stack.
typedef kvec_t(Cell) CellStack;

// Cell Stack
void InitCellStack(CellStack *stack);
void FreeCellStack(CellStack *stack);
void CellStackPush(CellStack *stack, Cell value);
Cell CellStackPop(CellStack *stack);
bool IsCellStackEmpty(CellStack *stack);
size_t CellStackSize(CellStack *stack);
Cell CellStackPeek(CellStack *stack, size_t index);


#endif // STACK_H
