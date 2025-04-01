/*----------------------------------------------------------------------------------*/
/* FATEC-São Caetano do Sul                        Estrutura de Dados                     */
/* Id da Atividade: B1 - 4                                */
/* Objetivo: << Fazer uma calculadora RPN >>                                 */
/* */
/* Autor: Mariana Alfonsetti Moderoso              */
/* Data: 01/04/2025              */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 4 

typedef struct {
    double dados[MAX];
    int topo;
} Pilha;  //LIFO = Last In First Out = O primeiro entra e o último sai, como uma pilha de livros lidos.
//só o primeiro da lista pode ser visto, o resto só pode ser quando ir retirando da pilha 

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
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

//PUSH insere um elemento no topo da pilha

void push(Pilha* p, double dado) {
    if (cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return;
    }
    p->topo++; 
    p->dados[p->topo] = dado;
}

//TOP consulta pelo elemento do topo 

double top(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    return p->dados[p->topo];
}

//POP tira e retorna o elemento do topo

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(1);
    }
    return p->dados[p->topo--];
}

double calcular_rpn(char* expressao) {
    Pilha* p = criar_pilha();
    char* parte = strtok(expressao, " "); //STRTOK divide uma string em partes menores (torna a tecla "espaço" um delimitador para processar número/operador)
    char expressao_alg[100] = "";
    char temp[50]; //para armazenar os números colocados (na versão algébrica)

//ISDIGIT confirma que é número ATOF converte string para double (letra pra número)

    while (parte) {
        if (isdigit(parte[0]) || (parte[0] == '-' && isdigit(parte[1]))) {
            double num = atof(parte);
            push(p, num);
            sprintf(temp, "%.2f ", num);
            strcat(expressao_alg, temp); // STRCAT junta as strings
        } else {
            double b = pop(p);
            double a = pop(p);
            double resultado;
            char operador = ' ';

            if (parte[0] == '+') {
                resultado = a + b;
                operador = '+';
            } else if (parte[0] == '-') {
                resultado = a - b;
                operador = '-';
            } else if (parte[0] == '*') {
                resultado = a * b;
                operador = '*';
            } else if (parte[0] == '/') {
                if (b == 0) {
                    printf("Erro: Divisão por zero!\n");
                    exit(1);
                }
                resultado = a / b;
                operador = '/';
            } else {
                printf("Erro: Operador inválido!\n");
                exit(1);
            }

            push(p, resultado);
            sprintf(temp, "(%.2f %c %.2f) ", a, operador, b);
            strcat(expressao_alg, temp);
        }
        parte = strtok(NULL, " ");
    }

    double resultado_final = pop(p);
    printf("Expressão algébrica: %s\n", expressao_alg);
    printf("Resultado: %.2f\n", resultado_final);
    free(p);
    return resultado_final;
}

int main() {
    char expressao[100];
    printf("Digite a expressão RPN: ");
    fgets(expressao, sizeof(expressao), stdin); //FGETS lê o que o user inseriu no caso o STDIN
    expressao[strcspn(expressao, "\n")] = 0;//STRCSPN encontra a posição de um caractere em uma string
    calcular_rpn(expressao);
    return 0;
}