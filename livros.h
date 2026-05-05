#define LIVROS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Livro
{
    char titulo[100];
    char autor[100];
    int codigo;
    int disponivel; // 1 para disponível, 0 pra indisponível
    struct Livro *prox;
} Livro;

typedef struct
{
    Livro *inicio;
    int tamanho;
} ListaLivros;

void inicializarLista(ListaLivros *lista); 

void cadastrarLivro(ListaLivros *lista);

Livro* buscarLivro(ListaLivros *lista, int codigo);

void listarLivros(ListaLivros *lista);

void alterarDisponibilidade(Livro *livro, int status);