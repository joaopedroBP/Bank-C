#include <stdio.h>
#include "funcs.h"


int main(){
    clientes cls;
    int cod = lerclientes(&cls, "clientes.bin");// usa a lerclientes para checar se um arquivo exite
    if(cod == 1){
        //seta as quantidades para 0 caso não exista;
        cls.qtd = 0;
        cls.clientes[cls.qtd].eqtd = 0;
    }

    int escolha;
    int T = 0;
    while(T == 0){
        escolha = menu();

        switch(escolha){
            case 1:
                newclient(&cls);
                break;
            case 2:
                int place = securityCheck(&cls);
                if(place != -1){
                    deletarConta(&cls,place);
                }else{
                    printf("CPF ou senha invalidos!");
                }
                break;
            case 3:
                listclients(cls);
                break;
            case 4:
                //São pedidos o CPF e senha por uma questão de padronização e praticidade.
                int pos = securityCheck(&cls);
                if(pos != -1){
                    deposito(&cls,pos);
                }else{
                    printf("CPF ou senha invalidos!");
                }
                break;
            case 5:
                int local = securityCheck(&cls);
                if(local != -1){
                    debito(&cls,local);
                }else{
                    printf("CPF ou senha invalidos!");
                }
                break;
            case 6:
                int posicao_extrato = securityCheck(&cls);
                if(posicao_extrato != -1){
                    showextr(cls,posicao_extrato);
                }else{
                    printf("CPF ou senha invalidos");
                }
                break;
            case 7:
                int lugar = securityCheck(&cls);
                if(lugar != -1){
                    transf(&cls,lugar);
                }else{
                    printf("CPF ou senha invalidos/incorretos!");
                }
                break;
            case 8:
                T++; 
                break;
        }
    }

    cod = saveclients(&cls,"clientes.bin");
    if(cod == 1){
        printf("falha ao salvar dados");
    }else{
        printf("Dados salvos com exito, obrgado por usar os nossos serviços");
    }
    return 0;
}
