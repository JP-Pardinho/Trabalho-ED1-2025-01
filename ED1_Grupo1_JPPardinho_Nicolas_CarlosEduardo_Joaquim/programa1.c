/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

#include "Pilha.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_EXPRESSAO 10000

char expressao[MAX_EXPRESSAO];

// Função para verificar se é um caractere abertura
int abertura(char c){
    if (c == '(' || c == '[' || c == '{'){
        return 1; // É um caractere de abertura
    }
        return 0; // Não é um caractere de abertura
}

// Função para verificar se é um caractere fechamento
int fechamento(char c){
    if (c == ')' || c == ']' || c == '}'){
        return 1; // É um um caractere de fechamento
    }
        return 0; // Não é um caractere de fechamento
}

// Função para verificar se a abertura corresponde com o fechamento
int corresponde(char abertura, char fechamento){
    if (abertura == '(' && fechamento == ')'){
        return 1;
    }
    else if (abertura == '[' && fechamento == ']'){
        return 1;
    }
    else if (abertura == '{' && fechamento == '}'){
        return 1;
    }
    return 0; 
}

//Verifica se está sendo fechado direito
int verificaFechamento(char *expressao)
{
    Pilha *p = criaPilha();
    int resultado = 1; 

    for (int i = 0; expressao[i] != '\0'; i++)
    {
        char c = expressao[i];

        if (abertura(c))
        {
            // Aloca a memória para guardar um char
            char* ponteiroC = (char*) malloc(sizeof(char));
            if (ponteiroC == NULL) {
                printf("Erro de alocacao de memoria!\n");
                exit(1); 
            }
            //Guarda o valor do char na memória
            *ponteiroC = c;

            //Empilha o PONTEIRO para a memória alocada
            empilhar(p, (Generico)ponteiroC); 
        }
        else if (fechamento(c))
        {
            if (verificaPilhaVazia(p))
            {
                resultado = 0;
                break;
            }
            //Desempilha o PONTEIRO
            char* topoP = (char*)desempilhar(p);
            //Pega o VALOR que está no endereço apontado pelo ponteiro
            char topo = *topoP; 
            //LIBERA a memória que foi alocada para aquele char
            free(topoP);

            if (!corresponde(topo, c))
            {
                resultado = 0;
                break;
            }
        }
    }

    //Se a pilha não estiver vazia no final, faltaram fechamentos.
    //limpa a memória de qualquer item que sobrou
    if (!verificaPilhaVazia(p))
    {
        resultado = 0;
        //Laço para limpar a memória restante e evitar vazamento(GPT que fez)
        while(!verificaPilhaVazia(p)) {
            char* restoP = (char*)desempilhar(p);
            free(restoP);
        }
    }

    destroiPilha(&p);
    return resultado;
}

//Verifica a precedência dos delimitadores

int verificaPrecedencia(char *expressao){
    Pilha *p = criaPilha();
    int resultado = 1;

    for (int i = 0; expressao[i] != '\0'; i++){
        char c = expressao[i];

        if (abertura(c)){
            empilhar(p, (Generico)(size_t)c);
        }
        else if (fechamento(c)){
            if (verificaPilhaVazia(p)){
                resultado = 0;
                break;
            }

            char topo = (char)(size_t)desempilhar(p);
            if (!corresponde(topo, c)){
                resultado = 0;
                break;
            }
        }
    }

    if (!verificaPilhaVazia(p))
    {
        resultado = 0;
    }

    destroiPilha(&p);
    return resultado;
}

//Função que verifica se a expressão contém apenas caracteres válidos
int expressaoValida(char *expressao)
{
    for (int i = 0; expressao[i] != '\0'; i++)
    {
        char c = expressao[i];
        if (!(isalpha(c) && toupper(c) >= 'A' && toupper(c) <= 'J') &&                 
            !(c == '+' || c == '-' || c == '/' || c == '*' || c == '^') &&             
            !(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') && 
            !isspace(c))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    //Para inserir mais caracteres basta mudar a variavel global MAX_EXPRESSAO
    int op;

    for (int i = 0; i < 3; i++)
    {
        if (i == 4)
        {
            break;
        }
        printf("Digite a expressão matemática (use A-J como variáveis):\n");
        fgets(expressao, sizeof(expressao), stdin);
        expressao[strcspn(expressao, "\n")] = '\0';

        int contemAlgo = 0;
        for (int j = 0; expressao[j] != '\0'; j++)
        {
            if (!isspace(expressao[j]))
            {
                contemAlgo = 1;
                break;
            }
        }
        if (!contemAlgo)
        {
            printf("Expressão inválida: está vazia ou contém apenas espaços.\n");
            return 1;
        }

        if (!expressaoValida(expressao))
        {
            printf("Expressão inválida: contém caracteres não permitidos.\n");
            return 1;
        }

        int validoA = verificaFechamento(expressao);

        int validoB = verificaPrecedencia(expressao);

        printf("\nResultados da validação:\n");
        printf("a) Fechamento correto: %s\n", validoA ? "VÁLIDO" : "INVÁLIDO");
        printf("b) Precedência correta: %s\n", validoB ? "VÁLIDO" : "INVÁLIDO");

        if (validoA && validoB)
        {
            printf("\nA expressão é totalmente válida para ambos os critérios!\n");
        }
        else if (validoA)
        {
            printf("\nA expressão é válida apenas para o critério a) (fechamento correto).\n");
        }
        else
        {
            printf("\nA expressão é inválida para ambos os critérios.\n");
        }
    }
    return 0;
}