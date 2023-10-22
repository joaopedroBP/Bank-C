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

int chartoint(char *txt){
    int num;
    num = atoi(txt);
    return num;
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

        
        entrada("Se sua conta for ser do tipo plus, digite 1, caso contrario,digite 0",str,500);
        cls->clientes[cls->qtd].conta = chartoint(str);


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

int listclients(clientes cls){
    if(cls.qtd == 0){
        printf("nenhum cliente cadastrado\n");
        return 1;
    }

    printf("\nclientes cadastrados: \n\n");
    
    for(int i = 0; i < cls.qtd ; i++){
        printf("Numero do cliente: %d\n", i + 1);
        printf("Nome: %s", cls.clientes[i].nome);
        printf("CPF: %s", cls.clientes[i].CPF);
        printf("Tipo de conta: %s", cls.clientes[i].conta);
        printf("Senha: %s",cls.clientes[i].senha);
    }

    printf("\n");
    return 0;
}

int securityCheck(clientes cls){
    char str[500];
    char CPF[500];
    char senha[100];

    while(1){
        clearbuffer();
        entrada("Qual o CPF vinculado a sua conta?: ",str,500);
        strcpy(CPF,str);

        entrada("Qual a senha da sua conta?: ",str,500);
        strcpy(senha,str);

        break;
    }

    for(int i = 0; i < cls.qtd; i++){
        if(strcmp(cls.clientes[i].CPF, CPF) == 0 && strcmp(cls.clientes[i].senha, senha) == 0){
            return i; // retorna o indice/posição do cliente na struct de clientes caso os valores batam
        }

    }

        
    return -1;
}

int deposito(clientes cls, int pos){
    char str[200];;
    entrada("digite o valor que dejesa depositar em sua conta: ",str,500);
    cls.clientes[pos].valor += chartofloat(str);
    printf("Deposito realizada com sucesso! o valor depostido em sua conta agora é de %.2f R$\n\n",cls.clientes[pos].valor);
    return 0;
    
}
