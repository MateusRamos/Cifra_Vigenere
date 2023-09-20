#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char criptografia[128];

//fun�ao para transformar todas as letras em maiusculas.
void transformarMaiusculas(char *texto_entrada){
  int i;
  int k = strlen(texto_entrada);

  for(i=0; i < k; i++)
  {
    texto_entrada[i] = toupper(texto_entrada[i]);
  }
}

//fun��o para remover numeros e caracteres especiais n�o permitidos.
void removerNaoLetras(char *texto_entrada){

    int i , j = 0;
    int k = strlen(texto_entrada);
    char texto_limpo[128];

    for(i=0; i < k; i++){
        if(texto_entrada[i]>='A' && texto_entrada[i]<='Z'){ 
            texto_limpo[j] = texto_entrada[i];
            j++;
        }
    }

    for(i=0; i < j; i++){
        texto_entrada[i] = texto_limpo[i];
    }
    texto_entrada[i] = '\0';
}

void cifrar(char *texto_entrada, char *chave, int tipo_cifra){

    int i;
    int k = strlen(texto_entrada);

    transformarMaiusculas(texto_entrada);
    transformarMaiusculas(chave);
    removerNaoLetras(texto_entrada);
    removerNaoLetras(chave);

    for(i = 0; i < k; i++){
        if(tipo_cifra == 1){
            criptografia[i] = ((texto_entrada[i] - 'A') + (chave[i % strlen(chave)] - 'A')) % 26 + 'A';
        }
        else{
            criptografia[i] = (texto_entrada[i] - chave[i % strlen(chave)] + 26) % 26 + 'A';
        }
    }
}

//Fun��o para remover qualquer espe�o em branco da string de entrada
void removerEspacos(char *texto_entrada) {
    int len = strlen(texto_entrada);
    int i, j = 0;

    for (i = 0; i < len; i++) {
        if (texto_entrada[i] != ' ') {
            texto_entrada[j++] = texto_entrada[i];
        }
    }

    texto_entrada[j] = '\0';
}

int main() {
    char texto_entrada[128], chave[128], m1[128], m2[128];
    int option = 0, auxiliar, opcao;

    printf("||=================================================================||");
    printf("\n||==============>> CRIPTOGRAFIA - CIFRA DE VIGENERE <<=============||\n");
    printf("||-----------------------------------------------------------------||");
    printf("\n|| Regras:                                                         ||");
    printf("\n|| > No maximo 128 caracteres;                                     ||");
    printf("\n|| > Somente e permitida a utilizacao de letras e espacos;         ||");
    printf("\n|| > Acentos e cedilha nao sao permitidos                          ||");
    printf("\n||-----------------------------------------------------------------||");
    printf("\n|| Escolha uma opcao:                                              ||\n");
    printf("|| ( 1 ) Criptografar                                              ||\n");
    printf("|| ( 2 ) Descriptografar                                           ||\n");
    printf("|| ( 3 ) Encerrar                                                  ||\n");
    printf("||=================================================================||");


    do{
        printf("\n\nDigite o numero da opcao escolhida:\n");
        scanf("%d",&option);

        fflush(stdin); //__fpurge(stdin); //somente no linux

        auxiliar = 1;

        if(option!=1 && option!=2 && option!=3){
            printf("\n\nOpcao invalida!\n");
            auxiliar = 0;
        }
    }
    while(auxiliar == 0); // Verifica se foi digitado algum texto

    switch(option){
       
        case 1:
            printf("\n\n==>> Opcao escolhida: CRIPTOGRAFAR <<==\n");
            opcao = 1;
            strcpy(m1, "Texto original");
            strcpy(m2, "Texto criptografado");
            break;

        case 2:
            printf("\n\n==>> Opcao escolhida: DESCRIPTOGRAFAR <<==\n");
            opcao = 2;
            strcpy(m1, "Texto criptografado");
            strcpy(m2, "Texto original");
            break;

        case 3:
            printf("||=================================================================||");
            return 0;

    }

    //Tratamento do texto
    do{
        printf("\n> Digite o texto: \n>>");
        fgets(texto_entrada,128,stdin);
        
        removerEspacos(texto_entrada);

        fflush(stdin);//__fpurge(stdin); //somente no linux

        if(texto_entrada[strlen(texto_entrada)-1]=='\n'){
            texto_entrada[strlen(texto_entrada)-1]='\0';
        }
        
        auxiliar = 1;

        if((!strlen(texto_entrada)) || (strlen(texto_entrada) < 4)){
            printf("\n!-- O texto deve ter no minimo 4 caracteres --!");
            auxiliar = 0;
        }
    }
    while(auxiliar == 0);

    //Tratamento da chave
    do{
        printf("\n> Digite a chave: \n>>");
        fgets(chave,128,stdin);

        fflush(stdin);//__fpurge(stdin);  //somente no linux

         if(texto_entrada[strlen(texto_entrada)-1]=='\n'){
            texto_entrada[strlen(texto_entrada)-1]='\0';
        }

        auxiliar = 1;

        if((!strlen(chave)) || (strlen(chave) < 4)){
            printf("\n!-- A chave deve ter no minimo 4 caracteres --!");
            auxiliar = 0;
        }
    }
    while(auxiliar == 0);
        
        //Cifrar
        cifrar(texto_entrada,chave,opcao);

        printf("\n\n||----------------------------------------------------");
        printf("\n||> %s: \t\t%s",m1,texto_entrada);
        printf("\n||> Chave: \t\t\t\t%s",chave);
        printf("\n||> %s: \t\t%s",m2,criptografia);
        printf("\n||----------------------------------------------------");
        printf("\n\n\n");
        getchar();

    return 0;
}
