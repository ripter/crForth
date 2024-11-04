#include "../crForth.h"


// ( addr u -- )
// Using Current Working Directory as the base path, loads and executes the file at the given path.
// Example: s" src/forth/CoreWords.fth" included
// https://forth-standard.org/standard/file/INCLUDED
void Included(KernelState *state) {
  printf("\nIncluded Called\n");
  Cell u = CellStackPop(&state->dataStack);
  Cell addr = CellStackPop(&state->dataStack);
  const char *CWD = GetWorkingDirectory();
  String *path = CreateString(CWD);
  AppendToString(path, "/");
  AppendToString(path, (char *)addr.value);

  // u can be shorter than the string, so we need to truncate it.
  size_t totalLength = (size_t)u.value + TextLength(CWD) + 1;
  if (u.value > 0 &&  totalLength < path->l) {
    path->l = totalLength;
    path->s[totalLength] = '\0';
  }

  if (!FileExists(GetStringValue(path))) {
    fprintf(state->errorStream, "File not found: '%s'\n", GetStringValue(path));
    return;
  }

  // Run it!
  fprintf(state->outputStream, "Included: %s\n", GetStringValue(path));
  RunForthFile(state, GetStringValue(path));
}
