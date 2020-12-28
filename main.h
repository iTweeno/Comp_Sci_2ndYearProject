typedef struct data {
	int dia;
	int mes;
	int ano;
}DATA;

typedef struct cliente {
	int id;
	char* nome;
	int idade;
	struct cliente* next;
}CLIENTE;

typedef struct agenda {
	int id;
	int idUser;
	char* evento;
	struct data data_inicio;
	struct data data_fim;
	int preco;
	int diferenca;
	struct agenda* next;
}AGENDA;

typedef struct estudio {
	int id;
	int quartos;
	int m2;
	int tamanho_preco;
	int num_precos;
	int num_clientes;
	int num_agendas;
	CLIENTE* clientes; //ll
	AGENDA* agenda; //ll
} ESTUDIO;

typedef struct plataforma {
	char* nome;
	char* estudios;
} PLATAFORMA;

typedef struct edificio {
	int preco_m2;
	int id;
	int tamanho_estudio;
	ESTUDIO* estudios; //arr
	int num_estudios;
	char* morada;
	int coordenadas;
	struct edificio * next;
} EDIFICIO;

typedef struct empresa {
	int num_edificios;
	EDIFICIO* edificio; //ll
	PLATAFORMA* plataformas;
} EMPRESA;

int trabalho();

extern EMPRESA empresa;