# Accumulator-Based-Programming-Language(accbpl)
* This is heavily based on the esolang [Deadfish](https://esolangs.org/wiki/Deadfish).
* In fact, the any deadfish program that doesn't relay on accumulator reset(at -1 and 256) should work fine with accbpl.
* I just added two extra instructions.

# Specification
* At the beginning of a program, accumulator is initialized to zero.
* Accumulator is a signed 32-bit integer.(int32_t)
* Supports the following instructions
## Instructions
| Instruction   | Effect on accumulator |
| ------------- |:---------------------:|
| i             | increment             |
| d             | decrement             |
| s             | square                |
| r             | square root, rounded to int|
| o             | output as int(32 bit) |
| c             | output as char(8 bit) |

* Of these, `i`, `d`, `s`, and `o` are from deadfish.
* `r` and `c` are the ones added extra to accbpl
