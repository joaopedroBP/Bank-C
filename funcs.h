typedef struct{
    char sinal[2];
    float valor;
}extrato; // struct que contem as informações de extrato de um cliente.

typedef struct{
    char nome[100];
    char CPF[500];
    int conta;
    float valor;
    char senha[100];
    extrato extr[100];// substruct de extratos.
    int eqtd;// quantidade de extratos armazenados.
}cliente;//struct que armazena as informações de um cliente.

typedef struct{
    cliente clientes[1000];
    int qtd;
}clientes;//struct que armazena os clientes;

//funções;

void entrada(char *txt, char *str,  int tamanho);
float chartofloat(char *txt);
int menu();
int newclient(clientes *cls);
void clearbuffer();
int saveclients(clientes *cls, char nome[]);
int lerclientes(clientes *cls, char nome[]);
int listclients(clientes cls);
int chartoint(char *txt);
int securityCheck(clientes *cls);
int accountCheck(clientes *cls, int pos);
int deposito(clientes *cls, int pos);
int debito(clientes *cls, int loc);
int transf(clientes*cls, int lug);
int deletarConta(clientes*cls, int plc);
int deletextr(clientes *cls, int cpos);
int showextr(clientes cls, int posext);
