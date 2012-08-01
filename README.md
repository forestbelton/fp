fp
==

fp is a software-based floating point library. It supports up to 14 decimal digits of precision, and uses a packed BCD format internally. I chose this format to mimic the floating point representation used on the TI-8x line
of calculators. This format takes up slightly more (2 bytes) space than an IEEE 754 binary64 type, but it has
several advantages:
* It's easy to read. Since the data is in BCD, you can look at and manipulate the hexadecimal representation easily.
* It accurately stores common values such as 0.1. This is not possible in base-2 floating point representations.

Associated tools
----------------
* tools/fp-repr: Provides internal representation of floating-point constants.
* tools/fpp: Preprocessor used to turn %FP(...) into an internal representation.
* tools/fp-calc: Simple REPL used to provide interactive testing of library.

Supported operations
--------------------
* Basic arithmetic (+, -, *, /) and comparison
* Polynomial evaluation using the Horner scheme
* Conversion operations to/from various data types
* Arithmetic-geometric mean computation
* Exponential functions (exp, pow, log, sqrt) (WIP)

Planned features
----------------
* Basic trigonometric functions (sin, cos, tan)
