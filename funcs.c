#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include <string.h>

void menu(){
    printf("\nbem vindo ao banco 'Quem poupa tem'!\n");
    printf("1 - Cadastrar novo cliente.\n"
    "2 - Deletar conta.\n"
    "3 - Listar clientes.\n"
    "4 - Depositar.\n"
    "5 - Debitar.\n"
    "6 - Extrato\n"
    "7 - Transferencia entre contas\n"
    "8 - Salvar Dados e sair.\n\n");
    printf("Qual a sua escolha?: ");
    printf("\n\n==========================\n\n");
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

    printf("%f", cls->clientes[cls->qtd].valor * 0.5);

    cls->qtd += 1; 
    printf("\n\n==========================\n\n");
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
    
    for(int i = 0; i < cls.qtd ;i++){
        printf("Numero do cliente - %d\n",i + 1);
        printf("Nome - %s", cls.clientes[i].nome);
        printf("CPF - %s",cls.clientes[i].CPF);
        printf("Valor - %f\n",cls.clientes[i].valor);
    }

    printf("\n\n==========================\n\n");
    
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
    printf("Deposito realizada com sucesso! o valor depostido em sua conta agora é de %f R$",cls.clientes[pos].valor);
    printf("\n\n==========================\n\n");
    
    return 0;
}

int accountCheck(clientes cls,int position){
    if(cls.clientes[position].conta == 1){
        return 1;
    }else{
        return 0;
    }
}

int debito(clientes cls, int local){
    char str[500];

    float taxa;
    int limite;
    int conta = accountCheck(cls,local);

    if(conta == 1){
        taxa = 0.03;
        limite = -5000;
    }else{
        taxa = 0.05;
        limite = -1000;
    }

    entrada("Qual o valor que você dejesa debitar da sua conta?: ",str,500);
    int Nvalor = cls.clientes[local].valor - (chartofloat(str) + (chartofloat(str) * taxa));
    if(Nvalor >= limite){
        cls.clientes[local].valor = Nvalor;
        printf("O valor foi debitado com sucesso, o valor na sua conta agora é de %f", cls.clientes[local].valor);
        printf("\n\n==========================\n\n");
        return 0;
    }else{
        printf("O valor exede o limite permitido pela sua conta!");
        printf("\n\n==========================\n\n");
        return 1;
    }   
}
