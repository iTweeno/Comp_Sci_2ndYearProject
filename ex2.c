#include<stdio.h>
#include"trabalho.h"
#include<string.h>
#include"ex2.h"
#include <stdbool.h>

bool checkEdificio = false;

int Gestao_Edificios() {
    int op;

    do {
        printf("\t\tGestor de edificios\n\n");
        printf("Escolha a opcao:\n");
        printf("\t1-Listar edificios\n");
        printf("\t2-Inserir edificio\n");
        printf("\t3-Remover edificio\n");
        printf("\t4-Historico de viagens\n");
        printf("\t0-Sair\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            listar_edificios();
            break;
        case 2:
            inserir_edificio();
            break;
        case 3:
            remover_edificio();
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

void listar_edificios() {
    if (empresa.num_edificios == 0) {
        printf("Nao ha edificios para listar");
    }
    else {
        for (int i = 0; i < empresa.num_edificios; i++) {
            printf("Id:%d, Morada:%s, Coordenadas:%s\n", empresa.edificios[i].id, empresa.edificios[i].morada, empresa.edificios[i].coordenadas);
        }
    }
};

void inserir_edificio() {
    int id;
    char scanmorada[100];
    char scancoords[100];
    if (!checkEdificio) {
        empresa.edificios = (EDIFICIO*)malloc(10 * sizeof(EDIFICIO));
        checkEdificio = true;
    }
    printf("Insira o id:");
    scanf("%d", &empresa.edificios[empresa.num_edificios].id);
    printf("Insira a morada:");
    scanf("%s", &scanmorada);
    printf("Insira as coordenadas:");
    scanf("%s", &scancoords);
    empresa.edificios[empresa.num_edificios].morada = malloc(strlen(scanmorada) + 1);
    strncpy(empresa.edificios[empresa.num_edificios].morada, scanmorada, strlen(scanmorada) + 1);
    empresa.edificios[empresa.num_edificios].coordenadas = malloc(strlen(scancoords) + 1);
    strncpy(empresa.edificios[empresa.num_edificios].coordenadas, scancoords, strlen(scancoords) + 1);
    empresa.num_edificios++;
};

void remover_edificio() {
    if (empresa.num_edificios = 0) {
        printf("Nao ha edificios para remover");
    }else {
        int op1;
        printf("Insira o id que quer remover");
        scanf("%d", &op1);
        for (int i = 0; i < empresa.num_edificios; i++) {
            if ((strcmp(empresa.edificios[i].id, op1)) == 0) {
                free(empresa.edificios[i].morada);
                free(empresa.edificios[i].coordenadas);
                free(empresa.edificios[i]);
                empresa.num_edificios--;
            }
        }
    }
};