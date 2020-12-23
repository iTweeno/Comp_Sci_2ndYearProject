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
	int data_inicio;
	int data_fim;
	struct agenda* next;
}AGENDA;

typedef struct preco {
	int mes;
	int preco;
}PRECO;

typedef struct estudio {
	int id;
	int quartos;
	int tamanho_preco;
	int num_precos;
	int num_clientes;
	int num_agendas;
	CLIENTE* clientes; //ll
	AGENDA* agenda; //ll
	PRECO* precos; //arr
} ESTUDIO;

typedef struct plataforma {
	char* nome;
	char* estudios;
} PLATAFORMA;

typedef struct edificio {
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