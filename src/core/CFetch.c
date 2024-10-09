#include "../crForth.h"


// ( c-addr -- char )
// Fetch the character stored at c-addr and push it to the stack.
void CFetch(KernelState* state, WordMetadata* wordMeta) {
    (void)wordMeta; // UNUSED
    // Pop the address from the stack
    Cell c_addr = PopFromCellStack(&state->dataStack);
    // Fetch the character at the address
    char ch = *(char*)c_addr.value;
    // Push the character onto the stack
    PushToCellStack(&state->dataStack, (Cell){ch, CELL_TYPE_WORD});
}
