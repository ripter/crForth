#include "../crForth.h"

// Loads and runs all the files found at `forth/*.fth`.
void AddForthWords(KernelState *state) {
  const char *CAD = GetApplicationDirectory();
  String *path = GetStringFromPool(CAD);
  AppendToString(path, "forth");

  FilePathList files = LoadDirectoryFiles(GetStringValue(path));
  // printf("Found %d files.\n", files.count);
  // printf("Loading %d Forth files from: '%sforth'\n", files.count, CAD);
  for (unsigned int i = 0; i < files.count; i++) {
    char *fileName = files.paths[i];
    // Skip if it's not a Forth file.
    if (!IsFileExtension(fileName, FILE_EXTENSION)) {
      continue;
    }
    // Skip if it's not a valid file.
    if (!FileExists(fileName)) {
      continue;
    }

    // printf("\tFile: %s\n", fileName);
    RunForthFile(state, fileName);
  }
  UnloadDirectoryFiles(files);
}
