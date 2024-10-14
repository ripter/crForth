#include <string.h>
#include "CoreWords.h"

#include "../crForth.h"
#include "../WordMetadata.h"

// Adds the Core Words to the dictionary.
// Words *MUST* be lowercase to be found.
void AddCoreWords(KernelState *state) {
  AddWordToDictionary(&state->dict, InitWordMetadata("+",         (xt_func_ptr)Add,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("-",         (xt_func_ptr)Subtract,      false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(".",         (xt_func_ptr)Dot,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("skip",      (xt_func_ptr)Skip,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("0skip",     (xt_func_ptr)SkipOnZero,    false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("branch",    (xt_func_ptr)Branch,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("?branch",   (xt_func_ptr)BranchNZ,       false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(".s",        (xt_func_ptr)DotS,          true,   NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(":",         (xt_func_ptr)Colon,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(";",         (xt_func_ptr)SemiColon,     true,   NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("words",     (xt_func_ptr)Words,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("see",       (xt_func_ptr)See,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("immediate", (xt_func_ptr)Immediate,     false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("latest",    (xt_func_ptr)Latest,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("emit",      (xt_func_ptr)Emit,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("c@",        (xt_func_ptr)CFetch,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("create",    (xt_func_ptr)Create,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("does>",     (xt_func_ptr)Does,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("dup",       (xt_func_ptr)Dup,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("drop",      (xt_func_ptr)Drop,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("swap",      (xt_func_ptr)Swap,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(">r",        (xt_func_ptr)ToR,           false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("r>",        (xt_func_ptr)RFrom,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(".sr",       (xt_func_ptr)DotSR,         true,   NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(".sd",       (xt_func_ptr)DotSD,         true,   NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("<",         (xt_func_ptr)LessThan,      false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata(">",         (xt_func_ptr)GreaterThan,   false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("<>",        (xt_func_ptr)NotEqual,      false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("=",         (xt_func_ptr)Equal,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("postpone",  (xt_func_ptr)Postpone,      true,   NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("'",         (xt_func_ptr)Tick,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("execute",   (xt_func_ptr)Execute,       false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("here",      (xt_func_ptr)Here,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("\\",        (xt_func_ptr)Backslash,     true,   NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("(",         (xt_func_ptr)Paren,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("invert",    (xt_func_ptr)Invert,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("or",        (xt_func_ptr)BitOr,         false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("and",       (xt_func_ptr)BitAnd,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("xor",       (xt_func_ptr)BitXor,        false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("lshift",    (xt_func_ptr)BitShiftLeft,  false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("rshift",    (xt_func_ptr)BitShiftRight, false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("0=",        (xt_func_ptr)ZeroEquals,    false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("if",        (xt_func_ptr)IF,            false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("else",      (xt_func_ptr)ELSE,          false,  NULL));
  AddWordToDictionary(&state->dict, InitWordMetadata("then",      (xt_func_ptr)THEN,          false,  NULL));
}
