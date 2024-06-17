#include <stdio.h>
#include "calculadora.h"

int main() {
    char posFixa1[] = "3 4 2 * 1 5 - 2 3 ^ ^ / +";
    char posFixa2[] = "5 1 2 + 4 * + 3 -";

    printf("Testando a expressão: %s\n", posFixa1);
    printf("Infixa: %s\n", getFormaInFixa(posFixa1));
    printf("Valor: %f\n", getValor(posFixa1));

    printf("Testando a expressão: %s\n", posFixa2);
    printf("Infixa: %s\n", getFormaInFixa(posFixa2));
    printf("Valor: %f\n", getValor(posFixa2));

    return 0;
}
