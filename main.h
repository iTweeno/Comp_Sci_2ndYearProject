typedef struct cliente {
	int id;
	char* nome;
	int idade;
	char* email;
}CLIENTE;

typedef struct caracteristicas_estudio {
	int dias_ocupados;
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
	char* nome;
	char* estudios;
} PLATAFORMA;

typedef struct edificio {
	ESTUDIO* estudios; //array
	int num_estudios;
	char* morada;
	int coordenadas;
	struct edificio * next;
} EDIFICIO;

typedef struct empresa {
	int num_edificios;
	EDIFICIO* edificio;
	PLATAFORMA* plataformas;
} EMPRESA;

int trabalho();

extern EMPRESA empresa;