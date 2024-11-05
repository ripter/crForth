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

/**
 * @brief Peeks at an element in the specified stack without modifying it.
 *
 * This function retrieves the `Cell` at a given index from the `CellStack`. 
 * The index is zero-based and is relative to the bottom of the stack, meaning
 * `index 0` corresponds to the base (first) element. If the index is out of 
 * bounds (greater than or equal to the size of the stack), the function returns 
 * an empty `Cell` with a type `CELL_TYPE_EMPTY` and value `0`.
 *
 * @param stack A pointer to the `CellStack` to be peeked at.
 * @param index The zero-based index of the cell to retrieve.
 * @return The `Cell` at the specified index, or an empty `Cell` if the index is out of bounds.
 */

Cell CellStackPeek(CellStack *stack, size_t index);

const char* CellTypeToName(CellType type);

#endif // STACK_H
