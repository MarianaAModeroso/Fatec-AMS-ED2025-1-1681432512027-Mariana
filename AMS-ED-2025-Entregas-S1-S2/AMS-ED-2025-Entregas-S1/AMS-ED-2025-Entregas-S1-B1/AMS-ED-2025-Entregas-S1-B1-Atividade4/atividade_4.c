/*----------------------------------------------------------------------------------*/
/* FATEC-São Caetano do Sul                        Estrutura de Dados                 */
/* Id da Atividade: B1 - 4                                                           */
/* Objetivo: << Fazer uma calculadora RPN >>                                         */
/* */
/* Autor: Mariana Alfonsetti Moderoso                                                */
/* Data: 01/04/2025                                                                  */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 10 
#define MAX_EXP 1024

typedef struct {
    double dados[MAX];
    int topo;
    char expressao[MAX][MAX_EXP];
} Pilha;


Pilha *criar_pilha() {
    Pilha *p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro: Falha ao alocar memória para a pilha.\n");
        exit(1);
    }
    p->topo = -1;
    return p;
}


int vazia(Pilha* p) {
    return p->topo == -1;
}

int cheia(Pilha* p) {
    return p->topo == MAX - 1;
}


void push(Pilha *p, double dado, char *expr) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->topo++;
    p->dados[p->topo] = dado;
    strncpy(p->expressao[p->topo], expr, MAX_EXP - 1);
    p->expressao[p->topo][MAX_EXP - 1] = '\0';
}


double pop(Pilha *p, char *expr) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    double valor = p->dados[p->topo];
    strcpy(expr, p->expressao[p->topo]);
    p->topo--;
    return valor;
}

void calcular_rpn(char *expressao) {
    Pilha *pilha = criar_pilha();
    
    char expressao_orig[MAX_EXP];
    strncpy(expressao_orig, expressao, MAX_EXP - 1);
    expressao_orig[MAX_EXP - 1] = '\0';  

    char expressao_copia[MAX_EXP];  
    strncpy(expressao_copia, expressao, MAX_EXP - 1);
    expressao_copia[MAX_EXP - 1] = '\0';

    char *parte = strtok(expressao_copia, " ");

    while (parte != NULL) {
        if (isdigit(parte[0]) || (parte[0] == '-' && isdigit(parte[1]))) {
            push(pilha, atof(parte), parte);
        } else {
            if (pilha->topo < 1) {
                printf("Expressão Inválida!\n");
                free(pilha);
                return;
            }

            char expr1[MAX_EXP], expr2[MAX_EXP];
            double b = pop(pilha, expr2);
            double a = pop(pilha, expr1);
            double resultado;
            char nova_expr[MAX_EXP];

            if (parte[0] == '+') {
                resultado = a + b;
                snprintf(nova_expr, MAX_EXP, "(%s + %s)", expr1, expr2); 
            } else if (parte[0] == '-') {
                resultado = a - b;
                snprintf(nova_expr, MAX_EXP, "(%s - %s)", expr1, expr2);
            } else if (parte[0] == '*') {
                resultado = a * b;
                snprintf(nova_expr, MAX_EXP, "(%s * %s)", expr1, expr2);
            } else if (parte[0] == '/') {
                if (b == 0) {
                    printf("Erro: Divisão por zero!\n");
                    free(pilha);
                    return;
                }
                resultado = a / b;
                snprintf(nova_expr, MAX_EXP, "(%s / %s)", expr1, expr2);
            } else {
                printf("Erro: Operador inválido!\n");
                free(pilha);
                return;
            }

            push(pilha, resultado, nova_expr);
        }

        parte = strtok(NULL, " ");
    }

    if (pilha->topo != 0) {
        printf("Expressão Inválida!\n");
        free(pilha);
        return;
    }

    char expressao_final[MAX_EXP];
    double resultado_final = pop(pilha, expressao_final);

    printf("Expressão RPN: %s\n", expressao_orig);
    printf("Expressão Algébrica: %s\n", expressao_final);
    printf("Resultado: %.2f\n", resultado_final);

    free(pilha);
}


int main() {
    char expressao[MAX_EXP];
    printf("Digite a expressão RPN: ");
    fgets(expressao, sizeof(expressao), stdin);
    expressao[strcspn(expressao, "\n")] = 0;
    calcular_rpn(expressao);

    return 0;
}