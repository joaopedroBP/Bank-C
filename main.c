#include <stdio.h>
#include "funcs.h"


int main(){
    clientes cls;
    cls.qtd = 0;
    while(1){
        menu();
        printf("Qual a sua escolha?: ");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                newclient(&cls);
                break;
        }
        break;
    }
    return 0;
}
