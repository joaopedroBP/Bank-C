#include <stdio.h>
#include "funcs.h"

int main(){
    clientes cls;

    while(1){
        menu();
        printf("Qual a sua escolha?:\n");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
            printf("hello");
                break;
        }
        break;
    }
    return 0;
}
