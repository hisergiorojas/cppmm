# CPPMM
C-plus-plus-minus-minus

## Introduction

`cppmm` is a binding generator for creating C and Rust interfaces to C++ libraries. It is targeting a very small subset of libraries--just those in consideration by the `vfx-rs` project--and is not expected to work for anything else and will have assumptions about the C++ it will accept based on the types and idioms found in those libraries baked into it.

## Quick start
You must have LLVM and clang installed, as well as fmtlib. I've tested it with llvm 10.0.1 only. To run the test you'll need OIIO 2.2.8 and openexr 2.4.0 (other versions may work but are untested)
```
mkdir build && cd build
env LLVM_ROOT=</path/to/llvm/installation> cmake ..
./cppmm ../test/oiio/c-imageio.cpp -u -- \
    -I</path/to/oiio/includes>           \
    -I</path/to/openexr/includes>        \
    -I</path/to/libc++/includes>
```
for me this is:
```
./cppmm ../test/oiio/c-imageio.cpp -u  --                         \
    -I/home/anders/packages/oiio/2.2.8/include                    \
    -I/home/anders/packages/openexr/2.4.0/include                 \
    -I/home/anders/packages/llvm/10.0.1/lib/clang/10.0.1/include/
```

This will generate `c-imageio.cpp`, `c-imageio.h` and `casts.h` in the build directory. They will not currently compile but should give you an idea of what the output will look like.

## Todo
[ ] Add type registry and warn on missing type declarations
[ ] Add parameter names for copy constructors and assignment operators
[ ] Add support for declaring enums
[ ] Add support for generating C versions of C++ types (value types)
[ ] Add Rust -sys crate output
[ ] Figure out how to parse attributes inside macros
[ ] Add support for binding straight from the original C++ headers with attributes
