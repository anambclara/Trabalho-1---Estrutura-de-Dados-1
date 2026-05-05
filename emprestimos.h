#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

#include <stdio.h>
#include <stdlib.h>
#include "livros.h"
#include "usuarios.h"
#include "lista.h"

typedef struct Emprestimo
{
    int codigoLivro;
    int idUsuario;
    struct Emprestimo *prox;
} Emprestimo;

typedef struct
{
    Emprestimo *inicio;
    int tamanho;
} ListaEmprestimos;

void inicializarEmprestimos(ListaEmprestimos *lista);

void realizarEmprestimo(
    ListaEmprestimos *emprestimos,
    ListaLivros *livros,
    ListaUsuarios *usuarios,
    ListaEspera *filaEspera
);

void registrarDevolucao(
    ListaEmprestimos *emprestimos,
    ListaLivros *livros,
    ListaUsuarios *usuarios
);

void listarLivrosEmprestadosPorUsuario(
    ListaEmprestimos *emprestimos,
    ListaLivros *livros,
    ListaUsuarios *usuarios
);

#endif