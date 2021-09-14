# cs554-warmup

This implements an interpreter for a simple machine language.

## Building

To build, simply run:
```bash
./build.sh
```
In the root directory of the project. This should build with GCC 10 or newer.

Arguments passed to `./build.sh` are then forwarded to CMake, so you may 
optionally build with clang using `./build.sh -DCMAKE_CXX_COMPILER=clang++`. 

## Packaging for other systems

If you're building for a system that doesn't have a recent version of gcc,
you can create a self-contained executable that contains all the libraries it
needs to run by using the following command:

```bash
./build.sh -DALWAYS_FETCH=ON -DCMAKE_CXX_FLAGS="-static"
```

This will build dependencies as static libraries, and it will also statically link the C++20 standard library. The resulting executable can be copied to other
machines, and should run without issue (this was tested on the UNM CS machines).

Alternatively, running `./package.sh` will invoke the above command before
copying everything into a newly created `package` directory inside the root of
the project. This `package` directory will contain both the executable, and
the list of sample programs that can be run.
