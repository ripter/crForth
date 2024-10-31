#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "./libs/klib/kvec.h"

#define MAX_WORD_LENGTH 256 // This does NOT include space for the null terminator.

// Define the possible types of values in the stack.
// Cells hold a type and a value. The type tells us how to interpret the value.
#define CELL_TYPE_LIST                                                         \
  X(EMPTY)                                                                     \
  X(NUMBER)                                                                    \
  X(WORD)                                                                      \
  X(BOOL)                                                                      \
  X(ADDRESS)                                                                   \
  X(VARIABLE)                                                                  \
  X(DOSYS)                                                                     \
  X(IFSYS)

typedef enum {
  #define X(name) CELL_TYPE_##name,
    CELL_TYPE_LIST
  #undef X
} CellType;

// Define the type for the cell, the basic data type for the stack.
typedef intptr_t CellValue;

// Define a struct to hold both the value and its type.
typedef struct {
  CellValue value;       // The actual value.
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

const char* CellTypeToName(CellType type);

#endif // STACK_H
