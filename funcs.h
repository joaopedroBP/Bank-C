typedef struct{
    char nome[100];
    char CPF[500];
    char conta[100];
    float valor;
    char senha[100];
}cliente;

typedef struct{
    cliente clientes[1000];
    int qtd;
}clientes;

typedef struct{
    char CPF[500];
    char info[100][300];

}extrato;

void entrada(char *txt, char *str,  int tamanho);
int chartofloat(char *txt);


void menu();
int newclient(clientes *cls);
void clearbuffer();
int saveclients(clientes *cls, char nome[]);
int lerclientes(clientes *cls, char nome[]);
