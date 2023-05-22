# Frama-c

## What is it?

Frama-C is an open-source extensible and collaborative platform dedicated to source-code analysis of C software. The Frama-C analyzers assist you in various source-code-related activities, from the navigation through unfamiliar projects up to the certification of critical software.

## What it can do?

The collaborative approach of Frama-C allows analyzers to build upon the results already computed by other analyzers in the framework. Thanks to this approach, Frama-C can provide a number of sophisticated tools such as a concurrency safety analysis (Mthread), an enforcer of secure information flow (SecureFlow), or a set of tools for various test coverage criteria (LTest), among many others.

## Frama-C Plugins

Here are some of the most important plugins:

-   ## Value

    The Value plugin performs abstract interpretation on C programs to infer information about the possible values of variables and expressions. It can detect potential runtime errors such as null pointer dereferences, buffer overflows, and integer overflows. The plugin can also provide information on variable initialization, pointer aliasing, and interprocedural analysis. It is a powerful tool for both bug-finding and program optimization.

-   ## WP

    The WP (Weakest Precondition) plugin is a deductive verification tool that uses mathematical logic to prove the correctness of programs. It can prove properties such as functional correctness, safety properties, and temporal properties. The plugin requires the programmer to provide annotations in the form of preconditions and postconditions, and it uses these annotations to generate proof obligations. The plugin can also generate counterexamples to aid in debugging. It is a powerful tool for ensuring the correctness of critical software.

-   ## EVA

    The EVA (Evaluation of C Expressions with Value Analysis) plugin evaluates complex C expressions at compile-time using abstract interpretation. It can provide precise information on the possible values of expressions, making it useful for program optimization and bug-finding. The plugin can also detect potential runtime errors such as null pointer dereferences and division by zero. It is a lightweight and efficient tool for analyzing C code.

-   ## Jessie

    The Jessie plugin is a deductive verification tool that uses the Jessie intermediate language to prove the correctness of programs. It requires the programmer to provide annotations in the form of preconditions and postconditions, and it generates proof obligations from these annotations. The plugin supports a variety of programming constructs, including pointers, arrays, and recursion. It is a powerful tool for ensuring the correctness of critical software.

-   ## RTE

    The RTE plugin verifies the correctness of programs that use the RTE (Runtime Environment) library of Frama-C. It checks if the library functions are used correctly and if the program meets all runtime restrictions of the library. The plugin is capable of finding errors such as invalid pointers and array bounds violations. Additionally, it verifies if the library functions are called with the correct arguments and if the program does not try to access uninitialized variables. The plugin is useful for ensuring the correctness of programs that use the RTE library in critical environments.

-   ## Frama-Clang

    The Frama-Clang plugin is a front-end for Frama-C that allows it to handle C++ code. It uses the Clang compiler to parse the code and generate an AST (Abstract Syntax Tree), which is then passed to Frama-C for analysis. The plugin supports a variety of C++ language features, including templates and namespaces. It is a useful tool for analyzing C++ code using the Frama-C framework.

-   ## PathCrawler
    The PathCrawler plugin is a symbolic execution engine for C programs. It explores all possible paths through the program and checks for potential runtime errors such as null pointer dereferences and buffer overflows. The plugin can also generate test cases that exercise different program paths, making it useful for automated testing. It is a powerful tool for analyzing complex C programs.

---

## New versions! [CLICK ME](./NewVersions.md)

## Tutorial for frama-c installation: [CLICK ME!](./TutorialFramaC.md)

## Example of use(interactive mode): [CLICK ME!](./exampleOfInteractivemode.md)

## Example of use and documentation of slicing tool(command line tool): [CLICK ME!](./exampleOfCLIMode.md)

---

---

---

## to go back to the previous page: [Click me!](../../README.md)
