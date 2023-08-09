# **Tests with loop_array1-1.c**

-   [code](/tests/loop_tests/loop_array1-1/array_1-1.c)

## **What does this code do?**

- Definition of Constants and Variables:
  - An array A of 2048 integers and an integer i are declared.

- Filling the Array:
  - `for (i = 0; i < 1024; i++) { A[i] = i; }` This loop fills the first 1024 elements of the array A with their respective indices.

- Assertion Check:
  - `__VERIFIER_assert(A[1023] != 1023);` This line of code calls the __VERIFIER_assert function with the condition A[1023] != 1023. This function will abort the program execution if the condition is false, i.e., when the 1023rd element in the array A is equal to 1023.

- The `__VERIFIER_assert(int cond)` function is a custom assertion function that aborts program execution when the passed condition is false. reach_error() calls the standard __assert_fail function, which reports an assertion failure.

## **Frama-c**

-   it was made one test verifying all code related to __assert_fail, with the objective to analyze the behavior of the tool in this case.
-   the command to slice the code:
-   ```bash
    1.    frama-c -slice-calls __assert_fail ./array_1-1.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./array1-1-sliced.c
    ```
-   this test made frama-c slice the unnecessary parts of the code, which were the `abort()` function call in `reach_error()` that in this case, made the same thing as return and the unnecessary statements in the `__VERIFIER_assert` function

**observations:**

-   notice that in this case, the `-slice-return` option doesn't work because it only selects the return portion of the functions, since `main` and `__VERIFIER_assert` don't return anything.
-   there isn't a `pragma` in the code so `-slice-pragma` doesn't work too since it is used to maintain the statements subsequentially after the pragma in the code, which impacts in the detection of frama-c to do not slice the __VERIFIER_assert function internal statements.

## **ESBMC**
The tests with the ESBMC verification tool will use the k-induction-parallel option, 

- the first test was with the original file, which presented a failure in the verification. Look:
       
  ![terminal output](../../../materials/imgs/loop-array1-1-kinduction.png)

## **Frama-c + ESBMC**
these tests will follow the same models for the ones in the original file.
```
ESBMC couldn't verify the through the induction step, even with the slice of unnecessary parts of this code. 
```
- loop_array1-1-sliced.c
  - k-induction-parallel 

   ![terminal output](../../../materials/imgs/loop-array1-1-sliced-kinduction.png) 
        
---

---

---

## to go back to the previous page: [Click me!](../../../README.md)
