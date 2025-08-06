/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

#include "Pilha.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função auxiliar para verificar se um caractere é um delimitador de abertura
int ehAbertura(char c)
{
    return c == '(' || c == '[' || c == '{';
}

// Função auxiliar para verificar se um caractere é um delimitador de fechamento
int ehFechamento(char c)
{
    return c == ')' || c == ']' || c == '}';
}

// Função auxiliar para verificar se os delimitadores correspondem
int corresponde(char abertura, char fechamento)
{
    return (abertura == '(' && fechamento == ')') ||
           (abertura == '[' && fechamento == ']') ||
           (abertura == '{' && fechamento == '}');
}

// Problema 1 a) - Verifica apenas o fechamento correto dos delimitadores
int verificaFechamento(char *expressao)
{
    Pilha *p = criaPilha();
    int resultado = 1; // Assume que é válido inicialmente

    for (int i = 0; expressao[i] != '\0'; i++)
    {
        char c = expressao[i];

        if (ehAbertura(c))
        {
            empilhar(p, (Generico)(size_t)c);
        }
        else if (ehFechamento(c))
        {
            if (verificaPilhaVazia(p))
            {
                resultado = 0;
                break;
            }

            char topo = (char)(size_t)desempilhar(p);
            if (!corresponde(topo, c))
            {
                resultado = 0;
                break;
            }
        }
    }

    // Se a pilha não estiver vazia no final, faltaram fechamentos
    if (!verificaPilhaVazia(p))
    {
        resultado = 0;
    }

    destroiPilha(&p);
    return resultado;
}

// Problema 1 b) - Verifica a precedência dos delimitadores
int verificaPrecedencia(char *expressao)
{
    Pilha *p = criaPilha();
    int resultado = 1; // Assume que é válido inicialmente

    for (int i = 0; expressao[i] != '\0'; i++)
    {
        char c = expressao[i];

        if (ehAbertura(c))
        {
            // Verifica a precedência ao empilhar
            if (!verificaPilhaVazia(p))
            {
                char topo = (char)(size_t)valorTopo(p);

                // Verifica a hierarquia: { > [ > (
                if (c == '[' && topo == '{')
                {
                    // OK: [ dentro de {
                }
                else if (c == '(' && (topo == '[' || topo == '{'))
                {
                    // OK: ( dentro de [ ou {
                }
                else if (c != topo && !(c == '{' && (topo == '[' || topo == '(')))
                {
                    // Não pode ter { dentro de [ ou (, etc.
                    resultado = 0;
                    break;
                }
            }
            empilhar(p, (Generico)(size_t)c);
        }
        else if (ehFechamento(c))
        {
            if (verificaPilhaVazia(p))
            {
                resultado = 0;
                break;
            }

            char topo = (char)(size_t)desempilhar(p);
            if (!corresponde(topo, c))
            {
                resultado = 0;
                break;
            }
        }
    }

    // Se a pilha não estiver vazia no final, faltaram fechamentos
    if (!verificaPilhaVazia(p))
    {
        resultado = 0;
    }

    destroiPilha(&p);
    return resultado;
}

// Função para verificar se a expressão contém apenas caracteres válidos
int expressaoValida(char *expressao)
{
    for (int i = 0; expressao[i] != '\0'; i++)
    {
        char c = expressao[i];
        if (!(isalpha(c) && toupper(c) >= 'A' && toupper(c) <= 'J') &&                 // A-J
            !(c == '+' || c == '-' || c == '/' || c == '*' || c == '~') &&             // operadores
            !(c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}') && // delimitadores
            !isspace(c))
        { // espaços são permitidos
            return 0;
        }
    }
    return 1;
}

int main()
{
    char expressao[1000];
    int op;
    
    for(int i=0; i<3; i++) {
        if (i == 4){
            break;
        }
        printf("Digite a expressão matemática (use A-J como variáveis):\n");
        fgets(expressao, sizeof(expressao), stdin);
        expressao[strcspn(expressao, "\n")] = '\0'; // Remove o \n do final

        // Verifica se a expressão contém apenas caracteres válidos
        if (!expressaoValida(expressao))
        {
            printf("Expressão inválida: contém caracteres não permitidos.\n");
            return 1;
        }

        // Verificação a) - apenas fechamento correto
        int validoA = verificaFechamento(expressao);

        // Verificação b) - precedência dos delimitadores
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