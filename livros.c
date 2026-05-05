#include "livros.h"

void inicializarLista(ListaLivros *lista)
{
    lista->inicio = NULL; // Lista vazia
    lista->tamanho = 0;
}

// Função para cadastrar um livro na lista
void cadastrarLivro(ListaLivros *lista)
{
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    if (novoLivro == NULL)
    {
        printf("Erro: memória insuficiente!\n");
        exit(1);
    }

    printf("Digite o código do livro: ");
    scanf("%d", &novoLivro->codigo);

    if (buscarLivro(lista, novoLivro->codigo) != NULL)
    {
        printf("Erro: código de livro já existe!\n");
        free(novoLivro);
        return;
    }

    printf("Digite o título do livro: ");
    scanf(" %[^\n]", novoLivro->titulo);

    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", novoLivro->autor);

    novoLivro->disponivel = 1;

    novoLivro->prox = lista->inicio;
    lista->inicio = novoLivro;
    lista->tamanho++;
};

Livro *buscarLivro(ListaLivros *lista, int codigo)
{
    Livro *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->codigo == codigo)
            return atual;
        atual = atual->prox;
    }
    return NULL; // Livro não encontrado
};

void listarLivros(ListaLivros *lista)
{
    printf("Lista de Livros: ");
    Livro *atual = lista->inicio;

    while (atual != NULL)
    {
        printf("\nCódigo: %d\nTítulo: %s\nAutor: %s\nDisponibilidade: %s\n",
               atual->codigo,
               atual->titulo,
               atual->autor,
               atual->disponivel ? "Disponível" : "Indisponível");
        atual = atual->prox;
    }
    printf("\nTotal de livros: %d\n", lista->tamanho);
};

void alterarDisponibilidade(Livro *livro, int status)
{
    if (livro != NULL)
    {
        livro->disponivel = status;
    }
};
