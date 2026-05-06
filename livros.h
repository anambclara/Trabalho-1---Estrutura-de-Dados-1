#ifndef LIVROS_H
#define LIVROS_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct Livro
{
    char titulo[100];
    char autor[100];
    int codigo;
    int disponivel; // 1 para disponível, 0 pra indisponível
    FilaCircular filaEspera; // cada livro tem sua propria fila
    struct Livro *prox;
} Livro;

typedef struct ListaLivros
{
    Livro *inicio;
    int tamanho;
} ListaLivros;

void inicializarListaLivros(ListaLivros *lista);

void cadastrarLivro(ListaLivros *lista);

Livro *buscarLivro(ListaLivros *lista, int codigo);

void listarLivros(ListaLivros *lista);

void alterarDisponibilidade(Livro *livro, int status);

#endif
