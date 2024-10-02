# crForth
UNFINISHED: Yet Another Forth implimentation, In C


This is not a Forth for your embeded system. This is a Forth intergrated into Raylib. It will only work on systems where Raylib can be found.

Core Libraries Used:
* [Raylib](https://www.raylib.com/), linked via pkg-config.
* [minunit](https://github.com/siu/minunit/tree/master), source added to project.
* [klib](https://github.com/attractivechaos/klib), source added to project.



### Linking Raylib

This project uses `pkg-config` to link to Raylib. If you encounter issues where Raylib functions (e.g., `EndDrawing`, `DrawText`) aren't found during linking, it may be due to `pkg-config` not correctly detecting your Raylib installation—especially if you built Raylib from source.

You can check if `pkg-config` knows about Raylib by running:

```
pkg-config --cflags raylib
```

### C Defined words vs Forth Defined words
While I like the idea of having as much of the system written in Forth as possible, I like the idea of a fast enough system more. So if the C version is faster, the C version might be the better choice, depending on how much faster the C version is.


## To Fix:
* CoreForth is loading the CoreWords from a path relative to the path used to run crForth. It should be either included into the binary, or relative to the binary location, not the calling location.
* need TYPE
* does> returns the "address" of the word it ran
* create name should create a variable by default, running it puts the "address" on the stack.
* need ' tick
* need EXECUTE
* need? REFILL
* need? SOURCE
