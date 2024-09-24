#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "raylib.h"
#include "./libs/klib/kvec.h"

#include "crForth.h"

typedef kvec_t(cell_t) CellStack;


void InitCellStack(CellStack *stack);
void FreeCellStack(CellStack *stack);
void PushCellStack(CellStack *stack, cell_t value);
cell_t PopCellStack(CellStack *stack);
bool IsCellStackEmpty(CellStack *stack);
size_t CellStackSize(CellStack *stack);
cell_t ViewCellStack(CellStack *stack, size_t index);


#endif // STACK_H
