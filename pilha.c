//=====================================================
// Arquivo: pilha.c
//
// Autor: Guilherme Cardoso Silva 0022545
// Data: 27/07/2016
// Disciplina: Programacao II
// Atividade: Trabalho 2
//=====================================================

#include <stdlib.h>
#include <stdio.h>
#include "pilha.h"

struct nodo{
        int Valor;
        struct nodo* prox;
    };

struct pilha{
        struct nodo* Inicio;
    };

typedef struct nodo *NodoPilha;

Pilha criaPilha(void){
  Pilha aux   = (Pilha) malloc(sizeof(struct pilha));
  aux->Inicio = NULL;
  return(aux);
}

void inserePilha(Pilha pilha, int v){
  NodoPilha aux = (NodoPilha) malloc(sizeof(struct nodo));
  aux->Valor    = v;
  aux->prox     = NULL;

  if(!pilha->Inicio){
    pilha->Inicio = aux;
  }else{
    aux->prox     = pilha->Inicio;
    pilha->Inicio = aux;
  }
}

int retiraPilha(Pilha pilha){
  int val       = pilha->Inicio->Valor;
  NodoPilha aux = pilha->Inicio;

  pilha->Inicio = aux->prox;
  free(aux);
  aux = NULL;
  return(val);
}

int PilhaVazia(Pilha pilha){
  if(!pilha->Inicio){
    return(1);
  }
  return(0);
}

void destroiPilha(Pilha pilha){
  while(!PilhaVazia(pilha)){
    retiraPilha(pilha);
  }
  free(pilha);
  pilha = NULL;
}
