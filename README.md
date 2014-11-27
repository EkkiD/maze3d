maze3d
======

A 2.5D maze generator / animation written in C++11.

Compiles (mostly) cleanly into x86 linux and asm.js through emscripten.

# Setup for Emscripten
1. Intall [emscripten](http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html#installation-instructions)
   Don't forget to `source ./emsdk_env.sh` from your emscripten install dir to ensure our PATH contains the necessary directories.
2. In the root directory of the clone, run `./setup_emscripten.sh` to setup the build directory for emscripten (embuild).
3. In the embuild directory, run make
4. In a browser, navigate to file:///<path-to-your-clone>/embuild/test.html

# Setup for Local
1. In the root directory of the clone, run `./setup_local.sh` to setup the build directory for local dev (build).
2. In the build directory, run make.
3. In the maze directory, run ../build/maze .
