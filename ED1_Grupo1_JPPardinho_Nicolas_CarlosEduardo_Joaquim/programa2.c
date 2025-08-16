/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

#include "Pilha.h"

// Função para limpar o buffer de entrada (evita loops infinitos em caso de input inválido)
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void obterValoresLiterais(double valores[]) {
    printf("--- Entrada dos valores das literais (A-J) ---\n");
    for (char c = 'A'; c <= 'J'; c++) {
        // Loop para a literal ATUAL. Só sairá quando uma entrada válida for fornecida.
        while (1) {
            printf("Digite o valor para %c: ", c);

            // Tenta ler um valor double.
            // Se scanf retornar 1, a leitura foi um sucesso.
            if (scanf("%lf", &valores[c - 'A']) == 1) {
                // Limpa o restante da linha no buffer, caso o usuário
                // tenha digitado algo a mais (ex: "12.5 extra").
                limparBufferEntrada();
                break; // Entrada válida, sai do loop e vai para a próxima letra.
            } else {
                // Se a leitura falhar, informa o erro.
                printf("\nERRO: Entrada invalida. Por favor, insira apenas valores numericos.\n");
                // Limpa o buffer para remover a entrada inválida (ex: "texto").
                limparBufferEntrada();
                // O loop continuará, pedindo o valor para a mesma letra novamente.
            }
        }
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

// Nova função para validar os caracteres da expressão
void validarCaractere(char c) {
    // Permite letras (A-J), operadores, parênteses e espaços
    if (!isalpha(c) && !ehOperador(c) && c != '(' && c != ')' && !isspace(c)) {
        printf("\nERRO: A expressao contem um caractere invalido: '%c'.\n", c);
        exit(1);
    }
    // Garante que apenas as literais definidas (A-J) sejam usadas
    if (isalpha(c) && toupper(c) > 'J') {
        printf("\nERRO: Literal '%c' invalida. Use apenas letras de A a J.\n", c);
        exit(1);
    }
}

void infixaParaPosfixa(const char *infixa, char *posfixa){
    Pilha *p = criaPilha();
    int j = 0;

    for (int i = 0; infixa[i] != '\0'; i++){
        char expressao = infixa[i];

        // Valida cada caractere da expressão
        validarCaractere(expressao);

        if (isspace(expressao))
            continue;

        // Converte para maiúscula para tratar A e a da mesma forma
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
            while (!verificaPilhaVazia(p) && *(char *)valorTopo(p) != '('){
                char *op = (char *)desempilhar(p);
                posfixa[j++] = *op;
                free(op);
            }
            if (!verificaPilhaVazia(p)){ // Remove o '(' da pilha
                free(desempilhar(p));
            } else { // Se a pilha estiver vazia, os parênteses não estão balanceados
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
        // Se encontrar um parêntese aqui, a expressão estava desbalanceada
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

double avaliarPosfixa(const char *posfixa, double valores[]){
    Pilha *p = criaPilha();
    double resultado = 0.0;

    for (int i = 0; posfixa[i] != '\0'; i++){
        char expressao = posfixa[i];

        // Valida cada caractere da expressão
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

            // ERRO: Faltam operandos para o operador
            if (valor1P == NULL || valor2P == NULL){
                printf("\nERRO: A expressao posfixa e invalida (faltam operandos para um operador).\n");
                exit(1);
            }

            double valor1 = *valor1P;
            double valor2 = *valor2P;
            free(valor1P);
            free(valor2P);

            // ERRO: Tentativa de divisão por zero
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

    // ERRO: Se a pilha não estiver vazia após a operação final, há operandos em excesso
    if (!verificaPilhaVazia(p) || resultadoFinalP == NULL) {
        printf("\nERRO: A expressao posfixa e invalida (excesso de operandos ou expressao vazia).\n");
        exit(1);
    }
    
    resultado = *resultadoFinalP;
    free(resultadoFinalP);

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

    limparBufferEntrada(); // Limpa o buffer após o scanf do número

    memset(expressaoPosfixa, 0, sizeof(expressaoPosfixa));


    if (escolha == 1){
        printf("\nDigite a expressao infixa: \n");
        fgets(expressaoInfixa, sizeof(expressaoInfixa), stdin);
        expressaoInfixa[strcspn(expressaoInfixa, "\n")] = 0; // Remove a nova linha

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
        expressaoPosfixa[strcspn(expressaoPosfixa, "\n")] = 0; // Remove a nova linha
    }
    else{
        printf("\nERRO: Opcao invalida. Escolha 1 para Infixa ou 2 para Posfixa.\n");
        return 1;
    }

    // 3. Avaliação da expressão posfixa e impressão do resultado
    if (strlen(expressaoPosfixa) > 0){
        double resultado = avaliarPosfixa(expressaoPosfixa, valores);
        printf("\nResultado da expressao: %.2lf\n", resultado);
    }
    else{
        // Este caso agora é mais difícil de acontecer devido às validações, mas é mantido por segurança
        printf("\nNenhuma expressao valida para avaliar.\n");
    }

    return 0;
}