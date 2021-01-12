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
	char* plataforma;
	int preco;
	int diferenca;
	struct agenda* next;
}AGENDA;

typedef struct estudio {
	int id;
	int quartos;
	int m2;
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
	char* nome;
	int preco_m2;
	int id;
	int tamanho_estudio;
	ESTUDIO* estudios; //arr
	int num_estudios;
	char* morada;
	double latitude;
	double longitude;
	struct edificio * next;
} EDIFICIO;

typedef struct empresa {
	int num_edificios;
	EDIFICIO* edificio; //ll
	PLATAFORMA* plataformas;
} EMPRESA;

typedef struct Taxa {
	int moneyCount;
	int edificio;
	int estudio;
	int estadiaCount;
} TAXA;

int trabalho();

int inserir_edificio(EMPRESA* empresa, char morada[], char nome[], double latitude, double longitude, int id, int preco_m2);
int inserir_estudio(EMPRESA* empresa, int id, int idEstudio, int quartos, int m2);
int inserir_cliente(EMPRESA* empresa, int id, int idEstudio, int idCliente, char nome[], int idade);
int inserir_agenda(EMPRESA* empresa, int id, int IdEstudio, int idAgenda, int idCliente, char evento[], int data_fim_dia, int data_fim_mes, int data_fim_ano, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, char plataforma[]);
int remover_edificio(EMPRESA* empresa, int id);
int remover_estudio(EMPRESA* empresa, int id, int idEstudio);
int remover_cliente(EMPRESA* empresa, int id, int IdEstudio, int idCliente);
int remover_agenda(EMPRESA* empresa, int id, int IdEstudio, int idAgenda);
int editar_edificio(EMPRESA* empresa, int id, char morada[], char nome[], double latitude, double longitude, int preco_m2);
int editar_estudio(EMPRESA* empresa, int id, int idEstudio, int quartos);
int editar_cliente(EMPRESA* empresa, int id, int IdEstudio, int idCliente, char nome[], int idade);
int editar_agenda(EMPRESA* empresa, int id, int IdEstudio, int idAgenda, int idCliente, char evento[], int data_fim_dia, int data_fim_mes, int data_fim_ano, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, char plataforma[]);
int print_edificios(EMPRESA* empresa);
int print_estudios(EMPRESA* empresa, int id);
int print_clientes(EMPRESA* empresa, int id, int IdEstudio);
int print_agenda(EMPRESA* empresa, int id, int IdEstudio);

int Taxa_Ocupacao_Estudio(EMPRESA* empresa, int idEdificio, int idEstudio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]);
int Taxa_Ocupacao_Edificio(EMPRESA* empresa, int idEdificio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[], char order[]);
int Taxa_Ocupacao_Lote(EMPRESA* empresa, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[], char order[]);
int Taxa_Faturacao_Estudio(EMPRESA* empresa, int idEdificio, int idEstudio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[]);
int Taxa_Faturacao_Edificio(EMPRESA* empresa, int idEdificio, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[], char order[]);
int Taxa_Faturacao_Lote(EMPRESA* empresa, int data_inicio_dia, int data_inicio_mes, int data_inicio_ano, int data_fim_dia, int data_fim_mes, int data_fim_ano, char type[], char order[]);

int Guardar_Texto_Ficheiro(EMPRESA* empresa);
int Guardar_Texto_Agenda(EMPRESA* empresa);
int Guardar_Texto_Binary(EMPRESA* empresa);
int Guardar_Texto_Binary_Agenda(EMPRESA* empresa);
int Carregar_Ficheiro(EMPRESA* empresa);
int Carregar_Ficheiro_Agenda(EMPRESA* empresa);
int Ler_Binary(EMPRESA* empresa);
int Ler_Binary_Agenda(EMPRESA* empresa);

void insertionSort(int arr[], int n);
int binarySearch(int arr[], int l, int r, int x);
int getDifference(DATA dt1, DATA dt2);
int countLeapYears(DATA d);

void swap(int* xp, int* yp);
void selectionSortCrescente(TAXA arr[], int n, char type[]);
void selectionSortDecrescente(TAXA arr[], int n, int type[]);

extern EMPRESA empresa;