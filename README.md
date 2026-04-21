# Accumulator-Based-Programming-Language(accbpl)
* This is heavily based on the esolang [Deadfish](https://esolangs.org/wiki/Deadfish).
* In fact, the any deadfish program that doesn't relay on accumulator reset(at -1 and 256) should work fine with accbpl.
* I just added few extra instructions.

## Specification
* At the beginning of a program, accumulator is initialized to zero.
* Accumulator is a signed 32-bit integer.(int32_t)
* Supports the following instructions: i, d, s, r, o, c, g, q.
* Any character that is not part of the above instruction set is ignored.
* Overflow is not handled, just like Deadfish.
* Newline and whitespaces are also ignored.
### Instructions
| Instruction   | Effect                |
| ------------- |:---------------------:|
| q             | stops interpretation  |
| i             | increment             |
| d             | decrement             |
| s             | square                |
| r             | square root, rounded to int (-ve acc terminates)|
| o             | output as int(32 bit) |
| c             | output as char(8 bit) |
| g             | get single int(32 bit) as input and overwrite |

* Of these, `i`, `d`, `s`, and `o` are from deadfish.

## Usage Example
First clone the repo recursively.

### Windows example
Specify a generator manually like so:
```bash
$ cmake -S. -Bbuild -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
$ .\build\windows_x86-64\Debug\accbpl.exe
```
Or use a predefined preset. <br>
For example, to use gcc and makefiles for a debug build on windows x86-64:
```bash
$ cmake --preset=windows_x86-64_debug_mingw-w64_makefiles
$ cmake --build build
$ .\build\windows_x86-64\Debug\accbpl.exe
```

### Linux example
Specify a generator manually like so:
```bash
$ cmake -S. -Bbuild -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build
$ ./build/linux_x86-64/Debug/accbpl
```
Or use a predefined preset. <br>
For example, to use gcc and makefiles for a debug build on linux x86-64:
```bash
$ cmake --preset=linux_x86-64_debug_gcc_makefiles
$ cmake --build build
$ ./build/linux_x86-64/Debug/accbpl
```

Run `accbpl` with no arguments for REPL mode, or `accbpl examples/hello-world-int.accbpl` to run a program (from the directory that contains the `accbpl` binary; `examples/` is copied there at build time).

Note: Use `cmake --list-presets` to see all available presets
