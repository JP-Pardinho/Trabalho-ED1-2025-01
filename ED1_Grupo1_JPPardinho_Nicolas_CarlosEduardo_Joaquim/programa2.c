/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

#include "Pilha.h"

// Limpa o buffer de entrada do teclado.
void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Pede ao usuario os valores para as variaveis de A a J.
void obterValoresLiterais(double valores[]) {
    printf("--- Entrada dos valores das literais (A-J) ---\n");
    for (char c = 'A'; c <= 'J'; c++) {
        while (1) {
            printf("Digite o valor para %c: ", c);
            if (scanf("%lf", &valores[c - 'A']) == 1){
                limparBufferEntrada();
                break;
            } else {
                printf("\nERRO: Entrada invalida. Por favor, insira apenas valores numericos.\n");
                limparBufferEntrada();
            }
        }
    }
}

// Retorna a precedencia do operador.
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

// Verifica se um caractere e um operador valido.
int ehOperador(char c){
    if (c == '+'|| c == '*'|| c == '/' || c == '-' || c == '^'){
        return 1;
    }
    return 0;
}

// Valida se um caractere e permitido. Encerra o programa em caso de erro.
void validarCaractere(char c) {
    if (!isalpha(c) && !ehOperador(c) && c != '(' && c != ')' && !isspace(c)) {
        printf("\nERRO: A expressao contem um caractere invalido: '%c'.\n", c);
        exit(1);
    }
    if (isalpha(c) && toupper(c) > 'J') {
        printf("\nERRO: caractere '%c' invalida. Use apenas letras de A a J.\n", c);
        exit(1);
    }
}

// Converte uma expressao da notacao infixa para a posfixa.
void infixaParaPosfixa(const char *infixa, char *posfixa){
    Pilha *p = criaPilha();
    int j = 0;

    for (int i = 0; infixa[i] != '\0'; i++){
        char expressao = infixa[i];

        validarCaractere(expressao);

        if (isspace(expressao))
            continue;

        char caractereUpper = toupper(expressao);

        if (isalpha(caractereUpper)){
            posfixa[j++] = caractereUpper;
        }
        else if (caractereUpper == '('){
            char *expressaoP = (char *)malloc(sizeof(char));
            *expressaoP = caractereUpper;
            empilhar(p, expressaoP);
        }
        else if (caractereUpper == ')'){
            while (!verificaPilhaVazia(p) && *(char *)valorTopo(p) != '(') {
                char *op = (char *)desempilhar(p);
                posfixa[j++] = *op;
                free(op);
            }
            if (!verificaPilhaVazia(p)){ 
                free(desempilhar(p));
            } else { 
                printf("\nERRO: Expressao com parenteses desbalanceados.\n");
                exit(1);
            }
        }
        else if (ehOperador(caractereUpper)){
            while (!verificaPilhaVazia(p) && *(char *)valorTopo(p) != '(' &&
                   (obterPrecedencia(*(char *)valorTopo(p)) > obterPrecedencia(caractereUpper) ||
                    (obterPrecedencia(*(char *)valorTopo(p)) == obterPrecedencia(caractereUpper) && caractereUpper != '^'))){
                char *op = (char *)desempilhar(p);
                posfixa[j++] = *op;
                free(op);
            }
            char *expressaoP = (char *)malloc(sizeof(char));
            *expressaoP = caractereUpper;
            empilhar(p, expressaoP);
        }
    }

    while (!verificaPilhaVazia(p)){
        char *op = (char *)desempilhar(p);
        if (*op == '(') {
            printf("\nERRO: Expressao com parenteses desbalanceados.\n");
            exit(1);
        }
        posfixa[j++] = *op;
        free(op);
    }

    posfixa[j] = '\0';
    destroiPilha(&p);
}

// Avalia uma expressao posfixa e retorna o resultado numerico.
double avaliarPosfixa(const char *posfixa, double valores[]){
    Pilha *p = criaPilha();
    double resultado = 0.0;

    for (int i = 0; posfixa[i] != '\0'; i++){
        char expressao = posfixa[i];

        validarCaractere(expressao);

        if (isspace(expressao))
            continue;

        char caractereUpper = toupper(expressao);

        if (isalpha(caractereUpper)){
            double *valorP = (double *)malloc(sizeof(double));
            *valorP = valores[caractereUpper - 'A'];
            empilhar(p, valorP);
        }
        else if (ehOperador(caractereUpper)){
            double *valor2P = (double *)desempilhar(p);
            double *valor1P = (double *)desempilhar(p);

            if (valor1P == NULL || valor2P == NULL){
                printf("\nERRO: Faltam operandos para um operador.\n");
                exit(1);
            }

            double valor1 = *valor1P;
            double valor2 = *valor2P;
            free(valor1P);
            free(valor2P);

            if (caractereUpper == '/' && valor2 == 0) {
                printf("\nERRO: Divisao por zero nao permitida.\n");
                exit(1);
            }

            double *resultadoP = (double *)malloc(sizeof(double));
            switch (caractereUpper){
            case '+': *resultadoP = valor1 + valor2; break;
            case '-': *resultadoP = valor1 - valor2; break;
            case '*': *resultadoP = valor1 * valor2; break;
            case '/': *resultadoP = valor1 / valor2; break;
            case '^': *resultadoP = pow(valor1, valor2); break;
            }
            empilhar(p, resultadoP);
        }
    }

    double *resultadoFinalP = (double *)desempilhar(p);

    if (!verificaPilhaVazia(p) || resultadoFinalP == NULL) {
        printf("\nERRO: A expressao posfixa e invalida.\n");
        exit(1);
    }
    
    resultado = *resultadoFinalP;
    free(resultadoFinalP);

    destroiPilha(&p);
    return resultado;
}

int main(){
    double valores[10];
    char expressaoInfixa[256];
    char expressaoPosfixa[256];
    int escolha;

    obterValoresLiterais(valores);
    
    printf("\nEscolha o formato da expressao:\n");
    printf("1. Expressao Infixa\n");
    printf("2. Expressao Posfixa\n");
    while(1){
        printf("\nOpcao: ");
        scanf("%d", &escolha);
        if (escolha == 1 || escolha == 2) { 
            break;
        } else {
            printf("\nERRO: Opcao invalida. Digite 1 ou 2.\n");
            limparBufferEntrada();
        }
    }

    limparBufferEntrada();
    memset(expressaoPosfixa, 0, sizeof(expressaoPosfixa));

    if (escolha == 1){
        printf("\nDigite a expressao infixa: \n");
        fgets(expressaoInfixa, sizeof(expressaoInfixa), stdin);
        expressaoInfixa[strcspn(expressaoInfixa, "\n")] = 0;

        if (strlen(expressaoInfixa) == 0) {
            printf("\nERRO: Nenhuma expressao foi digitada.\n");
            return 1;
        }

        infixaParaPosfixa(expressaoInfixa, expressaoPosfixa);
        printf("\nExpressao convertida para Posfixa: %s\n", expressaoPosfixa);
    }
    else if (escolha == 2){
        printf("\nDigite a expressao posfixa: \n");
        fgets(expressaoPosfixa, sizeof(expressaoPosfixa), stdin);
        expressaoPosfixa[strcspn(expressaoPosfixa, "\n")] = 0; 
    }
    else{
        printf("\nERRO: Opcao invalida. Escolha 1 para Infixa ou 2 para Posfixa.\n");
        return 1;
    }

    if (strlen(expressaoPosfixa) > 0){
        double resultado = avaliarPosfixa(expressaoPosfixa, valores);
        printf("\nResultado da expressao: %.2lf\n", resultado);
    }
    else{
        printf("\nNenhuma expressao valida para avaliar.\n");
    }

    return 0;
}