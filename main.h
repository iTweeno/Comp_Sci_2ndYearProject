typedef struct cliente {
	int id;
	char* nome;
	int idade;
	struct CLIENTE* next;
}CLIENTE;

typedef struct agenda {
	int id;
	int idUser;
	char* evento;
	int dia; //array
	struct agenda* next;
}AGENDA;

typedef struct preco {
	int mes;
	int preco;
}PRECO;

typedef struct estudio {
	int id;
	int quartos;
	CLIENTE clientes;
	AGENDA agenda;
	PRECO* precos;
	int tamanho;
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