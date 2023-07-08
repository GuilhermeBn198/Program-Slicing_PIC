# **Tests with loop_array2-2.c**

-   [code](/tests/loop_tests/loop_array2-2.c)

## **Frama-c**

-   it was made 5 different tests using different methods of verification, with the objective to analyze the behavior of the tool in this case.
-   these are the tests made with the frama-c slicing tool:
-   ```bash
    1.    frama-c -slice-calls __VERIFIER_assert loop_array2-2.c -then-last -print
    2.    frama-c -slice-value A,B loop_array2-2.c -then-last -print
    3.
    ```
    -   **for test 1**, frama-c sliced the statements inside the `__VERIFIER_assert` and maintained the rest of the code, **_modifying the for loops to whiles_**, making the code more understandable.
    -   **for test 2**, frama-c sliced everything but the statements about the arrays A and B, **INCLUDING** the
    
        -   ```bash
			while (i < 2048) {
			tmp = A[i];
			B[i] = tmp;
			i ++;
			}
			```

		which is a simplified version of the declaration of SZ constant

**observations:**

-   notice that in this case, the `-slice-return` option doesn't work because it only selects the return portion of the functions, since `main` and `__VERIFIER_assert` don't return anything.
-   there isn't a `pragma` in the code so `-slice-pragma` doesn't work too since it is used to maintain the statements subsequentially after the pragma in the code.

## **ESBMC**

## **Frama-c + ESBMC**
---

---

---

## to go back to the previous page: [Click me!](../../README.md)