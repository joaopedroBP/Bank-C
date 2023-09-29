#include <stdio.h>
#include "funcs.h"

void menu(){
    printf("bem vindo ao seu banco \n");
    printf("1: Cadastrar novo cliente.\n"
    "2:Deletar conta.\n"
    "3:Listar clientes.\n"
    "4:Debitar.\n"
    "5:Depositar.\n"
    "6:Extrato\n"
    "7:Transferencia entre contas\n"
    "8:Salvar Dados.\n"
    "9:Sair.\n");
}

void entrada(char *txt, char *str, int tamanho){
    printf("%s\n",txt);
    strcpy(str,"");
    fgets(str,tamanho,stdin);
    printf("");
}



int newclient(clientes *cls){
    char str[200];
    if(cls->qtd == 1000){
        printf("limite de contas atingido");
        return 1;
    }

    entrada("Qual vai ser o nome da sua conta?: ",str,500);
    strcpy(cls->clientes[cls->qtd].nome,str);
    getchar();

    entrada("Qual o seu CPF?: ",str,500);
    strcpy(cls->clientes[cls->qtd].CPF,str);
    getchar();

    entrada("Sua conta sera do tipo comum ou do tiplo plus?: ",str,500);
    strcpy(cls->clientes[cls->qtd].conta,str);
    getchar();

    printf("Qual o valor inicial que dejesa colocar na sua conta?: ");
    scanf("%d",&cls->clientes[cls->qtd].valor);
    getchar();

    entrada("Qual sera a senha da sua conta?: ",str,500);
    strcpy(cls->clientes[cls->qtd].senha,str);
    getchar();

    printf("%c",cls->clientes[cls->qtd].senha);
    cls->qtd += 1;
    return 0;
}

