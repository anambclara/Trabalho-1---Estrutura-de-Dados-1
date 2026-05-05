#include <stdio.h>
#include "livros.h"
#include "usuarios.h"
#include "emprestimos.h"
#include "lista.h"

void exibirMenu()
{
    printf("\n===== SISTEMA DA BIBLIOTECA =====\n");
    printf("1 - Cadastrar livro\n");
    printf("2 - Cadastrar usuário\n");
    printf("3 - Listar livros\n");
    printf("4 - Listar usuários\n");
    printf("5 - Realizar empréstimo\n");
    printf("6 - Registrar devolução\n");
    printf("7 - Listar livros emprestados por usuário\n");
    printf("8 - Exibir fila de espera de um livro\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

void executarOpcao(
    int opcao,
    ListaLivros *livros,
    ListaUsuarios *usuarios,
    ListaEmprestimos *emprestimos,
    ListaEspera *filaEspera
)
{
    switch (opcao)
    {
        case 1:
            cadastrarLivro(livros);
            break;

        case 2:
            cadastrarUsuario(usuarios);
            break;

        case 3:
            listarLivros(livros);
            break;

        case 4:
            listarUsuarios(usuarios);
            break;

        case 5:
            realizarEmprestimo(emprestimos, livros, usuarios, filaEspera);
            break;

        case 6:
            registrarDevolucao(emprestimos, livros, usuarios);
            break;

        case 7:
            listarLivrosEmprestadosPorUsuario(emprestimos, livros, usuarios);
            break;

        case 8:
            exibirFilaEspera(filaEspera);
            break;

        case 0:
            printf("Encerrando sistema...\n");
            break;

        default:
            printf("Opção inválida.\n");
    }
}

int main()
{
    ListaLivros livros;
    ListaUsuarios usuarios;
    ListaEmprestimos emprestimos;
    ListaEspera filaEspera;

    inicializarListaLivros(&livros);
    inicializarListaUsuarios(&usuarios);
    inicializarEmprestimos(&emprestimos);
    inicializarFilaEspera(&filaEspera);

    int opcao;

    do
    {
        exibirMenu();
        scanf("%d", &opcao);

        executarOpcao(opcao, &livros, &usuarios, &emprestimos, &filaEspera);

    } while (opcao != 0);

    return 0;
}