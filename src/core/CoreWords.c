#include <string.h>
#include "CoreWords.h"

#include "../crForth.h"

// Adds the Core Words to the dictionary.
// Words *MUST* be lowercase to be found.
// Side note: this list is not alphabetized, its the order they were implemented. I find the history of things interesting.
void AddCoreWords(KernelState *state) {
  AddWordToDictionary(&state->dict, CreateForthWord("+",               (xt_func_ptr)Add,           false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("-",               (xt_func_ptr)Subtract,      false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(".",               (xt_func_ptr)Dot,           false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("skip",            (xt_func_ptr)Skip,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("0skip",           (xt_func_ptr)SkipOnZero,    false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("branch",          (xt_func_ptr)Branch,        false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("?branch",         (xt_func_ptr)BranchNZ,      false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(".s",              (xt_func_ptr)DotS,          true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(":",               (xt_func_ptr)Colon,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(";",               (xt_func_ptr)SemiColon,     true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("words",           (xt_func_ptr)Words,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("see",             (xt_func_ptr)See,           false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("immediate",       (xt_func_ptr)Immediate,     false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("latest",          (xt_func_ptr)Latest,        false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("emit",            (xt_func_ptr)Emit,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("c@",              (xt_func_ptr)CFetch,        false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("create",          (xt_func_ptr)Create,        false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("does>",           (xt_func_ptr)Does,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("dup",             (xt_func_ptr)Dup,           false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("drop",            (xt_func_ptr)Drop,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("swap",            (xt_func_ptr)Swap,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(">r",              (xt_func_ptr)ToR,           false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("r>",              (xt_func_ptr)RFrom,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(".sr",             (xt_func_ptr)DotSR,         true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(".sd",             (xt_func_ptr)DotSD,         true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("<",               (xt_func_ptr)LessThan,      false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord(">",               (xt_func_ptr)GreaterThan,   false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("<>",              (xt_func_ptr)NotEqual,      false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("=",               (xt_func_ptr)Equal,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("postpone",        (xt_func_ptr)Postpone,      true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("'",               (xt_func_ptr)Tick,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("execute",         (xt_func_ptr)Execute,       false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("here",            (xt_func_ptr)Here,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("\\",              (xt_func_ptr)Backslash,     true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("(",               (xt_func_ptr)Paren,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("invert",          (xt_func_ptr)Invert,        false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("or",              (xt_func_ptr)BitOr,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("and",             (xt_func_ptr)BitAnd,        false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("xor",             (xt_func_ptr)BitXor,        false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("lshift",          (xt_func_ptr)BitShiftLeft,  false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("rshift",          (xt_func_ptr)BitShiftRight, false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("0=",              (xt_func_ptr)ZeroEquals,    false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("if",              (xt_func_ptr)IF,            false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("else",            (xt_func_ptr)ELSE,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("then",            (xt_func_ptr)THEN,          false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("do",              (xt_func_ptr)DO,            true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("i",               (xt_func_ptr)I,             false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("loop",            (xt_func_ptr)LOOP,          true,   NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("evaluate",        (xt_func_ptr)Evaluate,      false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("allot",           (xt_func_ptr)Allot,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("allot-size",      (xt_func_ptr)AllocatedSize, false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("leave",           (xt_func_ptr)Leave,         false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("j",               (xt_func_ptr)J,             false,  NULL));
  AddWordToDictionary(&state->dict, CreateForthWord("constant",        (xt_func_ptr)Constant,      false,  NULL));
}
