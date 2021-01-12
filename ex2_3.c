#include<stdio.h>
#include"main.h"

int Gestao_Edificios() {
	int op;
	do {
		printf("\t\tGestor de edificios\n\n");
		printf("Escolha a opcao:\n");
		printf("\t1-Inserir edificio\n");
		printf("\t2-Inserir estudio\n");
		printf("\t3-Inserir cliente\n");
		printf("\t4-Inserir agenda\n");
		printf("\t5-Remover edificio\n");
		printf("\t6-Remover estudio\n");
		printf("\t7-Remover cliente\n");
		printf("\t8-Remover agenda\n");
		printf("\t9-Editar edificio\n");
		printf("\t10-Editar estudio\n");
		printf("\t11-Editar cliente\n");
		printf("\t12-Editar agenda\n");
		printf("\t13-Print edificio\n");
		printf("\t14-Print estudio\n");
		printf("\t15-Print cliente\n");
		printf("\t16-Print agenda\n");
		printf("\t0-Sair\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			inserir_edificio(&empresa, "Sjoao1", "DManuel", 10.2212, -10.4821, 1, 10, 10);
			break;
		case 2:
			inserir_estudio(&empresa, 1, 1, 3, 20);
			break;
		case 3:
			inserir_cliente(&empresa, 1, 1, 1, "Joao", 19);
			break;
		case 4:
			inserir_agenda(&empresa, 1, 1, 1, 1, "estadia", 19, 10, 2020, 10, 10, 2020, "AirBNB");
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
			remover_agenda(&empresa, 1, 1, 1);
			break;
		case 9:
			editar_edificio(&empresa,1,"Joao d1","Rei Duarte",10.2455,12.3333,10);
			break;
		case 10:
			editar_estudio(&empresa, 1, 1, 5);
			break;
		case 11:
			editar_cliente(&empresa, 1, 1, 1, "Joaoo crlll", 19);
			break;
		case 12:
			editar_agenda(&empresa, 1, 1, 1, 1, "Tratamento", 11, 10, 2020, 20, 10, 2020, "booking");
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
			print_agenda(&empresa, 1, 1);
			break;
		case 0:
			break;
		default:

			printf("Opcao invalida!\n\n");
		}
	} while (op != 0);

};

extern int checkIfDatesCoincide(DATA a, DATA b)
{
	if (a.ano < b.ano) return 1;
	if (a.ano == b.ano && a.mes < b.mes) return 1;
	if (a.ano == b.ano && a.mes == b.mes && a.dia < b.dia) return 1;
	if (a.ano == b.ano && a.mes == b.mes && a.dia == b.dia) return 1;
	return 0;
}

const int monthDays[12]
= { 31, 28, 31, 30, 31, 30,
   31, 31, 30, 31, 30, 31 };

int countLeapYears(DATA d)
{
	int years = d.ano;

	if (d.mes <= 2)
		years--;

	return years / 4
		- years / 100
		+ years / 400;
}


int getDifference(DATA dt1, DATA dt2)
{

	long int n1 = dt1.ano * 365 + dt1.dia;

	for (int i = 0; i < dt1.mes - 1; i++)
		n1 += monthDays[i];

	n1 += countLeapYears(dt1);


	long int n2 = dt2.ano * 365 + dt2.dia;
	for (int i = 0; i < dt2.mes - 1; i++)
		n2 += monthDays[i];
	n2 += countLeapYears(dt2);

	return (n2 - n1);
}

int binarySearch(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;


		if (arr[mid] == x)
			return mid;

		if (arr[mid] > x)
			return binarySearch(arr, l, mid - 1, x);

		return binarySearch(arr, mid + 1, r, x);
	}
	return -1;
}

void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

int inserir_edificio(EMPRESA* empresa, char morada[], char nome[], double latitude, double longitude, int id, int preco_m2) {
	EDIFICIO* e = (EDIFICIO*)malloc(sizeof(EDIFICIO));
	e->morada = (char*)malloc(sizeof(char) * (strlen(morada) + 1));
	strncpy(e->morada, morada, (sizeof(char) * strlen(morada) + 1));
	e->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
	strncpy(e->nome, nome, (sizeof(char) * strlen(nome) + 1));
	e->id = id;
	e->latitude = latitude;
	e->longitude = longitude;
	e->num_estudios = 0;
	e->next = NULL;
	e->preco_m2 = preco_m2;
	e->tamanho_estudio = 10;

	if (empresa->num_edificios == 0 || empresa->edificio == NULL) {
		empresa->edificio = e;
		empresa->num_edificios++;
		return;
	}
	EDIFICIO* pprev = NULL;
	EDIFICIO* pcurrent = empresa->edificio;
	while (pcurrent != NULL ) {
		if (pcurrent->id == id) {
			printf("Ja existe um edificio com este id\n");
			return;
		}
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

int inserir_estudio(EMPRESA* empresa, int id, int idEstudio, int quartos, int m2) {
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
		int index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, idEstudio);
		if (index != -1) {
			printf("estudio ja existe\n");
			return;
		}
		empresa->edificio->estudios[empresa->edificio->num_estudios].id = idEstudio;
		empresa->edificio->estudios[empresa->edificio->num_estudios].quartos = quartos;
		empresa->edificio->estudios[empresa->edificio->num_estudios].m2 = m2;
		empresa->edificio->estudios[empresa->edificio->num_estudios].agenda = NULL;
		empresa->edificio->estudios[empresa->edificio->num_estudios].clientes = NULL;
		empresa->edificio->estudios[empresa->edificio->num_estudios].num_agendas = 0;
		empresa->edificio->estudios[empresa->edificio->num_estudios].num_clientes = 0;
		empresa->edificio->num_estudios++;
		insertionSort(empresa->edificio->estudios, empresa->edificio->num_estudios);
		return;
	}
	if (pcurrent->num_estudios == 0) {
		pcurrent->estudios = (ESTUDIO*)malloc(10 * sizeof(ESTUDIO));
	}
	if (pcurrent->num_estudios == 10) {
		return;
	}
	int index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, idEstudio);
	if (index != -1) {
		printf("estudio ja existe\n");
		return;
	}
	pcurrent->estudios[pcurrent->num_estudios].id = idEstudio;
	pcurrent->estudios[pcurrent->num_estudios].quartos = quartos;
	pcurrent->estudios[pcurrent->num_estudios].m2 = m2;
	pcurrent->estudios[pcurrent->num_estudios].agenda = NULL;
	pcurrent->estudios[pcurrent->num_estudios].clientes = NULL;
	pcurrent->estudios[pcurrent->num_estudios].num_agendas = 0;
	pcurrent->estudios[pcurrent->num_estudios].num_clientes = 0;
	pcurrent->num_estudios++;
	insertionSort(pcurrent->estudios, pcurrent->num_estudios);
}

int inserir_cliente(EMPRESA* empresa, int id, int idEstudio, int idCliente, char nome[], int idade) {
	CLIENTE* e = (CLIENTE*)malloc(sizeof(CLIENTE));
	e->id = idCliente;
	e->idade = idade;
	e->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));
	strncpy(e->nome, nome, (sizeof(char) * strlen(nome) + 1));
	e->next = NULL;

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
		int index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, idEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
		if (empresa->edificio->estudios[index].num_clientes == 0) {
			empresa->edificio->estudios[index].clientes = e;
			empresa->edificio->estudios[index].num_clientes++;
			return;
		}
		CLIENTE* pprevcl = NULL;
		CLIENTE* pcurrentcl = empresa->edificio->estudios[index].clientes;
		while (pcurrentcl != NULL ) {
			if (pcurrentcl->id == idCliente) {
				printf("Ja existe um utilizador com este id\n");
				return;
			}
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
	else {
		int index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, idEstudio);
		if (index == -1) {
			printf("estudio nao encontrado\n");
			return;
		}
		if (pcurrent->estudios[index].num_clientes == 0) {
			pcurrent->estudios[index].clientes = e;
			pcurrent->estudios[index].num_clientes++;
			return;
		}
		CLIENTE* pprevcl = NULL;
		CLIENTE* pcurrentcl = empresa->edificio->estudios[index].clientes;
		while (pcurrentcl != NULL) {
			if (pcurrentcl->id == idCliente) {
				printf("Ja existe um utilizador com este id");
				return;
			}
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

int inserir_agenda(EMPRESA* empresa, int id, int IdEstudio, int idAgenda, int idCliente, char evento[], int data_fim_dia, int data_fim_mes, int data_fim_ano, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, char plataforma[]) {
	AGENDA* e = (AGENDA*)malloc(sizeof(AGENDA));
	e->id = idAgenda;
	e->idUser = idCliente;
	e->evento = (char*)malloc(sizeof(char) * (strlen(evento) + 1));
	strncpy(e->evento, evento, (sizeof(char) * strlen(evento) + 1));
	e->plataforma = (char*)malloc(sizeof(char) * (strlen(plataforma) + 1));
	strncpy(e->plataforma, plataforma, (sizeof(char) * strlen(plataforma) + 1));
	e->data_fim.dia = data_fim_dia;
	e->data_fim.mes = data_fim_mes;
	e->data_fim.ano = data_fim_ano;
	e->data_inicio.dia = data_inicio_dia;
	e->data_inicio.mes = data_inicio_mes;
	e->data_inicio.ano = data_inicio_ano;
	e->diferenca = getDifference(e->data_inicio, e->data_fim);
	e->next = NULL;

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
		int index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado\n");
			return;
		}
		if (strcmp(evento, "estadia") == 0) {
			e->preco = empresa->edificio->estudios[index].m2 * empresa->edificio->preco_m2 * e->diferenca;
			if (e->diferenca > 6) {
				e->preco = e->preco * 0.7;
			}
			if (e->data_inicio.dia > 9) {
				e->preco = e->preco + 20;
			}
			else if (e->data_inicio.dia >= 6 && e->data_inicio.dia < 9) {
				e->preco = e->preco + 40;
			}
		}
		else {
			e->preco = 0;
		}
		if (empresa->edificio->estudios[index].num_agendas == 0) {
			empresa->edificio->estudios[index].agenda = e;
			empresa->edificio->estudios[index].num_agendas++;
			return;
		}

		AGENDA* pprevcl = NULL;
		AGENDA* pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (checkIfDatesCoincide(pcurrentcl->data_inicio, e->data_inicio) && checkIfDatesCoincide(e->data_inicio, pcurrentcl->data_fim)) {
				printf("Ja existe um evento nesta data\n");
				return;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		pprevcl = NULL;
		pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrentcl != NULL && pcurrentcl->id != idAgenda) {
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}

		if (pcurrentcl == empresa->edificio->estudios[index].agenda) {
			e->next = empresa->edificio->estudios[index].agenda;
			empresa->edificio->estudios[index].agenda = e;
			empresa->edificio->estudios[index].num_agendas++;
			return;
		}
		e->next = pcurrentcl;
		pprevcl->next = e;
		empresa->edificio->estudios[index].num_agendas++;
		return;
	}
	else {
		int index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado\n");
			return;
		}
		if (strcmp(evento, "estadia") == 0) {
			e->preco = pcurrent->estudios[index].m2 * pcurrent->preco_m2 * e->diferenca;
			if (e->diferenca > 6) {
				e->preco = e->preco * 0.7;
			}
		}
		else {
			e->preco = 0;
		}
		if (pcurrent->estudios[index].num_agendas == 0) {
			pcurrent->estudios[index].agenda = e;
			pcurrent->estudios[index].num_agendas++;
			return;
		}
		AGENDA* pprevcl = NULL;
		AGENDA* pcurrentcl = pcurrent->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (checkIfDatesCoincide(pcurrentcl->data_inicio, e->data_inicio) && checkIfDatesCoincide(e->data_inicio, pcurrentcl->data_fim)) {
				printf("Ja existe um evento nesta data\n");
				return;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		pprevcl = NULL;
		pcurrentcl = pcurrent->estudios[index].agenda;
		while (pcurrentcl != NULL && pcurrentcl->id != idAgenda) {
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		if (pcurrent == pcurrent->estudios[index].agenda) {
			e->next = pcurrent->estudios[index].agenda;
			pcurrent->estudios[index].agenda = e;
			pcurrent->estudios[index].num_agendas++;
			return;
		}
		e->next = pcurrent;
		pprev->next = e;
		pcurrent->estudios[index].num_agendas++;
		return;

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
		index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, idEstudio);
		if (index == -1) {
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
				empresa->edificio->estudios[i].clientes = empresa->edificio->estudios[i + 1].clientes;
				empresa->edificio->estudios[i].agenda = empresa->edificio->estudios[i + 1].agenda;

			}
			empresa->edificio->num_estudios--;
		}
		return;
	}

	index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, idEstudio);
	if (index == -1) {
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
		index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
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
	index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, IdEstudio);
	if (index == -1) {
		printf("estudio nao encontrado");
		return;
	}
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

int remover_agenda(EMPRESA* empresa, int id, int IdEstudio, int idAgenda) {

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
		index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
		if (empresa->edificio->estudios[index].agenda == NULL) {
			printf("Nao ha agendas\n");
			return;
		}
		AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrent != NULL && idAgenda != pcurrentcl->id) {
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		if (pcurrentcl == NULL) {
			printf("Nao ha agendas com este id\n");
			return;
		}
		if (empresa->edificio->estudios[index].agenda == pcurrentcl) {
			empresa->edificio->estudios[index].agenda = pcurrentcl->next;
			empresa->edificio->estudios[index].num_agendas--;
			free(pcurrentcl);
			return;
		}
		pprevcl->next = pcurrentcl->next;
		free(pcurrentcl);
		empresa->edificio->estudios[index].num_agendas--;
		return;
	}
	index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, IdEstudio);
	if (index == -1) {
		printf("estudio nao encontrado");
		return;
	}
	if (pcurrent->estudios[index].agenda == NULL) {
		printf("Nao ha agendas\n");
		return;
	}
	AGENDA* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].agenda;
	while (pcurrent != NULL && idAgenda != pcurrentcl->id) {
		pprevcl = pcurrentcl;
		pcurrentcl = pcurrentcl->next;
	}
	if (pcurrentcl == NULL) {
		printf("Nao ha agendas com este id\n");
		return;
	}
	if (pcurrent->estudios[index].agenda == pcurrentcl) {
		pcurrent->estudios[index].agenda = pcurrentcl->next;
		pcurrent->estudios[index].num_agendas--;
		free(pcurrentcl);
		return;
	}
	pprevcl->next = pcurrentcl->next;
	free(pcurrentcl);
	pcurrent->estudios[index].num_agendas--;
	return;
}

int editar_edificio(EMPRESA* empresa, int id, char morada[],char nome[], double latitude, double longitude, int preco_m2) {
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
		strcpy(empresa->edificio->morada, morada, (sizeof(char) * strlen(morada) + 1));
		strcpy(empresa->edificio->nome, nome, (sizeof(char) * strlen(nome) + 1));
		empresa->edificio->latitude = latitude;
		empresa->edificio->longitude = longitude;
		empresa->edificio->preco_m2 = preco_m2;
		return;
	}
	strcpy(pcurrent->morada, morada, (sizeof(char) * strlen(morada) + 1));
	strcpy(pcurrent->nome, nome, (sizeof(char) * strlen(nome) + 1));
	pcurrent->latitude = latitude;
	pcurrent->longitude = longitude;
	pcurrent->preco_m2 = preco_m2;
}

int editar_estudio(EMPRESA* empresa, int id, int idEstudio, int quartos) {
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
		index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, idEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
		empresa->edificio->estudios[index].quartos = quartos;
		return;
	}
	index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, idEstudio);
	if (index == -1) {
		printf("estudio nao encontrado");
		return;
	}
	pcurrent->estudios[index].quartos = quartos;
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
		index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
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
	index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, IdEstudio);
	if (index == -1) {
		printf("estudio nao encontrado");
		return;
	}

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

int editar_agenda(EMPRESA* empresa, int id, int IdEstudio, int idAgenda, int idCliente, char evento[], int data_fim_dia, int data_fim_mes, int data_fim_ano, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, char plataforma[]) {
	int index;
	DATA dataInicio = { data_inicio_dia,data_inicio_mes,data_inicio_ano };
	DATA dataFim = { data_fim_dia,data_fim_mes,data_fim_ano };
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
		index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
		if (empresa->edificio->estudios[index].agenda == NULL) {
			printf("Nao ha agendas\n");
			return;
		}
		AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (checkIfDatesCoincide(pcurrentcl->data_inicio, dataInicio) && checkIfDatesCoincide(dataInicio, pcurrentcl->data_fim)) {
				printf("Ja existe um evento nesta data");
				return;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		pprevcl = NULL;
		pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrent != NULL && idAgenda != pcurrentcl->id) {
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		if (pcurrentcl == NULL) {
			printf("Nao ha agendas com este id\n");
			return;
		}
		if (empresa->edificio->estudios[index].agenda == pcurrentcl) {
			strcpy(empresa->edificio->estudios[index].agenda->evento, evento, (sizeof(char) * strlen(evento) + 1));
			strcpy(empresa->edificio->estudios[index].agenda->plataforma, plataforma, (sizeof(char) * strlen(plataforma) + 1));
			empresa->edificio->estudios[index].agenda->idUser = idCliente;
			empresa->edificio->estudios[index].agenda->data_inicio.dia = data_inicio_dia;
			empresa->edificio->estudios[index].agenda->data_inicio.mes = data_inicio_mes;
			empresa->edificio->estudios[index].agenda->data_inicio.ano = data_inicio_ano;
			empresa->edificio->estudios[index].agenda->data_fim.dia = data_fim_dia;
			empresa->edificio->estudios[index].agenda->data_fim.mes = data_fim_mes;
			empresa->edificio->estudios[index].agenda->data_fim.ano = data_fim_ano;
			empresa->edificio->estudios[index].agenda->diferenca = getDifference(empresa->edificio->estudios[index].agenda->data_inicio, empresa->edificio->estudios[index].agenda->data_fim);
			if (strcmp(evento, "estadia") == 0) {
				empresa->edificio->estudios[index].agenda->preco = empresa->edificio->estudios[index].m2 * empresa->edificio->preco_m2 * empresa->edificio->estudios[index].agenda->diferenca;
				if (empresa->edificio->estudios[index].agenda->diferenca > 6) {
					empresa->edificio->estudios[index].agenda->preco = empresa->edificio->estudios[index].agenda->preco * 0.7;
				}
			}
			else {
				empresa->edificio->estudios[index].agenda->preco = 0;
			}
			return;
		}
		strcpy(pcurrentcl->evento, evento, (sizeof(char) * strlen(evento) + 1));
		strcpy(pcurrentcl->plataforma, plataforma, (sizeof(char) * strlen(plataforma) + 1));
		pcurrentcl->idUser = idCliente;
		pcurrentcl->data_inicio.dia = data_inicio_dia;
		pcurrentcl->data_inicio.mes = data_inicio_mes;
		pcurrentcl->data_inicio.ano = data_inicio_ano;
		pcurrentcl->data_fim.dia = data_fim_dia;
		pcurrentcl->data_fim.mes = data_fim_mes;
		pcurrentcl->data_fim.ano = data_fim_ano;
		pcurrentcl->diferenca = getDifference(pcurrentcl->data_inicio, pcurrentcl->data_fim);
		if (strcmp(evento, "estadia") == 0) {
			pcurrentcl->preco = empresa->edificio->estudios[index].m2 * empresa->edificio->preco_m2 * pcurrentcl->diferenca;
			if (pcurrentcl->diferenca > 6) {
				pcurrentcl->preco = pcurrentcl->preco * 0.7;
			}
		}
		else {
			pcurrentcl->preco = 0;
		}
		return;

	}
	index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, IdEstudio);
	if (index == -1) {
		printf("estudio nao encontrado");
		return;
	}

	if (pcurrent->estudios[index].agenda == NULL) {
		printf("Nao ha agendas\n");
		return;
	}
	AGENDA* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].agenda;
	while (pcurrentcl != NULL) {
		if (checkIfDatesCoincide(pcurrentcl->data_inicio, dataInicio) && checkIfDatesCoincide(dataInicio, pcurrentcl->data_fim)) {
			printf("Ja existe um evento nesta data");
			return;
		}
		pprevcl = pcurrentcl;
		pcurrentcl = pcurrentcl->next;
	}
	pprevcl = NULL;
	pcurrentcl = pcurrent->estudios[index].agenda;
	while (pcurrent != NULL && idAgenda != pcurrentcl->id) {
		pprevcl = pcurrentcl;
		pcurrentcl = pcurrentcl->next;
	}
	if (pcurrentcl == NULL) {
		printf("Nao ha agendas com este id\n");
		return;
	}
	if (pcurrent->estudios[index].agenda == pcurrentcl) {
		strcpy(pcurrent->estudios[index].agenda->evento, evento, (sizeof(char) * strlen(evento) + 1));
		strcpy(pcurrent->estudios[index].agenda->plataforma, plataforma, (sizeof(char)* strlen(plataforma) + 1));
		pcurrent->estudios[index].agenda->idUser = idCliente;
		pcurrent->estudios[index].agenda->idUser = idCliente;
		pcurrent->estudios[index].agenda->data_inicio.dia = data_inicio_dia;
		pcurrent->estudios[index].agenda->data_inicio.mes = data_inicio_mes;
		pcurrent->estudios[index].agenda->data_inicio.ano = data_inicio_ano;
		pcurrent->estudios[index].agenda->data_fim.dia = data_fim_dia;
		pcurrent->estudios[index].agenda->data_fim.mes = data_fim_mes;
		pcurrent->estudios[index].agenda->data_fim.ano = data_fim_ano;
		pcurrent->estudios[index].agenda->diferenca = getDifference(pcurrent->estudios[index].agenda->data_inicio, pcurrent->estudios[index].agenda->data_fim);
		if (strcmp(evento, "estadia") == 0) {
			pcurrent->estudios[index].agenda->preco = pcurrent->estudios[index].m2 * pcurrent->preco_m2 * pcurrent->estudios[index].agenda->diferenca;
			if (pcurrent->estudios[index].agenda->diferenca > 6) {
				pcurrent->estudios[index].agenda->preco = pcurrent->estudios[index].agenda->preco * 0.7;
			}
		}
		else {
			pcurrent->estudios[index].agenda->preco = 0;
		}
		return;
	}
	strcpy(pcurrentcl->evento, evento, (sizeof(char) * strlen(evento) + 1));
	strcpy(pcurrentcl->plataforma, plataforma, (sizeof(char)* strlen(plataforma) + 1));
	pcurrentcl->idUser = idCliente;
	pcurrentcl->data_inicio.dia = data_inicio_dia;
	pcurrentcl->data_inicio.mes = data_inicio_mes;
	pcurrentcl->data_inicio.ano = data_inicio_ano;
	pcurrentcl->data_fim.dia = data_fim_dia;
	pcurrentcl->data_fim.mes = data_fim_mes;
	pcurrentcl->data_fim.ano = data_fim_ano;
	pcurrentcl->diferenca = getDifference(pcurrentcl->data_inicio, pcurrentcl->data_fim);
	if (strcmp(evento, "estadia") == 0) {
		pcurrentcl->preco = pcurrent->estudios[index].m2 * pcurrent->preco_m2 * pcurrentcl->diferenca;
		if (pcurrentcl->diferenca > 6) {
			pcurrentcl->preco = pcurrentcl->preco * 0.7;
		}
	}
	else {
		pcurrentcl->preco = 0;
	}
}

int print_edificios(EMPRESA* empresa) {
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		printf("Id: %d | Morada: %s | Nome: %s | Coordenadas: %0.4f %0.4f | Preco m2: %d\n", pcurrent->id, pcurrent->morada, pcurrent->nome, pcurrent->latitude, pcurrent->longitude, pcurrent->preco_m2);
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
}

int print_estudios(EMPRESA* empresa, int id) {
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
			printf("Id: %d | Numero de quartos: %d | Area: %d\n", empresa->edificio->estudios[i].id, empresa->edificio->estudios[i].quartos, empresa->edificio->estudios[i].m2);
		}
		return;
	}
	if (pcurrent->num_estudios == 0) {
		printf("Este edificio nao tem estudios");
		return;
	}
	for (int i = 0; i < pcurrent->num_estudios; i++) {
		printf("Id: %d | Numero de quartos: %d | Area: %d\n", pcurrent->estudios[i].id, pcurrent->estudios[i].quartos, empresa->edificio->estudios[i].m2);
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
		int index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
		if (empresa->edificio->estudios[index].num_clientes == 0) {
			printf("Nao ha clientes\n");
			return;
		}
		CLIENTE* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].clientes;
		while (pcurrentcl != NULL) {
			printf("Id: %d | Nome: %s | Idade: %d\n", pcurrentcl->id, pcurrentcl->nome, pcurrentcl->idade);
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		return;
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

int print_agenda(EMPRESA* empresa, int id, int IdEstudio) {
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
		int index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, IdEstudio);
		if (index == -1) {
			printf("estudio nao encontrado");
			return;
		}
		if (empresa->edificio->estudios[index].num_agendas == 0) {
			printf("Nao ha agendas\n");
			return;
		}
		AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			printf("Id: %d | Id do User: %d | Descriçao do Evento: %s | Data Inicio: %d/%d/%d | Data Fim: %d/%d/%d | Preco: %d | Plataforma: %s\n", pcurrentcl->id, pcurrentcl->idUser, pcurrentcl->evento, pcurrentcl->data_inicio.dia, pcurrentcl->data_inicio.mes, pcurrentcl->data_inicio.ano, pcurrentcl->data_fim.dia, pcurrentcl->data_fim.mes, pcurrentcl->data_fim.ano, pcurrentcl->preco, pcurrentcl->plataforma);
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		return;
	}
	if (pcurrent->num_estudios == 0) {
		printf("Este edificio nao tem estudios");
		return;
	}
	for (index = 0; index < pcurrent->num_estudios; index++) {
		if (pcurrent->estudios[index].id == IdEstudio) {
			if (pcurrent->estudios[index].agenda == 0) {
				printf("Nao ha agendas\n");
				return;
			}
			AGENDA* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].agenda;
			while (pcurrentcl != NULL) {
				printf("Id: %d | Id do User: %d | Descriçao do Evento: %s | Data Inicio: %d/%d/%d | Data Fim: %d/%d/%d | Preco: %d | Plataforma: %s\n", pcurrentcl->id, pcurrentcl->idUser, pcurrentcl->evento, pcurrentcl->data_inicio.dia, pcurrentcl->data_inicio.mes, pcurrentcl->data_inicio.ano, pcurrentcl->data_fim.dia, pcurrentcl->data_fim.mes, pcurrentcl->data_fim.ano, pcurrentcl->preco, pcurrentcl->plataforma);
				pprevcl = pcurrentcl;
				pcurrentcl = pcurrentcl->next;
			}
			return;
		}
	}
}