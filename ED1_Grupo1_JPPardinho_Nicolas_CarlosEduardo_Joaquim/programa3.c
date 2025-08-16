/*
    Trabalho Estrutura de dados I / 2025-1 
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

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
    
    Pilha* pilha = criaPilha();
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {

            if (planta[i][j] == '.' && !visitado[i][j]) {
                contador++;
                
                visitado[i][j] = 1;
                Posicao* pos = (Posicao*)malloc(sizeof(Posicao));
                pos->linha = i;
                pos->coluna = j;
                empilhar(pilha, pos);
                
                while (!verificaPilhaVazia(pilha)) {
                    Posicao* atual = (Posicao*)desempilhar(pilha);
                    
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
    
    destroiPilha(&pilha);
    
    return contador;
}

int main() {
    int n, m;
    char planta[MAX][MAX];
    
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%s", planta[i]);
    }
    
    int comodos = contarComodos(planta, n, m);
    printf("%d\n", comodos);
    
    return 0;
}