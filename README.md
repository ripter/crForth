# crForth
UNFINISHED: Yet Another Forth implimentation, In C


This is not a Forth for your embeded system. This is a Forth intergrated into Raylib. It will only work on systems where Raylib can be found.


### Linking Raylib

This project uses `pkg-config` to link to Raylib. If you encounter issues where Raylib functions (e.g., `EndDrawing`, `DrawText`) aren't found during linking, it may be due to `pkg-config` not correctly detecting your Raylib installation—especially if you built Raylib from source.

You can check if `pkg-config` knows about Raylib by running:

```
pkg-config --cflags raylib
```

