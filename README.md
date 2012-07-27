fp
==

I don't really have anything to say quite yet about this project. fp is an API that implements a decimal floating-point format with up to 14 digits of precision.

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
