#include<stdio.h>
#include"main.h"


EMPRESA empresa = { 0,NULL };

int main() {
	inserir_edificio(&empresa, "Sjoao1", "DManuel", 10.2212, -10.4821, 1, 10);
	inserir_edificio(&empresa, "Sjoao2", "DManuel", 10.2212, -10.4821, 2, 10);
	print_edificios(&empresa);
	editar_edificio(&empresa, 1, "Sjoao2", "DJoao", 10.2222, -10, 10);
	remover_edificio(&empresa, 2);
	print_edificios(&empresa);
	inserir_estudio(&empresa, 1, 1, 2, 20);
	inserir_estudio(&empresa, 1, 2, 2, 20);
	print_estudios(&empresa, 1);
	editar_estudio(&empresa, 1, 1, 5);
	remover_estudio(&empresa, 1, 2);
	print_estudios(&empresa, 1);
	inserir_cliente(&empresa, 1, 1, 1, "Joao", 19);
	inserir_cliente(&empresa, 1, 1, 2, "Beatriz", 19);
	print_clientes(&empresa, 1, 1);
	editar_cliente(&empresa, 1, 1, 2, "David", 21);
	remover_cliente(&empresa, 1, 1, 2);
	print_clientes(&empresa, 1, 1);
	inserir_agenda(&empresa, 1, 1, 1, 1, "estadia", 19, 10, 2020, 10, 10, 2020, "airbnb");
	inserir_agenda(&empresa, 1, 1, 2, 1, "limpeza", 19, 11, 2020, 10, 11, 2020, "none");
	print_agenda(&empresa, 1, 1);
	editar_agenda(&empresa, 1, 1, 1, 1, "estadia", 19, 12, 2020, 10, 12, 2020, "booking");
	remover_agenda(&empresa, 1, 1, 2);
	print_agenda(&empresa, 1, 1);

	Taxa_Ocupacao_Estudio(&empresa, 1, 1, 1, 1, 2010, 1, 1, 2030, "print");
	Taxa_Ocupacao_Edificio(&empresa, 1, 1, 1, 2010, 1, 1, 2030, "print", "crescente");
	Taxa_Ocupacao_Lote(&empresa, 1, 1, 2010, 1, 1, 2030, "print", "crescente");
	Taxa_Faturacao_Estudio(&empresa, 1, 1, 1, 1, 2010, 1, 1, 2030, "print");
	Taxa_Faturacao_Edificio(&empresa, 1, 1, 1, 2010, 1, 1, 2030, "print", "crescente");
	Taxa_Faturacao_Lote(&empresa, 1, 1, 2010, 1, 1, 2030, "print", "crescente");

	Guardar_Texto_Ficheiro(&empresa);
	Guardar_Texto_Agenda(&empresa);
	Guardar_Texto_Binary(&empresa);
	Guardar_Texto_Binary_Agenda(&empresa);
	Carregar_Ficheiro(&empresa);
	Carregar_Ficheiro_Agenda(&empresa);
	Ler_Binary(&empresa);
	Ler_Binary_Agenda(&empresa);

};

/*	int op;
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

	return 0;*/