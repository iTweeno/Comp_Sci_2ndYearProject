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
        printf("\t3-Inserir cliente\n");
        printf("\t4-Inserir preco\n");
        printf("\t5-Inserir Agenda\n");
        printf("\t6-Print estudios\n");
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
            inserir_cliente(&empresa, "Rua s joao 1",1, 1, "Joao", 25);
            break;
        case 4:
            inserir_preco(&empresa, "Rua s joao 1", 1, 1,10,100);
            break;
        case 5:
            remover_edificio(&empresa, "Rua s joao 1", 1345);
            break;
        case 6:
            remover_estudio(&empresa, "Rua s joao 1", 1);
            break;
        case 7:
            remover_cliente(&empresa, "Rua s joao 1", 1, 1, "Joao", 25);
            break;
        case 8:
            remover_preco(&empresa, "Rua s joao 1", 1, 1, 10, 100);
            break;
        case 9:
            editar_edificio(&empresa, "Rua s joao 1");
            break;
        case 10:
            editar_estudio(&empresa, "Rua s joao 1",1);
            break;
        case 11:
            editar_cliente(&empresa, "Rua s joao 1");
            break;
        case 12:
            editar_preco(&empresa, "Rua s joao 1");
            break;
        case 13:
            print_edificios(&empresa, "Rua s joao 1", 1, 1, 10, 100);
            break;
        case 14:
            print_estudios(&empresa, "Rua s joao 1");
            break;
        case 15:
            print_clientes(&empresa, "Rua s joao 1", 1);
            break;
        case 16:
            print_precos(&empresa, "Rua s joao 1");
            break;
        case 0:
            break;
        default:

            printf("Opcao invalida!\n\n");
        }
    } while (op != 0);

};

int inserir_edificio(EMPRESA* empresa,char morada[], int coordenadas) { //make insertion sort
    EDIFICIO* e = (EDIFICIO*)malloc(sizeof(EDIFICIO));
    e->morada = (char*)malloc(sizeof(char) * (strlen(morada) + 1));
    strncpy(e->morada, morada, (sizeof(char) * strlen(morada) + 1));
    e->coordenadas = coordenadas;
    e->num_estudios = 0;
    e->next = NULL;
    e->estudios = (ESTUDIO*)malloc(10 * sizeof(ESTUDIO));
    e->tamanho_estudio = 10;

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

int inserir_estudio(EMPRESA* empresa, char morada[], int id, int quartos) { //change size of arr
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
        empresa->edificio->estudios[empresa->edificio->num_estudios].precos = (PRECO*)malloc(10 * sizeof(PRECO));
        empresa->edificio->estudios[empresa->edificio->num_estudios].num_precos = 0;
        empresa->edificio->estudios[empresa->edificio->num_estudios].num_clientes = 0;
        empresa->edificio->estudios[empresa->edificio->num_estudios].tamanho_preco = 10;

        empresa->edificio->num_estudios++;
        return;
    }
    if (pcurrent->num_estudios == 10) {
        return;
    }
    pcurrent->estudios[pcurrent->num_estudios].id = id;
    pcurrent->estudios[pcurrent->num_estudios].quartos = quartos;
    pcurrent->num_estudios++;
}

int inserir_cliente(EMPRESA* empresa, char morada[], int id, int idCliente, char nome[], int idade) { //make insertion sort
    CLIENTE* e = (CLIENTE*)malloc(sizeof(CLIENTE));
    e->id = idCliente;
    e->idade = idade;
    e->nome = nome;
    e->next = NULL;

    int index;
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
        for (index = 0; index < empresa->edificio->num_estudios; index++) {
            if (empresa->edificio->estudios[index].id == id) {
                if (empresa->edificio->estudios[index].num_clientes == 0) {
                    empresa->edificio->estudios[index].clientes = e;
                    empresa->edificio->estudios[index].num_clientes++;
                    return;
                }
                CLIENTE* pprevcl = NULL;
                CLIENTE* pcurrentcl = empresa->edificio->estudios[index].clientes;
                while (pcurrentcl != NULL && strcmp(nome, pcurrentcl->nome) < 0) {
                    pprevcl = pcurrentcl;
                    pcurrentcl = pcurrentcl->next;
                }
                if (pcurrentcl == empresa->edificio->estudios[index].clientes) {
                    e->next = empresa->edificio->estudios[index].clientes;
                    empresa->edificio->estudios[index].clientes = e;
                    empresa->edificio->estudios[index].num_clientes++;
                    return;
                }
                e->next = pcurrentcl;
                pprevcl->next = e;
                empresa->edificio->estudios[index].num_clientes++;
                return;

            }
        }
        printf("Estudio nao encontrado");
    }
    else {
        for (index = 0; index < pcurrent->num_estudios; index++) {
            if (pcurrent->estudios[index].id == id) {
                if (pcurrent->estudios[index].num_clientes == 0) {
                    pcurrent->estudios[index].clientes = e;
                    pcurrent->estudios[index].num_clientes++;
                    return;
                }
                CLIENTE* pprevcl = NULL;
                CLIENTE* pcurrentcl = empresa->edificio->estudios[index].clientes;
                while (pcurrentcl != NULL && strcmp(nome, pcurrentcl->nome) < 0) {
                    pprevcl = pcurrentcl;
                    pcurrentcl = pcurrentcl->next;
                }
                if (pcurrent == pcurrent->estudios[index].clientes) {
                    e->next = pcurrent->estudios[index].clientes;
                    pcurrent->estudios[index].clientes = e;
                    pcurrent->estudios[index].num_clientes++;
                    return;
                }
                e->next = pcurrent;
                pprev->next = e;
                empresa->edificio->estudios[index].num_clientes++;
                return;

            }
        }
        printf("Estudio nao encontrado");
    }
}

int inserir_preco(EMPRESA* empresa, char morada[], int id, int mes, int preco) { //make insertion sort
    int index;
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
        for (index = 0; index < empresa->edificio->num_estudios; index++) {
            if (empresa->edificio->estudios[index].id == id) {
                    empresa->edificio->estudios[index].precos[empresa->edificio->estudios[index].num_precos].mes = mes;
                    empresa->edificio->estudios[index].precos[empresa->edificio->estudios[index].num_precos].preco = preco;
                    empresa->edificio->estudios[index].num_precos++;
                    return;
            }
        }
        printf("Estudio nao encontrado");
    }
    else {
        for (index = 0; index < pcurrent->num_estudios; index++) {
            if (pcurrent->estudios[index].id == id) {
                    pcurrent->estudios[index].precos[pcurrent->estudios[index].num_precos].mes = mes ;
                    pcurrent->estudios[index].precos[pcurrent->estudios[index].num_precos].preco = preco;
                    pcurrent->estudios[index].num_precos++;
                    return;
            }
        }
        printf("Estudio nao encontrado");
    }
}

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

int remover_estudio(EMPRESA* empresa, char morada[], int id) {
    int index, i;
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
        if (empresa->edificio->num_estudios == 1) {
            free(empresa->edificio->estudios);
            empresa->edificio->num_estudios--;
            return;
        }
        for (index = 0; index < empresa->edificio->num_estudios; index++) {
            if (empresa->edificio->estudios[index].id == id) {
                break;

            }
        }
        if (index + 1 == empresa->edificio->num_estudios) {

            empresa->edificio->num_estudios--;
        }
        else {
            for (i = index - 1; i < empresa->edificio->num_estudios - 1; i++) {


                empresa->edificio->estudios[i].id = empresa->edificio->estudios[i + 1].id;
                empresa->edificio->estudios[i].quartos = empresa->edificio->estudios[i + 1].quartos;
                empresa->edificio->estudios[i].tamanho_preco = empresa->edificio->estudios[i + 1].tamanho_preco;
                empresa->edificio->estudios[i].clientes = empresa->edificio->estudios[i + 1].clientes;
                empresa->edificio->estudios[i].agenda = empresa->edificio->estudios[i + 1].agenda;
                empresa->edificio->estudios[i].precos = empresa->edificio->estudios[i + 1].precos;

            }
            empresa->edificio->num_estudios--;
        }
        return;
    }

    if (pcurrent->num_estudios == 1) {
        free(pcurrent->estudios);
        pcurrent->num_estudios--;
        return;
    }
    for (index = 0; index < pcurrent->num_estudios; index++) {
        if (pcurrent->estudios[index].id == id) {
            break;

        }
    }
    if (index + 1 == pcurrent->num_estudios) {

        pcurrent->num_estudios--;
    }
    else {
        for (i = index - 1; i < empresa->edificio->num_estudios - 1; i++) {


            pcurrent->estudios[i].id = pcurrent->estudios[i + 1].id;
            pcurrent->estudios[i].quartos = pcurrent->estudios[i + 1].quartos;
            pcurrent->estudios[i].id = pcurrent->estudios[i + 1].id;
            pcurrent->estudios[i].clientes = pcurrent->estudios[i + 1].clientes;
            pcurrent->estudios[i].agenda = pcurrent->estudios[i + 1].agenda;
            pcurrent->estudios[i].precos = pcurrent->estudios[i + 1].precos;

        }
        empresa->edificio->num_estudios--;
    }

}

int print_edificios(EMPRESA* empresa) {
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

int print_estudios(EMPRESA* empresa, char morada[]) { //make this binary
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
        if (empresa->edificio->num_estudios == 0) {
            printf("Este edificio nao tem estudios");
            return;
        }
        for (int i = 0; i < empresa->edificio->num_estudios; i++) {
            printf("Id: %d | Numero de quartos: %d\n", empresa->edificio->estudios[i].id, empresa->edificio->estudios[i].quartos);
        }
        return;
    }
    if (pcurrent->num_estudios == 0) {
        printf("Este edificio nao tem estudios");
        return;
    }
    for (int i = 0; i < pcurrent->num_estudios; i++) {
        printf("Id: %d | Numero de quartos: %d\n", pcurrent->estudios[i].id, pcurrent->estudios[i].quartos);
    }
}