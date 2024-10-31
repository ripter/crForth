#include "../crForth.h"

void PrintHeader(void) {
  printf("           ______         _   _         \n"); 
  printf("          |  ____|       | | | |        \n"); 
  printf("  ___ _ __| |__ ___  _ __| |_| |__      \n");
  printf(" / __| '__|  __/ _ \\| '__| __| '_ \\   \n");
  printf("| (__| |  | | | (_) | |  | |_| | | |    \n");
  printf(" \\___|_|  |_|  \\___/|_|   \\__|_| |_| \n");
  printf("                                        \n");
  printf("crForth version: %s\n", APP_VERSION);
  printf("Cell Size: %zu bytes\n", sizeof(CellValue));
}
