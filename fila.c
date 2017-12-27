//=====================================================
// Arquivo: fila.c
//
// Autor: Guilherme Cardoso Silva 0022545
// Data: 27/07/2016
// Disciplina: Programacao II
// Atividade: Trabalho 2
//=====================================================

#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

struct nodo{
        int Valor;
        struct nodo* prox;
    };

struct fila{
        struct nodo* Inicio;
        struct nodo* Fim;
    };

typedef struct nodo* NodoFila;

Fila criaFila(void){
  Fila aux   = (Fila) malloc(sizeof(struct fila));
  aux->Inicio = NULL;
  aux->Fim    = NULL;
  return(aux);
}

void insereFila(Fila fila, int v){
  NodoFila aux = (NodoFila) malloc(sizeof(struct nodo));
  aux->Valor   = v;
  aux->prox    = NULL;

  if(!fila->Inicio){
    fila->Inicio = aux;
    fila->Fim    = aux;
  }else{
    fila->Fim->prox = aux;
    fila->Fim       = aux;
  }
}

int retiraFila(Fila fila){
  int val = fila->Inicio->Valor;
  NodoFila aux = fila->Inicio;

  fila->Inicio = aux->prox;
  free(aux);
  aux = NULL;
  return(val);
}

int FilaVazia(Fila fila){
  if(!fila->Inicio){
    return(1);
  }
  return(0);
}

void destroiFila(Fila fila){
  while(!FilaVazia(fila)){
    retiraFila(fila);
  }
  free(fila);
  fila = NULL;
}
