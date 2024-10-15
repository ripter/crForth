#include "../crForth.h"

// ( x1 -- x2 ) 
// Invert all bits of x1, giving its logical inverse x2. 
// https://forth-standard.org/standard/core/INVERT
void Invert(KernelState *state) {
  Cell a = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){~a.value, a.type});
}

// ( x1 x2 -- x3 ) 
// x3 is the bitwise inclusive OR of x1 and x2.
// https://forth-standard.org/standard/core/OR
void BitOr(KernelState *state) {
  Cell a = CellStackPop(&state->dataStack);
  Cell b = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value | b.value, a.type});
}

// ( x1 x2 -- x3 )
// x3 is the bit-by-bit logical "and" of x1 with x2. 
// https://forth-standard.org/standard/core/AND
void BitAnd(KernelState *state) {
  Cell a = CellStackPop(&state->dataStack);
  Cell b = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value & b.value, a.type});
}

// ( x1 x2 -- x3 )
// x3 is the bit-by-bit exclusive-or of x1 with x2.
// https://forth-standard.org/standard/core/XOR
void BitXor(KernelState *state) {
  Cell a = CellStackPop(&state->dataStack);
  Cell b = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value ^ b.value, a.type});
}


// ( x1 u -- x2 )
// Perform a logical left shift of u bit-places on x1, giving x2. 
// Put zeroes into the least significant bits vacated by the shift. 
// An ambiguous condition exists if u is greater than or equal to the number of bits in a cell. 
// https://forth-standard.org/standard/core/LSHIFT
void BitShiftLeft(KernelState *state) {
  Cell a = CellStackPop(&state->dataStack);
  Cell b = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value << b.value, a.type});
}


// ( x1 u -- x2 ) 
// Perform a logical right shift of u bit-places on x1, giving x2. 
// Put zeroes into the most significant bits vacated by the shift. 
// An ambiguous condition exists if u is greater than or equal to the number of bits in a cell. 
// https://forth-standard.org/standard/core/RSHIFT
void BitShiftRight(KernelState *state) {
  Cell a = CellStackPop(&state->dataStack);
  Cell b = CellStackPop(&state->dataStack);
  CellStackPush(&state->dataStack, (Cell){a.value >> b.value, a.type});
}
