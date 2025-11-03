#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// -----------------------------------------------------------
// Estrutura de dados
// -----------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// -----------------------------------------------------------
// Protótipos
// -----------------------------------------------------------
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItens(Item mochila[], int numItens);
int buscarSequencial(Item mochila[], int numItens, char nome[], int *comparacoes);
void ordenarVetor(Item mochila[], int numItens);
int buscarBinaria(Item mochila[], int numItens, char nome[], int *comparacoes);

// -----------------------------------------------------------
// Programa principal
// -----------------------------------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int opcao;

    do {
        printf("\n===== MOCHILA (VETOR) =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item (Sequencial)\n");
        printf("5 - Ordenar e Buscar item (Binaria)\n");
        printf("0 - Sair\n");
        printf("============================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4: {
                char nome[30];
                int comp = 0;
                printf("\nNome do item: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                int pos = buscarSequencial(mochila, numItens, nome, &comp);
                if (pos != -1)
                    printf("Item encontrado: %s | Tipo: %s | Qtd: %d\n",
                           mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
                else
                    printf("Item nao encontrado.\n");
                printf("Comparacoes: %d\n", comp);
                break;
            }
            case 5: {
                char nome[30];
                int comp = 0;
                ordenarVetor(mochila, numItens);
                printf("\nNome do item (busca binaria): ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                int pos = buscarBinaria(mochila, numItens, nome, &comp);
                if (pos != -1)
                    printf("Item encontrado: %s | Tipo: %s | Qtd: %d\n",
                           mochila[pos].nome, mochila[pos].tipo, mochila[pos].quantidade);
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

    return 0;
}

// -----------------------------------------------------------
// Funções Vetor
// -----------------------------------------------------------
void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;
    printf("\nNome: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*numItens] = novo;
    (*numItens)++;
    printf("Item inserido!\n");
}

void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *numItens - 1; j++)
                mochila[j] = mochila[j + 1];
            (*numItens)--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item nao encontrado.\n");
}

void listarItens(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    printf("\n=== Itens na mochila (%d/%d) ===\n", numItens, MAX_ITENS);
    for (int i = 0; i < numItens; i++)
        printf("%d) %s | %s | %d\n", i + 1,
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

int buscarSequencial(Item mochila[], int numItens, char nome[], int *comparacoes) {
    for (int i = 0; i < numItens; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void ordenarVetor(Item mochila[], int numItens) {
    for (int i = 0; i < numItens - 1; i++) {
        for (int j = 0; j < numItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
    printf("\nItens ordenados por nome.\n");
}

int buscarBinaria(Item mochila[], int numItens, char nome[], int *comparacoes) {
    int inicio = 0, fim = numItens - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(nome, mochila[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}
