/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: Atividade B1-3                          */
/*             Objetivo: << Comanda automatizada >>                */
/*                                                                                  */
/*                                  Autor: Mariana Alfonsetti Moderoso   */
/*                                                                   Data:24/03/2025*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Comanda {
    int pedido;
    char nome_cli[100];
    char status_ped[50];
    char desc_ped[500];
    int quant;
    struct Comanda *prox_comanda;
} Comanda;

void inserircomanda(Comanda **lista, int pedido_cli, char nome[], char status[], char desc[], int quantidade) {
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
    nova_comanda->prox_comanda = *lista;
    *lista = nova_comanda;
}

void pesquisarComandas(Comanda *lista, int pedido){
    Comanda *list = lista;
    while (list != NULL){
        if (list-> pedido == pedido){
            printf("Pedido encontrado:\n");
            printf("Nome:%s\n", list->nome_cli);
            printf("Descrição do prato:%s\n", list ->desc_ped);
            printf("Quantidade: %d\n", list->quant);
            printf("Status do pedido:%s\n", list->status_ped);
            return;
        }
        list = list -> prox_comanda;}
        printf("Pedido com número: %d não encontrado!", pedido);
    }
 void modificarStatus(Comanda *lista, int pedido, char novo_status[]){
 Comanda *list = lista;
 while (list != NULL) {
        if (list->pedido == pedido) {
            strcpy(list->status_ped, novo_status);
            printf("Status do pedido %d alterado para: %s\n", pedido, novo_status);
            return;
        }
        list = list->prox_comanda;
    } 
    printf("Pedido com número: %d não encontrado!\n", pedido);
 }
void Deletarpedido(Comanda **lista, int pedido)
{
    Comanda *atual = *lista;
    Comanda *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->pedido == pedido)
        {
            if (anterior == NULL)
            {
                *lista = atual->prox_comanda;
            }
            else
            {
                anterior->prox_comanda = atual->prox_comanda;
            }
            free(atual);
            printf("Pedido %d removido com sucesso!\n", pedido);
            return;
        }
        anterior = atual;
        atual = atual->prox_comanda;
    }
    printf("Pedido não encontrado.\n");

}

void Liberarlista(Comanda *lista)
{
    Comanda *atual = lista;
    while (atual != NULL)
    {
        Comanda *proximo = atual->prox_comanda;
        free(atual);
        atual = proximo;
    }
}

 int main(void) {
    Comanda *lista_comandas = NULL;
    char escolha[10];
    
    while (1) {
        printf("\nO que você deseja fazer?\n");
        printf("Digite 'I' para inserir um novo pedido\n");
        printf("Digite 'P' para pesquisar pedidos\n");
        printf("Digite 'M' para modificar o status de um pedido\n");
        printf("Digite 'D' para deletar um pedido\n");
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

            inserircomanda(&lista_comandas, pedido_cli, nome, status, desc, quantidade);
        } 
        else if (strcmp(escolha, "P") == 0) {
            int pedido_pesquisa;
            printf("Qual pedido deseja pesquisar?\n");
            scanf("%d", &pedido_pesquisa);
            getchar();
            pesquisarComandas(lista_comandas, pedido_pesquisa);
        } 
        else if (strcmp(escolha, "M") == 0) {
            int pedido_novo;
            char status_novo[50];
            printf("Qual pedido deseja modificar o status?\n");
            scanf("%d", &pedido_novo);
            getchar();
            printf("Digite o novo status: ");
            scanf("%[^\n]", status_novo);
            getchar();
            modificarStatus(lista_comandas, pedido_novo, status_novo);
        } 
        else if (strcmp(escolha, "D") == 0) {
            int pedido_deletar;
            printf("Digite o número do pedido para excluir: ");
            scanf("%d", &pedido_deletar);
            Deletarpedido(&lista_comandas, pedido_deletar);
        } 
        else if (strcmp(escolha, "S") == 0) {
            printf("Liberando lista\n");
            Liberarlista(lista_comandas);
            break;
        } 
        else {
            printf("Opção inválida!\n");
        }
    }
    
return 0;
}