//=====================================================
// Arquivo: caminho.c
//
// Autores: Guilherme Cardoso Silva 0022545
//          Flavia Ribeiro Santos   0022651
// Data: 27/05/2016
// Disciplina: Programacao II
// Atividade: Trabalho1
//=====================================================

#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>

#define INFINITO 99999

void ImprimiCaminho(int*Caminho);
int TodosVisitados(int*Visitados, int QtdVertices);

void Gcaminho(Grafo PGrafo, int *pesos, int inicio, int fim){
  int i,Temp,erro=0;
  int min=INFINITO;                                            /*defini valor minimo como INFINITO para começar o laço*/
  int QtdVertices = GInumeroVertices(PGrafo);                  /*pega qtd de vertices*/
  int *Dist      = (int*) malloc ((QtdVertices+1)*sizeof(int));/*usado para medir a distancia entre os nós*/
  int *Caminho   = (int*) malloc ((QtdVertices+1)*sizeof(int));/*usado para traçar o caminho inverso*/
  int *Resposta  = (int*) malloc ((QtdVertices+1)*sizeof(int));/*Usado no fim do algoritimo para gravar o caminho*/
  int *Visitados = (int*) malloc ((QtdVertices+1)*sizeof(int));/*usado para controlar quais vertices já foram visitados*/
  /*define os valores iniciais de cada vetor*/
  for (i=1; i <= QtdVertices; i++){
    Dist[i]=INFINITO;
    Visitados[i]=0;
    Caminho[i]=0;
  }
  Dist[inicio]=0;                    /*distancia de Inicio começa com zero para ser primeiro valor a contar*/
  while(!TodosVisitados(Visitados, QtdVertices)){
    min=INFINITO;
    for(i=1; i <= QtdVertices; i++){ /*pego o nó com distancia minima que ainda não foi visitado*/
        if (Visitados[i] == 0){
            if (Dist[i] < min){
                min = i;
            }
        }
    }
    if (min==INFINITO && !Visitados[fim]){
      erro=1;
      break;
    }else{
        if(min==INFINITO && Visitados[fim]){
            break;
        }
    }

    Visitados[min]=1;                           /*Marco visitado o minimo localizado*/
    for(i=1; i <= QtdVertices; i++){            /*percorre todos os vertices para alterar as distancias*/
      if (GBexisteArestaDir(PGrafo,min,i)){   /*Verifico se existe a aresta*/
        Temp=GApegaArestaDir(PGrafo,min,i);   /*Se existir pego o indice dela*/
        if (Dist[min]+pesos[Temp] < Dist[i]){
          Dist[i]=Dist[min]+pesos[Temp];
          Caminho[i]=min;
        }
      }
    }
  }
  /*o caminho esta gravado no vetor Caminho*/
  if(erro){
    printf("%d\n",inicio);
  }else{
    i=fim;
    Resposta[0]=1;/*posição 0 controla tamanho do vetor*/
    Resposta[1]=fim;
    while(i!=inicio){ /*i é o A*/
      i=Caminho[i];
      Resposta[0]++;
      Resposta[Resposta[0]]=i;
    }
    ImprimiCaminho(Resposta);
  }
}

int TodosVisitados(int*Visitados, int QtdVertices){
  int i;
  int res=1;
  for(i=1;i <= QtdVertices; i++){
    if(Visitados[i]==0){
      res=0;
    }
  }
  return(res);
}

void ImprimiCaminho(int *Caminho){
  int i;
  for(i=Caminho[0];i > 1;i--){
    printf("%d->",Caminho[i]);
  }
  printf("%d\n",Caminho[i]);
}
