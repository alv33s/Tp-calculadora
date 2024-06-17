#ifndef CALCULADORA_H
#define CALCULADORA_H

typedef struct {
    char posFixa[512];     
    char inFixa[512];      
    float valor;           
} Expressao;

char* getFormaInFixa(char *Str);    
float getValor(char *Str);         

#endif
