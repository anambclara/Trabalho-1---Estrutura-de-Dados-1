# Sistema de Empréstimo de Livros da Biblioteca

Trabalho Prático I – Estrutura de Dados Linear | Linguagem C

## Descrição

Sistema em C para controle de empréstimos de livros de uma biblioteca. Permite cadastrar livros e usuários, realizar empréstimos, registrar devoluções e gerenciar fila de espera quando um livro está indisponível.

Cada livro possui um único exemplar. Usuário pode ter no máximo 2 livros emprestados. Se o livro estiver emprestado, o usuário entra na **fila de espera**, implementada com **lista circular encadeada**.

## Funcionalidades

- Cadastrar livro (título, autor, código)
- Cadastrar usuário (nome, RA/SIAPE, tipo: estudante ou professor)
- Realizar empréstimo (verifica disponibilidade e limite de 2 livros por usuário)
- Registrar devolução (notifica próximo da fila de espera)
- Listar livros emprestados por usuário
- Exibir fila de espera de um livro

## Estrutura de Dados: Lista Circular

A fila de espera de cada livro é implementada como uma **lista circular encadeada simples**.

### Como funciona

Cada nó da lista armazena o nome e o RA/SIAPE do usuário em espera, além de um ponteiro `prox` para o próximo nó. O último nó não aponta para `NULL` — ele aponta de volta para o **primeiro nó**, formando um ciclo.

A lista mantém um ponteiro chamado `ultimo`, que aponta sempre para o nó inserido mais recentemente. Com isso:

- `ultimo->prox` é sempre o **primeiro** da fila (próximo a ser atendido)
- Inserir no fim: basta atualizar `ultimo` — **O(1)**
- Remover do início: basta avançar `ultimo->prox` — **O(1)**

### Funções implementadas

| Função | O que faz |
|---|---|
| `filaInicializar` | Prepara a fila vazia |
| `filaInserir` | Adiciona usuário no fim da fila |
| `filaRemover` | Remove o primeiro (quando livro é devolvido) |
| `filaExibir` | Lista todos em ordem de espera |
| `filaContem` | Verifica se usuário já está na fila (evita duplicata) |
| `filaDestruir` | Libera toda a memória alocada |

## Autores

- Ana Clara Martins Batista
- Flavia Rosa Santos
- Joyce Adriana Borecki