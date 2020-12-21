typedef struct cliente {
	int id;
	char* nome;
	int idade;
	char* email;
	int* diasEstadia;
	struct CLIENTE* next;
}CLIENTE;

typedef struct dias_ocupados {
	char* descricao;
	int dia;
	struct dias_ocupados* next;
}DIAS_OCUPADOS;

typedef struct preco {
	int mes;
	int preco;
}PRECO;

typedef struct estudio {
	int id;
	int quartos;
	CLIENTE clientes;
	DIAS_OCUPADOS dias_ocupados;
	PRECO* precos;
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