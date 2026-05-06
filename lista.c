

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "livros.h"
#include "usuarios.h"


//filaInicializar - Prepara a fila para uso, sem alocar memoria.
void filaInicializar(FilaCircular *fila) {
    fila->ultimo = NULL;
    fila->tamanho = 0;
}


//filaInserir - Adiciona usuario ao fim da fila circular.
int filaInserir(FilaCircular *fila, const char *ra, const char *nome) {
    if (filaContem(fila, ra)) {
        printf("Usuario %s ja esta na fila de espera.\n", nome);
        return 0;
    }

    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));
    if (!novo) {
        printf("Erro: memoria insuficiente.\n");
        return 0;
    }

    strncpy(novo->ra, ra, sizeof(novo->ra) - 1);
    novo->ra[sizeof(novo->ra) - 1] = '\0';
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    if (fila->ultimo == NULL) {
        //Fila vazia: no aponta para si mesmo 
        novo->prox = novo;
        fila->ultimo = novo;
    } else {
        //Insere apos o ultimo, antes do primeiro 
        novo->prox = fila->ultimo->prox;
        fila->ultimo->prox = novo;
        fila->ultimo = novo;
    }

    fila->tamanho++;
    return 1;
}

//filaRemover - Remove o primeiro da fila (proximo a ser atendido).
int filaRemover(FilaCircular *fila, char *ra_out, char *nome_out) {
    if (fila->ultimo == NULL) {
        printf("Fila de espera vazia.\n");
        return 0;
    }

    NoFila *primeiro = fila->ultimo->prox;

    if (ra_out) {
        strncpy(ra_out, primeiro->ra, 19);
        ra_out[19] = '\0';
    }
    if (nome_out) {
        strncpy(nome_out, primeiro->nome, 99);
        nome_out[99] = '\0';
    }

    if (primeiro == fila->ultimo) {
        fila->ultimo = NULL;
    } else {
        fila->ultimo->prox = primeiro->prox;
    }

    free(primeiro);
    fila->tamanho--;
    return 1;
}

//filaExibir - Mostra todos os usuarios na fila de espera em ordem.
void filaExibir(const FilaCircular *fila) {
    if (fila->ultimo == NULL) {
        printf("Fila de espera vazia.\n");
        return;
    }

    printf("Fila de espera (%d pessoa(s)):\n", fila->tamanho);
    NoFila *atual = fila->ultimo->prox; 
    int pos = 1;
    do {
        printf("  %d. %s (RA/SIAPE: %s)\n", pos++, atual->nome, atual->ra);
        atual = atual->prox;
    } while (atual != fila->ultimo->prox);
}


//filaContem - Verifica se ra ja esta na fila. Evita duplicatas.
int filaContem(const FilaCircular *fila, const char *ra) {
    if (fila->ultimo == NULL) return 0;

    NoFila *atual = fila->ultimo->prox;
    do {
        if (strcmp(atual->ra, ra) == 0) return 1;
        atual = atual->prox;
    } while (atual != fila->ultimo->prox);

    return 0;
}

//filaDestruir - Libera toda a memoria alocada pela fila.
void filaDestruir(FilaCircular *fila) {
    if (fila->ultimo == NULL) return;

    NoFila *primeiro = fila->ultimo->prox;
    NoFila *atual = primeiro;
    NoFila *prox;

    fila->ultimo->prox = NULL;

    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }

    fila->ultimo = NULL;
    fila->tamanho = 0;
}


//Funções auxiliares com nomenclatura alternativa
void inicializarFilaEspera(ListaEspera *fila) {
    filaInicializar(fila);
}

int inserirNaFilaEspera(ListaLivros *livros, ListaUsuarios *usuarios, int codigoLivro, int idUsuario) {
    Livro *livro = buscarLivro(livros, codigoLivro);
    Usuario *usuario = buscarUsuario(usuarios, idUsuario);

    if (!livro || !usuario) return 0;
    
    char ra_str[20];
    snprintf(ra_str, sizeof(ra_str), "%d", usuario->id);
    
    return filaInserir(&livro->filaEspera, ra_str, usuario->nome);
}

void exibirFilaEspera(const ListaEspera *fila) {
    filaExibir(fila);
}

// pede o codigo do livro e mostra somente a fila daquele livro
void exibirFilaEsperaLivro(ListaLivros *livros) {
    int codigoLivro;

    printf("Digite o codigo do livro: ");
    scanf("%d", &codigoLivro);

    Livro *livro = buscarLivro(livros, codigoLivro);

    if (livro == NULL) {
        printf("Livro nao encontrado.\n");
        return;
    }

    printf("\nFila de espera do livro: %s\n", livro->titulo);
    filaExibir(&livro->filaEspera);
}
