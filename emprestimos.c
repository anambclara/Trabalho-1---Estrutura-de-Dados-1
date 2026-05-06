#include "emprestimos.h"

void inicializarEmprestimos(ListaEmprestimos *lista) {
    lista->inicio = NULL;
    lista->tamanho = 0;
}

// faz o empréstimo se o livro estiver livre. Se não estiver, coloca na fila do próprio livro
void realizarEmprestimo (
    ListaEmprestimos *emprestimos,
    ListaLivros *livros,
    ListaUsuarios *usuarios
)
{
    int codigoLivro;
    int idUsuario;

    printf("Digite o código do livro: ");
    scanf("%d", &codigoLivro);

    Livro *livro = buscarLivro(livros, codigoLivro);

    if (livro == NULL)
    {
        printf("Livro não encontrado.\n");
        return;
    }

    printf("Digite o RA ou SIAPE do usuário: ");
    scanf("%d", &idUsuario);

    Usuario *usuario = buscarUsuario(usuarios, idUsuario);

    if (usuario == NULL)
    {
        printf("Usuário não encontrado.\n");
        return;
    }

    if (usuario->qtdEmprestimos >= 2)
    {
        printf("Usuário atingiu o limite de 2 empréstimos.\n");
        return;
    }

    if (livro->disponivel == 0)
    {
        printf("Livro indisponível. Usuário adicionado à fila de espera.\n");

        inserirNaFilaEspera(livros, usuarios, codigoLivro, idUsuario);

        return;
    }

    Emprestimo *novo = (Emprestimo *) malloc(sizeof(Emprestimo));

    if (novo == NULL)
    {
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }

    novo->codigoLivro = codigoLivro;
    novo->idUsuario = idUsuario;
    novo->prox = emprestimos->inicio;

    emprestimos->inicio = novo;
    emprestimos->tamanho++;

    alterarDisponibilidade(livro, 0);
    usuario->qtdEmprestimos++;

    printf("Empréstimo realizado com sucesso.\n");
}

// registra a devolucao e se tiver fila empresta o livro para o proximo usuario
void registrarDevolucao(
    ListaEmprestimos *emprestimos,
    ListaLivros *livros,
    ListaUsuarios *usuarios
)
{
    int codigoLivro;
    int idUsuario;

    printf("Digite o código do livro devolvido: ");
    scanf("%d", &codigoLivro);

    printf("Digite o RA ou SIAPE do usuário: ");
    scanf("%d", &idUsuario);

    Emprestimo *atual = emprestimos->inicio;
    Emprestimo *anterior = NULL;
    Livro *livro = buscarLivro(livros, codigoLivro);
    Usuario *usuario = buscarUsuario(usuarios, idUsuario);

    while (atual != NULL)
    {
        if (atual->codigoLivro == codigoLivro && atual->idUsuario == idUsuario)
        {
            if (anterior == NULL)
            {
                emprestimos->inicio = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            if (livro != NULL)
            {
                alterarDisponibilidade(livro, 1);
            }

            if (usuario != NULL && usuario->qtdEmprestimos > 0)
            {
                usuario->qtdEmprestimos--;
            }

            free(atual);
            emprestimos->tamanho--;

            printf("Devolução registrada com sucesso.\n");

            if (livro != NULL)
            {
                char raFila[20];
                char nomeFila[100];

                // depois da devolucao, tenta emprestar para o primeiro da fila do livro
                while (livro->filaEspera.tamanho > 0 && filaRemover(&livro->filaEspera, raFila, nomeFila))
                {
                    int idFila = atoi(raFila);
                    Usuario *usuarioFila = buscarUsuario(usuarios, idFila);

                    if (usuarioFila == NULL)
                    {
                        printf("Usuário da fila não encontrado: %s.\n", nomeFila);
                    }
                    else if (usuarioFila->qtdEmprestimos >= 2)
                    {
                        printf("%s estava na fila, mas atingiu o limite de 2 empréstimos.\n", usuarioFila->nome);
                    }
                    else
                    {
                        Emprestimo *novo = (Emprestimo *) malloc(sizeof(Emprestimo));

                        if (novo == NULL)
                        {
                            printf("Erro: memória insuficiente.\n");
                            exit(1);
                        }

                        novo->codigoLivro = codigoLivro;
                        novo->idUsuario = usuarioFila->id;
                        novo->prox = emprestimos->inicio;

                        emprestimos->inicio = novo;
                        emprestimos->tamanho++;

                        alterarDisponibilidade(livro, 0);
                        usuarioFila->qtdEmprestimos++;

                        printf("Livro emprestado automaticamente para %s.\n", usuarioFila->nome);
                        return;
                    }
                }
            }

            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("Empréstimo não encontrado.\n");
}

void listarLivrosEmprestadosPorUsuario(
    ListaEmprestimos *emprestimos,
    ListaLivros *livros,
    ListaUsuarios *usuarios
)
{
    int idUsuario;
    int encontrou = 0;

    printf("Digite o RA ou SIAPE do usuário: ");
    scanf("%d", &idUsuario);

    Usuario *usuario = buscarUsuario(usuarios, idUsuario);

    if (usuario == NULL)
    {
        printf("Usuário não encontrado.\n");
        return;
    }

    printf("\nLivros emprestados por %s:\n", usuario->nome);

    Emprestimo *atual = emprestimos->inicio;

    while (atual != NULL)
    {
        if (atual->idUsuario == idUsuario)
        {
            Livro *livro = buscarLivro(livros, atual->codigoLivro);

            if (livro != NULL)
            {
                printf("\nCódigo: %d\nTítulo: %s\nAutor: %s\n",
                       livro->codigo,
                       livro->titulo,
                       livro->autor);

                encontrou = 1;
            }
        }

        atual = atual->prox;
    }

    if (!encontrou)
    {
        printf("Este usuário não possui livros emprestados.\n");
    }
}
