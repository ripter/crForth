#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#define ERR_UNKNOWN_WORD                  "Error 001: Unknown word: %s\n"
#define ERR_EMPTY_STACK                   "Error 002: branch requires an address on the return stack. But found an Empty return stack instead.\n"
#define ERR_INVALID_WORD_ON_RETURN_STACK  "Error 003: Return Stack did not contain an address. Expected to find ( R: u c-addr )\n"
#define ERR_WORD_NOT_FOUND                "Error 004: Word not found: %s\n"
#define ERR_EMPTY_FORTH_STRING            "Error 005: Expected a string of Forth code, found an empty string instead.\n"
#define ERROR_INVALID_NUMBER              "Error 006: Invalid number '%s'.\n"
#define ERR_MISSING_LENGTH                "Error 007: Missing length (u) for evaluation.\n"
#define ERR_MISSING_ADDRESS               "Error 008: Missing address (c-addr) for evaluation.\n"
#define ERR_INVALID_LENGTH                "Error 009: Invalid length type for evaluation.\n"
#define ERR_INVALID_ADDRESS               "Error 010: Invalid address type for evaluation.\n"
#define ERR_ZERO_LENGTH                   "Error 011: Length for evaluation cannot be zero.\n"

#define BAIL_IF_EMPTY_RETURN_STACK()                                           \
  if (IsCellStackEmpty(&state->returnStack)) {                                 \
    fprintf(state->errorStream, ERR_EMPTY_STACK);                              \
    return;                                                                    \
  }                                                                            \

#define BAIL_IF_RETURN_STACK_LESS_THAN(n)                                      \
  if (CellStackSize(&state->returnStack) < n) {                                 \
    fprintf(state->errorStream, ERR_INVALID_WORD_ON_RETURN_STACK);             \
    return;                                                                    \
  }                                                                            \

#define BAIL_IF_EMPTY_DATA_STACK()                                             \
  if (IsCellStackEmpty(&state->dataStack)) {                                   \
    fprintf(state->errorStream, ERR_EMPTY_STACK);                              \
    return;                                                                    \
  }                                                                            \



#endif // ERROR_CODES_H
