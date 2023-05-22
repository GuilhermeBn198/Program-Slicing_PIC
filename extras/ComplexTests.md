# Now that we saw a little about how the tool works, we will start testing it again with more complex tests

## pragma-assert-return-calls testcase 1:

-   [code](/tests/complex_tests/pragma_assert_return/test1.c)
-   [sliced code](/tests/sliced_tests/pragma_assert_return/test1-sliced.c)
-   assumptions:

    -   In this example, we have added slicing pragmas "add" and "multiply" for the addition and multiplication functions, respectively. We also have an assertion y >= x in the main function.
    -   The subtract function and the variable z are not related to any slicing pragma, assertion, or return value.
    -   In this example, it is intended this function and the variable z are about to be sliced from the code.
    -   Now, let's slice the code using the same slicing options as before:

        ```bash
        frama-c -slice-assert main -slice-pragma add -slice-return multiply test1.c -then-on 'Slicing export' -print -ocode 'test1-sliced.c'
        ```

    -   We can see in sliced code that frama-c output returned the code sliced, without the subtract function and the variable z, but the definition of the add functions changed too.

    -   The slicing pragma was intended to keep the add function, but it seems that Frama-C did not consider it necessary to preserve the function's behavior as it was not directly related to the assertion or the value returned by the multiply function.

        -   The slicing pragma can be useful for guiding the slicing process and preserving certain parts of the code. However, in this specific case, it appears that the slicing pragma did not have the desired effect.

            -   An approach to resolving this problem is using another assert in the main function like `/*@ assert sum == x + y; */;` and execute the command. This case is to demonstrate that it may be difficult to use the pragmas in a way it can be effective, needs testing!

                -   with this we can maintain the correct sliced code of add in the code, but with this we loss the need of -slice-pragma.
                -   This is the slicing command to execute it:

                ```bash
                frama-c -slice-assert main -slice-return multiply test1.c -then-on 'Slicing export' -print -ocode 'test1-sliced.c''
                ```

---

---

---

## pragma-assert-return-calls testcase 2:

-   [code](../tests/complex_tests/pragma_assert_return/test2.c)
-   [sliced code](../tests/complex_tests/pragma_assert_return/test2-sliced.c)

-   In this example:

    -   The add function has a /_@ slice pragma stmt; _/ pragma to preserve its behavior.
    -   The multiply function has a /_@ slice pragma expr result; _/ pragma to preserve the value of its result.
    -   The main function has a /_@ slice pragma ctrl; _/ pragma before the conditional statement to preserve the control point.
    -   To slice this code with the desired options, use the following command:

    ```bash
    frama-c -slice-pragma main -slice-assert main -slice-return multiply -slice-calls add test.c -then-on 'Slicing.export' -print -ocode 'sliced_test.c'
    ```

---

---

---

### Cruise Control

-   [code](/tests/complex_tests/cruise_control/)

---

---

---

## to go back to the previous page: [Click me!](./exampleOfCLIMode.md)
