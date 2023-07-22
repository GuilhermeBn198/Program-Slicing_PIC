# **Tests with loop_array2-2.c**

-   [code](/tests/loop_tests/loop_array2-2/loop_array2-2.c)


## **What does this code do?**
- It declares two arrays A and B of size SZ (which is defined as 2048).
- It then fills both arrays with non-deterministic integers using the __VERIFIER_nondet_int function. This function is often used in the context of formal verification or testing to represent any possible integer.
- After that, it copies the values from array A to array B.
- Finally, it asserts that the value at the middle index of array A is equal to the value at the middle index of array B.

The functions `abort, assert, and reach_error` are used for error handling. If the condition in __VERIFIER_assert is not met (i.e., if A[SZ / 2] is not equal to B[SZ / 2]), the program will call reach_error and abort, indicating a failure of the assertion.

## **Frama-c**

-   it was made two tests using different methods of verification, with the objective to analyze the behavior of the tool in this case.
-   these are the tests made with the frama-c slicing tool:
-   ```bash
    1.    frama-c -slice-calls reach_error ./loop_array2-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./loop_array2-2-sliced1.c
    ```
-   this test made frama-c slice the unnecessary parts of the code, which were the definition of SZ, that could be made inside the main function, the `assert(0)` function call in `reach_error()` that in this case, made the same thing as return and the unnecessary statements in the `__VERIFIER_assert` function

**observations:**

-   notice that in this case, the `-slice-return` option doesn't work because it only selects the return portion of the functions, since `main` and `__VERIFIER_assert` don't return anything.
-   there isn't a `pragma` in the code so `-slice-pragma` doesn't work too since it is used to maintain the statements subsequentially after the pragma in the code, which impacts in the detection of frama-c to do not slice the __VERIFIER_assert function internal statements.

## **ESBMC**
The tests with the ESBMC verification tool will use the k-induction-parallel option, 

- the first test was with the original file, which presented an error in verification, similar to the other codes. Look:
- for the k-induction option 
    
    ![terminal output](../../../materials/imgs/loop-array2-2-kinduction.png)

## **Frama-c + ESBMC**
these tests will follow the same models for the ones in the original file.

- loop_array2-2-sliced1.c
  - Interesting discoveries were made, such as, with the sliced code in a way the ESBMC can understand better, the results of the k-induction-parallel option now can achieve the status of successfull verification! 

   ![terminal output](../../../materials/imgs/loop-array2-2-sliced-kinduction.png) 
        
---

---

---

## to go back to the previous page: [Click me!](../../../README.md)
