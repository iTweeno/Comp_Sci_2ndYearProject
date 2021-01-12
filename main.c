#include<stdio.h>
#include"main.h"


EMPRESA empresa = { 0,NULL,NULL };

int main() {
	int op;
	do {
		printf("\t\tGestor para a Empresa\n\n");
		printf("Escolha a opcao:\n");
		printf("\t1-Gestao Edificios\n");
		printf("\t2-Relatorios\n");
		printf("\t3-Print e Leitura\n");
		printf("\t4\n");
		printf("\t0-Sair\n");
		scanf("%d", &op);
		switch (op) {
		case 1:
			Gestao_Edificios();
			break;
		case 2:
			Relatorios();
			break;
		case 3:
			Ler_Escrever();
			break;
		case 4:

			break;
		case 0:

			return 0;
		default:

			printf("Opcao invalida!\n\n");
		}
	} while (op != 0);

	return 0;
};