#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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