#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADs_pilha_fila_aloc_enc.h"
//Jean da Silva Cruz 2011312026

// Função para avaliar a expressão aritmética
int avalia_expressao(TipoFila *exp)
{
    TipoPilha *pilha = (TipoPilha *)malloc(sizeof(TipoPilha));
    CriaPilhaVazia(pilha);

    while (!TestaFilaVazia(exp)){
        TipoItem item;
        RemoveFila(exp, &item);
        if (isdigit(item.valor)){
            item.valor = item.valor - '0';
            InserePilha(pilha, item);
        }
        else
        {
            TipoItem operando2, operando1, calculando;
            RemovePilha(pilha, &operando2);
            RemovePilha(pilha, &operando1);

            switch (item.valor){
                case '+':
                    calculando.valor = operando1.valor + operando2.valor;
                    break;
                case '-':
                    calculando.valor = operando1.valor - operando2.valor;
                    break;
                case '*':
                    calculando.valor = operando1.valor * operando2.valor;
                    break;
                case '/':
                    calculando.valor = operando1.valor / operando2.valor;
                    break;
            }
        InserePilha(pilha, calculando);
        }
    }
    TipoItem resultado;
    RemovePilha(pilha, &resultado);
    return resultado.valor;
}

// Função para ler a expressão aritmética e retornar uma fila com os caracteres da expressão
TipoFila *le_expressao(char *exp)
{
    TipoFila *fila = (TipoFila *)malloc(sizeof(TipoFila));
    CriaFilaVazia(fila);

    for(int i = 0; i < strlen(exp); i++){
        if(exp[i] != ' '){
            TipoItem item;
            item.valor = exp[i];
            InsereFila(fila,item);
        }
    }

    printf("\nExpressao: ");
    ImprimeFila(fila);
    printf("\n");

    return fila;
}

int main() {
    // A entrada é por uma array de caracteres, não aceita numeros de 2 digitos ou acima de 9 e nem negativos, porem o resultado pode ser numeros negativo.
    char expressao[] = "4 2 - 5 9 1 + * 5 / 5 / 2 * 8 -";
    TipoFila *fila = le_expressao(expressao);
    int resultado = avalia_expressao(fila);
    // Saida -4
    printf("\nResultado: %d\n", resultado);

    return 0;
}
