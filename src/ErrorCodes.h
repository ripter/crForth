#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#define ERR_EMPTY_STACK "Error 001: branch requires an address on the return stack. But found an Empty return stack instead.\n"
#define ERR_INVALID_WORD_ON_RETURN_STACK "Error 002: Return Stack did not contain an address. Expected to find ( R: u c-addr )\n"
#define ERR_WORD_NOT_FOUND "Error 003: Word not found: %s\n"

#endif // ERROR_CODES_H
