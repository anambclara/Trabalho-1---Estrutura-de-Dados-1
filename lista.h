

#ifndef LISTA_H
#define LISTA_H

//No da fila de espera
typedef struct NoFila {
    char ra[20];        
    char nome[100];
    struct NoFila *prox;
} NoFila;

//Lista circular: aponta para o ultimo no (ultimo->prox = primeiro)
typedef struct {
    NoFila *ultimo;
    int tamanho;
} FilaCircular;

typedef FilaCircular ListaEspera;

typedef struct ListaLivros ListaLivros;
typedef struct ListaUsuarios ListaUsuarios;

//Inicializa fila vazia
void filaInicializar(FilaCircular *fila);

//Insere usuario no fim da fila
int filaInserir(FilaCircular *fila, const char *ra, const char *nome);

//Remove o primeiro da fila (quando livro e devolvido)
//Copia ra e nome do removido
int filaRemover(FilaCircular *fila, char *ra_out, char *nome_out);

//Exibe todos na fila de espera
void filaExibir(const FilaCircular *fila);

//Verifica se usuario ja esta na fila (evita duplicata)
int filaContem(const FilaCircular *fila, const char *ra);

//Libera toda a memoria da fila
void filaDestruir(FilaCircular *fila);

//Funções auxiliares com nomenclatura alternativa
void inicializarFilaEspera(ListaEspera *fila);
int inserirNaFilaEspera(ListaLivros *livros, ListaUsuarios *usuarios, int codigoLivro, int idUsuario);
void exibirFilaEspera(const ListaEspera *fila);
void exibirFilaEsperaLivro(ListaLivros *livros);

#endif
