/*
    Trabalho Estrutura de dados I / 2025-1 
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

#ifndef __PILHA_H__
#define __PILHA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef void* Generico;
typedef struct no {
    Generico dado;
    struct no* proximo;
} No;

typedef struct pilha
{
    No *topo;
    int tamanho;
}Pilha;

// Cria um nó generico
No* criaNo(Generico valor);

// Cria uma nova pilha vazia
Pilha* criaPilha();

// Destroi a pilha, liberando toda a memória
void destroiPilha(Pilha** p);

// Empilha um elemento genérico
void empilhar(Pilha* p, Generico elemento);

// Desempilha um elemento (retorna NULL se vazia)
Generico desempilhar(Pilha* p);

// Retorna o elemento do topo sem remover (NULL se vazia)
Generico valorTopo(Pilha* p);

// Verifica se a pilha está vazia
int verificaPilhaVazia(Pilha* p);

// Retorna o tamanho atual da pilha
int tamanhoPilha(Pilha* p);

#endif