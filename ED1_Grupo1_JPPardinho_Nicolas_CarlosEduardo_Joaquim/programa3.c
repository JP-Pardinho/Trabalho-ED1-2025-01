#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

#define MAX 1000

// Estrutura para representar uma posição na matriz
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Função para verificar se uma posição é válida e é um piso
int ehPisoValido(char planta[MAX][MAX], int n, int m, int linha, int coluna, int visitado[MAX][MAX]) {
    return (linha >= 0) && (linha < n) && 
           (coluna >= 0) && (coluna < m) && 
           (planta[linha][coluna] == '.') && 
           (!visitado[linha][coluna]);
}

// Função principal para contar os cômodos
int contarComodos(char planta[MAX][MAX], int n, int m) {
    int visitado[MAX][MAX] = {0};
    int contador = 0;
    
    // Inicializa a pilha
    Pilha* pilha = criaPilha();
    
    // Percorre toda a matriz
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Se encontrou um piso não visitado, é um novo cômodo
            if (planta[i][j] == '.' && !visitado[i][j]) {
                contador++;
                
                // Marca como visitado e empilha
                visitado[i][j] = 1;
                Posicao* pos = (Posicao*)malloc(sizeof(Posicao));
                pos->linha = i;
                pos->coluna = j;
                empilhar(pilha, pos);
                
                // DFS usando pilha
                while (!verificaPilhaVazia(pilha)) {
                    Posicao* atual = (Posicao*)desempilhar(pilha);
                    
                    // Verifica todas as direções possíveis
                    int dx[] = {-1, 1, 0, 0};
                    int dy[] = {0, 0, -1, 1};
                    
                    for (int k = 0; k < 4; k++) {
                        int novaLinha = atual->linha + dx[k];
                        int novaColuna = atual->coluna + dy[k];
                        
                        if (ehPisoValido(planta, n, m, novaLinha, novaColuna, visitado)) {
                            visitado[novaLinha][novaColuna] = 1;
                            Posicao* novaPos = (Posicao*)malloc(sizeof(Posicao));
                            novaPos->linha = novaLinha;
                            novaPos->coluna = novaColuna;
                            empilhar(pilha, novaPos);
                        }
                    }
                    free(atual);
                }
            }
        }
    }
    
    // Libera a memória da pilha
    destroiPilha(&pilha);
    
    return contador;
}

int main() {
    int n, m;
    char planta[MAX][MAX];
    
    // Lê as dimensões da planta
    scanf("%d %d", &n, &m);
    
    // Lê a planta linha por linha
    for (int i = 0; i < n; i++) {
        scanf("%s", planta[i]);
    }
    
    // Conta os cômodos e imprime o resultado
    int comodos = contarComodos(planta, n, m);
    printf("%d\n", comodos);
    
    return 0;
}