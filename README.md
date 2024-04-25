# MacJS9

work in progress JavaScript Interpreter for Mac OS 9, using Duktape.

to compile currently, get Retro98, then create a build directory and do

`cmake .. -DBUILD_QJS_LIBC=OFF -DRETRO68_ROOT=${RETRO68_TOOLCHAIN_PATH} -DCMAKE_TOOLCHAIN_FILE=${RETRO68_INSTALL_PATH}/cmake/retroppc.toolchain.cmake.in`

(swap `retroppc` with `retro68`) to get 68k support

then make, and if done correctly, you should get `.bin` which, on Mac OS with Stuffit installed, will expand to the build.

better readme coming soon.
