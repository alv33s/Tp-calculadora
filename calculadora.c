#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "calculadora.h"

#define MAX 100
#define MAX_TAM 512
#define MAX_OPERANDOS 100

struct PilhaCalc {
    double valores[MAX_OPERANDOS];
    char infixas[MAX_OPERANDOS][MAX_TAM];
    char posfixa[MAX_TAM];
    int topo;
};

void inicializaPilha(struct PilhaCalc *p) {
    p->topo = -1;
    p->posfixa[0] = '\0';
}

int pilhaVazia(struct PilhaCalc *p) {
    return p->topo == -1;
}

int pilhaCheia(struct PilhaCalc *p) {
    return p->topo == MAX_OPERANDOS - 1;
}

void empilhaCalc(struct PilhaCalc *p, double valor, const char *infixa, const char *token) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia.\n");
        return;
    }
    p->topo++;
    p->valores[p->topo] = valor;
    strcpy(p->infixas[p->topo], infixa);
    strcat(p->posfixa, token);
    strcat(p->posfixa, " ");
}

double desempilhaCalc(struct PilhaCalc *p, char *infixa) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia.\n");
        return 0;
    }
    double valor = p->valores[p->topo];
    strcpy(infixa, p->infixas[p->topo]);
    p->topo--;
    return valor;
}

void processaOperadorBinario(struct PilhaCalc *p, const char *token, double (*operacao)(double, double), const char *formato) {
    char infixa2[MAX_TAM], infixa1[MAX_TAM];
    double numero2 = desempilhaCalc(p, infixa2);
    double numero1 = desempilhaCalc(p, infixa1);
    double resultado = operacao(numero1, numero2);
    char novaInfixa[MAX_TAM];
    sprintf(novaInfixa, formato, infixa1, infixa2);
    empilhaCalc(p, resultado, novaInfixa, token);
}

void processaOperadorUnario(struct PilhaCalc *p, const char *token, double (*operacao)(double), const char *formato) {
    char infixa[MAX_TAM];
    double numero = desempilhaCalc(p, infixa);
    double resultado = operacao(numero);
    char novaInfixa[MAX_TAM];
    sprintf(novaInfixa, formato, infixa);
    empilhaCalc(p, resultado, novaInfixa, token);
}

double soma(double a, double b) { return a + b; }
double subtracao(double a, double b) { return a - b; }
double multiplicacao(double a, double b) { return a * b; }
double divisao(double a, double b) { return a / b; }
double potencia(double a, double b) { return pow(a, b); }
double raizQuadrada(double a) { return sqrt(a); }
double seno(double a) { return sin(a); }
double cosseno(double a) { return cos(a); }
double tangente(double a) { return tan(a); }

void processaToken(struct PilhaCalc *p, const char *token) {
    char *endptr;
    double numero = strtod(token, &endptr);
    if (endptr != token) {
        empilhaCalc(p, numero, token, token);
    } else {
        if (strcmp(token, "+") == 0) {
            processaOperadorBinario(p, token, soma, "(%s + %s)");
        } else if (strcmp(token, "-") == 0) {
            processaOperadorBinario(p, token, subtracao, "(%s - %s)");
        } else if (strcmp(token, "*") == 0) {
            processaOperadorBinario(p, token, multiplicacao, "(%s * %s)");
        } else if (strcmp(token, "/") == 0) {
            processaOperadorBinario(p, token, divisao, "(%s / %s)");
        } else if (strcmp(token, "^") == 0) {
            processaOperadorBinario(p, token, potencia, "(%s ^ %s)");
        } else if (strcmp(token, "sin") == 0) {
            processaOperadorUnario(p, token, seno, "sin(%s)");
        } else if (strcmp(token, "cos") == 0) {
            processaOperadorUnario(p, token, cosseno, "cos(%s)");
        } else if (strcmp(token, "tan") == 0) {
            processaOperadorUnario(p, token, tangente, "tan(%s)");
        } else if (strcmp(token, "raiz") == 0) {
            processaOperadorUnario(p, token, raizQuadrada, "raiz(%s)");
        } else {
            printf("Operação invalida.\n");
            exit(EXIT_FAILURE);
        }
    }
}

double avaliarExp(char *expressao, char *infixaFinal, char *posfixaCompleta) {
    struct PilhaCalc p;
    inicializaPilha(&p);

    char *token = strtok(expressao, " ");
    while (token) {
        processaToken(&p, token);
        token = strtok(NULL, " ");
    }

    double resultadoFinal = desempilhaCalc(&p, infixaFinal);
    strcpy(posfixaCompleta, p.posfixa);
    return resultadoFinal;
}

float getValor(char *Str) {
    char infixa[MAX_TAM];
    char posfixa[MAX_TAM];
    return avaliarExp(Str, infixa, posfixa);
}

char* getFormaInFixa(char *Str) {
    static char infixa[MAX_TAM];
    char posfixa[MAX_TAM];
    avaliarExp(Str, infixa, posfixa);
    return infixa;
}
