#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include <string.h>

void menu(){
    printf("bem vindo ao banco 'Quem poupa tem'!\n");
    printf("1: Cadastrar novo cliente.\n"
    "2:Deletar conta.\n"
    "3:Listar clientes.\n"
    "4:Debitar.\n"
    "5:Depositar.\n"
    "6:Extrato\n"
    "7:Transferencia entre contas\n"
    "8:Salvar Dados e sair.\n");
}

int lerclientes(clientes *cls, char nome[]){
    FILE *f = fopen(nome, "rb");
    if(f == NULL){
        return 1;
    }

    fread(cls,sizeof(clientes),1,f);

    fclose(f);
    
    return 0;
}


void entrada(char *txt, char *str, int tamanho){
    printf("%s\n",txt);
    strcpy(str,"");
    fgets(str,tamanho,stdin);
    printf("");
}

void clearbuffer() {
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}

int chartofloat(char *txt){
    float num;
    int contador = 0;
    for(int i = 0; i < strlen(txt); i++){
        if(txt[i] == ','){
            contador += 1;
        }
    }
    num = atof(txt);
    // contar toda as virgulas e usar um for para subistituir apenas a da casa decimal(se der tempo de fazer isso);
    return num;
}

int newclient(clientes *cls){
    char str[200];
    if(cls->qtd == 1000){
        printf("limite de contas atingido");
        return 1;
    }
    while(1){
        clearbuffer();
        entrada("Qual vai ser o nome da sua conta?: ",str,500);
        strcpy(cls->clientes[cls->qtd].nome,str);

        entrada("Qual o seu CPF?: ",str,500);
        strcpy(cls->clientes[cls->qtd].CPF,str);

        
        entrada("Sua conta sera do tipo comum ou do tiplo plus?: ",str,500);
        strcpy(cls->clientes[cls->qtd].conta,str);


        entrada("Qual sera a senha da sua conta?: ",str,500);
        strcpy(cls->clientes[cls->qtd].senha,str);

        entrada("Qual ser ao valor inicial da sua conta?: ",str,500);
        cls->clientes[cls->qtd].valor = chartofloat(str);

        break;
    }
    cls->qtd += 1;  
    return 0;
}

int saveclients(clientes *cls, char nome[]){
    FILE *f = fopen(nome,"wb");

    if(f == NULL){
        return 1;
    }  

    fwrite(cls,sizeof(clientes),1,f);
    fclose(f);
}
