#include <stdio.h>
#include <string.h>

// Definição da capacidade da mochila
#define CAPACIDADE_MAX 10

// Struct para representar o Loot
typedef struct {
    char nome[30];
    char tipo[20]; // Ex: Arma, Municao, Cura
    int quantidade;
} Item;

int main() {
    Item mochila[CAPACIDADE_MAX];
    int totalItens = 0;
    int opcao;
    int i, j;
    
    // Variáveis auxiliares para busca e remoção
    char nomeBusca[30];
    int encontrado; 

    printf("=== FREE FIRE: GERENCIADOR DE MOCHILA (NIVEL AVENTUREIRO) ===\n");

    do {
        printf("\n--- MENU DE LOOT ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Mochila\n");
        printf("4. Buscar Item (NOVO)\n"); // Nova opção
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer

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
                    
                    totalItens++;
                    printf("Item adicionado com sucesso!\n");
                } else {
                    printf("\n[!] MOCHILA CHEIA! Descarte algo antes.\n");
                }
                break;

            case 2: // REMOVER
                if (totalItens == 0) {
                    printf("\n[!] A mochila esta vazia.\n");
                } else {
                    printf("\nNome do item para remover: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                    encontrado = 0; // Reset da flag
                    for (i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                            encontrado = 1;
                            // Shift para cobrir o buraco no vetor
                            for (j = i; j < totalItens - 1; j++) {
                                mochila[j] = mochila[j + 1];
                            }
                            totalItens--;
                            printf("Item '%s' removido!\n", nomeBusca);
                            break; 
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

            case 4: // BUSCAR (Novidade do Nível Aventureiro)
                if (totalItens == 0) {
                    printf("\n[!] Mochila vazia. Nada para buscar.\n");
                } else {
                    printf("\nDigite o nome do item para buscar: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove \n

                    encontrado = 0; // Flag de controle (0 = não achou, 1 = achou)
                    
                    printf("\n--- RESULTADO DA BUSCA ---\n");
                    // Busca Sequencial
                    for (i = 0; i < totalItens; i++) {
                        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
                            printf("Item Encontrado!\n");
                            printf("Nome: %s\n", mochila[i].nome);
                            printf("Tipo: %s\n", mochila[i].tipo);
                            printf("Quantidade: %d\n", mochila[i].quantidade);
                            encontrado = 1;
                            break; // Para o loop pois já achou
                        }
                    }

                    if (!encontrado) {
                        printf("Ops! O item '%s' nao esta na mochila.\n", nomeBusca);
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