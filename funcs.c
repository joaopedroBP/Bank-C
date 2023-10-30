#include <stdio.h>
#include <stdlib.h>
#include "funcs.h"
#include <string.h>

int menu(){ // função que imprime o menu para o usuario e recebe-retorna sua escolha de opção;
    int escolha;
    printf("\nbem vindo ao banco 'Quem poupa tem'!\n");
    printf("1 - Cadastrar novo cliente.\n"
    "2 - Deletar conta.\n"
    "3 - Listar clientes.\n"
    "4 - Depositar.\n"
    "5 - Debitar.\n"
    "6 - Extrato\n"
    "7 - Transferencia entre contas\n"
    "8 - Salvar Dados e sair.\n\n");
    printf("Qual a sua escolha?:");
    scanf("%d",&escolha);
    printf("\n\n==========================\n\n");
    return escolha;
}

int lerclientes(clientes *cls, char nome[]){//função que checa se existe ou não um arquivo que contem os clientes.
    FILE *f = fopen(nome, "rb");
    if(f == NULL){
        return 1;
    }
    // se o arquivo existir ela le todas as inforamções presentes nele.
    fread(cls,sizeof(clientes),1,f);

    fclose(f);
    
    return 0;
}


void entrada(char *txt, char *str, int tamanho){// função que rebe um entrada do usuario; 
    printf("%s\n",txt);
    strcpy(str,"");
    fgets(str,tamanho,stdin);
    printf("");
}

int chartoint(char *txt){ // função que trasnforma um char singular em um int.
//usada em apenas alguns casos especificos. 
    int num;
    num = atoi(txt);
    return num;
}



void clearbuffer(){
    // função criada para limpar o buffer entre fget's
    int c = getchar();

    while (c != '\n' && c != EOF)
        c = getchar();
}

float chartofloat(char *txt){ // função que converte um char para um float e o retorna.
    float num;
    int contador = 0;
    for(int i = 0; i < strlen(txt); i++){
        if(txt[i] == ','){
            contador += 1;
        }
    }
    num = atof(txt);
    return num;
}

int newclient(clientes *cls){// função que cria um novo cliente.
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

        entrada("Qual ser ao valor inicial da sua conta?separe apenas os valores decimais e use '.' para faze-lo: ",str,500);
        cls->clientes[cls->qtd].valor = chartofloat(str);

        break;
    }

    char *sinal = "+";
    strcpy(cls->clientes[cls->qtd].extr[cls->clientes[cls->qtd].eqtd].sinal,sinal);
    cls->clientes[cls->qtd].extr[cls->clientes[cls->qtd].eqtd].valor = cls->clientes[cls->qtd].valor;


    cls->clientes[cls->qtd].eqtd += 1;
    cls->qtd += 1; 

    printf("Conta criada com exito,seja bem vindo ao nosso banco!");
    printf("\n\n==========================\n\n");
    return 0;
}

int saveclients(clientes *cls, char nome[]){// função que informações modificadas/criadas ao longo do programa a um arquivo binario.
    FILE *f = fopen(nome,"wb");

    if(f == NULL){
        return 1;
    }  

    fwrite(cls,sizeof(clientes),1,f);
    fclose(f);
}

int listclients(clientes cls){// função que lista todos os clientes criados.
    
    if(cls.qtd == 0){ // se não há clientes ela retorna 1;
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

int securityCheck(clientes *cls){// função usada pra checar se um CPF/Senha estão vinculados a alguma conta.
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
            return i;//ele retorna a posição do cliente vinculado a esse CPF/senha 
        }
    }

    return -1;// retorna -1 caso não estajam vinculados a nenhuma conta;
}

int accountCheck(clientes *cls, int pos ){//checa qual o tipo de conta um cliente tem;
    if(cls->clientes[pos].conta == 1){
        return 1;
    }else{
        return 0;
    }
}

int deposito(clientes *cls, int pos){//função para depositar uma quantia em sua conta;
    char str[500];
    char *sinaldp = "+";
    entrada("Qual o valor que dejesa depositar na sua conta?: ",str,500);
    cls->clientes[pos].valor += chartofloat(str);
    printf("Deposito realizado com exito!");
    strcpy(cls->clientes[pos].extr[cls->clientes[pos].eqtd].sinal,sinaldp);
    cls->clientes[pos].extr[cls->clientes[pos].eqtd].valor = chartofloat(str);
    cls->clientes[pos].eqtd += 1;
    printf("\n\n==========================\n\n");
    if(cls->clientes[pos].eqtd == 101){
        deletextr(cls,pos);
    }
    return 0;
}

int debito(clientes *cls, int loc){//função que permite debitar um valor da sua conta;
    char *sinaldb = "-";
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
        printf("Devito realizado com exito!");
        printf("\n\n==========================\n\n");
        //mundanças no extrato.
        strcpy(cls->clientes[loc].extr[cls->clientes[loc].eqtd].sinal,sinaldb);
        cls->clientes[loc].extr[cls->clientes[loc].eqtd].valor = chartofloat(str) + (chartofloat(str) * taxa);
        cls->clientes[loc].eqtd += 1;
        
        if(cls->clientes[loc].eqtd == 101){
            deletextr(cls,loc);//checa se o extrato exede o limite.
        }
        return 1;
    }else{
        printf("Valor debitado excede o limite da conta!");
        printf("\n\n==========================\n\n");
        return 0;
    }
}

int transf(clientes*cls, int lug){//função que permite transferir um valor de uma conta para a outra.
    char *sinaltf = "+";
    char *sinaltf2 = "-";
    
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

    printf("Certo, dados do doador confirmados, aperte enter para entrar com os dados do receptor!");
    //este enter é necessário pois usar dois security checks acaba travandando o codigo, então fiz isso pra mascarar esse questão.
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
            //mudanças no extrato.
            strcpy(cls->clientes[lug].extr[cls->clientes[lug].eqtd].sinal,sinaltf2);
            cls->clientes[lug].extr[cls->clientes[lug].eqtd].valor = chartofloat(str) + (chartofloat(str) * taxa);
            cls->clientes[lug].eqtd += 1;
            
            strcpy(cls->clientes[lug2].extr[cls->clientes[lug2].eqtd].sinal,sinaltf);
            cls->clientes[lug2].extr[cls->clientes[lug2].eqtd].valor = chartofloat(str);
            cls->clientes[lug2].eqtd += 1
                ;
            if(cls->clientes[lug].eqtd == 101){
                deletextr(cls,lug);//checa se o extrato exede o limite.
            }
            if(cls->clientes[lug2].eqtd == 101){
                deletextr(cls,lug2);//checa se o extrato exede o limite.
            }
            return 1;
        }else{
            printf("Valor debitado exede o limite da conta, transferência cancelada");
            printf("\n\n==========================\n\n");
            return 0;
        }

    }
}

int deletextr(clientes *cls, int cpos) {// função que deleta o primeiro extrato de um cliente.Usada caso o limite seja exedido.
    int pos = cpos;  
    
    if (cls->clientes[pos].eqtd > 0) {
        for (int i = 0; i < cls->clientes[pos].eqtd - 1; i++) {
            strcpy(cls->clientes[pos].extr[i].sinal, cls->clientes[pos].extr[i + 1].sinal);
            cls->clientes[pos].extr[i].valor = cls->clientes[pos].extr[i + 1].valor;
        }
        
        
        cls->clientes[pos].eqtd--;
        
        return 0; 
    } else {
        
        return -1;
    }
}

int deletarConta(clientes*cls, int plc){// funlção que permite deletar uma conta existente;
    int indice = plc;
    char  str[500];

    entrada("Essa conta sera deletada permanentemente, tem certeza que dejsesa fazer isso?\nse sim digite 1, se não digite 0",str,500);

    if(chartoint(str) == 0){
        printf("Operação cancelada!");
        printf("\n\n==========================\n\n");
        return 0;
    }else if(chartoint(str) == 1){
        deletextr(cls,plc);
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


int showextr(clientes cls, int posext) {// função que cria um arquivo txt que mostra o extrato de um cliente.
    FILE *f;
    char filename[256];
        snprintf(filename, sizeof(filename), "extrato_cliente_%s.txt", cls.clientes[posext].nome);

        f = fopen(filename, "w");
        
        if (f == NULL) {
            perror("Error opening file");
            return -1;
        }

        fprintf(f, "Seu extrato\n\n\n");

        for (int i = 0; i < cls.clientes[posext].eqtd; i++) {
            fprintf(f, "%s", cls.clientes[posext].extr[i].sinal);
            fprintf(f, "%f", cls.clientes[posext].extr[i].valor);
            fprintf(f, "\n\n");
        }

        fclose(f);

        printf("Um arquivo com seu extrato foi criado!\n");
        printf("\n\n==========================\n\n");

        return 0;
    }
    return -1;  
}
