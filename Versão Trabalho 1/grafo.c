//=====================================================
// Arquivo: grafo.c
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

typedef struct dados{
        int Vert1;
        int Vert2;
        int Aresta;
    }*Dados;
struct grafo{
        Dados PGrafo;
        int MaxVertices;
        int MaxArestas;
        int QtdVertices;
        int QtdArestas;
    };

Grafo GGcriaGrafo(int vertice,int aresta){
	if ((vertice>0)&&(aresta>0)){
		Grafo registro	      = (Grafo) malloc(sizeof(struct grafo));
		registro->PGrafo      = (Dados) malloc((aresta+1)*sizeof(struct dados));
		registro->MaxVertices = vertice;
		registro->MaxArestas  = aresta;
		registro->QtdVertices = 0;
		registro->QtdArestas  = 0;
		return (registro);
	}
	return(NULL);
}

Grafo GGdestroiGrafo(Grafo P){
	free(P->PGrafo);   /*Libera primeiro o campo ponteiro e depois o Grafo*/
	free(P);
	return(NULL);
}

int GVcriaVertice(Grafo PGrafo){
	if (PGrafo->QtdVertices < PGrafo->MaxVertices){
		PGrafo->QtdVertices++;    /*O numero do vertice é correspondente a quantidade de vertices*/
		return(PGrafo->QtdVertices);
	}
	return(0);
}

int GAcriaAresta(Grafo PGrafo,int vert1,int vert2){
	if (PGrafo->QtdArestas < PGrafo->MaxArestas  /* verifica se os dados batem para criar aresta*/
      && GBexisteIdVertice(PGrafo,vert1) && GBexisteIdVertice(PGrafo,vert2)){
		PGrafo->QtdArestas++;
		PGrafo->PGrafo[PGrafo->QtdArestas].Vert1  = vert1;
		PGrafo->PGrafo[PGrafo->QtdArestas].Vert2  = vert2;
		PGrafo->PGrafo[PGrafo->QtdArestas].Aresta = PGrafo->QtdArestas;
		return(PGrafo->QtdArestas);
	}
	return(0);
}

int GBexisteIdVertice(Grafo PGrafo,int vert){
	if (vert <= PGrafo->QtdVertices && vert > 0){  /* 1 = True; 0 = False*/
		return(1);
	}
	return(0);
}

int GBexisteIdAresta(Grafo PGrafo,int aresta){
	if (aresta <= PGrafo->QtdArestas && aresta > 0){
		return(1);
	}
	return(0);
}

int GBexisteArestaDir(Grafo PGrafo,int vert1,int vert2){
	int i;
	for (i=1; i <= PGrafo->QtdArestas; i++){  /* Verifico todo o vetor de arestas procurando*/
		if (PGrafo->PGrafo[i].Vert1 == vert1 && PGrafo->PGrafo[i].Vert2 == vert2){
			return(1);
		}
	}
	return(0);
}

int GBexisteAresta(Grafo PGrafo,int vert1,int vert2){
	int i;
	for (i=1; i <= PGrafo->QtdArestas; i++){  /* Procuro no vetor pela aresta em qualquer direcao*/
		if ((PGrafo->PGrafo[i].Vert1 == vert1 && PGrafo->PGrafo[i].Vert2 == vert2)
				|| (PGrafo->PGrafo[i].Vert1 == vert2 && PGrafo->PGrafo[i].Vert2 == vert1)){
			return(1);
		}
	}
	return(0);
}

int GApegaArestaDir(Grafo PGrafo,int vert1,int vert2){
	int i;
	for (i=1; i <= PGrafo->QtdArestas; i++){/* 1 = True; 0 = False*/
		if (PGrafo->PGrafo[i].Vert1 == vert1 && PGrafo->PGrafo[i].Vert2 == vert2){
			return(i);/*Se encontrar automaticamente ele já retorna o valor da aresta que é o indice + 1*/
		}
	}
	return(0);
  /*Aqui eu poderia usar a função GBexisteArestaDir, mas como tenho que retornar a aresta,
  vou percorrer o vetor para pegar o indice da aresta sem ter q rodar o vetor duas vezes*/
}

int GApegaAresta(Grafo PGrafo,int vert1,int vert2){
	int i;
	for (i=1; i <= PGrafo->QtdArestas; i++){
		if ((PGrafo->PGrafo[i].Vert1 == vert1 && PGrafo->PGrafo[i].Vert2 == vert2)
				|| (PGrafo->PGrafo[i].Vert1 == vert2 && PGrafo->PGrafo[i].Vert2 == vert1)){
			return(i);
		}
	}
	return(0);
}

int GVprimeiroVertice(Grafo PGrafo){
	if (PGrafo->QtdVertices>0){
		return(1);
	}
	return(0);
}

int GVproximoVertice(Grafo PGrafo,int vert){
  if (vert != PGrafo->QtdVertices && GBexisteIdVertice(PGrafo,vert)){
    return(vert+1);
	}
	return(0);
}

int GAprimeiraAresta(Grafo PGrafo){
	if (PGrafo->QtdArestas>0){
		return(PGrafo->PGrafo[1].Aresta);
	}
	return(0);
}

int GAproximaAresta(Grafo PGrafo,int aresta){
	if (aresta != PGrafo->QtdArestas && GBexisteIdAresta(PGrafo,aresta)){
		return(aresta+1);
	}
	return(0);
}

int GInumeroVertices(Grafo PGrafo){
	return(PGrafo->QtdVertices);
}

int GInumeroVerticesMax(Grafo PGrafo){
	return(PGrafo->MaxVertices);
}

int GInumeroArestas(Grafo PGrafo){
	return(PGrafo->QtdArestas);
}

int GInumeroArestasMax(Grafo PGrafo){
	return(PGrafo->MaxArestas);
}

Grafo GGcarregaGrafo(char f[]){
	FILE *Arq;
  Arq=fopen(f,"r");
  if(Arq){
    int i,val1,val2;
    Grafo PGrafo;
    fscanf(Arq,"%d %d\n",&val1,&val2);
    PGrafo=GGcriaGrafo(val1,val2);
    for(i=0; i < PGrafo->MaxVertices;i++){
      val1 = GVcriaVertice(PGrafo);
    }
    for (i=0; i < PGrafo->MaxArestas;i++){
      fscanf(Arq,"%d %d\n",&val1,&val2);
      val1 = GAcriaAresta(PGrafo,val1,val2);
    }
    return(PGrafo);
  }else{
    return(NULL);
  }
}

int GBsalvaGrafo(Grafo PGrafo, char f[]){
  if (PGrafo==NULL){
    return(0);
  }else{
    FILE *Arq;
    int i;
    Arq=fopen(f,"w");
    fprintf(Arq,"%d %d\n",PGrafo->QtdVertices,PGrafo->QtdArestas);
    for(i=1; i <= PGrafo->QtdArestas; i++){
      fprintf(Arq,"%d %d\n",PGrafo->PGrafo[i].Vert1,PGrafo->PGrafo[i].Vert2);
    }
    return(1);
  }
}

int GIpegaGrau(Grafo PGrafo,int vert){
	if (!GBexisteIdVertice(PGrafo,vert)){
		return 0;   /*Se vertice não existir sai fora*/
	}else{
		int cont=0,i; /*Verifico todas as arestas e faço um contador para acrescentar no grau*/
		for (i=1; i <= PGrafo->QtdArestas; i++){
			if ((PGrafo->PGrafo[i].Vert1 == vert && PGrafo->PGrafo[i].Vert2 != vert) ||
          (PGrafo->PGrafo[i].Vert1 != vert && PGrafo->PGrafo[i].Vert2 == vert)){
				cont++;
			}else{
        if(PGrafo->PGrafo[i].Vert1 == vert && PGrafo->PGrafo[i].Vert2 == vert){
          cont++;
          cont++;
        }
      }
		}
		return(cont);
	}
}

int GAprimaAresta(Grafo PGrafo,int vert){
	if (!GBexisteIdVertice(PGrafo,vert)){
		return 0;
	}else{
    int i;
    for (i=1; i <= PGrafo->QtdArestas; i++){
			if (PGrafo->PGrafo[i].Vert1 == vert || PGrafo->PGrafo[i].Vert2 == vert){
				return(PGrafo->PGrafo[i].Aresta); /*Na primeira aresta que bater o vert analizado
        ele já retorna como primeiro, pois o vetor está ordenado*/
			}
		}
	}
  return(0);
}

int GAproxAresta(Grafo PGrafo,int vert,int aresta){
	if (!GBexisteIdVertice(PGrafo,vert) || !GBexisteIdAresta(PGrafo,aresta)){
		return (0);
	}else{
		int i;
    for(i=aresta;i <= PGrafo->QtdArestas; i++){
      if((PGrafo->PGrafo[i].Vert1 == vert || PGrafo->PGrafo[i].Vert2 == vert)/*um dos valores tem q ser igual ao vert*/
        && (PGrafo->PGrafo[i].Aresta > PGrafo->PGrafo[aresta-1].Aresta)){/*Aresta maior que a passada ele ja retorna a proxima aresta*/
          return(i);
        }
    }
		return(0);/*Se chegar aqui é por que não existe prox aresta*/
	}
}

int GAprimaEntrada(Grafo PGrafo,int vert){
	if (!GBexisteIdVertice(PGrafo,vert)){
		return(0);
	}else{
		int i;
		for(i=1; i <= PGrafo->QtdArestas; i++){
			if (PGrafo->PGrafo[i].Vert2 == vert){
				return(i);/*retorna a primeira posição de entrada que encontrar*/
			}
		}
	}
	return(0);
}

int GAproxEntrada(Grafo PGrafo,int vert,int aresta){
	if (!GBexisteIdVertice(PGrafo,vert) || !GBexisteIdAresta(PGrafo,aresta) || PGrafo->PGrafo[aresta].Vert2 != vert){
    /*Se a aresta não existir, ou o vertice nao existir, ou a aresta não tiver a entrada como o valor passado sai fora*/
		return (0);
	}else{
		int i;
		for(i=aresta; i <= PGrafo->QtdArestas; i++){
			if (PGrafo->PGrafo[i].Vert1 == vert){
				return(i);
			}
		}
	}
	return(0);
}

int GAprimaSaida(Grafo PGrafo,int vert){
	if (!GBexisteIdVertice(PGrafo,vert)){
		return(0);
	}else{
		int i;
		for (i=1; i <= PGrafo->QtdArestas; i++){
			if (PGrafo->PGrafo[i].Vert1 == vert){
				return(i);/*No primeiro vertice de saida ele já retorna*/
			}
		}
	}
	return(0);
}

int GAproxSaida(Grafo PGrafo,int vert,int aresta){
	if (!GBexisteIdVertice(PGrafo,vert) || !GBexisteIdAresta(PGrafo,aresta)){
		return(0);
	}else{
		int i;
		for(i=aresta; i <= PGrafo->QtdArestas; i++){
			if (PGrafo->PGrafo[i].Vert1 == vert){
				return(i);
			}
		}
	}
	return(0);
}

int GBarestaLaco(Grafo PGrafo,int aresta){
	if (!GBexisteIdAresta(PGrafo,aresta)){
		return(0);
	}else{
		if (PGrafo->PGrafo[aresta].Vert1 == PGrafo->PGrafo[aresta].Vert2){
			return(1);/*retorna 1 somente se entrada e saida forem iguais*/
		}else{
      return(0);
    }
	}
}

int GValfa(Grafo PGrafo,int aresta){
	if (!GBexisteIdAresta(PGrafo,aresta)){
		return(0);
	}else{
		return(PGrafo->PGrafo[aresta].Vert1);
	}
}

int GVomega(Grafo PGrafo,int aresta){
	if (!GBexisteIdAresta(PGrafo,aresta)){
		return(0);
	}else{
		return(PGrafo->PGrafo[aresta].Vert2);
	}
}

int GVvizinho(Grafo PGrafo,int aresta,int vert){
	if (!GBexisteIdAresta(PGrafo,aresta) ||
		(PGrafo->PGrafo[aresta].Vert1 != vert  && PGrafo->PGrafo[aresta].Vert2 != vert)){
		return(0);/*se a aresta nao existir ou o vert nao pertencer a aresta sai fora*/
	}else{
		if (PGrafo->PGrafo[aresta].Vert1 == vert){
			return(PGrafo->PGrafo[aresta].Vert2);/*Se o vert1 for o vert passado retorna o vert2*/
		}else{
			return(PGrafo->PGrafo[aresta].Vert1);/*Se o vert2 for o vert passado retorna o vert1*/
		}
	}
}
