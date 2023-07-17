# **TO DO's**:

## **27/03~10/04**:

- [x] Install Frama-C
  - [x] Installation tutorial of the program completed!
- [x] Create a tutorial on how to use https://frama-c.com/fc-plugins/slicing.html
  - [x] Learn how to use the tool
  - [x] Perform tests
- [x] Read Chapter 2 of the Thesis on program slicing
  - [x] 1/3
  - [x] 2/3
  - [x] 3/3

---

## **10/04~17/04**:

- [x] Present an example with slides of what program slicing is and how to execute it using Frama-C via command line.
  - [x] (EXTRA!) present an example of program slicing with frama-c GUI
- [ ] Present an example with slides of what program slicing is and how to execute it WITHOUT USING SOFTWARE, for function and instruction as a cutting criterion.
- [x] (EXTRA!) add pt-br support to the repository.

---

## **03/05~10/05**:

- [x] complete the documentation for -slice-assert, -slice-pragma
  - [x] (EXTRA!) enhance the documentation for types of slices in frama-c
  - [x] (EXTRA!) enhance the documentation for the definition of slices
- [x] study more about **-slice-assert**, **-slice-pragma**, **-slice-return**, **-slice-calls**
  - [x] 1/2 slice-assert
  - [x] 2/2 slice-pragma
  - [x] 3/4 slice-return
  - [x] 4/4 slice-calls019980
- [ ] 1 example with various criterions focusing in a **assert(0)** <- this is expected to be an error
- [x] test the output of frama-c combined with **esbmc.org** <- COMPLEX!
  - [x] 1/5
  - [x] 2/5
  - [x] 3/5
  - [x] 4/5
  - [x] 5/5
- [x] Refactor all the repository, adding the new tools to the README
  - [x] Refactor documentation of frama-c
  - [x] Create documentation for esbmc
    - [x] 1/4 what is it?
    - [x] 2/4 installation
    - [x] 3/4 what it can do?
    - [x] 4/4 Examples of use

---

## **22/05~29/05**

- [x] Selecionar 5 programas de https://sv-comp.sosy-lab.org/2023/benchmarks.php com LOOPs

- [x] Testar com várias opções do FRAMA-C
  - [x] 1/5 [loop_array2-2.c](./tests/loop_tests/loop_array2-2.c)
    - [x] 1/5
    - [x] 2/5
    - [x] 3/5
    - [x] 4/5
    - [x] 5/5
  - [ ] 2/5 [loop_functions1-1.c](./tests/loop_tests/loop_functions1-1.c)
    - [ ] 1/5
    - [ ] 2/5
    - [ ] 3/5
    - [ ] 4/5
    - [ ] 5/5
  - [ ] 3/5 [loop_multivar1-1.c](./tests/loop_tests/loop_multivar1-1.c)
    - [ ] 1/5
    - [ ] 2/5
    - [ ] 3/5
    - [ ] 4/5
    - [ ] 5/5
  - [ ] 4/5 [loop_nested1-1.c](./tests/loop_tests/loop_nested1-1.c)
    - [ ] 1/5
    - [ ] 2/5
    - [ ] 3/5
    - [ ] 4/5
    - [ ] 5/5
  - [ ] 5/5 [loop_underapprox1-2.c](./tests/loop_tests/loop_underapprox1-2.c)]
    - [ ] 1/5
    - [ ] 2/5
    - [ ] 3/5
    - [ ] 4/5
    - [ ] 5/5
- [ ] Slice por localização no código
- [x] Um exemplo de uso com ESBMC
- [x] (EXTRA!) complete the udemy course:**Functiona Verification - a holistic view**
- [ ] (EXTRA!) complete the udemy course: **ROS for Beginners II**
- [ ] (EXTRA!) study all the 3 slide presentations in ESBMC documentation website:
  - [x] 1/3
  - [ ] 2/3
  - [ ] 3/3

## 31/05/23 ~ 11/07/23

- [ ] Definir as opções do FRAMA-C para efetuar o slice nos arquivos em C
  - [ ] Verificar para cada programa se ele é um código funcional, i.e., aceito pelo ESBMC
  - [ ] Passar cada código pelo ESBMC, e tabelar os resultados incluindo o tempo
  - [ ] Análise comparativa usando o ESBMC sem efetuar o slice com o Frama-C, i.e., os códigos originais
- [ ] Testar a ferramenta map2check
- [ ] (EXTRA!) Realizar testes no cruise_control

---

---

---

## to go back to the previous page: [Click me!](../../README.md)
