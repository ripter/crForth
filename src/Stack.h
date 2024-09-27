#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "./libs/klib/kvec.h"

// Define the type for the cell, the basic data type for the stack.
typedef intptr_t cell_t;
// Define the type for the stack.
typedef kvec_t(cell_t) CellStack;


void InitCellStack(CellStack *stack);
void FreeCellStack(CellStack *stack);
void PushToCellStack(CellStack *stack, cell_t value);
cell_t PopFromCellStack(CellStack *stack);
bool IsCellStackEmpty(CellStack *stack);
size_t CellStackSize(CellStack *stack);
cell_t ViewCellStack(CellStack *stack, size_t index);


#endif // STACK_H
