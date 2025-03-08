#include <stdio.h>

#define MAX_CANDIDATOS 50

//Isso aqui é a estrutura para guardar os dados do candidato :D
struct Cand {
    char nomeal[100];
    float ntPE[4];
    float ntAC[5];
    float ntPP[10];
    float ntEB[3];
    float ntfinal;
};

// Funçãozinha para calcular a média das notas centrais
float calcularNota(float *notas, int qtdnotas) {//quantidade de notas que tem de cada tipo de avaliação
    float soma = 0.0, maior = notas[0], menor = notas[0];
    
    for (int i = 0; i < qtdnotas; i++) {
        soma += notas[i]; //Lembrar que aqui soma todas as notas
        if (notas[i] > maior) maior = notas[i]; // aqui pega a maior nota
        if (notas[i] < menor) menor = notas[i]; // aqui pega a menor nota
    }
    
    return (soma - maior - menor) / (qtdnotas - 2); //nota central 
}

void inserirCand(struct Cand *candidatos) {//ponteiro da estrutura struct cand
    printf("Insira o nome do candidato: ");
    scanf(" %[^\n]", candidatos->nomeal);//candidados -> = obrigatório para estrutura e o conteúdo inserido refere-se ao ponteiro candidatos
    getchar();//pegar os caracteres
    
    printf("\nDigite as 4 notas da Prova Escrita (PE):\n");
    for(int i = 0; i < 4; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &candidatos->ntPE[i]);
    }
    
    printf("\nDigite as 5 notas da Análise Curricular (AC):\n");
    for(int i = 0; i < 5; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &candidatos->ntAC[i]);
    }
    
    printf("\nDigite as 10 notas da Prova Prática (PP):\n");
    for(int i = 0; i < 10; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &candidatos->ntPP[i]);
    }
    
    printf("\nDigite as 3 notas da Entrevista em Banca (EB):\n\n");
    for(int i = 0; i < 3; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &candidatos->ntEB[i]);
    }
    
    float PE = calcularNota(candidatos->ntPE, 4);//declarando uma variável que vai guardar o return da função, no caso as notas 
    float AC = calcularNota(candidatos->ntAC, 5);
    float PP = calcularNota(candidatos->ntPP, 10);
    float EB = calcularNota(candidatos->ntEB, 3);
    
    candidatos->ntfinal = (PE * 0.3) + (AC * 0.1) + (PP * 0.4) + (EB * 0.2);//conta da nota final
}



//Essa função *ordena os candidatos* em ordem decrescente com base na notaFinal, utilizando o algoritmo *Bubble Sort*.
void ordenarCandidatos(struct Cand *candidatos, int total) {

    for (int i = 0; i < total - 1; i++) {//percorre as notas armazenadas dentro da estrutura
        for (int j = 0; j < total - i - 1; j++) {//percorre elementos desordenados
            if (candidatos[j].ntfinal < candidatos[j + 1].ntfinal) {
                struct Cand temp = candidatos[j];
                candidatos[j] = candidatos[j + 1];
                candidatos[j + 1] = temp;
                //**O loop externo (i)** → Representa as passagens pelo array.
                //- **O loop interno (j)** → Compara dois candidatos consecutivos e os troca se necessário.


            }
        }
    }
}

// Funçãozinha para mostrar os TOP 5 candidatos :D
void top5(struct Cand *candidatos, int total) {
    int qtd = (total < 5) ? total : 5;
    printf("\n===== TOP %d Candidatos =====\n", qtd);
    for (int i = 0; i < qtd; i++) {
        printf("\n%dº Lugar: %s", i + 1, candidatos[i].nomeal);
        printf("\nNota Final: %.2f\n", candidatos[i].ntfinal);
    }
}

int main() {
    struct Cand candidatos[MAX_CANDIDATOS];
    int totalCan;

   printf("Quantos candidatos deseja inserir? (Max. %d): ", MAX_CANDIDATOS);
    scanf("%d", &totalCan);

    if (totalCan > MAX_CANDIDATOS)
    {
        printf("Número de candidatos inválido!!!");
    }
    else
    {
        for (int i = 0; i < totalCan; i++) {
        printf("\n== Candidato %d ==\n", i + 1);
        inserirCand(&candidatos[i]);
    }
    //chamando função pra apresentar resultados (não precisa do printf)
    ordenarCandidatos(candidatos, totalCan);
    top5(candidatos, totalCan);
}

return 0;
}
