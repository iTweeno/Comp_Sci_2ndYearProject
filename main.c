struct estudio {
	char edificio,
	char coordenadas[],
	char morada,
	char quartos;
} ESTUDIO;

struct agenda_estudio {
	int dias_ocupados[][],
	int plataforma[] //array liga aos dias ocupados para saber quais dias ocupados tem
	int dias_limpeza[],
	int dias_manutenção[],
	int faturação[]
	int cliente_id[]
	int preco[],

}AGENDA_ESTUDIO;

struct cliente {
	int id,
	char nome[],
	int idade,
	char email[],
}CLIENTE ;

struct plataforma {
	char nome,
	char estudios[]
} PLATAFORMA;

int main() {
	
}