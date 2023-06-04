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

-   this initial test will be demonstrating the features concerning floating-point numbers:

    -   we will be using the [code](/tests/ESBMC-tests/initialTest.c) in this first example

    -   ```bash
        ./esbmc /tests/ESBMC-tests/initialtest.c --floatbv --k-induction
        ```
    -   `--floatbv` is a option that says ESBMC will use floating-point arithmetic to represent the program's float and double variables.
    -   ![floating point declarations](../../materials/imgs/ESBMC-initialtest-variables.png)
    -   **observe** that these functions in the code above doesn't exist in C codes, it's specifically used in the ESBMC library.
    -   `--k-induction` is a option that is selection the k-induction proof rule for the verification.
    -   the result should be:
    -   ```
        Checking inductive step, k = 2
        Starting Bounded Model Checking
        Unwinding loop 3  iteration  1   file initialTest.c line 12 function main
        Not unwinding
        Symex completed in: 0.001s (33 assignments)
        Slicing time: 0.000s (removed 14 assignments)
        Generated 2 VCC(s), 2 remaining after simplification (19 assignments)
        No solver specified; defaulting to Boolector
        Encoding remaining VCC(s) using bit-vector/floating-point arithmetic
        Encoding to solver time: 0.003s
        Solving with solver Boolector 3.2.2
        Runtime decision procedure: 0.358s
        BMC program time: 0.362s

        VERIFICATION SUCCESSFUL

        Solution found by the inductive step (k = 2)
        ```

-   now, for point safety verifications:

    -   we will be using the [code](/tests/ESBMC-tests/pointsafety.c)
    -   ```bash
        ./esbmc pointsafety.c --memory-leak-check
        ```
    -   `--memory-leak-check` is a option that says to ESBMC to use the memory-leak verification
    -   ```bash
        Generated 785 VCC(s), 783 remaining after simplification (1314 assignments)
        No solver specified; defaulting to Boolector
        Encoding remaining VCC(s) using bit-vector/floating-point arithmetic
        Encoding to solver time: 0.029s
        Solving with solver Boolector 3.2.2
        Runtime decision procedure: 0.981s
        Building error trace

        [Counterexample]


        State 1 file pointsafety.c line 22 function main thread 0
        ----------------------------------------------------
        a = (signed int *)0

        State 2 file pointsafety.c line 23 function main thread 0
        ----------------------------------------------------
        b = (signed int *)(&dynamic_3_array[0])

        State 3 file pointsafety.c line 25 function main thread 0
        ----------------------------------------------------
        b = &dynamic_3_array[0] + 1

        State 7 file pointsafety.c line 25 function main thread 0
        ----------------------------------------------------
        *tmp$3 = 0 (00000000 00000000 00000000 00000000)

        State 8 file pointsafety.c line 25 function main thread 0
        ----------------------------------------------------
        *tmp$3 = 0 (00000000 00000000 00000000 00000000)

        State 9 file pointsafety.c line 25 function main thread 0
        ----------------------------------------------------
        *tmp$3 = 0 (00000000 00000000 00000000 00000000)

        State 10 file pointsafety.c line 25 function main thread 0
        ----------------------------------------------------
        *tmp$3 = 0 (00000000 00000000 00000000 00000000)

        State 11 file pointsafety.c line 14 function foo thread 0
        ----------------------------------------------------
        Violated property:
        file pointsafety.c line 14 function foo
        dereference failure: NULL pointer


        VERIFICATION FAILED
        ```

    -   in this case, notice that there will be multiple errors in different states in the report

## These are some of the various features that are present in ESBMC
---

---

---

## to go back to the previous page: [Click me!](../../README.md)
