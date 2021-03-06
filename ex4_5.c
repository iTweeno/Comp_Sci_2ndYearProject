#include<stdio.h>
#include"main.h"

int Ler_Escrever() {
	int op;
	do {
		printf("\t\tGestor de Escrita e leitura\n\n");
		printf("Escolha a opcao:\n");
		printf("\t1-Guardar Texto Tudo excepto agenda\n");
		printf("\t2-Guardar Texto Agenda\n");
		printf("\t3-Guardar texto Binary tudo excepto agenda\n");
		printf("\t4-Guardar Texto Binary Agenda\n");
		printf("\t5-Carregar Tudo Excepto Agenda\n");
		printf("\t6-Carregar Agenda\n");
		printf("\t7-Ler tudo binary excepto agenda\n");
		printf("\t8-Ler tudo binary agenda\n");
		printf("\t0-Sair\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			Guardar_Texto_Ficheiro(&empresa);
			break;
		case 2:
			Guardar_Texto_Agenda(&empresa);
			break;
		case 3:
			Guardar_Texto_Binary(&empresa);
			break;
		case 4:
			Guardar_Texto_Binary_Agenda(&empresa);
			break;
		case 5:
			Carregar_Ficheiro(&empresa);
			break;
		case 6:
			Carregar_Ficheiro_Agenda(&empresa);
			break;
		case 7:
			Ler_Binary(&empresa);
			break;
		case 8:
			Ler_Binary_Agenda(&empresa);
			break;
		case 0:

			return 0;
		default:

			printf("Opcao invalida!\n\n");
		}
	} while (op != 0);

	return 0;
};
///guarda tudoo o que est� dentro das structs para um ficheiro Info.txt excepto a agenda
int Guardar_Texto_Ficheiro(EMPRESA* empresa) {
	FILE* pfile = fopen("Info.txt", "w");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	fprintf(pfile, "Num edificios: %d\n", empresa->num_edificios);
	EDIFICIO* pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		fprintf(pfile, "Edifico: %d | Preco_m2: %d | Nome: %s | Num_Estudios: %d | Morada: %s | Latitude: %0.4f | Longitude: %0.4f | Tamanho_Estudio: %d\n", pcurrent->id, pcurrent->preco_m2, pcurrent->nome, pcurrent->num_estudios, pcurrent->morada, pcurrent->latitude, pcurrent->longitude, pcurrent->tamanho_estudio);

		for (int i = 0; i < pcurrent->num_estudios; i++) {
			fprintf(pfile, "Estudio: %d | Quartos: %d | Area: %d | Num_Clientes: %d | Num_Agendas: %d\n", pcurrent->estudios[i].id, pcurrent->estudios[i].quartos, pcurrent->estudios[i].m2, pcurrent->estudios[i].num_clientes, pcurrent->estudios[i].num_agendas);
			CLIENTE* pcurrentcl = pcurrent->estudios[i].clientes;
			while (pcurrentcl != NULL) {
				fprintf(pfile, "Cliente: %d | Nome: %s | Idade: %d\n", pcurrentcl->id, pcurrentcl->nome, pcurrentcl->idade);
				pcurrentcl = pcurrentcl->next;
			}
		}
		pcurrent = pcurrent->next;
	}
	fclose(pfile);
}
///Guarda todos os eventos na agenda para um ficheiro Agenda.txt
int Guardar_Texto_Agenda(EMPRESA* empresa) {
	FILE* pfile = fopen("Agenda.txt", "w");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	EDIFICIO* pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		for (int i = 0; i < pcurrent->num_estudios; i++) {
			fprintf(pfile, "Num_Agendas: %d\n", pcurrent->estudios[i].num_agendas);
			AGENDA* pcurrentag = pcurrent->estudios[i].agenda;
			while (pcurrentag != NULL) {
				fprintf(pfile, "Edificio: %d | Estudio: %d | Agenda: %d | Id_User: %d | Evento: %s | Data_Inicio: %d / %d / %d | Data_Fim: %d / %d / %d | Preco: %d | Diferenca_dias: %d | Plataforma: %s\n", pcurrent->id, pcurrent->estudios[i].id, pcurrentag->id, pcurrentag->idUser, pcurrentag->evento, pcurrentag->data_inicio.dia, pcurrentag->data_inicio.mes, pcurrentag->data_inicio.ano, pcurrentag->data_fim.dia, pcurrentag->data_fim.mes, pcurrentag->data_fim.ano, pcurrentag->preco, pcurrentag->diferenca, pcurrentag->plataforma);
				pcurrentag = pcurrentag->next;
			}
		}
		pcurrent = pcurrent->next;
	}
	fclose(pfile);
}
///Guarda as structs para um ficheiroo binario excepto a agenda
int Guardar_Texto_Binary(EMPRESA* empresa) {
	FILE* pfile = fopen("InfoB.bin", "wb");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	fwrite(&(empresa->num_edificios), sizeof(int), 1, pfile);
	EDIFICIO* pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		fwrite(&(pcurrent->id), sizeof(int), 1, pfile);
		fwrite(&(pcurrent->preco_m2), sizeof(int), 1, pfile);
		fwrite(pcurrent->nome, sizeof(char), 50, pfile);
		fwrite(&(pcurrent->num_estudios), sizeof(int), 1, pfile);
		fwrite(pcurrent->morada, sizeof(char), 50, pfile);
		fwrite(&(pcurrent->latitude), sizeof(double), 1, pfile);
		fwrite(&(pcurrent->longitude), sizeof(double), 1, pfile);
		fwrite(&(pcurrent->tamanho_estudio), sizeof(int), 1, pfile);
		for (int i = 0; i < pcurrent->num_estudios; i++) {
			fwrite(&(pcurrent->estudios[i].id), sizeof(int), 1, pfile);
			fwrite(&(pcurrent->estudios[i].quartos), sizeof(int), 1, pfile);
			fwrite(&(pcurrent->estudios[i].m2), sizeof(int), 1, pfile);
			fwrite(&(pcurrent->estudios[i].num_clientes), sizeof(int), 1, pfile);
			fwrite(&(pcurrent->estudios[i].num_agendas), sizeof(int), 1, pfile);
			CLIENTE* pcurrentcl = pcurrent->estudios[i].clientes;
			while (pcurrentcl != NULL) {
				fwrite(&(pcurrentcl->id), sizeof(int), 1, pfile);
				fwrite(pcurrentcl->nome, sizeof(char), 50, pfile);
				fwrite(&(pcurrentcl->idade), sizeof(int), 1, pfile);
				pcurrentcl = pcurrentcl->next;
			}
		}
		pcurrent = pcurrent->next;
	}
	fclose(pfile);
}
///guarda a agenda em binario para um ficheiro bin
int Guardar_Texto_Binary_Agenda(EMPRESA* empresa) {
	FILE* pfile = fopen("AgendaB.bin", "wb");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	EDIFICIO* pcurrent = empresa->edificio;
	while (pcurrent != NULL) {
		for (int i = 0; i < pcurrent->num_estudios; i++) {
			fwrite(&(pcurrent->estudios[i].num_agendas), sizeof(int), 1, pfile);
			AGENDA* pcurrentag = pcurrent->estudios[i].agenda;
			while (pcurrentag != NULL) {
				fwrite(&(pcurrent->id), sizeof(int), 1, pfile);
				fwrite(&(pcurrent->estudios[i].id), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->id), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->idUser), sizeof(int), 1, pfile);
				fwrite(pcurrentag->evento, sizeof(char), 50, pfile);
				fwrite(pcurrentag->plataforma, sizeof(char), 50, pfile);
				fwrite(&(pcurrentag->preco), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->diferenca), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->data_inicio.dia), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->data_inicio.mes), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->data_inicio.ano), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->data_fim.dia), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->data_fim.mes), sizeof(int), 1, pfile);
				fwrite(&(pcurrentag->data_fim.ano), sizeof(int), 1, pfile);

				pcurrentag = pcurrentag->next;
			}
		}
		pcurrent = pcurrent->next;
	}
	fclose(pfile);
}
///Carrega o ficheiro e adiciona � struct
int Carregar_Ficheiro(EMPRESA* empresa) {
	FILE* pfile = fopen("Info.txt", "r");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	int num_edificios, idEdificio, precom2, num_estudios, tamanho_estudio, idEstudio, quartos, area, num_clientes, num_agendas, idCliente, Idade;
	double latitude, longitude;
	char nomeEdificio[50], morada[50], nomeCliente[50];
	fscanf(pfile, "%*s %*s %d", &num_edificios);
	//test
	for (int i = 0; i < num_edificios; i++) {
		fscanf(pfile, "%*s %d %*s %*s %d  %*s %*s %s %*s %*s %d %*s %*s %s %*s %*s %lf %*s %*s %lf %*s %*s %d", &idEdificio, &precom2, nomeEdificio, &num_estudios, morada, &latitude, &longitude, &tamanho_estudio); 
		inserir_edificio(empresa, morada, nomeEdificio, latitude, longitude, idEdificio, precom2);
		for (int j = 0; j < num_estudios; j++) {
			fscanf(pfile, "%*s %d %*s %*s %d  %*s %*s %d  %*s %*s %d  %*s %*s %d", &idEstudio, &quartos, &area, &num_clientes, &num_agendas);
			inserir_estudio(empresa, idEdificio, idEstudio, quartos, area);
			for (int k = 0; k < num_clientes; k++) {
				fscanf(pfile, "%*s %d %*s %*s %s %*s %*s %d", &idCliente, nomeCliente, &Idade);
				inserir_cliente(empresa, idEdificio, idEstudio, idCliente, nomeCliente, Idade);
			}
		}
	}

}
///Carrega os eventos e adiciona �s structs
int Carregar_Ficheiro_Agenda(EMPRESA* empresa) {
	FILE* pfile = fopen("Agenda.txt", "r");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	int num_agendas, idEdificio, idEstudio, idAgenda, idUser, data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano, diferenca,preco;
	char evento[50], plataforma[50];
	fscanf(pfile, "%*s %d", &num_agendas);
	for (int i = 0; i < num_agendas; i++) {
		fscanf(pfile,"%*s %d %*s %*s %d %*s %*s %d %*s %*s %d %*s %*s %s %*s %*s %d %*s %d %*s %d %*s %*s %d %*s %d %*s %d %*s %*s %d %*s %*s %d %*s %*s %s", &idEdificio, &idEstudio, &idAgenda, &idUser, evento, &data_inicio_dia, &data_inicio_mes, &data_inicio_ano, &data_fim_dia, &data_fim_mes, &data_fim_ano, &preco, &diferenca,plataforma);
		inserir_agenda(empresa, idEdificio, idEstudio, idAgenda, idUser, evento, data_fim_dia, data_fim_mes, data_fim_ano, data_inicio_dia, data_fim_mes, data_inicio_ano, plataforma);
	}
}
///l� o ficheiro em bin�rio e faz print do seu conteudo
int Ler_Binary(EMPRESA* empresa) {
	FILE* pfile = fopen("InfoB.bin", "rb");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	int numEd, idEs, precom2, num_estudios, tam_estudio, idEst, quartos, m2, num_clientes, num_agendas, idcl, idade;
	double latitude, longitude;
	char nomeEd[50], morada[50], nomeCl[50];
	fread(&numEd, sizeof(int), 1, pfile);
	printf("Num edificios: %d\n", numEd);
	for (int i = 0; i < numEd; i++) {
		fread(&idEs, sizeof(int), 1, pfile);
		fread(&precom2, sizeof(int), 1, pfile);
		fread(nomeEd, sizeof(char), 50, pfile);
		fread(&num_estudios, sizeof(int), 1, pfile);
		fread(morada, sizeof(char), 50, pfile);
		fread(&latitude, sizeof(double), 1, pfile);
		fread(&longitude, sizeof(double), 1, pfile);
		fread(&tam_estudio, sizeof(int), 1, pfile);
		printf("Edifico: %d | Preco_m2: %d | Nome: %s | Num_Estudios: %d | Morada: %s | Latitude: %lf | Longitude: %lf | Tamanho_Estudio: %d\n", idEs, precom2, nomeEd, num_estudios, morada, latitude, longitude, tam_estudio);
		for (int j = 0; j < num_estudios; j++) {
			fread(&idEst, sizeof(int), 1, pfile);
			fread(&quartos, sizeof(int), 1, pfile);
			fread(&m2, sizeof(int), 1, pfile);
			fread(&num_clientes, sizeof(int), 1, pfile);
			fread(&num_agendas, sizeof(int), 1, pfile);
			printf("Estudio: %d | Quartos: %d | Area: %d | Num_Clientes: %d | Num_Agendas: %d\n", idEst, quartos, m2, num_clientes, num_agendas);
		}
		for (int k = 0; k < num_clientes; k++) {
			fread(&idcl, sizeof(int), 1, pfile);
			fread(nomeCl, sizeof(char), 50, pfile);
			fread(&idade, sizeof(int), 1, pfile);
			printf("Cliente: Id: %d | Nome: %s | Idade: %d\n", idcl, nomeCl, idade);
		}
	}
	fclose(pfile);
}
///le o ficheiro AgendaB em binario e faz print do output
int Ler_Binary_Agenda(EMPRESA* empresa) {
	FILE* pfile = fopen("AgendaB.bin", "rb");
	if (pfile == NULL) {
		printf("Erro a aceder ao ficheiro");
		return;
	}
	int  num_agendas, idEs, idEst, idAg, idUser, preco, diferenca, idcl, idade, data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano;
	char evento[50], plataforma[50];
	fread(&num_agendas, sizeof(int), 1, pfile);
	printf("Num agendas: %d\n", num_agendas);
	for (int i = 0; i < num_agendas; i++) {
		fread(&idEs, sizeof(int), 1, pfile);
		fread(&idEst, sizeof(int), 1, pfile);
		fread(&idAg, sizeof(int), 1, pfile);
		fread(&idUser, sizeof(int), 1, pfile);
		fread(evento, sizeof(char), 50, pfile);
		fread(plataforma, sizeof(char), 50, pfile);
		fread(&preco, sizeof(int), 1, pfile);
		fread(&diferenca, sizeof(int), 1, pfile);
		fread(&data_inicio_dia, sizeof(int), 1, pfile);
		fread(&data_inicio_mes, sizeof(int), 1, pfile);
		fread(&data_inicio_ano, sizeof(int), 1, pfile);
		fread(&data_fim_dia, sizeof(int), 1, pfile);
		fread(&data_fim_mes, sizeof(int), 1, pfile);
		fread(&data_fim_ano, sizeof(int), 1, pfile);
		printf("Edifico: %d | Estudio: %d | Id: %d | idUser: %d | Evento: %s | Plataforma: %s | Preco: %d | Diferenca: %d | Data Inicio: %d/%d/%d | Data Fim: %d/%d/%d\n", idEs, idEst, idAg, idUser, evento, plataforma, preco, diferenca, data_inicio_dia, data_inicio_mes, data_inicio_ano, data_fim_dia, data_fim_mes, data_fim_ano);
	}
	fclose(pfile);
}