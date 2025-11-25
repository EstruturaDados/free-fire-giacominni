#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Necessario para o tipo bool

#define CAPACIDADE_MAX 10

// 1. Enumeração para os critérios de ordenação
typedef enum {
    ORD_NOME = 1,
    ORD_TIPO = 2,
    ORD_PRIORIDADE = 3
} CriterioOrdenacao;

// 2. Struct atualizada com campo Prioridade
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 (Baixa) a 5 (Alta)
} Item;

// Variaveis Globais (para facilitar o fluxo neste exemplo didatico)
Item mochila[CAPACIDADE_MAX];
int totalItens = 0;
bool ordenadoPorNome = false; // Flag para controlar se podemos usar busca binaria

// --- Funcoes Auxiliares ---

// Funcao de Ordenacao: Insertion Sort
// Retorna o numero de comparacoes realizadas
int ordenarMochila(CriterioOrdenacao criterio) {
    int i, j, comparacoes = 0;
    Item chave;

    for (i = 1; i < totalItens; i++) {
        chave = mochila[i];
        j = i - 1;

        // Logica de comparacao baseada no criterio escolhido
        bool deveMover = false;
        
        // O loop continua enquanto j >= 0 E o elemento atual for maior que a chave
        while (j >= 0) {
            comparacoes++; // Contabiliza a comparacao
            
            if (criterio == ORD_NOME) {
                if (strcmp(mochila[j].nome, chave.nome) > 0) deveMover = true;
                else deveMover = false;
            } 
            else if (criterio == ORD_TIPO) {
                if (strcmp(mochila[j].tipo, chave.tipo) > 0) deveMover = true;
                else deveMover = false;
            } 
            else if (criterio == ORD_PRIORIDADE) {
                // Prioridade: queremos ordem decrescente (5 no topo)? 
                // Ou crescente (1 no topo)? Vamos fazer Crescente (1, 2, 3...)
                if (mochila[j].prioridade > chave.prioridade) deveMover = true;
                else deveMover = false;
            }

            if (deveMover) {
                mochila[j + 1] = mochila[j];
                j = j - 1;
            } else {
                break; // Se nao precisa mover, para o while
            }
        }
        mochila[j + 1] = chave;
    }
    
    // Atualiza a flag de estado
    if (criterio == ORD_NOME) {
        ordenadoPorNome = true;
    } else {
        ordenadoPorNome = false;
    }

    return comparacoes;
}

// Funcao de Busca Binaria (Requer lista ordenada por nome)
int buscaBinaria(char* nomeBusca) {
    int inicio = 0;
    int fim = totalItens - 1;
    int meio;
    int cmp;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        cmp = strcmp(mochila[meio].nome, nomeBusca);

        if (cmp == 0) {
            return meio; // Encontrou, retorna o indice
        } else if (cmp < 0) {
            inicio = meio + 1; // Busca na metade direita
        } else {
            fim = meio - 1; // Busca na metade esquerda
        }
    }
    return -1; // Nao encontrado
}

void listarMochila() {
    printf("\n=== CONTEUDO DA MOCHILA ===\n");
    printf("%-20s | %-10s | %-3s | %s\n", "Nome", "Tipo", "Qtd", "Prioridade");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < totalItens; i++) {
        printf("%-20s | %-10s | %-3d | %d\n", 
               mochila[i].nome, mochila[i].tipo, 
               mochila[i].quantidade, mochila[i].prioridade);
    }
}

// --- Funcao Principal ---
int main() {
    int opcao;
    
    // Variaveis para adicao
    char tempNome[30], tempTipo[20];
    int tempQtd, tempPrio;
    
    // Variaveis para busca e ordenacao
    int indiceEncontrado, qtdComparacoes, escolhaOrd;

    printf("=== FREE FIRE: GERENCIADOR MESTRE ===\n");

    do {
        printf("\n--- MENU MESTRE ---\n");
        printf("1. Adicionar Item\n");
        printf("2. Ordenar Mochila\n");
        printf("3. Busca Binaria (Por Nome)\n");
        printf("4. Listar Mochila\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1: // ADICIONAR
                if (totalItens < CAPACIDADE_MAX) {
                    printf("\n>> Novo Loot:\n");
                    printf("Nome: "); fgets(tempNome, 30, stdin);
                    tempNome[strcspn(tempNome, "\n")] = '\0';

                    printf("Tipo: "); fgets(tempTipo, 20, stdin);
                    tempTipo[strcspn(tempTipo, "\n")] = '\0';

                    printf("Quantidade: "); scanf("%d", &tempQtd);
                    
                    do {
                        printf("Prioridade (1-Baixa a 5-Alta): "); 
                        scanf("%d", &tempPrio);
                    } while(tempPrio < 1 || tempPrio > 5);

                    // Copia para o vetor
                    strcpy(mochila[totalItens].nome, tempNome);
                    strcpy(mochila[totalItens].tipo, tempTipo);
                    mochila[totalItens].quantidade = tempQtd;
                    mochila[totalItens].prioridade = tempPrio;
                    
                    totalItens++;
                    // Ao adicionar um novo item no final, a ordem se perde
                    ordenadoPorNome = false; 
                    printf("Item adicionado! (Ordem da mochila foi resetada)\n");
                } else {
                    printf("Mochila cheia!\n");
                }
                break;

            case 2: // ORDENAR
                if (totalItens < 2) {
                    printf("Itens insuficientes para ordenar.\n");
                } else {
                    printf("\nCriterio de Ordenacao:\n");
                    printf("1. Nome\n2. Tipo\n3. Prioridade\nEscolha: ");
                    scanf("%d", &escolhaOrd);
                    getchar();

                    if (escolhaOrd >= 1 && escolhaOrd <= 3) {
                        qtdComparacoes = ordenarMochila((CriterioOrdenacao)escolhaOrd);
                        printf("Mochila ordenada com sucesso!\n");
                        printf("Performance: %d comparacoes realizadas.\n", qtdComparacoes);
                        listarMochila();
                    } else {
                        printf("Criterio invalido.\n");
                    }
                }
                break;

            case 3: // BUSCA BINARIA
                if (totalItens == 0) {
                    printf("Mochila vazia.\n");
                } 
                else if (!ordenadoPorNome) {
                    printf("\n[ERRO] A mochila PRECISA estar ordenada por NOME para usar Busca Binaria.\n");
                    printf("Va na opcao 2 e ordene por Nome primeiro.\n");
                } 
                else {
                    printf("\nBusca Binaria - Digite o Nome: ");
                    fgets(tempNome, 30, stdin);
                    tempNome[strcspn(tempNome, "\n")] = '\0';

                    indiceEncontrado = buscaBinaria(tempNome);

                    if (indiceEncontrado != -1) {
                        printf("\n[ENCONTRADO] Item no indice %d:\n", indiceEncontrado);
                        printf("Nome: %s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                               mochila[indiceEncontrado].nome,
                               mochila[indiceEncontrado].tipo,
                               mochila[indiceEncontrado].quantidade,
                               mochila[indiceEncontrado].prioridade);
                    } else {
                        printf("Item '%s' nao encontrado.\n", tempNome);
                    }
                }
                break;

            case 4: // LISTAR
                listarMochila();
                break;

            case 0:
                printf("Encerrando sistema...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}