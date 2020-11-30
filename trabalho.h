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

typedef struct plataforma {
	char nome;
	char estudios;
} PLATAFORMA;

typedef struct edificio {
	int num_estudios;
	int id;
	ESTUDIO estudios; //array
	char* morada;
	char* coordenadas;
} EDIFICIO;

typedef struct empresa {
	int num_edificios;
	EDIFICIO* edificios; //array
	PLATAFORMA* plataformas;
} EMPRESA;

int trabalho();

extern EMPRESA empresa;

extern struct EDIFICIO;

extern int num_edificios;