#include <stdio.h>
#include "funcs.h"


int main(){
    clientes cls;
    int cod = lerclientes(&cls, "clientes.bin");
    if(cod == 1){
        cls.qtd = 0;
    }

    int escolha;
    int T = 0;
    while(T == 0){
        menu();
        printf("Qual a sua escolha?: ");
        scanf("%d", &escolha);

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
            case 7:
                int lugar = securityCheck(&cls);
                if(lugar != -1){
                    transf(&cls,lugar);
                }else{
                    printf("CPF ou senha incorretos!");
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
