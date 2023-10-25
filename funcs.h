typedef struct{
    char nome[100];
    char CPF[500];
    int conta;
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
int listclients(clientes cls);
int securityCheck(clientes cls);
int accountCheck(clientes cls,int position);
int deposito(clientes cls,int pos);
int chartoint(char *txt);
int debito(clientes cls, int local);
