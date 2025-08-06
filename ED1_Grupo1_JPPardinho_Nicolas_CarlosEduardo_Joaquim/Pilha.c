/*
    Trabalho Estrutura de dados I / 2025-1
    GRUPO 1: João Pedro Pardinho, Nícolas Leal, Joaquim Moizes, Carlos Eduardo de Oliveira
*/

#include "Pilha.h"

Pilha *criaPilha()
{
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    if (p == NULL)
    {
        printf("\nErro de alocação ao criar a pilha (criaPilha)\n");
        exit(1);
    }

    p->topo = NULL;
    p->tamanho = 0;
    return p;
}

// Destroi a pilha, liberando toda a memória
void destroiPilha(Pilha **p)
{
    if (p == NULL || *p == NULL)
        return;

    No *atual = (*p)->topo;
    while (atual != NULL)
    {
        No *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    free(*p);
    *p = NULL;
}

// Empilha um elemento genérico
void empilhar(Pilha *p, Generico elemento)
{
    if (p == NULL)
        return;

    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("\nErro de alocação ao crair o nó (empilhar)\n");
        exit(1);
    }

    novo->dado = elemento;
    novo->proximo = p->topo;
    p->topo = novo;
    p->tamanho++;
}

// Desempilha um elemento (retorna NULL se vazia)
Generico desempilhar(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
        return NULL;

    No *aux = p->topo;
    Generico dado = aux->dado;

    p->topo = aux->proximo;
    p->tamanho--;
    free(aux);

    return dado;
}

// Retorna o elemento do topo sem remover (NULL se vazia)
Generico valorTopo(Pilha *p)
{
    if (p == NULL || p->topo == NULL)
        return NULL;
    return p->topo->dado;
}

// Verifica se a pilha está vazia (0 = false, 1 = true)
<<<<<<< HEAD
int verificaPilhaVazia(Pilha* p) {
    if (p == NULL) return 1;  // Consideramos NULL como vazia
=======
int verificaPilhaVazia(Pilha *p)
{
    if (p == NULL)
        return 1; // Consideramos NULL como vazia
>>>>>>> 08795ea (Programa 1 ok)
    return (p->topo == NULL);
}

// Retorna o tamanho atual da pilha
int tamanhoPilha(Pilha *p)
{
    if (p == NULL)
        return 0;
    return p->tamanho;
}