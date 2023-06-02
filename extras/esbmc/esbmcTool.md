# ESBMC

## What is it?

-   ESBMC is an open source, permissively licensed, context-bounded model checker based on satisfiability modulo theories for the verification of single- and multi-threaded C/C++ programs. It does not require the user to annotate the programs with pre- or postconditions, but allows the user to state additional properties using assert-statements, that are then checked as well. Furthermore, ESBMC provides two approaches (lazy and schedule recording) to model check multi-threaded programs. It converts the verification conditions using different background theories and passes them directly to an SMT solver.

## What it can do?

ESBMC aims to support all of C11, and detects errors in software by simulating a finite prefix of the program execution with all possible inputs.

It can detect erros from:

-   User specified assertion failures
-   Out of bounds array access
-   Illegal pointer dereferences
-   Integer overflows
-   NaN (Floating-point)
-   Divide by zero
-   Memory leak

It can also verify multiple-threaded programs with different conditions:

-   Deadlock (only on pthread mutexes and conditional variables)
-   Data races (i.e., competing writes)
-   Atomicity violations at visible assignments
-   Lock acquisition ordering

# Installation process

-   The installation process of ESBMC is simple:
    -   As a prerequisite, we recommend installing ESBMC on a GNU/Linux OS (the support for MacOS is still experimental).
    -   visit the oficial web site of the project [here](http://esbmc.org/)
    -   download the ESBMC-linux.sh file
    -   do the command to allow execution of the script:
    -   ```bash
        $ chmod +x ESBMC-Linux.sh
        ```
    -   then run the script
    -   ```bash
        $ ./ESBMC-Linux.sh
        ```
    -   the script will create the directory of the ESBMC with all its files, go to the bin file and execute the command to see if its working, it should display its options:
    -   ```bash
        ./esbmc --help
        ```

## initial tests

-

---

---

---

## to go back to the previous page: [Click me!](../../README.md)
