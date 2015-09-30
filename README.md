## Compiler Construction Coursework
This project implements a compiler for the **C Minus** programming language, a simple subset of C.  Over the course of 12 assignments, the compiler was developed in progressive functional stages.

### Compiling C Minus Source
The final result can be found in the `as12` folder.  The compiler can be built using

    cd as12
    make CMinDriver

Examples can subsequently be compiled

    ./CMinDriver ../tests/gcd.cm

This results in the creation of an abstract syntax tree representation of the parsed source (`gcd.ast`), an intermediate Assembly file (`gcd.s`), and an executable (`gcd`).

### Course Info

This work was completed as part of the CSCI 435: Compiler Construction course taught by Gary Zoppetti at Millersville University in the Fall of 2014.
