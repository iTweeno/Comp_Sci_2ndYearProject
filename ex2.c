#include<stdio.h>
#include"trabalho.h"


int asd() {
    int op;

    do {
        printf("\t\tGestor de edificios\n\n");
        printf("Escolha a opcao:\n");
        printf("\t1-Inserir edificio\n");
        printf("\t2-Inserir estudio\n");
        printf("\t3-Clientes\n");
        printf("\t4-Historico de viagens\n");
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

};

void inserir_edificio() {
    empresa->edificios = malloc(10,sizeof(PLATAFORMA));
};