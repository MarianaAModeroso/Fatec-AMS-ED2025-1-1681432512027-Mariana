/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-5                       */
/*             Objetivo: << Transformar Lista ligada em Pilha >>                */
/*                                                                                  */
/*                                  Autor: Mariana Alfonsetti Moderoso   */
/*                                                                   Data:01/04/2025*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Comanda {
    int pedido;
    char nome_cli[100];
    char status_ped[50];
    char desc_ped[500];
    int quant;
    struct Comanda *prox;
} Comanda;

typedef struct Pilha {
    Comanda *topo;
} Pilha;

Pilha* criarPilha() {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    p->topo = NULL;
    return p;
}

Comanda* Top(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Erro: a pilha está vazia\n");
        return NULL;
    }
    return pilha->topo;
}

void push(Comanda **topo, int pedido_cli, char nome[], char status[], char desc[], int quantidade) {
    Comanda *nova_comanda = (Comanda *)malloc(sizeof(Comanda));
    if (nova_comanda == NULL) {
        printf("Erro ao alocar memória\n");
        return;
    }
    nova_comanda->pedido = pedido_cli;
    strcpy(nova_comanda->nome_cli, nome);
    strcpy(nova_comanda->status_ped, status);
    strcpy(nova_comanda->desc_ped, desc);
    nova_comanda->quant = quantidade;
    nova_comanda->prox = *topo;
    *topo = nova_comanda;
}

void listarPedidos(Comanda *topo) {
    if (topo == NULL) {
        printf("Nenhum pedido cadastrado!\n");
        return;
    }
    printf("\nLista de Pedidos:\n");
    Comanda *atual = topo;
    while (atual != NULL) {
        printf("Pedido: %d, Cliente: %s, Status: %s, Quantidade: %d\n", atual->pedido, atual->nome_cli, atual->status_ped, atual->quant);
        atual = atual->prox;
    }
}

void pop(Comanda **topo) {
    if (*topo == NULL) {
        printf("Nenhum pedido para remover!\n");
        return;
    }
    Comanda *temp = *topo;
    *topo = (*topo)->prox;
    printf("Pedido %d removido!\n", temp->pedido);
    free(temp);
}

void liberarPilha(Comanda *topo) {
    Comanda *atual = topo;
    while (atual != NULL) {
        Comanda *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int main(void) {
    Comanda *pilha_comandas = NULL;
    char escolha[10];
    
    while (1) {
        printf("\nO que você deseja fazer?\n");
        printf("Digite 'I' para inserir um novo pedido\n");
        printf("Digite 'L' para listar os pedidos\n");
        printf("Digite 'R' para remover o último pedido\n");
        printf("Digite 'S' para sair\n");
        scanf("%s", escolha);
        getchar();

        if (strcmp(escolha, "I") == 0) {
            int pedido_cli;
            char nome[100];
            char status[50];
            char desc[500];
            int quantidade;

            printf("Qual o número do pedido?\n");
            scanf("%d", &pedido_cli);
            getchar();

            printf("Qual o nome do cliente?\n");
            scanf("%[^\n]", nome);
            getchar();

            printf("Qual o status do pedido?\n");
            scanf("%[^\n]", status);
            getchar();

            printf("Descreva o prato:\n");
            scanf("%[^\n]", desc);
            getchar();

            printf("Quantidade: ");
            scanf("%d", &quantidade);
            getchar();

            push(&pilha_comandas, pedido_cli, nome, status, desc, quantidade);
        } 
        else if (strcmp(escolha, "L") == 0) {
            listarPedidos(pilha_comandas);
        } 
        else if (strcmp(escolha, "R") == 0) {
            pop(&pilha_comandas);
        } 
        else if (strcmp(escolha, "S") == 0) {
            printf("Liberando pilha\n");
            liberarPilha(pilha_comandas);
            break;
        } 
        else {
            printf("Opção inválida!\n");
        }
    }
    return 0;
}
