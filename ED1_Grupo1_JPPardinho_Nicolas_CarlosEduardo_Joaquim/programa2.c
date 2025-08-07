/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
    --- IMPLEMENTAÇÃO DO PROBLEMA 2 (LÓGICA DE PRECEDÊNCIA CORRIGIDA) ---
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "Pilha.h"

// Protótipos das funções auxiliares
void obterValoresLiterais(double valores[]);
int obterPrecedencia(char op);
int ehOperador(char c);
void infixaParaPosfixa(const char *infixa, char *posfixa);
double avaliarPosfixa(const char *posfixa, double valores[]);

int main()
{
    double valores[10]; // Armazena valores para literais de A a J
    char expressaoInfixa[256];
    char expressaoPosfixa[256];
    int escolha;

    // Cabeçalho com informações do grupo
    printf("--------------------------------------------------------------------------\n");
    printf("Trabalho Estrutura de dados I / 2025-1\n");
    printf("GRUPO 1: Joao Pedro Pardinho, Nicolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira\n");
    printf("--------------------------------------------------------------------------\n\n");

    // 1. Entrada dos valores das literais
    obterValoresLiterais(valores);

    // 2. Escolha do formato da expressão
    printf("\nEscolha o formato da expressao a ser inserida:\n");
    printf("1. Expressao Infixa\n");
    printf("2. Expressao Posfixa\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    while (getchar() != '\n')
        ;

    memset(expressaoPosfixa, 0, sizeof(expressaoPosfixa));

    if (escolha == 1)
    {
        printf("\nDigite a expressao infixa (com literais de A-J e operadores +, -, *, /, ^): \n");
        fgets(expressaoInfixa, sizeof(expressaoInfixa), stdin);
        expressaoInfixa[strcspn(expressaoInfixa, "\n")] = 0;

        infixaParaPosfixa(expressaoInfixa, expressaoPosfixa);
        printf("\nExpressao convertida para Posfixa: %s\n", expressaoPosfixa);
    }
    else if (escolha == 2)
    {
        printf("\nDigite a expressao posfixa (com literais de A-J e operadores +, -, *, /, ^): \n");
        fgets(expressaoPosfixa, sizeof(expressaoPosfixa), stdin);
        expressaoPosfixa[strcspn(expressaoPosfixa, "\n")] = 0;
    }
    else
    {
        printf("Opcao invalida!\n");
        return 1;
    }

    // 3. Avaliação da expressão posfixa e impressão do resultado
    if (strlen(expressaoPosfixa) > 0)
    {
        double resultado = avaliarPosfixa(expressaoPosfixa, valores);
        printf("\nResultado da avaliacao da expressao: %lf\n", resultado);
    }
    else
    {
        printf("\nNenhuma expressao valida para avaliar.\n");
    }

    return 0;
}

/**
 * @brief Solicita ao usuário que insira os valores para as literais de A a J.
 */
void obterValoresLiterais(double valores[])
{
    printf("--- Entrada dos valores das literais (A-J) ---\n");
    for (char c = 'A'; c <= 'J'; c++)
    {
        printf("Digite o valor para %c: ", c);
        scanf("%lf", &valores[c - 'A']);
    }
}

/**
 * @brief Retorna a precedência de um operador matemático.
 */
int obterPrecedencia(char op)
{
    switch (op)
    {
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0; // Para parênteses
    }
}

/**
 * @brief Verifica se um caractere é um operador válido.
 */
int ehOperador(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

/**
 * @brief Converte uma string de expressão infixa para posfixa com lógica de precedência corrigida.
 */
void infixaParaPosfixa(const char *infixa, char *posfixa)
{
    Pilha *p = criaPilha();
    int j = 0;

    for (int i = 0; infixa[i] != '\0'; i++)
    {
        char token = infixa[i];

        if (isspace(token))
            continue;

        if (isalpha(token))
        {
            posfixa[j++] = token;
        }
        else if (token == '(')
        {
            char *token_ptr = (char *)malloc(sizeof(char));
            *token_ptr = token;
            empilhar(p, token_ptr);
        }
        else if (token == ')')
        {
            while (!verificaPilhaVazia(p) && *(char *)valorTopo(p) != '(')
            {
                char *op = (char *)desempilhar(p);
                posfixa[j++] = *op;
                free(op);
            }
            if (!verificaPilhaVazia(p))
            {
                free(desempilhar(p));
            }
        }
        else if (ehOperador(token))
        {
            // --- LÓGICA DE PRECEDÊNCIA E ASSOCIATIVIDADE CORRIGIDA ---
            // Enquanto a pilha não estiver vazia, o topo não for '(', e
            // a precedência do operador no topo for maior que a do token atual, OU
            // a precedência for igual e o token NÃO for associativo à direita (ou seja, for associativo à esquerda como *, /, +, -)
            while (!verificaPilhaVazia(p) && *(char *)valorTopo(p) != '(' &&
                   (obterPrecedencia(*(char *)valorTopo(p)) > obterPrecedencia(token) ||
                    (obterPrecedencia(*(char *)valorTopo(p)) == obterPrecedencia(token) && token != '^')))
            {
                char *op = (char *)desempilhar(p);
                posfixa[j++] = *op;
                free(op);
            }
            char *token_ptr = (char *)malloc(sizeof(char));
            *token_ptr = token;
            empilhar(p, token_ptr);
        }
    }

    while (!verificaPilhaVazia(p))
    {
        char *op = (char *)desempilhar(p);
        posfixa[j++] = *op;
        free(op);
    }

    posfixa[j] = '\0';
    destroiPilha(&p);
}

/**
 * @brief Avalia uma expressão no formato posfixo.
 */
double avaliarPosfixa(const char *posfixa, double valores[])
{
    Pilha *p = criaPilha();
    double resultado = 0.0;

    for (int i = 0; posfixa[i] != '\0'; i++)
    {
        char token = posfixa[i];

        if (isspace(token))
            continue;

        if (isalpha(token))
        {
            double *valor_ptr = (double *)malloc(sizeof(double));
            *valor_ptr = valores[token - 'A'];
            empilhar(p, valor_ptr);
        }
        else if (ehOperador(token))
        {
            double *val2_ptr = (double *)desempilhar(p);
            double *val1_ptr = (double *)desempilhar(p);

            if (val1_ptr && val2_ptr)
            {
                double val1 = *val1_ptr;
                double val2 = *val2_ptr;
                free(val1_ptr);
                free(val2_ptr);

                double *res_ptr = (double *)malloc(sizeof(double));
                switch (token)
                {
                case '+':
                    *res_ptr = val1 + val2;
                    break;
                case '-':
                    *res_ptr = val1 - val2;
                    break;
                case '*':
                    *res_ptr = val1 * val2;
                    break;
                case '/':
                    *res_ptr = val1 / val2;
                    break;
                case '^':
                    *res_ptr = pow(val1, val2);
                    break;
                }
                empilhar(p, res_ptr);
            }
        }
    }

    if (!verificaPilhaVazia(p))
    {
        double *res_final_ptr = (double *)desempilhar(p);
        resultado = *res_final_ptr;
        free(res_final_ptr);
    }

    destroiPilha(&p);
    return resultado;
}