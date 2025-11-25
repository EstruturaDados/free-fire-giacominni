#include <stdio.h>
#include <string.h>

// Definição da capacidade da mochila
#define CAPACIDADE_MAX 10

// 1. Struct para representar o Loot
typedef struct {
    char nome[30];
    char tipo[20]; // Ex: Arma, Municao, Cura
    int quantidade;
} Item;

int main() {
    // 2. Vetor estático (Mochila)
    Item mochila[CAPACIDADE_MAX];
    int totalItens = 0; // Controla quantos itens temos atualmente
    int opcao;
    int i, j;
    char nomeBusca[30];
    int encontrado;

    printf("=== FREE FIRE: GERENCIADOR DE MOCHILA (NIVEL NOVATO) ===\n");

    do {
        // Menu Interativo
        printf("\n--- MENU DE LOOT ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Mochila\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer do teclado

        switch(opcao) {
            case 1: // ADICIONAR
                if (totalItens < CAPACIDADE_MAX) {
                    printf("\n>> Adicionando Loot [%d/%d]:\n", totalItens + 1, CAPACIDADE_MAX);
                    
                    printf("Nome do item: ");
                    fgets(mochila[totalItens].nome, 30, stdin);
                    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';

                    printf("Tipo (Arma/Cura/Municao): ");
                    fgets(mochila[totalItens].tipo, 20, stdin);
                    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

                    printf("Quantidade: ");
                    scanf("%d", &mochila[totalItens].quantidade);
                    
                    totalItens++; // Incrementa o contador de itens
                    printf("Item adicionado com sucesso!\n");
                } else {
                    printf("\n[!] MOCHILA CHEIA! Descarte algo antes de pegar mais loot.\n");
                }
                break;

            case 2: // REMOVER
                if (totalItens == 0) {
                    printf("\n[!] A mochila esta vazia.\n");
                } else {
                    printf("\nNome do item para remover: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                    encontrado = 0;
                    for (i = 0; i < totalItens; i++) {
                        // Compara strings (0 significa igual)
                        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                            encontrado = 1;
                            // Remove o item movendo os proximos uma casa para trás
                            for (j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            totalItens--; // Decrementa o contador
                            printf("Item '%s' removido!\n", nomeBusca);
                            break; // Para o loop após remover
                        }
                    }

                    if (!encontrado) {
                        printf("[!] Item nao encontrado na mochila.\n");
                    }
                }
                break;

            case 3: // LISTAR
                printf("\n=== CONTEUDO DA MOCHILA ===\n");
                printf("%-20s | %-15s | %s\n", "Nome", "Tipo", "Qtd");
                printf("----------------------------------------------------\n");
                
                if (totalItens == 0) {
                    printf("Mochila vazia... Procure loot!\n");
                } else {
                    for (i = 0; i < totalItens; i++) {
                        printf("%-20s | %-15s | %d\n", 
                               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
                    }
                }
                break;

            case 0:
                printf("Saindo da ilha...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}