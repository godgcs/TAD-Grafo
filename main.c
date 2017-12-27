//=====================================================
// Arquivo: main.c
//
// Autor: Guilherme Cardoso Silva 0022545
// Data: 27/07/2016
// Disciplina: Programacao II
// Atividade: Trabalho 2
//=====================================================

#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "fila.h"
#include "pilha.h"

int existeVerticeCinza(int* vetorCor, int n);
int existeArestaNaoVisitadaEmEstrela(Grafo g, int* vetorAresta, int Vert);
int primaArestaNaoVisitadaEmEstrela(Grafo g, int* vetorAresta, int Vert);
int ultimoVertice(Grafo g);
int ultimaAresta(Grafo g);
void buscaLargura(Grafo g, int partida);
void buscaProfundidade(Grafo g, int partida);
void coloracaoGulosa(Grafo g, Grafo copia, int k);
int verticeMenorGrau(Grafo g);
int menorCorNoGrau(Grafo g, int Vert, int k, int *vetorCor);

int main(int argc, char *argv[]){
  if(argc !=2){
    printf("Entrada de Dados Invalida\n");
    printf("Para Executar digite ./{prog} {nomeGrafo}\n");
    return(1);
  }
  Grafo g = GGcarregaGrafo(argv[1]);
  printf("*****************************************************************************\n");
  printf("********************************Busca Largura********************************\n");
  printf("*****************************************************************************\n");
  buscaLargura(g,1);
  printf("\n\n*****************************************************************************\n");
  printf("*******************************Busca Profundidade****************************\n");
  printf("*****************************************************************************\n");
  buscaProfundidade(g,1);
  printf("\n\n*****************************************************************************\n");
  printf("********************************Coloração Gulosa*****************************\n");
  printf("*****************************************************************************\n");

  Grafo copia = GGcarregaGrafo(argv[1]);
  coloracaoGulosa(g,copia,6);

  GGdestroiGrafo(g);
  GGdestroiGrafo(copia);
  return(0);
}

void buscaLargura(Grafo g, int partida){
  if(GBexisteIdVertice(g, partida)){
    int i;
    int Vert,Vert2,nVert = ultimoVertice(g);
    int Aresta, nAresta  = ultimaAresta(g);
    int *vetorCor    = (int*)malloc((nVert+1)*sizeof(int));
    int *vetorAresta = (int*)malloc((nAresta+1)*sizeof(int));
    Fila fila = criaFila();
  //TORNA TODOS OS VERTICES BRACOS----------------------------------------------------------------------
    printf("Todos os Vertices estão Brancos\n");
    //branco = 1, cinza = 2, preto = 3;; 0 quer dizer que não é um vertice valido
    for(i=1; i <= nVert; i++){
      vetorCor[i]=0;
    }
    Vert = GVprimeiroVertice(g);
    vetorCor[Vert] = 1;
    while(GVproximoVertice(g, Vert)!=0){
      Vert = GVproximoVertice(g, Vert);
      vetorCor[Vert] = 1;
    }
  //TORNA TODOS AS ARESTAS NÃO VISITADAS----------------------------------------------------------------
    printf("Todos os Vertices estão não Visitadas\n");
    //não visitado = 1, visitado = 2;; 0 quer dizer que não é um vertice valido
    for(i=1; i <= nAresta; i++){
      vetorAresta[i]=0;
    }
    Aresta = GAprimeiraAresta(g);
    vetorAresta[Aresta] = 1;
    while(GAproximaAresta(g,Aresta)!=0){
      Aresta = GAproximaAresta(g,Aresta);
      vetorAresta[Aresta] = 1;
    }
    Vert = partida;
    vetorCor[Vert] = 2;
    printf("Vertice %d ficou Cinza\n",Vert);
    insereFila(fila, Vert);

    while(existeVerticeCinza(vetorCor, nVert)){
      Vert = retiraFila(fila);
      printf("Vertice %d Ativo\n",Vert);
      while(existeArestaNaoVisitadaEmEstrela(g,vetorAresta,Vert)){
        Aresta = primaArestaNaoVisitadaEmEstrela(g,vetorAresta,Vert);
        vetorAresta[Aresta] = 2;
        printf("Aresta %d Visitada\n",Aresta);
        Vert2 = GVvizinho(g,Aresta,Vert);
        if(vetorCor[Vert2] == 1){
          vetorCor[Vert2] = 2;
          printf("Vertice %d ficou Cinza\n",Vert2);
          insereFila(fila,Vert2);
        }
      }
      vetorCor[Vert] = 3;
      printf("Vertice %d ficou Preto\n",Vert);
      printf("Vertice %d Desativado\n",Vert);
    }
    free(vetorCor);
    free(vetorAresta);
    destroiFila(fila);
  }
}

void buscaProfundidade(Grafo g, int partida){
  if(GBexisteIdVertice(g, partida)){
    int i;
    int Vert,Vert2,nVert  = ultimoVertice(g);
    int Aresta, nAresta   = ultimaAresta(g);
    int *vetorCor    = (int*)malloc((nVert+1)*sizeof(int));
    int *vetorAresta = (int*)malloc((nAresta+1)*sizeof(int));
    Pilha pilha = criaPilha();
  //TORNA TODOS OS VERTICES BRACOS----------------------------------------------------------------------
    //branco = 1, cinza = 2, preto = 3;; 0 quer dizer que não é um vertice valido
    for(i=1; i <= nVert; i++){
      vetorCor[i]=0;
    }
    Vert = GVprimeiroVertice(g);
    vetorCor[Vert] = 1;
    while(GVproximoVertice(g, Vert)!=0){
      Vert = GVproximoVertice(g, Vert);
      vetorCor[Vert] = 1;
    }
  //TORNA TODOS AS ARESTAS NÃO VISITADAS----------------------------------------------------------------
    //não visitado = 1, visitado = 2;; 0 quer dizer que não é um vertice valido
    for(i=1; i <= nAresta; i++){
      vetorAresta[i]=0;
    }
    Aresta = GAprimeiraAresta(g);
    vetorAresta[Aresta] = 1;
    while(GAproximaAresta(g,Aresta)!=0){
      Aresta = GAproximaAresta(g,Aresta);
      vetorAresta[Aresta] = 1;
    }
    Vert = partida;
    vetorCor[Vert] = 2;
    printf("Vertice %d ficou Cinza\n",Vert);
    inserePilha(pilha, Vert);

    while(existeVerticeCinza(vetorCor, nVert)){
      Vert = retiraPilha(pilha);
      printf("Vertice %d Ativo\n",Vert);
      while(existeArestaNaoVisitadaEmEstrela(g,vetorAresta,Vert)){
        Aresta = primaArestaNaoVisitadaEmEstrela(g,vetorAresta,Vert);
        vetorAresta[Aresta] = 2;
        printf("Aresta %d Visitada\n",Aresta);
        Vert2 = GVvizinho(g,Aresta,Vert);
        if(vetorCor[Vert2] == 1){
          vetorCor[Vert2] = 2;
          printf("Vertice %d ficou Cinza\n",Vert2);
          inserePilha(pilha,Vert2);
        }
      }
      vetorCor[Vert] = 3;
      printf("Vertice %d ficou Preto\n",Vert);
      printf("Vertice %d Desativado\n",Vert);
    }
    free(vetorCor);
    free(vetorAresta);
    destroiPilha(pilha);
  }
}

void coloracaoGulosa(Grafo g, Grafo copia, int k){
  int Vert, i, nVert = ultimoVertice(g);
  Pilha pilha = criaPilha();
  int *vetorCor = (int*)malloc((nVert+1)*sizeof(int));
  //Define Todos os Vertices como não coloridos
  for(i=1; i <= nVert; i++){
    vetorCor[i]=0;
  }
  //FASE 1 - Define ordem de coloração
  while(GInumeroVertices(copia)){
    Vert = verticeMenorGrau(copia);
    GVdestroiVertice(copia, Vert);
    inserePilha(pilha, Vert);
  }
  // FASE 2 - Colore os Vertices
  printf("\n");
  while(!PilhaVazia(pilha)){
    Vert = retiraPilha(pilha);
    if(GIpegaGrau(g,Vert) > k){
      printf("Não tem Solução\n");
      return;
    }else{
      vetorCor[Vert] = menorCorNoGrau(g, Vert, k, vetorCor);
    }
  }
  Vert = GVprimeiroVertice(g);
  printf("Vertice %d cor = %d\n",Vert,vetorCor[Vert]);
  while(GVproximoVertice(g, Vert)!=0){
    Vert = GVproximoVertice(g, Vert);
    printf("Vertice %d cor = %d\n",Vert,vetorCor[Vert]);
  }
  free(vetorCor);
  destroiPilha(pilha);
}

int existeVerticeCinza(int* vetorCor, int n){
  int i;
  for(i=1; i <= n; i++){
    if(vetorCor[i]==2){
      return(1);
    }
  }
  return(0);
}

int existeArestaNaoVisitadaEmEstrela(Grafo g, int* vetorAresta, int Vert){
  int Aresta = GAprimaSaida(g,Vert);
  if(vetorAresta[Aresta]==1){
    return(1);
  }
  while(GAproxSaida(g,Vert,Aresta)!=0){
    Aresta = GAproxSaida(g,Vert,Aresta);
    if(vetorAresta[Aresta]==1){
      return(1);
    }
  }
  return(0);
}

int primaArestaNaoVisitadaEmEstrela(Grafo g, int* vetorAresta, int Vert){
  int Aresta = GAprimaSaida(g,Vert);
  if(vetorAresta[Aresta]==1){
    return(Aresta);
  }
  while(GAproxSaida(g,Vert,Aresta)!=0){
    Aresta = GAproxSaida(g,Vert,Aresta);
    if(vetorAresta[Aresta]==1){
      return(Aresta);
    }
  }
  return(0);
}

int ultimoVertice(Grafo g){
  int vert = GVprimeiroVertice(g);
  while(GVproximoVertice(g, vert)!=0){
    vert = GVproximoVertice(g, vert);
  }
  return(vert);
}

int ultimaAresta(Grafo g){
  int Aresta = GAprimeiraAresta(g);
  while(GAproximaAresta(g, Aresta)!=0){
    Aresta = GAproximaAresta(g, Aresta);
  }
  return(Aresta);
}

int verticeMenorGrau(Grafo g){
  char c;
  //printf("%d, %d\n",GValfa(g,12),GVomega(g,12));
  int Vert  = GVprimeiroVertice(g);
  int menor = Vert;
  //printf("Menor no momento %d",menor);
  //scanf("%c",&c);
  while(GVproximoVertice(g, Vert)!=0){
    Vert = GVproximoVertice(g, Vert);
    //printf("Grau %d < %d\n",GIpegaGrau(g, Vert),GIpegaGrau(g, menor));
    if(GIpegaGrau(g, Vert) < GIpegaGrau(g, menor)){
      menor = Vert;
    }
    //printf("Menor no momento %d",menor);
    //scanf("%c",&c);
  }
  return(menor);
}

int menorCorNoGrau(Grafo g, int Vert, int k, int *vetorCor){
  int VertGrau, Aresta, i, cor;
  cor = 1;
  for (i=1; i <= k; i++){
    Aresta = GAprimaAresta(g, Vert);
    if (Aresta){
      VertGrau = GVvizinho(g,Aresta,Vert);
      if (vetorCor[VertGrau] == cor){cor=0;}
      while (GAproxAresta(g, Vert, Aresta)!=0){
        Aresta = GAproxAresta(g, Vert, Aresta);
        VertGrau = GVvizinho(g,Aresta,Vert);
        if (vetorCor[VertGrau]==cor){cor=0;}
      }
      if (cor!=0){
        return(cor);
      }
      cor=i;
    }
  }
  return(1);
}
