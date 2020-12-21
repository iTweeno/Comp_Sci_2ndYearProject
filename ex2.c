#include<stdio.h>
#include"ex2.h"
#include"main.h"


int Gestao_Edificios() {
    int op;

    do {
        printf("\t\tGestor de edificios\n\n");
        printf("Escolha a opcao:\n");
        printf("\t1-Inserir edificio\n");
        printf("\t2-Inserir estudio\n");
        printf("\t3-Eliminar edificio\n");
        printf("\t4-Historico de viagens\n");
        printf("\t0-Sair\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            inserir_edificio(&empresa,"Rua s joao 1", 1345);
            break;
        case 2:
            inserir_estudio(&empresa, "Rua s joao 1",1,3);
            break;
        case 3:
            remover_edificio(&empresa, "Rua s joao 1");
            break;
        case 4:
            print_edificio(&empresa);
            break;
        case 0:
            break;
        default:

            printf("Opcao invalida!\n\n");
        }
    } while (op != 0);

};

int inserir_edificio(EMPRESA* empresa,char morada[], int coordenadas) {
    EDIFICIO* e = (EDIFICIO*)malloc(sizeof(EDIFICIO));
    e->morada = (char*)malloc(sizeof(char) * (strlen(morada) + 1));
    strncpy(e->morada, morada, (sizeof(char) * strlen(morada) + 1));
    e->coordenadas = coordenadas;
    e->num_estudios = 0;
    e->next = NULL;
    e->estudios = (ESTUDIO*)malloc(10 * sizeof(ESTUDIO));;

    if (empresa->num_edificios == 0 || empresa->edificio == NULL) {
        empresa->edificio = e;
        empresa->num_edificios++;
        return;
    }
    EDIFICIO* pprev = NULL;
    EDIFICIO* pcurrent = empresa->edificio;
    while (pcurrent != NULL && strcmp(morada, pcurrent->morada) < 0) {
        pprev = pcurrent;
        pcurrent = pcurrent->next;
    }
    if (pcurrent == empresa->edificio) {
        e->next = empresa->edificio;
        empresa->edificio = e;
        empresa->num_edificios++;
        return;
    }
    e->next = pcurrent;
    pprev->next = e;
    empresa->num_edificios++;
    return;
};

int remover_edificio(EMPRESA* empresa, char morada[]) {
    if (empresa->edificio == NULL) {
        printf("Nao ha edificios\n");
        return;
    }
    EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
    while (pcurrent != NULL && strcmp(morada, pcurrent->morada) != 0) {
        pprev = pcurrent;
        pcurrent = pcurrent->next;
    }
    if (pcurrent == NULL) {
        printf("Nao ha edificios com este nome\n");
        return;
    }
    if (empresa->edificio == pcurrent) {
        empresa->edificio = pcurrent->next;
        empresa->num_edificios--;
        free(pcurrent);
        return;
    }
    pprev->next = pcurrent->next;
    free(pcurrent);
    empresa->num_edificios--;
}

int inserir_estudio(EMPRESA* empresa, char morada[], int id, int quartos) {
    if (empresa->edificio == NULL) {
        printf("Nao ha edificios\n");
        return;
    }
    EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
    while (pcurrent != NULL && strcmp(morada, pcurrent->morada) != 0) {
        pprev = pcurrent;
        pcurrent = pcurrent->next;
    }
    if (pcurrent == NULL) {
        printf("Nao ha edificios com este nome\n");
        return;
    }
    if (empresa->edificio == pcurrent) {
        if (empresa->edificio->num_estudios == 10) {
            return;
        }
        empresa->edificio->estudios[empresa->edificio->num_estudios].id = id;
        empresa->edificio->estudios[empresa->edificio->num_estudios].quartos = quartos;
        empresa->edificio->num_estudios++;
        return;
    }
    if (pcurrent->num_estudios == 10) {
        return;
    }
    if (pcurrent->num_estudios == 0) {
        pcurrent->estudios = (ESTUDIO*)malloc(10 * sizeof(ESTUDIO));
    }
    pcurrent->estudios[pcurrent->num_estudios].id = id;
    pcurrent->estudios[pcurrent->num_estudios].quartos = quartos;
    pcurrent->num_estudios++;
    
}

int print_edificio(EMPRESA* empresa) {
    if (empresa->edificio == NULL) {
        printf("Nao ha edificios\n");
        return;
    }
    EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
    while (pcurrent != NULL) {
        printf("Morada: %s | Coordenadas: %d\n", pcurrent->morada, pcurrent->coordenadas);
        pprev = pcurrent;
        pcurrent = pcurrent->next;
    }
}