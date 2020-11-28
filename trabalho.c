#include<stdio.h>
#include"trabalho.h"

int trabalho() {

    struct empresa* empresa;

    int op;

    do {
        printf("\t\tGestor para a Empresa\n\n");
        printf("Escolha a opcao:\n");
        printf("\t1\n");
        printf("\t2\n");
        printf("\t3\n");
        printf("\t4\n");
        printf("\t0-Sair\n");
        scanf("%d", &op);
        switch (op) {
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 0:
            break;
        default:

            printf("Opcao invalida!\n\n");
        }
    } while (op != 0);

    return 0;
};