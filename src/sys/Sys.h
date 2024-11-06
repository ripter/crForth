#ifndef SYS_H
#define SYS_H

#include "../Stack.h"
#include "../String.h"

//
// ColonSys
// A struct for definitions.
typedef struct {
  String *name; // The name of the definition.
  String *src;  // The source code for the definition.
} ColonSys;

// Function to create a ColonSys, src is not owned by the ColonSys.
ColonSys *CreateColonSys(const char* newName, String *src);
// Function to free the ColonSys, does not free the src string.
void FreeColonSys(ColonSys *colonSys);

//
// NestSys
typedef struct {
  String *src; // The source code for the nest.
} NestSys;

//
// DoSys
// A struct to hold the loop control parameters.
typedef struct {
  CellValue limit; // The limit of the loop, the loop will run until the index is equal to or greater than the limit.
  CellValue index; // The current index of the loop.
  bool isNested;   // True if this is a nested loop.
  String *loopSrc; // The source code for the loop body. When the loop runs, this code will be executed.
} DoSys;

DoSys *CreateDoSys(void);
void FreeDoSys(DoSys *doSys);



typedef struct {
  CellValue flag;
} IfSys;


#endif // SYS_H
