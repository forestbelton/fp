fp
==

fp is an ISO/IEC 9899:1999 ([C99](http://en.wikipedia.org/wiki/C99)) compliant software floating point library. It supports up to 14 decimal digits of precision, utilizing an internal format based on [packed BCD](http://en.wikipedia.org/wiki/Binary-coded_decimal#Packed_BCD). I chose this format to mimic the floating point representation used on the TI-8x line of calculators. This format takes up slightly more (2 bytes) space than an [IEEE 754 binary64](http://en.wikipedia.org/wiki/Double-precision_floating-point_format#IEEE_754_double-precision_binary_floating-point_format:_binary64) type, but it has several advantages:
* It's easy to read. Since the data is in BCD, you can examine and manipulate the hexadecimal representation easily.
* It accurately stores common values such as 0.1. This is not possible in base-2 floating point representations.

Associated tools
----------------
* tools/fpp: Preprocessor used to turn `%FP(...)` or `%FP_CONST(...)` into an internal representation.
* tools/fp-calc: Simple REPL used to provide interactive testing of library.

Supported operations
--------------------
* Basic arithmetic (+, -, *, /) and comparison
* Polynomial evaluation using the [Horner scheme](http://en.wikipedia.org/wiki/Horner_scheme)
* Conversion operations to/from various data types
* Arithmetic-geometric mean
* Exponential functions (exp, pow, log, sqrt) (WIP)

Planned features
----------------
* Basic trigonometric functions (sin, cos, tan)

Build instructions
------------------
The only programs required to build this program are [gcc](http://gcc.gnu.org/), [bison](http://www.gnu.org/software/bison/) and [flex](http://www.gnu.org/software/flex/). To build and install, all you have to do is

```bash
$ make && sudo make install
```

Example usage
-------------
The API is designed for ease of use over efficiency. You can find examples available in the `ex` directory. If `%FP(...)` or `%FP_CONST(...)` is used in your source code for floating-point constants, you need to run your code through the `fpp` preprocessor before compiling. A sample invocation is given below:

```bash
$ fpp mycode.c | gcc -xc - -o mycode
```
