# **Tests with loop_array2-2.c**

-   [code](/tests/loop_tests/loop_array2-2/loop_array2-2.c)

## **Frama-c**

-   it was made 2 different tests using different methods of verification, with the objective to analyze the behavior of the tool in this case.
-   these are the tests made with the frama-c slicing tool:
-   ```bash
    1.    frama-c -slice-pragma __VERIFIER_assert -slice-calls __VERIFIER_assert ./loop_array2-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./loop_array2-2-sliced1.c

    2.    frama-c -slice-value A,B ./loop_array2-2.c -then-on 'Slicing export' -set-project-as-default -print -then -print -ocode ./loop_array2-2-sliced2.c
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
-   there isn't a `pragma` in the code so `-slice-pragma` doesn't work too since it is used to maintain the statements subsequentially after the pragma in the code, which impacts in the detection of frama-c to do not slice the __VERIFIER_assert function internal statements. The researcher  purposely introducted a pragma stmt so ESBMC can run the frama-c verified code.

## **ESBMC**
The tests with the ESBMC verification tool will use the floatbv and k-induction options, the reasearcher needed to change the external `__VERIFIER_nondet_int` function to `nondet_uint` so the ESBMC can be run

- the first test was with the original file, which with only the floatbv option, it goes all good, but with the k-induction option, it presented fail. Look:
- for the floatbv option 
    
    ![terminal output](../../../materials/imgs/loop-array2-2-floatbv.png)
- for the k-induction option 
    
    ![terminal output](../../../materials/imgs/loop-array2-2-kinduction.png)

## **Frama-c + ESBMC**
these tests will follow the same models for the ones in the original file.
```
Interesting discoveries were made, such as, with the sliced code in a way the ESBMC can understand better the results of the k-induction option now can achieve the status of successfull verification!, the same occurs with the floatbv option 
```
- loop_array2-2-sliced1.c
  - k-induction alone 
        
     ![terminal output](../../../materials/imgs/loop-array2-2-sliced1-kinduction.png) 
  - floatbv alone 
  
     ![terminal output](../../../materials/imgs/loop-array2-2-sliced1-floatbv.png) 
  


- loop_array2-2-sliced2.c:
  - floatbv alone
 
     ![terminal output](../../../materials/imgs/loop-array2-2-sliced2-floatbv.png)
  - k-induction alone
   
     ![terminal output](../../../materials/imgs/loop-array2-2-sliced2-kinduction.png) 


---

---

---

## to go back to the previous page: [Click me!](../../../README.md)
