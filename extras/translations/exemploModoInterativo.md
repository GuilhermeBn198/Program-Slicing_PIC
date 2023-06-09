# Example of use(interactive mode):

-   first, to open the interactive mode you can run the command:

        frama-c-gui

    -   you can access your original source code with the options at the top left corner and run the tests with the EVA plugin. Just like the image below. ⬇️
        ![example](../../materials/imgs/frama-cExample1.png)
    -   here you can see that your code is displayed at the right corner of the screen, which cannot be modified, whenever the code changes you need to reach the marked in green option in the top corner of the screen and select it again.
    -   the panel below the code show you the messages of the analysis and other properties of the archive.

-   here is a example of my code which was improved by the analysis of the tool, I discovered that the variables of my code were reaching overflow. I solved the problem typing them to unsigned long long. [you can see it here](../../tests/simple_tests/slice-calls/test1.c)

    ```c
    void readln(char *str) {
        fgets(str, 100, stdin); // lê até 100 caracteres da entrada padrão (teclado) e armazena em 'str'
        if (str[strlen(str) - 1] == '\n') // verifica se a última letra é um caractere de nova linha
            str[strlen(str) - 1] = '\0'; // se sim, substitui por um caractere nulo
    }

    int main() {
        char n[100];
        readln(n);
        unsigned long long i = 1;
        unsigned long long sum = 0; // utilizamos o tipo de dados unsigned long long para evitar overflow em sum
        unsigned long long product = 1; // msm caso de sum
        int num = atoi(n);
        while (i <= num) {
            sum = sum + i;
            product = product * i;
            i = i + 1;
            printf("soma: %llu \n", sum); // utilizamos o especificador de formato %llu para imprimir valores unsigned long long
            printf("produto: %llu \n", product);
        }
        return 0;
    }
    ```

---

# slicing code

-   After performing the initial analysis with EVA, we will start the steps to perform code slicing:

-   In this case, we will slice everything related to the "sum" variable's printf:
    ![Initial code](../../materials/imgs/slicingcodigoGUI1.png)

-   To do this, we need to select the printf statement on line 22, which is where the "sum" variable is being used. After that, right-click on it and hover over "Slicing." Then, click on "Slice calls to," which means that it will slice everything related to the call of this function.

-   After that, we can see the result:
    ![Sliced code](../../materials/imgs/slicingcodigoGUI2.png)

-   frama-c sliced the parts of the code which doesn't relate to the 'sum' variable.

## to go back to the previous page: [Click me!](../README.md)
