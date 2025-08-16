/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
    --- IMPLEMENTAÇÃO DO PROBLEMA 2 (LÓGICA DE PRECEDÊNCIA CORRIGIDA) ---
*/

#include "Pilha.h"

void obterValoresLiterais(double valores[]){
    printf("--- Entrada dos valores das literais (A-J) ---\n");
    for (char c = 'A'; c <= 'J'; c++){
        printf("Digite o valor para %c: ", c);
        scanf("%lf", &valores[c - 'A']);
    }
}

int obterPrecedencia(char op){
    switch (op){
    case '^':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0; 
    }
}

int ehOperador(char c){
    if (c == '+'|| c == '*'|| c == '/' || c == '-' || c == '^'){
        return 1; // É um operador
    }
    return 0;
}

void infixaParaPosfixa(const char *infixa, char *posfixa){
    Pilha *p = criaPilha();
    int j = 0;

    for (int i = 0; infixa[i] != '\0'; i++){
        char expressao = infixa[i];

        if (isspace(expressao))
            continue;

        if (isalpha(expressao)){
            posfixa[j++] = expressao;
        }
        else if (expressao == '('){
            char *expressaoP = (char *)malloc(sizeof(char));
            *expressaoP = expressao;
            empilhar(p, expressaoP);
        }
        else if (expressao == ')'){
            while (!verificaPilhaVazia(p) && *(char *)valorTopo(p) != '('){
                char *op = (char *)desempilhar(p);
                posfixa[j++] = *op;
                free(op);
            }
            if (!verificaPilhaVazia(p)){
                free(desempilhar(p));
            }
        }
        else if (ehOperador(expressao)){
            while (!verificaPilhaVazia(p) && *(char *)valorTopo(p) != '(' &&
                   (obterPrecedencia(*(char *)valorTopo(p)) > obterPrecedencia(expressao) ||
                    (obterPrecedencia(*(char *)valorTopo(p)) == obterPrecedencia(expressao) && expressao != '^'))){
                char *op = (char *)desempilhar(p);
                posfixa[j++] = *op;
                free(op);
            }
            char *expressaoP = (char *)malloc(sizeof(char));
            *expressaoP = expressao;
            empilhar(p, expressaoP);
        }
    }

    while (!verificaPilhaVazia(p)){
        char *op = (char *)desempilhar(p);
        posfixa[j++] = *op;
        free(op);
    }

    posfixa[j] = '\0';
    destroiPilha(&p);
}

double avaliarPosfixa(const char *posfixa, double valores[]){
    Pilha *p = criaPilha();
    double resultado = 0.0;

    for (int i = 0; posfixa[i] != '\0'; i++){
        char expressao = posfixa[i];

        if (isspace(expressao))
            continue;

        if (isalpha(expressao)){
            double *valorP = (double *)malloc(sizeof(double));
            *valorP = valores[expressao - 'A'];
            empilhar(p, valorP);
        }
        else if (ehOperador(expressao)){
            double *valor2P = (double *)desempilhar(p);
            double *valor1P = (double *)desempilhar(p);

            if (valor1P && valor2P){
                double valor1 = *valor1P;
                double valor2 = *valor2P;
                free(valor1P);
                free(valor2P);

                double *resultadoP = (double *)malloc(sizeof(double));
                switch (expressao){
                case '+':
                    *resultadoP = valor1 + valor2;
                    break;
                case '-':
                    *resultadoP = valor1 - valor2;
                    break;
                case '*':
                    *resultadoP = valor1 * valor2;
                    break;
                case '/':
                    *resultadoP = valor1 / valor2;
                    break;
                case '^':
                    *resultadoP = pow(valor1, valor2);
                    break;
                }
                empilhar(p, resultadoP);
            }
        }
    }

    if (!verificaPilhaVazia(p)){
        double *resultadoFinalP = (double *)desempilhar(p);
        resultado = *resultadoFinalP;
        free(resultadoFinalP);
    }

    destroiPilha(&p);
    return resultado;
}

int main(){
    double valores[10]; // Armazena valores para literais de A a J
    char expressaoInfixa[256];
    char expressaoPosfixa[256];
    int escolha;
    // 1. Entrada dos valores das literais
    obterValoresLiterais(valores);
    // 2. Escolha do formato da expressão
    printf("\nEscolha o formato da expressao:\n");
    printf("1. Expressao Infixa\n");
    printf("2. Expressao Posfixa\n");
    printf("Opcao: ");
    scanf("%d", &escolha);

    while (getchar() != '\n');

    memset(expressaoPosfixa, 0, sizeof(expressaoPosfixa));

    if (escolha == 1){
        printf("\nDigite a expressao infixa: \n");
        fgets(expressaoInfixa, sizeof(expressaoInfixa), stdin);
        expressaoInfixa[strcspn(expressaoInfixa, "\n")] = 0;

        infixaParaPosfixa(expressaoInfixa, expressaoPosfixa);
        printf("\nExpressao convertida para Posfixa: %s\n", expressaoPosfixa);
    }
    else if (escolha == 2){
        printf("\nDigite a expressao posfixa: \n");
        fgets(expressaoPosfixa, sizeof(expressaoPosfixa), stdin);
        expressaoPosfixa[strcspn(expressaoPosfixa, "\n")] = 0;
    }
    else{
        printf("Opcao invalida!\n");
        return 1;
    }
    // 3. Avaliação da expressão posfixa e impressão do resultado
    if (strlen(expressaoPosfixa) > 0){
        double resultado = avaliarPosfixa(expressaoPosfixa, valores);
        printf("\nResultado da avaliacao da expressao: %lf\n", resultado);
    }
    else{
        printf("\nNenhuma expressao valida para avaliar.\n");
    }

    return 0;
}