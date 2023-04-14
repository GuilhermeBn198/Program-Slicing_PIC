# Example of use(interactive mode):
- first, with the frama-c interactive version opened, you can access your original source code with the options at the top left corner and run the tests with the EVA plugin. Just like the image below. ⬇️
 ![example](../extras/imgs/frama-cExample1.png)
- you can see that your code is displayed at the right corner of the screen, which cannot be modified, you need to reach the option in the right side of where you went to put the modified code in the tool.
- the below section shows you the messages of the analysis and other properties. 
- here is a example of my code which was improved by the analysis of the tool, which i discovered that the variables of my code were reaching overflow. I solved the problem typing them to unsigned long long. [you can see it here](../tests/test1.c)
    ```
    void readln(char *str) {
        fgets(str, 100, stdin); // lê até 100 caracteres da entrada padrão (teclado) e armazena em 'str'
        if (str[strlen(str) - 1] == '\n') // verifica se a última letra é um caractere de nova linha
            str[strlen(str) - 1] = '\0'; // se sim, substitui por um caractere nulo
    }

    int main() {
        char n[100];
        readln(n);
        int i = 1;
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

## to go back to the previous page: [Click me!](../README.md)
