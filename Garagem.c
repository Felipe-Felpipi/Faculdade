#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Constantes
#define LIMITE_GARAGEM 5
#define TAMANHO_PLACA 8

// Struct com as informações do carro
typedef struct {
    int entradas; // Número de vezes que entrou na garagem
    int saidas;   // Número de vezes que saiu da garagem
    char placa[TAMANHO_PLACA];
} Carro;

// Struct de cada elemento da pilha
typedef struct no {
    Carro carro;
    struct no *proximo;
} No;

// Função para registrar um carro
Carro registrar_carro(char placa[TAMANHO_PLACA]) {
    Carro carro;
    strncpy(carro.placa, placa, TAMANHO_PLACA);
    carro.entradas = 1; // O carro está sendo inserido pela primeira vez
    carro.saidas = 0;
    return carro;
}

// Função para imprimir as informações de um carro
void imprimir_carro(Carro carro) {
    printf("\nPlaca: %s", carro.placa);
}

// Função para adicionar um carro à garagem
No* adicionar_carro(No **topo, char placa[TAMANHO_PLACA]) {
    No *novo = malloc(sizeof(No));
    if (!novo) {
        printf("\nErro ao alocar memória.\n");
        return NULL;
    }

    int n_carros = 0;
    No *aux = *topo;

    // Conta o número de carros na garagem
    while (aux) {
        aux = aux->proximo;
        n_carros++;
    }

    // Verifica se a garagem está cheia
    if (n_carros >= LIMITE_GARAGEM) {
        printf("\nA garagem já atingiu o limite de vagas. Carro %s não entrou.\n", placa);
        free(novo);
        return *topo;
    }

    // Adiciona o novo carro à pilha
    novo->carro = registrar_carro(placa);
    novo->proximo = *topo;
    printf("\nCarro %s entrou na garagem.\n", placa);
    return novo;
}

// Função para remover um carro da garagem
No* remover_carro(No **topo, char placa[TAMANHO_PLACA]) {
    No *remover = NULL;
    No *aux = *topo;

    if (*topo) {
        // Verifica se o carro a ser removido está no topo da pilha
        if (strcmp((*topo)->carro.placa, placa) == 0) {
            remover = *topo;
            *topo = remover->proximo;
            printf("\nCarro %s saiu da garagem.\n", remover->carro.placa);
        } else {
            // Procura o carro na pilha
            while (aux->proximo && strcmp(aux->proximo->carro.placa, placa) != 0) {
                aux = aux->proximo;
            }

            // Remove o carro encontrado
            if (aux->proximo) {
                remover = aux->proximo;
                aux->proximo = remover->proximo;
                printf("\nCarro %s saiu da garagem.\n", remover->carro.placa);
            } else {
                printf("\nCarro %s não encontrado na garagem.\n", placa);
            }
        }
    }

    if (remover) {
        remover->carro.saidas++;
    }

    return remover;
}

// Função para visualizar todos os carros na garagem
void visualizar_garagem(No *topo) {
    while (topo) {
        printf("\n\n==========================");
        imprimir_carro(topo->carro);
        printf("\n==========================");
        topo = topo->proximo;
    }
}

// Função para contar o número de manobras necessárias
void contagem_manobras(No **topo, No *remover) {
    int n_manobras = 0;
    No *aux = *topo;

    while (aux && aux != remover->proximo) {
        aux = aux->proximo;
        n_manobras++;
    }

    printf("\nNúmero de carros que precisaram fazer manobras: %d\n", n_manobras);
}

// Função para liberar toda a pilha
void liberar_pilha(No *topo) {
    No *aux;
    while (topo) {
        aux = topo;
        topo = topo->proximo;
        free(aux);
    }
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    No *remover, *topo = NULL;

    // Lista de movimentos (Entrada e Saída)
    char movimentos[][2][18] = {
        {"E", "JOV4340"}, {"E", "NFB4125"}, {"E", "HTJ8438"}, {"S", "NFB4125"},
        {"E", "MXC8514"}, {"S", "JOV4340"}, {"E", "MPE3615"}, {"E", "MMD9657"},
        {"S", "HTJ8438"}, {"E", "LWP6813"}, {"E", "NAV2363"}, {"S", "LWP6813"},
        {"E", "MYG5410"}, {"S", "MXC8514"}, {"E", "BHB3282"}, {"E", "KIM2792"},
        {"S", "MYG5410"}, {"E", "EGI6357"}
    };

    int n_movimentos = sizeof(movimentos) / sizeof(movimentos[0]);

    for (int i = 0; i < n_movimentos; i++) {
        if (strcmp(movimentos[i][0], "E") == 0) {
            topo = adicionar_carro(&topo, movimentos[i][1]);
        } else if (strcmp(movimentos[i][0], "S") == 0) {
            remover = remover_carro(&topo, movimentos[i][1]);
            if (remover) {
                contagem_manobras(&topo, remover);
                free(remover);
                printf("\n");
            }
        }
    }

    printf("\n\nCarros na garagem:\n");
    visualizar_garagem(topo);

    // Libera a memória alocada para a pilha
    liberar_pilha(topo);

    printf("\n\n\n");
    system("PAUSE");
    return 0;
}
