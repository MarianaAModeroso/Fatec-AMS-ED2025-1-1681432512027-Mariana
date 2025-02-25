
#include <stdio.h>

void calculodesc(float* Ppreco, float* Pprecodesc, float* Pprecocomdesc) {
    *Pprecocomdesc = *Ppreco - (*Ppreco * (*Pprecodesc / 100));
}

        
  


int main()
{


float preco;
float desc; 
float precodesc;
float precocomdesc;
char  resp;


float*Ppreco=&preco;
float*Pdesc=&desc;
float*Pprecodesc=&precodesc;
float*Pprecocomdesc=&precocomdesc;

printf("insira o valor do produto: ");
    scanf("%f", &preco);

printf("Digite S ou s caso queira adicionar desconto: ");
    scanf(" %c", &resp);

if(resp == 'S'|| resp == 's'){
    printf("insira o valor do desconto: "); 
    scanf("%f", Pprecodesc);
    
   calculodesc(Ppreco, Pprecodesc, Pprecocomdesc); 
   
        printf("O valor original do produto é: R$ %.2f \n", *Ppreco); 
        printf("O valor do desconto atribuído é: R$ %.2f \n", *Pprecodesc); 
        printf("O valor da compra com desconto é: R$ %.2f \n", *Pprecocomdesc); 
}
else {
    
   printf("O valor da compra é: R$ %.2f \n", preco);
}

return 0; 
}
