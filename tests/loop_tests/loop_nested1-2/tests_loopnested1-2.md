# **Tests with loop_diamond101.c**

-   [code](/tests/loop_tests/loop_diamond1-1/diamond_1-1.c)

## **What does this code do?**

- The main function initializes two unsigned integers, x and y, to 0.
- It then enters a loop that continues until `x is less than 0x0fffffff` (a large hexadecimal number).
- Inside this outer loop, y is reset to 0 and then a nested loop increments y until it reaches 10.
- After the inner loop finishes, x is incremented by 1.
- Once the outer loop finishes (when x reaches 0x0fffffff), the program checks an assertion using the __VERIFIER_assert function. This assertion checks if x is even (since !(x % 2) will return 1 for even numbers and 0 for odd numbers).
- The `__VERIFIER_assert` function takes an integer condition as an argument. If the condition is false (i.e., if x is odd), it calls the `reach_error` function and then aborts the program.
- The `reach_error` function calls the `__assert_fail` function, which is an external function (presumably from an assertion library) that does not return (as indicated by the `__noreturn__` attribute). This function likely prints an error message and terminates the program.

In summary, this program increments x from 0 to 0x0fffffff, and for each value of x, it increments y from 0 to 10. At the end, it checks if x is even and aborts the program if it is not.
  
## **Frama-c**

-   it was made various tests verifying all code related to `__assert_fail`, with the objective to analyze the behavior of the tool in this case.
-   the command to slice the code:
-   ```bash
    frama-c -slice-calls __assert_fail ./nested_1-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./nested_1-2-sliced.c

     frama-c -main main -slice-calls __assert_fail -slice-wr x,y ./nested_1-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./nested_1-2-sliced.c

    frama-c -main main -slice-calls __assert_fail -slice-loop-var main ./nested_1-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./nested_1-2-sliced.c

    frama-c -main main -slice-calls __assert_fail,abort ./nested_1-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./nested_1-2-sliced.c

    frama-c -main main -slice-calls __assert_fail -slice-loop-var main  ./nested_1-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./nested_1-2-sliced.c

    frama-c -main main -slice-calls __assert_fail -slice-wr cond  ./nested_1-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./nested_1-2-sliced.c

    frama-c -main main -slice-calls __assert_fail -slice-rd cond  ./nested_1-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./nested_1-2-sliced.c
    ```
-   - FRAMA-C COULDN'T SLICE THE `__VERIFIER_assert` function internal statements to reach the `__assert_fail` function with the -slice-calls option, and any other type of options that the researcher tried, needs further investigation!
-   IN this case, it couldn't detect how the variables were important to reach the `__assert_fail` function, so it just removed the variables from the call of `__VERIFIER_assert`.

**observations:**

-   notice that in this case, the `-slice-return` option doesn't work because it only selects the return portion of the functions, since `main` and `__VERIFIER_assert` don't return anything.
-   there isn't a `pragma` in the code so `-slice-pragma` doesn't work too since it is used to maintain the statements subsequentially after the pragma in the code, which impacts in the detection of frama-c to do not slice the __VERIFIER_assert function internal statements.

## **ESBMC**
The tests with the ESBMC verification tool will use the k-induction-parallel option, 

-With this case, ESBMC couldn't verify the code with the --k-induction option. Look:
       
  ![terminal output](../../../materials/imgs/loop-nested1-2-kinduction.png)


---

---

## to go back to the previous page: [Click me!](../../../README.md)
