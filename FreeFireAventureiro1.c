#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------
// Estruturas
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// -----------------------------------------------------------
// Protótipos
// -----------------------------------------------------------
void inserirItemLista(No **inicio);
void removerItemLista(No **inicio);
void listarItensLista(No *inicio);
int buscarItemLista(No *inicio, char nome[], int *comparacoes);

// -----------------------------------------------------------
// Programa principal
// -----------------------------------------------------------
int main() {
    No *inicio = NULL;
    int opcao;

    do {
        printf("\n===== MOCHILA (LISTA ENCADEADA) =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (Sequencial)\n");
        printf("0 - Sair\n");
        printf("=====================================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirItemLista(&inicio);
                break;
            case 2:
                removerItemLista(&inicio);
                break;
            case 3:
                listarItensLista(inicio);
                break;
            case 4: {
                char nome[30];
                int comp = 0;
                printf("\nNome do item: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                int achou = buscarItemLista(inicio, nome, &comp);
                if (achou)
                    printf("Item encontrado!\n");
                else
                    printf("Item nao encontrado.\n");
                printf("Comparacoes: %d\n", comp);
                break;
            }
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    // Libera memória
    No *aux;
    while (inicio != NULL) {
        aux = inicio;
        inicio = inicio->proximo;
        free(aux);
    }

    return 0;
}

// -----------------------------------------------------------
// Funções da lista encadeada
// -----------------------------------------------------------
void inserirItemLista(No **inicio) {
    No *novo = (No*)malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocacao!\n");
        return;
    }

    printf("\nNome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *inicio;
    *inicio = novo;
    printf("Item inserido!\n");
}

void removerItemLista(No **inicio) {
    if (*inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *inicio, *anterior = NULL;
    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Item nao encontrado.\n");
        return;
    }

    if (anterior == NULL)
        *inicio = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("Item removido!\n");
}

void listarItensLista(No *inicio) {
    if (inicio == NULL) {
        printf("\nLista vazia!\n");
        return;
    }

    int i = 1;
    printf("\n=== Itens na lista ===\n");
    while (inicio != NULL) {
        printf("%d) %s | %s | %d\n", i++, inicio->dados.nome,
               inicio->dados.tipo, inicio->dados.quantidade);
        inicio = inicio->proximo;
    }
}

int buscarItemLista(No *inicio, char nome[], int *comparacoes) {
    while (inicio != NULL) {
        (*comparacoes)++;
        if (strcmp(inicio->dados.nome, nome) == 0)
            return 1;
        inicio = inicio->proximo;
    }
    return 0;
}