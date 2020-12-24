#include<stdio.h>
#include"ex2.h"
#include"main.h"
#include <stdbool.h>

int Gestao_Edificios() {
	int op;

	do {
		printf("\t\tGestor de edificios\n\n");
		printf("Escolha a opcao:\n");
		printf("\t1-Inserir edificio\n");
		printf("\t2-Inserir estudio\n");
		printf("\t3-Inserir cliente\n");
		printf("\t4-Inserir preco\n");
		printf("\t5-Remover edificio\n");
		printf("\t6-Remover estudio\n");
		printf("\t7-Remover cliente\n");
		printf("\t8-Remover preco\n");
		printf("\t9-Editar edificio\n");
		printf("\t10-Editar estudio\n");
		printf("\t11-Editar cliente\n");
		printf("\t12-Editar preco\n");
		printf("\t13-Print edificio\n");
		printf("\t14-Print estudio\n");
		printf("\t15-Print cliente\n");
		printf("\t16-Print preco\n");
		printf("\t0-Sair\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			inserir_edificio(&empresa, "Rua s joao 1", 1345, 1);
			break;
		case 2:
			inserir_estudio(&empresa, 1, 1, 3);
			break;
		case 3:
			inserir_cliente(&empresa, 1, 1, 1, "Joao", 19);
			break;
		case 4:
			inserir_preco(&empresa, 1, 1, 10, 100);
			break;
		case 5:
			remover_edificio(&empresa, 1, 1);
			break;
		case 6:
			remover_estudio(&empresa, 1, 1, 1);
			break;
		case 7:
			remover_cliente(&empresa, 1, 1, 1, 1);
			break;
		case 8:
			remover_preco(&empresa, 1, 1, 1, 10);
			break;
		case 9:
			editar_edificio(&empresa, 1, "Rua s joao 2", 4000);
			break;
		case 10:
			editar_estudio(&empresa, 1, 1, 5);
			break;
		case 11:
			editar_cliente(&empresa, 1,1,1,"Joao",19);
			break;
		case 12:
			editar_preco(&empresa, 1,1,10,200);
			break;
		case 13:
			print_edificios(&empresa);
			break;
		case 14:
			print_estudios(&empresa, 1);
			break;
		case 15:
			print_clientes(&empresa, 1, 1);
			break;
		case 16:
			print_precos(&empresa, 1,1);
			break;
		case 0:
			break;
		default:

			printf("Opcao invalida!\n\n");
		}
	} while (op != 0);

};

int inserir_edificio(EMPRESA* empresa, char morada[], int coordenadas, int id) { //make insertion sort
	EDIFICIO* e = (EDIFICIO*)malloc(sizeof(EDIFICIO));
	e->morada = (char*)malloc(sizeof(char) * (strlen(morada) + 1));
	strncpy(e->morada, morada, (sizeof(char) * strlen(morada) + 1));
	e->coordenadas = coordenadas;
	e->id = id;
	e->num_estudios = 0;
	e->next = NULL;
	e->tamanho_estudio = 10;

	if (empresa->num_edificios == 0 || empresa->edificio == NULL) {
		empresa->edificio = e;
		empresa->num_edificios++;
		return;
	}
	EDIFICIO* pprev = NULL;
	EDIFICIO* pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
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

int inserir_estudio(EMPRESA* empresa, int id, int idEstudio, int quartos) { //change size of arr
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este id\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		if (empresa->edificio->num_estudios == 0) {
			empresa->edificio->estudios = (ESTUDIO*)malloc(10 * sizeof(ESTUDIO));
		}
		if (empresa->edificio->num_estudios == 10) {
			return;
		}
		empresa->edificio->estudios[empresa->edificio->num_estudios].id = idEstudio;
		empresa->edificio->estudios[empresa->edificio->num_estudios].quartos = quartos;
		empresa->edificio->estudios[empresa->edificio->num_estudios].agenda = NULL;
		empresa->edificio->estudios[empresa->edificio->num_estudios].clientes = NULL;
		empresa->edificio->estudios[empresa->edificio->num_estudios].num_precos = 0;
		empresa->edificio->estudios[empresa->edificio->num_estudios].num_agendas = 0;
		empresa->edificio->estudios[empresa->edificio->num_estudios].num_clientes = 0;
		empresa->edificio->estudios[empresa->edificio->num_estudios].tamanho_preco = 10; //move to inserir preco
		empresa->edificio->num_estudios++;
		return;
	}
	if (pcurrent->num_estudios == 0) {
		pcurrent->estudios = (ESTUDIO*)malloc(10 * sizeof(ESTUDIO));
	}
	if (pcurrent->num_estudios == 10) {
		return;
	}
	pcurrent->estudios[pcurrent->num_estudios].id = id;
	pcurrent->estudios[pcurrent->num_estudios].quartos = quartos;
	pcurrent->estudios[pcurrent->num_estudios].num_precos = 0;
	pcurrent->estudios[pcurrent->num_estudios].agenda = NULL;
	pcurrent->estudios[pcurrent->num_estudios].clientes = NULL;
	pcurrent->estudios[pcurrent->num_estudios].num_agendas = 0;
	pcurrent->estudios[pcurrent->num_estudios].num_clientes = 0;
	pcurrent->num_estudios++;
}

int inserir_cliente(EMPRESA* empresa, int id, int idEstudio, int idCliente, char nome[], int idade) { //make insertion sort
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
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == idEstudio) {
				if (empresa->edificio->estudios[index].num_clientes == 0) {
					empresa->edificio->estudios[index].clientes = e;
					empresa->edificio->estudios[index].num_clientes++;
					return;
				}
				CLIENTE* pprevcl = NULL;
				CLIENTE* pcurrentcl = empresa->edificio->estudios[index].clientes;
				while (pcurrentcl != NULL && pcurrentcl->id != idCliente) {
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
			if (pcurrent->estudios[index].id == idEstudio) {
				if (pcurrent->estudios[index].num_clientes == 0) {
					pcurrent->estudios[index].clientes = e;
					pcurrent->estudios[index].num_clientes++;
					return;
				}
				CLIENTE* pprevcl = NULL;
				CLIENTE* pcurrentcl = empresa->edificio->estudios[index].clientes;
				while (pcurrentcl != NULL && pcurrentcl->id != idCliente) {
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

int inserir_preco(EMPRESA* empresa, int id, int idCliente, int mes, int preco) { //make insertion sort
	int index;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == idCliente) {
				if (empresa->edificio->estudios[index].num_precos == 0) {
					empresa->edificio->estudios[index].precos = (PRECO*)malloc(10 * sizeof(PRECO));
					empresa->edificio->estudios[index].tamanho_preco = 10;
				}
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
			if (pcurrent->estudios[index].id == idCliente) {
				if (pcurrent->estudios[index].num_precos == 0) {
					pcurrent->estudios[empresa->edificio->num_estudios].precos = (PRECO*)malloc(10 * sizeof(PRECO));
					pcurrent->estudios[pcurrent->num_estudios].tamanho_preco = 10;
				}
				pcurrent->estudios[index].precos[pcurrent->estudios[index].num_precos].mes = mes;
				pcurrent->estudios[index].precos[pcurrent->estudios[index].num_precos].preco = preco;
				pcurrent->estudios[index].num_precos++;
				return;
			}
		}
		printf("Estudio nao encontrado");
	}
}

int remover_edificio(EMPRESA* empresa, int id) {
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
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

int remover_estudio(EMPRESA* empresa, int id, int idEstudio) {
	int index, i;
	bool isInArray = false;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == idEstudio) {
				isInArray = true;
				break;

			}
		}
		if (!isInArray) {
			printf("estudio nao encontrado");
			return;
		}
		if (empresa->edificio->num_estudios == 1) {
			free(empresa->edificio->estudios);
			empresa->edificio->num_estudios = 0;
			return;
		}
		if (index + 1 == empresa->edificio->num_estudios) {

			empresa->edificio->num_estudios--;
			return;
		}
		else {
			for (i = index; i < empresa->edificio->num_estudios; i++) {


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

	for (index = 0; index < pcurrent->num_estudios; index++) {
		if (pcurrent->estudios[index].id == idEstudio) {
			isInArray = true;
			break;
		}
	}
	if (!isInArray) {
		printf("Estudio nao encontrado");
		return;
	}
	if (pcurrent->num_estudios == 1) {
		free(pcurrent->estudios);
		pcurrent->num_estudios--;
		return;
	}
	if (index + 1 == pcurrent->num_estudios) {

		pcurrent->num_estudios--;
	}
	else {
		for (i = index; i < empresa->edificio->num_estudios; i++) {


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

int remover_cliente(EMPRESA* empresa, int id, int IdEstudio, int idCliente) {

	int index;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == IdEstudio) {
				if (empresa->edificio->estudios[index].clientes == NULL) {
					printf("Nao ha clientes\n");
					return;
				}
				CLIENTE* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].clientes;
				while (pcurrent != NULL && idCliente != pcurrentcl->id) {
					pprevcl = pcurrentcl;
					pcurrentcl = pcurrentcl->next;
				}
				if (pcurrentcl == NULL) {
					printf("Nao ha clientes com este id\n");
					return;
				}
				if (empresa->edificio->estudios[index].clientes == pcurrentcl) {
					empresa->edificio->estudios[index].clientes = pcurrentcl->next;
					empresa->edificio->estudios[index].num_clientes--;
					free(pcurrentcl);
					return;
				}
				pprevcl->next = pcurrentcl->next;
				free(pcurrentcl);
				empresa->edificio->estudios[index].num_clientes--;
				return;
			}
		}
		printf("Estudio nao encontrado");
	}
	else {
		for (index = 0; index < pcurrent->num_estudios; index++) {
			if (pcurrent->estudios[index].id == IdEstudio) {
				if (pcurrent->estudios[index].clientes == NULL) {
					printf("Nao ha clientes\n");
					return;
				}
				CLIENTE* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].clientes;
				while (pcurrent != NULL && idCliente != pcurrentcl->id) {
					pprevcl = pcurrentcl;
					pcurrentcl = pcurrentcl->next;
				}
				if (pcurrentcl == NULL) {
					printf("Nao ha clientes com este id\n");
					return;
				}
				if (pcurrent->estudios[index].clientes == pcurrentcl) {
					pcurrent->estudios[index].clientes = pcurrentcl->next;
					pcurrent->estudios[index].num_clientes--;
					free(pcurrentcl);
					return;
				}
				pprevcl->next = pcurrentcl->next;
				free(pcurrentcl);
				pcurrent->estudios[index].num_clientes--;
				return;
			}
		}
		printf("Estudio nao encontrado");
	}
}

int remover_preco(EMPRESA* empresa, int id, int idEstudio, int mes) { //make insertion sort

	int index, indexpr, i;
	bool isInArray = false;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == idEstudio) {
				for (indexpr = 0; indexpr < empresa->edificio->estudios[index].num_precos; indexpr++) {
					if (empresa->edificio->estudios[index].precos[indexpr].mes == mes) {
						isInArray = true;
						break;

					}
				}
				if (!isInArray) {
					printf("Mes nao encontrado");
					return;
				}
				if (empresa->edificio->estudios[index].num_precos == 1) {
					free(empresa->edificio->estudios[index].precos);
					empresa->edificio->estudios[index].num_precos--;
					return;
				}
				if (indexpr + 1 == empresa->edificio->estudios[index].num_precos) {

					empresa->edificio->estudios[index].num_precos--;
				}
				else {
					for (i = indexpr; i < empresa->edificio->estudios[index].num_precos; i++) {

						empresa->edificio->estudios[index].precos[i].mes = empresa->edificio->estudios[index].precos[i + 1].mes;
						empresa->edificio->estudios[index].precos[i].preco = empresa->edificio->estudios[index].precos[i + 1].preco;

					}
					empresa->edificio->estudios[index].num_precos--;
				}
				return;

			}
		}
		printf("Estudio nao encontrado");
	}
	else {
		for (index = 0; index < pcurrent->num_estudios; index++) {
			if (pcurrent->estudios[index].id == idEstudio) {
				for (indexpr = 0; indexpr < pcurrent->estudios[index].num_precos; indexpr++) {
					if (pcurrent->estudios[index].precos[indexpr].mes == mes) {
						isInArray = true;
						break;

					}
				}
				if (!isInArray) {
					printf("Mes nao encontrado");
					return;
				}
				if (pcurrent->estudios[index].num_precos == 1) {
					free(pcurrent->estudios[index].precos);
					pcurrent->estudios[index].num_precos--;
					return;
				}
				if (indexpr + 1 == pcurrent->estudios[index].num_precos) {

					pcurrent->estudios[index].num_precos--;
				}
				else {
					for (i = indexpr; i < pcurrent->estudios[index].num_precos; i++) {


						pcurrent->estudios[index].precos[i].mes = pcurrent->estudios[index].precos[i + 1].mes;
						pcurrent->estudios[index].precos[i].preco = pcurrent->estudios[index].precos[i + 1].preco;

					}
					pcurrent->estudios[index].num_precos--;
				}
				return;
			}
		}
		printf("Estudio nao encontrado");
	}
}

int editar_edificio(EMPRESA* empresa, int id, char morada[], int coordenadas) {
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		strcpy(empresa->edificio->morada, morada, (sizeof(char) * strlen(morada) + 1));
		empresa->edificio->coordenadas = coordenadas;
		return;
	}
	strcpy(pcurrent->morada, morada, (sizeof(char) * strlen(morada) + 1));
	pcurrent->morada = coordenadas;
}

int editar_estudio(EMPRESA* empresa, int id, int idEstudio, int quartos) {
	int index;
	bool isInArray = false;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == idEstudio) {
				empresa->edificio->estudios[index].quartos = quartos;
				return;

			}
		}
		printf("estudio nao encontrado");
		return;
	}
	for (index = 0; index < pcurrent->num_estudios; index++) {
		if (pcurrent->estudios[index].id == idEstudio) {
			pcurrent->estudios[index].quartos = quartos;
			return;

		}
	}
	printf("estudio nao encontrado");
	return;
}

int editar_cliente(EMPRESA* empresa, int id, int IdEstudio, int idCliente, char nome[], int idade) {
	int index;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == IdEstudio) {
				if (empresa->edificio->estudios[index].clientes == NULL) {
					printf("Nao ha clientes\n");
					return;
				}
				CLIENTE* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].clientes;
				while (pcurrent != NULL && idCliente != pcurrentcl->id) {
					pprevcl = pcurrentcl;
					pcurrentcl = pcurrentcl->next;
				}
				if (pcurrentcl == NULL) {
					printf("Nao ha clientes com este id\n");
					return;
				}
				if (empresa->edificio->estudios[index].clientes == pcurrentcl) {
					strcpy(empresa->edificio->estudios[index].clientes->nome, nome, (sizeof(char) * strlen(nome) + 1));
					empresa->edificio->estudios[index].clientes->idade = idade;
					return;
				}
				strcpy(pcurrentcl->nome, nome, (sizeof(char) * strlen(nome) + 1));
				pcurrentcl->idade = idade;
				return;
			}
		}
		printf("Estudio nao encontrado");
	}
	for (index = 0; index < pcurrent->num_estudios; index++) {
		if (pcurrent->estudios[index].id == IdEstudio) {
			if (pcurrent->estudios[index].clientes == NULL) {
				printf("Nao ha clientes\n");
				return;
			}
			CLIENTE* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].clientes;
			while (pcurrent != NULL && idCliente != pcurrentcl->id) {
				pprevcl = pcurrentcl;
				pcurrentcl = pcurrentcl->next;
			}
			if (pcurrentcl == NULL) {
				printf("Nao ha clientes com este id\n");
				return;
			}
			if (pcurrent->estudios[index].clientes == pcurrentcl) {
				strcpy(pcurrent->estudios[index].clientes->nome, nome, (sizeof(char) * strlen(nome) + 1));
				pcurrent->estudios[index].clientes->idade = idade;
				return;
			}
			strcpy(pcurrentcl->nome, nome, (sizeof(char) * strlen(nome) + 1));
			pcurrentcl->idade = idade;
			return;
		}
	}
	printf("Estudio nao encontrado");
}

int editar_preco(EMPRESA* empresa, int id, int IdEstudio, int mes, int preco) {
	int index, indexpr;
	bool isInArray = false;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este nome\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == IdEstudio) {
				for (indexpr = 0; indexpr < empresa->edificio->estudios[index].num_precos; indexpr++) {
					if (empresa->edificio->estudios[index].precos[indexpr].mes == mes) {
						isInArray = true;
						break;

					}
				}
				if (!isInArray) {
					printf("Mes nao encontrado");
					return;
				}
				empresa->edificio->estudios[index].precos[indexpr].preco = preco;
			}
		}
		printf("Estudio nao encontrado");
	}
	for (index = 0; index < pcurrent->num_estudios; index++) {
		if (pcurrent->estudios[index].id == IdEstudio) {
			for (indexpr = 0; indexpr < pcurrent->estudios[index].num_precos; indexpr++) {
				if (pcurrent->estudios[index].precos[indexpr].mes == mes) {
					isInArray = true;
					break;

				}
			}
			if (!isInArray) {
				printf("Mes nao encontrado");
				return;
			}
			pcurrent->estudios[index].precos[indexpr].preco = preco;
		}
	}
	printf("Estudio nao encontrado");
}

int print_edificios(EMPRESA* empresa) {
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		printf("Id: %d | Morada: %s | Coordenadas: %d\n", pcurrent->id, pcurrent->morada, pcurrent->coordenadas);
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
}

int print_estudios(EMPRESA* empresa, int id) { //make this binary
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
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

int print_clientes(EMPRESA* empresa, int id, int IdEstudio) {
	int index;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
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
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == IdEstudio) {
				if (empresa->edificio->estudios[index].num_clientes == 0) {
					printf("Nao ha clientes\n");
					return;
				}
				CLIENTE* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].clientes;
				while (pcurrentcl != NULL) {
					printf("Id: %d | Nome: %s | Idade: %d\n", pcurrentcl->id, pcurrentcl->nome, pcurrentcl->idade);
					pprevcl = pcurrentcl;
					pcurrentcl = pcurrentcl ->next;
				}
				return;

			}
		}

	}
	if (pcurrent->num_estudios == 0) {
		printf("Este edificio nao tem estudios");
		return;
	}
	for (index = 0; index < pcurrent->num_estudios; index++) {
		if (pcurrent->estudios[index].id == IdEstudio) {
			if (pcurrent->estudios[index].num_clientes == 0) {
				printf("Nao ha clientes\n");
				return;
			}
			CLIENTE* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].clientes;
			while (pcurrentcl != NULL) {
				printf("Id: %d | Nome: %s | Idade: %d\n", pcurrentcl->id, pcurrentcl->nome, pcurrentcl->idade);
				pprevcl = pcurrentcl;
				pcurrentcl = pcurrentcl->next;
			}
			return;

		}
	}

}

int print_precos(EMPRESA* empresa, int id, int IdEstudio) {
	int index;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != id) {
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
		for (index = 0; index < empresa->edificio->num_estudios; index++) {
			if (empresa->edificio->estudios[index].id == IdEstudio) {
				if (empresa->edificio->estudios[index].num_clientes == 0) {
					printf("Nao ha clientes\n");
					return;
				}
				for (int i = 0; i < empresa->edificio->estudios[index].num_precos; i++) {
					printf("Mes: %d | Preco: %d\n", empresa->edificio->estudios[index].precos[i].mes, empresa->edificio->estudios[index].precos[i].preco);
				}
				return;
			}
		}
	}
	if (pcurrent->num_estudios == 0) {
		printf("Este edificio nao tem estudios");
		return;
	}
	for (index = 0; index < pcurrent->num_estudios; index++) {
		if (pcurrent->estudios[index].id == IdEstudio) {
			if (pcurrent->estudios[index].num_clientes == 0) {
				printf("Nao ha clientes\n");
				return;
			}
			for (int i = 0; i < pcurrent->estudios[index].num_precos; i++) {
				printf("Mes: %d | Preco: %d\n", pcurrent->estudios[index].precos[i].mes, pcurrent->estudios[index].precos[i].preco);
			}
			return;
		}
	}
}