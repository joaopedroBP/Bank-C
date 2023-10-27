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
        printf("\n\n");
    }

    printf("\n\n==========================\n\n");
    
    return 0;
}

int securityCheck(clientes *cls){
    char str[500];
    char CPF[500];
    char senha[200];
    while(1){
        clearbuffer();
        entrada("Qual o CPF vinculado a sua conta?",str,500);
        strcpy(CPF,str);

        entrada("Qual a senha da sua conta?",str,500);
        strcpy(senha,str);
        break;
    }
    
    for(int i = 0; i < cls->qtd; i++){
        if(strcmp(cls->clientes[i].CPF,CPF) == 0 && strcmp(cls->clientes[i].senha,senha) == 0){
            return i;
        }
    }

    return -1;
}

int accountCheck(clientes *cls, int pos ){
    if(cls->clientes[pos].conta == 1){
        return 1;
    }else{
        return 0;
    }
}

int deposito(clientes *cls, int pos){
    char str[500];
    entrada("Qual o valor que dejesa depositar na sua conta?: ",str,500);
    cls->clientes[pos].valor += chartofloat(str);
    printf("o valor da sua conta agora é %f",cls->clientes[pos].valor);
    printf("\n\n==========================\n\n");
    return 0;
}

int debito(clientes *cls, int loc){
    char str[500];
    float taxa;
    float limite;

    int conta = accountCheck(cls,loc);

    if(conta == 1){
        taxa = 0.03;
        limite = -5000;
    }else{
        taxa = 0.05;
        limite = -1000;
    }

    entrada("Qual o valor que dejesa debitar da sua conta?: ",str,500);

    float Nvalor = cls->clientes[loc].valor - (chartofloat(str) + (chartofloat(str) * taxa));
    if(Nvalor >= limite){
        cls->clientes[loc].valor = Nvalor;
        printf("\n\n==========================\n\n");
        return 1;
    }else{
        printf("Valor debitado excede o limite da conta!");
        printf("\n\n==========================\n\n");
        return 0;
    }


}

int transf(clientes*cls, int lug){
    char str[500];
    float taxa;
    float limite;

    int conta = accountCheck(cls,lug);

    if(conta == 1){
        taxa = 0.03;
        limite = -5000;
    }else{
        taxa = 0.05;
        limite = -1000;
    }

    printf("Certo, dados confirmados, aperte enter para entrar com os dados do receptor!");
    int lug2 = securityCheck(cls);

    if(lug2 == -1){
        printf("CPF ou senha do recptor incorretos!");
        return 0;
    }
    else{
        entrada("Qual valor você dejesa depositar na outra conta?: ",str,500);
        float Nvalor = cls->clientes[lug].valor - (chartofloat(str) + (chartofloat(str) * taxa));
        float Nvalor2 = chartofloat(str);
        if(Nvalor >= limite){
            cls->clientes[lug].valor = Nvalor;
            cls->clientes[lug2].valor += Nvalor2;
            printf("Trasnferência realizda com exito!");
            printf("\n\n==========================\n\n");
            return 1;
        }else{
            printf("Valor debitado exede o limite da conta, transferência cancelada");
            printf("\n\n==========================\n\n");
            return 0;
        }

    }
}

int deletarConta(clientes*cls, int plc){
    int indice = plc;
    char  str[500];

    entrada("Essa conta sera deletada permanentemente, tem certeza que dejsesa fazer isso?\nse sim digite 1, se não digite 0",str,500);

    if(chartoint(str) == 0){
        printf("Operação cancelada!");
        printf("\n\n==========================\n\n");
        return 0;
    }else if(chartoint(str) == 1){
        for(;indice < cls->qtd;indice++){
            strcpy(cls->clientes[indice].nome,cls->clientes[indice + 1].nome);
            strcpy(cls->clientes[indice].CPF,cls->clientes[indice + 1].CPF);
            cls->clientes[indice].conta = cls->clientes[indice + 1].conta;
            cls->clientes[indice].valor = cls->clientes[indice + 1].valor;
            strcpy(cls->clientes[indice].senha , cls->clientes[indice + 1].senha);
        }

        printf("\nConta deletada com sucesso!\n");
        printf("\n\n==========================\n\n");

        cls->qtd--;
        return 1;
    }
    
}
