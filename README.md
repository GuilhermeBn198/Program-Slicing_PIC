# Program Slicing PIC
 Oriented by Herbert Rocha <br>
Map2Check – Uma Abordagem para Verificação de Programas com Loops usando Program Slicing

---
### TO DO 27/03~10/04:
- [x] Instalar o Frama-C
  - [x] tutorial de instação do programa concluído!
- [ ] Criar um tutorial de como usar https://frama-c.com/fc-plugins/slicing.html
    - [ ] aprender a usar a ferramenta
    - [ ] fazer testes
- [ ] Ler o Capitulo 2 da Tese sobre program slicing
  - [x] 1/3
  - [x] 2/3
  - [ ] 3/3
---

## Program Slicing
### What is it?

It's a term used in several  techniques to decompose a program based on data-flow information. It extracts statements of a program that are relevant to the program’s behavior with respect to certain criteria. 

### We can divide program slicing into two categories:
1.  Dynamic analysis, which executes a program and look for erroneous behaviour during the execution of a program.
2.  Static analysis, which does not execute the program at all and tries to draw conclusions about a program only from the source code or some other program representation.
### There are 3 different aproaches we can do to slice a program:
1.  Data-Flow Aproach:
  
   a

2.  Use of Dependence Graphs
   
   a

3.  Slicing with pointers and Unstructured control flow

## FRAMA-C
### What is it?
Frama-C is an open-source extensible and collaborative platform dedicated to source-code analysis of C software. The Frama-C analyzers assist you in various source-code-related activities, from the navigation through unfamiliar projects up to the certification of critical software.
### What it can do?

### New versions! [CLICK ME](./extras/informacoesimportantes.md) (pt-br)
### Tutorial for installation: [CLICK ME!](./extras/TutorialPSFramaC.md)
### Example of usage: