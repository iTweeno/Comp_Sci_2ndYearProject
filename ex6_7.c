#include<stdio.h>
#include"ex2_3.h"
#include"main.h"
//Billing and sort missing
int Relatorios() {
	int op;
	do {
		printf("\t\tGestor de Relatorios\n\n");
		printf("Escolha a opcao:\n");
		printf("\t1-Taxa de ocupacao por estudio\n");
		printf("\t2-Taxa de ocupacao por edificio\n");
		printf("\t3-Taxa de ocupacao total\n");
		printf("\t4-Taxa de Faturacao por estudio\n");
		printf("\t5-Taxa de Faturacao por edificio\n");
		printf("\t6-Taxa de Faturacao total\n");
		printf("\t0-Sair\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			Taxa_Ocupacao_Estudio(&empresa, 1, 1, 1, 1, 2010, 1, 1, 2030, "print");
			break;
		case 2:
			Taxa_Ocupacao_Edificio(&empresa, 1, 1, 1, 2010, 1, 1, 2030, "print");
			break;
		case 3:
			Taxa_Ocupacao_Lote(&empresa, 1, 1, 2010, 1, 1, 2030, "print");
			break;
		case 4:
			Taxa_Faturacao_Estudio(&empresa, 1, 1, 1, 1, 2010, 1, 1, 2030, "print");
			break;
		case 5:
			Taxa_Faturacao_Edificio(&empresa, 1, 1, 1, 2010, 1, 1, 2030, "print");
			break;
		case 6:
			Taxa_Faturacao_Lote(&empresa, 1, 1, 2010, 1, 1, 2030, "print");
			break;
		case 0:
			break;
		default:

			printf("Opcao invalida!\n\n");
		}
	} while (op != 0);

	return 0;
};

void swap(int* xp, int* yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(AGENDA arr[], int n)
{
	int i, j, min_idx;

	for (i = 0; i < n - 1; i++) {

		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j].id < arr[min_idx].id)
				min_idx = j;


		swap(&arr[min_idx], &arr[i]);
	}
}

int Taxa_Ocupacao_Estudio(EMPRESA* empresa, int idEdificio, int idEstudio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]) {
	DATA inicio = { data_inicio_dia,data_inicio_mes ,data_inicio_ano };
	DATA fim = { data_fim_dia,data_fim_mes ,data_fim_ano };
	int estadiaCount = 0;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != idEdificio) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este id\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		if (empresa->edificio->num_estudios == 0) {
			return printf("Nao existem estudios");
		}
		int index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, idEstudio);
		if (index == -1) {
			printf("Estudio nao existe");
			return;
		}
		if (empresa->edificio->estudios[index].num_agendas == 0) {
			printf("Nao ha agendas\n");
			return;
		}
		AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (strcmp(pcurrentcl->evento, "estadia") != 0) {
				continue;
			}
			if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
				estadiaCount++;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		if (strcmp(type, "print") == 0) {
			printf("Durante %d/%d/%d e %d/%d/%d, houveram %d estadias\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount);
		}
		else {
			FILE* fp = fopen("taxa_ocupacao.txt", "w");
			if (fp == NULL) {
				printf("Erro ao abrir ficheiro");
				return;
			}
			fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, houveram %d estadias\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount);
			fclose(fp);
		}
		return;
	}
	if (pcurrent->num_estudios == 0) {
		return printf("Nao existem estudios");
	}
	int index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, idEstudio);
	if (index == -1) {
		printf("Estudio nao existe");
		return;
	}
	if (pcurrent->estudios[index].num_agendas == 0) {
		printf("Nao ha agendas\n");
		return;
	}
	AGENDA* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].agenda;
	while (pcurrentcl != NULL) {
		if (strcmp(pcurrentcl->evento, "estadia") != 0) {
			continue;
		}
		if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
			estadiaCount++;
		}
		pprevcl = pcurrentcl;
		pcurrentcl = pcurrentcl->next;
	}
	if (strcmp(type, "print") == 0) {
		printf("Durante %d/%d/%d e %d/%d/%d, houveram %d estadias\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount);
	}
	else {
		FILE* fp = fopen("taxa_ocupacao.txt", "w");
		if (fp == NULL) {
			printf("Erro ao abrir ficheiro");
			return;
		}
		fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, houveram %d estadias\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount);
		fclose(fp);
	}
}

int Taxa_Ocupacao_Edificio(EMPRESA* empresa, int idEdificio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]) {
	DATA inicio = { data_inicio_dia,data_inicio_mes ,data_inicio_ano };
	DATA fim = { data_fim_dia,data_fim_mes ,data_fim_ano };
	int estadiaCount = 0;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != idEdificio) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este id\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		if (empresa->edificio->num_estudios == 0) {
			return printf("Nao existem estudios");
		}

		for (int index = 0; index < empresa->edificio->num_estudios; index++) {
			AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
			while (pcurrentcl != NULL) {
				if (strcmp(pcurrentcl->evento, "estadia") != 0) {
					continue;
				}
				if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
					estadiaCount++;
				}
				pprevcl = pcurrentcl;
				pcurrentcl = pcurrentcl->next;
			}
			if (strcmp(type, "print") == 0) {
				printf("Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount, empresa->edificio->estudios[index].id);
			}
			else if (strcmp(type, "file") == 0) {
				FILE* fp = fopen("taxa_ocupacao.txt", "w");
				if (fp == NULL) {
					printf("Erro ao abrir ficheiro");
				}
				fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount, empresa->edificio->estudios[index].id);
				fclose(fp);
			}
			else {
				printf("Opcao invalida");
			}
			estadiaCount = 0;
		}
		return;
	}
	if (empresa->edificio->num_estudios == 0) {
		return printf("Nao existem estudios");
	}

	for (int index = 0; index < pcurrent->num_estudios; index++) {
		AGENDA* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (strcmp(pcurrentcl->evento, "estadia") != 0) {
				continue;
			}
			if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
				estadiaCount++;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		if (strcmp(type, "print") == 0) {
			printf("Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount, pcurrent->estudios[index].id);
		}
		else if (strcmp(type, "file") == 0) {
			FILE* fp = fopen("taxa_ocupacao.txt", "w");
			if (fp == NULL) {
				printf("Erro ao abrir ficheiro");
			}
			fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount, pcurrent->estudios[index].id);
			fclose(fp);
		}
		else {
			printf("Opcao invalida");
		}
		estadiaCount = 0;
	}
}

int Taxa_Ocupacao_Lote(EMPRESA* empresa, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]) {
	DATA inicio = { data_inicio_dia,data_inicio_mes ,data_inicio_ano };
	DATA fim = { data_fim_dia,data_fim_mes ,data_fim_ano };
	int estadiaCount = 0;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		if (pcurrent->num_estudios == 0) {
			return printf("Nao existem estudios");
		}

		for (int index = 0; index < pcurrent->num_estudios; index++) {
			AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
			while (pcurrentcl != NULL) {
				if (strcmp(pcurrentcl->evento, "estadia") != 0) {
					continue;
				}
				if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
					estadiaCount++;
				}
				pprevcl = pcurrentcl;
				pcurrentcl = pcurrentcl->next;
			}
			if (strcmp(type, "print") == 0) {
				printf("Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d no edificio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount, pcurrent->estudios[index].id, pcurrent->id);
			}
			else if (strcmp(type, "file") == 0) {
				FILE* fp = fopen("taxa_ocupacao.txt", "w");
				if (fp == NULL) {
					printf("Erro ao abrir ficheiro");
				}
				fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d no edificio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, estadiaCount, pcurrent->estudios[index].id, pcurrent->id);
				fclose(fp);
			}
			else {
				printf("Opcao invalida");
			}
		}
		estadiaCount = 0;
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}

}

int Taxa_Faturacao_Estudio(EMPRESA* empresa, int idEdificio, int idEstudio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]) {
	DATA inicio = { data_inicio_dia,data_inicio_mes ,data_inicio_ano };
	DATA fim = { data_fim_dia,data_fim_mes ,data_fim_ano };
	int moneyAmount = 0;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != idEdificio) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este id\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		if (empresa->edificio->num_estudios == 0) {
			return printf("Nao existem estudios");
		}
		int index = binarySearch(empresa->edificio->estudios, 0, empresa->edificio->num_estudios - 1, idEstudio);
		if (index == -1) {
			printf("Estudio nao existe");
			return;
		}
		AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (strcmp(pcurrentcl->evento, "estadia") != 0) {
				continue;
			}
			if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
				moneyAmount += pcurrentcl->preco;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		if (strcmp(type, "print") == 0) {
			printf("Durante %d/%d/%d e %d/%d/%d, foram feitos %d euros\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount);
		}
		else {
			FILE* fp = fopen("taxa_ocupacao.txt", "w");
			if (fp == NULL) {
				printf("Erro ao abrir ficheiro");
				return;
			}
			fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, foram feitos %d euros\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount);
			fclose(fp);
		}
		return;
	}
	if (pcurrent->num_estudios == 0) {
		return printf("Nao existem estudios");
	}
	int index = binarySearch(pcurrent->estudios, 0, pcurrent->num_estudios - 1, idEstudio);
	if (index == -1) {
		printf("Estudio nao existe");
		return;
	}
	for (int i = 0; i < pcurrent->estudios[index].num_agendas; i++) {
		AGENDA* pprevcl = NULL, * pcurrentcl = pcurrent->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (strcmp(pcurrentcl->evento, "estadia") != 0) {
				continue;
			}
			if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
				moneyAmount += pcurrentcl->preco;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
	}
	if (strcmp(type, "print") == 0) {
		printf("Durante %d/%d/%d e %d/%d/%d, foram feitos %d euros\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount);
	}
	else {
		FILE* fp = fopen("taxa_ocupacao.txt", "w");
		if (fp == NULL) {
			printf("Erro ao abrir ficheiro");
			return;
		}
		fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, foram feitos %d euros\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount);
		fclose(fp);
	}
}

int Taxa_Faturacao_Edificio(EMPRESA* empresa, int idEdificio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]) {
	DATA inicio = { data_inicio_dia,data_inicio_mes ,data_inicio_ano };
	DATA fim = { data_fim_dia,data_fim_mes ,data_fim_ano };
	int moneyAmount = 0;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL && pcurrent->id != idEdificio) {
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}
	if (pcurrent == NULL) {
		printf("Nao ha edificios com este id\n");
		return;
	}
	if (empresa->edificio == pcurrent) {
		if (empresa->edificio->num_estudios == 0) {
			return printf("Nao existem estudios");
		}

		for (int index = 0; index < empresa->edificio->num_estudios; index++) {
			AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
			while (pcurrentcl != NULL) {
				if (strcmp(pcurrentcl->evento, "estadia") != 0) {
					continue;
				}
				if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
					moneyAmount += pcurrentcl->preco;
				}
				pprevcl = pcurrentcl;
				pcurrentcl = pcurrentcl->next;
			}
			if (strcmp(type, "print") == 0) {
				printf("Durante %d/%d/%d e %d/%d/%d, foram feitos %d euros no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount, empresa->edificio->estudios[index].id);
			}
			else if (strcmp(type, "file") == 0) {
				FILE* fp = fopen("taxa_ocupacao.txt", "w");
				if (fp == NULL) {
					printf("Erro ao abrir ficheiro");
				}
				fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, foram feitos %d euros no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount, empresa->edificio->estudios[index].id);
				fclose(fp);
			}
			else {
				printf("Opcao invalida");
			}
			moneyAmount = 0;
		}
		return;
	}
	if (empresa->edificio->num_estudios == 0) {
		return printf("Nao existem estudios");
	}

	for (int index = 0; index < pcurrent->num_estudios; index++) {
		AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
		while (pcurrentcl != NULL) {
			if (strcmp(pcurrentcl->evento, "estadia") != 0) {
				continue;
			}
			if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
				moneyAmount += pcurrentcl->preco;
			}
			pprevcl = pcurrentcl;
			pcurrentcl = pcurrentcl->next;
		}
		if (strcmp(type, "print") == 0) {
			printf("Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount, pcurrent->estudios[index].id);
		}
		else if (strcmp(type, "file") == 0) {
			FILE* fp = fopen("taxa_ocupacao.txt", "w");
			if (fp == NULL) {
				printf("Erro ao abrir ficheiro");
			}
			fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyAmount, pcurrent->estudios[index].id);
			fclose(fp);
		}
		else {
			printf("Opcao invalida");
		}
		moneyAmount = 0;
	}
}

int Taxa_Faturacao_Lote(EMPRESA* empresa, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]) {
	DATA inicio = { data_inicio_dia,data_inicio_mes ,data_inicio_ano };
	DATA fim = { data_fim_dia,data_fim_mes ,data_fim_ano };
	int moneyCount = 0;
	if (empresa->edificio == NULL) {
		printf("Nao ha edificios\n");
		return;
	}
	EDIFICIO* pprev = NULL, * pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		if (pcurrent->num_estudios == 0) {
			return printf("Nao existem estudios");
		}

		for (int index = 0; index < pcurrent->num_estudios; index++) {
			AGENDA* pprevcl = NULL, * pcurrentcl = empresa->edificio->estudios[index].agenda;
			while (pcurrentcl != NULL) {
				if (strcmp(pcurrentcl->evento, "estadia") != 0) {
					continue;
				}
				if (checkIfDatesCoincide(inicio, pcurrentcl->data_inicio) && checkIfDatesCoincide(pcurrentcl->data_inicio, fim)) {
					moneyCount += pcurrentcl->preco;
				}
				pprevcl = pcurrentcl;
				pcurrentcl = pcurrentcl->next;
			}
			if (strcmp(type, "print") == 0) {
				printf("Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d no edificio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyCount, pcurrent->estudios[index].id, pcurrent->id);
			}
			else if (strcmp(type, "file") == 0) {
				FILE* fp = fopen("taxa_ocupacao.txt", "w");
				if (fp == NULL) {
					printf("Erro ao abrir ficheiro");
				}
				fprintf(fp, "Durante %d/%d/%d e %d/%d/%d, houveram %d estadias no estudio %d no edificio %d\n", data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, moneyCount, pcurrent->estudios[index].id, pcurrent->id);
				fclose(fp);
			}
			else {
				printf("Opcao invalida");
			}
		}
		moneyCount = 0;
		pprev = pcurrent;
		pcurrent = pcurrent->next;
	}

}