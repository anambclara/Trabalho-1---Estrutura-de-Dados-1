#define USUARIOS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id; // RA ou SIAPE
    char nome[100];
    int tipo;           // 1 para aluno, 2 para professor
    int qtdEmprestimos; // Quantidade de livros emprestados
    struct Usuario *prox;
} Usuario;

typedef struct
{
    Usuario *inicio;
    int tamanho;
} ListaUsuarios;

void inicializarLista(ListaUsuarios *lista);

void cadastrarUsuario(ListaUsuarios *lista);

Usuario *buscarUsuario(ListaUsuarios *lista, int id);

void listarUsuarios(ListaUsuarios *lista);

void podeEmprestar(Usuario *usuario);