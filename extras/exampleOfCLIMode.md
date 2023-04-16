# Command Line Mode
## first some explanations about the slicing plugin and its parameters:
### The Frama-C Slicing plugin offers several command line options to specify slicing criteria. Here are some of the available options:
- -slice-calls f1,...,fn: Selects each call to functions f1,…,fn and all their effects.
- -slice-return f1,...,fn: Selects the result (returned value) of functions f1,…,fn.
- -slice-value v1,...,vn: Selects the result of the values on the left-hand side v1,…,vn at the end of the function given as an entry point.
- -slice-wr v1,...,vn: Selects the write accesses to the left-hand side values v1,…,vn.
- -slice-rd v1,...,vn: Selects the read accesses to the left-hand side values v1,…,vn.
- Slicing criteria can also be specified in the source code using slicing pragmas and the following command line option:
	- -slice-pragma f1,...,fn: Uses slicing pragmas in the code of functions f1,…,fn as slicing criteria.
	In addition, slicing criteria can be relative to ACSL annotations. In this case, the Slicing plugin ensures that if a property is verified by the sliced code, this implies that the corresponding property is satisfied by the initial code. The command line options related to this feature are:
      - -slice-assert f1,...,fn: Selects the assertions of functions f1,…,fn.
      - -slice-loop-inv f1,...,fn: Selects the loop invariants of functions f1,…,fn.
      - -slice-loop-var f1,...,fn: Selects the loop variants of functions f1,…,fn.
      - -slice-threat f1,...,fn: Selects the threats (issued by Eva) of functions f1,…,fn.

Several of these options can be used simultaneously to specify a complex slicing criteria. Note that the order of options does not affect the slicing result.

---

## now, for some examples we'll take the same code we used in the interactive version demonstration:  [click here to see it](../tests/test1.c)

---

## to go back to the previous page: [Click me!](../README.md)
