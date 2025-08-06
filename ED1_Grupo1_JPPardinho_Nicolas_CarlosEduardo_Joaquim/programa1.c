/*
    Trabalho Estrutura de dados I / 2025-1 
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

/*
    PERGUNTAR: 
        AS ENTRADAS TEM QUE SER EM ARQUIVO?
        TEM QUE FAZER VERICAÇÃO DOS SINAIS?
*/


#include "Pilha.h"

// Função auxiliar para verificar se um caractere é um delimitador de abertura
int ehAbertura(char c)
{
    if ( c == '(' || c == '[' || c == '{') {
        return 1;
    } else {
        return 0;
    }
}

// Função auxiliar para verificar se um caractere é um delimitador de fechamento
int ehFechamento(char c)
{
    if (c == ')' || c == ']' || c == '}') {
        return 1;
    } else {
        return 0;
    }
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














// Problema 1 a)
int verificaFechamento(Pilha p){
    // CADA TAG DE ABERTURA TEM QUE ESTÁ FECAHDO CORRETAMENTE
}

// Problema 1 b)
int verificaPrecedencia (Pilha p){
    // chamar a verificaFechamento
    // "( )" está contido em "[ ]" e está contido em "{ }"
} 

// PARA UM EXPRESSÃO SER VALIDA TEM QUE ATENDER AS DUAS VERIFICAÇÕES

int main() {
    
    /*
        IDEIA 
        printf("Digite a expressão matematica: ");
        scanf("%s", string);

        for(i=0; i<tamString; i++) {
            if (string[i] == " "){
                
            }
            empilhar(string[i]);
        }

    */

    return 0;
}