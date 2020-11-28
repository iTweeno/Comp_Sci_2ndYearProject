typedef struct cliente {
	int id;
	char nome;
	int idade;
	char email;
}CLIENTE;

typedef struct caracteristicas_estudio {
	int dias_ocupados[100][100];
	int dias_limpeza;
	int historico_hospedes;
	int dias_manutenção;
	int faturação;
	int cliente_id;
	int preco;
}CARACTERISTICAS_ESTUDIO;

typedef struct estudio {
	int id;
	int quartos;
	CARACTERISTICAS_ESTUDIO caracteristicas_estudio;
} ESTUDIO;

typedef struct edificio {
	ESTUDIO estudios; //array
	char morada;
	char coordenadas;
} EDIFICIO;

typedef struct plataforma {
	char nome;
	char estudios;
} PLATAFORMA;

struct empresa {
	EDIFICIO edificios[10]; //array
	PLATAFORMA plataformas;
};

int trabalho();

extern struct empresa* empresa;