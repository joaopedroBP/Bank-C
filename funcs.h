typedef struct{
    char nome[100];
    char CPF[500];
    char conta[100];
    int valor;
    char senha[100];
}cliente;

typedef struct{
    cliente clientes;
    int qtd;
}clientes;

typedef struct{
    char CPF[500];
    char info[100][300];

}extrato;




int escolha;
void menu();
