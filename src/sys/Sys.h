#ifndef SYS_H
#define SYS_H

#include "../Stack.h"
#include "../String.h"

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
