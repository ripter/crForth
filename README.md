# crForth
UNFINISHED: Yet Another Forth implimentation, In C

This is not a Forth for your embeded system. This is a Forth intergrated into Raylib. It will only work on systems where Raylib can be found.

Core Libraries Used:
* [Raylib](https://www.raylib.com/), linked via pkg-config.
* [minunit](https://github.com/siu/minunit/tree/master), source added to project.
* [klib](https://github.com/attractivechaos/klib), source added to project.


Project Goals: 
* Pass Forth Standard Tests: https://github.com/gerryjackson/forth2012-test-suite/tree/master
* Run all Raylib Examples.
* Be compatable with packages found on: http://theforth.net/packages


### Linking Raylib

This project uses `pkg-config` to link to Raylib. If you encounter issues where Raylib functions (e.g., `EndDrawing`, `DrawText`) aren't found during linking, it may be due to `pkg-config` not correctly detecting your Raylib installation—especially if you built Raylib from source.

You can check if `pkg-config` knows about Raylib by running:

```
pkg-config --cflags raylib
```



### crForth Features
* Runs on a stream.


### C Helper Functions

These functions work with data pointer defined in the word metadata.

* DoForthString - Runs DoForth with the ForthWord->data as the input stream and the current Kernel State.
* Variable - Returns the memmory address for WorldMetadata->data
* Nothing - Does nothing.




## To Fix:
* BASE
* LOOPS!
  * ✅ DO LOOP
  * BEGIN WHILE REPEAT
* CoreForth is loading the CoreWords from a path relative to the path used to run crForth. It should be either included into the binary, or relative to the binary location, not the calling location.
* need TYPE
* Finish ' tick
  * when run inside a compiled definition, it should return the XT of the word after the definition. (Test tick_compile_mode checks for this.)
* need EXECUTE
* need? REFILL
* need? SOURCE
* 



