#include "usuarios.h"

void inicializarLista(ListaUsuarios *lista)
{
    lista->inicio = NULL; // Lista vazia
    lista->tamanho = 0;
};

void cadastrarUsuario(ListaUsuarios *lista)
{
    Usuario *novoUsuario = (Usuario *)malloc(sizeof(Usuario));
    if (novoUsuario == NULL)
    {
        printf("Erro: memória insuficiente!\n");
        exit(1);
    }

    printf("Digite o RA ou SIAPE do usuário: ");
    scanf("%d", &novoUsuario->id);

    if (buscarUsuario(lista, novoUsuario->id) != NULL)
    {
        printf("Erro: usuário já existe!\n"); // Chama a função de busca para verificar se o usuário já existe
        free(novoUsuario);
        return;
    }

    printf("Digite o nome do usuário: ");
    scanf(" %[^\n]", novoUsuario->nome);

    printf("Digite o tipo do usuário (1 para aluno, 2 para professor): ");
    scanf("%d", &novoUsuario->tipo);

    novoUsuario->qtdEmprestimos = 0; // Inicializa a quantidade de empréstimos

    // Adiciona o usuário a lista
    novoUsuario->prox = lista->inicio;
    lista->inicio = novoUsuario;
    lista->tamanho++;
};

Usuario *buscarUsuario(ListaUsuarios *lista, int id)
{
    Usuario *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->id == id)
            return atual;
        atual = atual->prox;
    }
    return NULL; // Usuário não encontrado
};

void listarUsuarios(ListaUsuarios *lista) {
     printf("Lista de Usuários: ");
    Usuario *atual = lista->inicio;

    while (atual != NULL)
    {
        printf("\nID: %d\nNome: %s\nTipo: %d\nQuantidade de Empréstimos: %d\n",
               atual->id,
               atual->nome,
               atual->tipo,
               atual->qtdEmprestimos);
        atual = atual->prox;
    }
    printf("\nTotal de usuários: %d\n", lista->tamanho);
};



void podeEmprestar(Usuario *usuario) {
    if(usuario->qtdEmprestimos >= 3) {
        printf("Usuário não pode emprestar mais livros. Limite de 3 empréstimos atingido.\n");
    } else {
        printf("Usuário pode emprestar livros. Empréstimos atuais: %d\n", usuario->qtdEmprestimos);
    }
};