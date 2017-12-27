//=====================================================
// Arquivo: grafo.c
//
// Autor: Guilherme Cardoso Silva 0022545
//        Flavia Ribeiro Santos   0022651
// Data: 27/07/2016
// Disciplina: Programacao II
// Atividade: Trabalho 2
//=====================================================

#include "grafo.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

struct vertice{
        int Vert;
        struct estrela *Estrela;
        struct estrela *UltimaEstrela;
        struct vertice *prox;
        struct vertice *ant;
    };

struct aresta{
        int Aresta;
        struct vertice *Vert1;
        struct vertice *Vert2;
        struct aresta *prox;
        struct aresta *ant;
    };

struct estrela{
        struct aresta *Pertence;
        struct estrela *prox;
        struct estrela *ant;
    };

struct grafo{
        struct vertice *Vertice;
        struct vertice *UltimoVert;
        int QtdVertices;
        int TamUltimoVertice;

        struct aresta *Aresta;
        struct aresta *UltimaAresta;
        int QtdArestas;
        int TamUltimaAresta;
    };

typedef struct vertice *NodoVertice;
typedef struct aresta  *NodoAresta;
typedef struct estrela *NodoEstrela;

//Cabeçalho funções escondidas da TAD
NodoVertice GVNodoVerdice(Grafo PGrafo, int vert);                //retorna o endereço de um vertice
NodoAresta  GANodoAresta(Grafo PGrafo, int aresta);               //retorna o endereço de uma aresta
NodoEstrela GENodoEstrela(NodoVertice vert, NodoAresta aresta);   //retorna o endereço de uma estrela
void GcriaEstrela(Grafo PGrafo, NodoAresta aresta);               //cria estrela a partir de aresta
int GEdestroiEstrela(Grafo PGrafo, NodoAresta aresta);            //destroi estrela apartir de aresta

//Funções
NodoVertice GVNodoVerdice(Grafo PGrafo, int vert){
  NodoVertice aux = PGrafo->Vertice;    //Esta função procura por um vertice e retorna o seu Endereço
  if (aux->Vert == vert){
    return (aux);
  }else{
    while (aux->Vert != vert){
      aux = aux->prox;
      if (aux->Vert == vert){
        return (aux);
      }
    }
  }
  return (NULL);
}

NodoAresta GANodoAresta(Grafo PGrafo, int aresta){
  NodoAresta aux = PGrafo->Aresta;      //Esta função procura por uma aresta e retorna o seu Endereço
  if (aux->Aresta == aresta){
    return (aux);
  }else{
    while (aux->Aresta != aresta){
      aux = aux->prox;
      if (aux->Aresta == aresta){
        return (aux);
      }
    }
  }
  return (NULL);
}

NodoEstrela GENodoEstrela(NodoVertice vert, NodoAresta aresta){
  NodoEstrela aux = vert->Estrela;      //Esta função procura por uma estrela e retorna o seu Endereço
  if (aux->Pertence == aresta){
    return (aux);
  }else{
    while (aux->Pertence != aresta){
      aux = aux->prox;
      if (aux->Pertence == aresta){
        return (aux);
      }
    }
  }
  return (NULL);
}

Grafo GGcriaGrafo(void){
  Grafo aux = (Grafo) malloc(sizeof(struct grafo));               //aloco espaço para o grafo
  if (aux){                                                       //seto valores iniciais para as variaveis do Grafo
    aux->Vertice          = NULL;                                 //Primeiro Vertice recebe NULL
    aux->UltimoVert       = NULL;                                 //Ultimo Vertice recebe NULL
    aux->QtdVertices      = 0;                                    //Quantidade de vertices recebe 0
    aux->TamUltimoVertice = 0;                                    //Tamanho do ultimo vertice recebe 0

    aux->Aresta           = NULL;                                 //Primeira Aresta recebe NULL
    aux->UltimaAresta     = NULL;                                 //Ultima Aresta recebe NULL
    aux->QtdArestas       = 0;                                    //Quantidade de arestas recebe 0
    aux->TamUltimaAresta  = 0;                                    //Tamanho da ultima aresta recebe 0
    return (aux);
  }else{
    return (NULL);
  }
}

Grafo GGdestroiGrafo(Grafo PGrafo){
  NodoVertice aux = PGrafo->Vertice;    //Destruo todos os vertices do Grafo
  while (aux){                          //Consequentimente todas as arestas e todas as estrelas dos vertices serão apagadas juntas
    if (!GVdestroiVertice(PGrafo, aux->Vert));
    aux = PGrafo->Vertice;
  }
  free (PGrafo);
  PGrafo = NULL;
  return (PGrafo);
}

int GVcriaVertice(Grafo PGrafo){
  if (PGrafo->TamUltimoVertice < INT_MAX){                          //Verifica maximo de Vertices
    NodoVertice aux = (NodoVertice) malloc(sizeof(struct vertice)); //Aloca posição para nodo vertice
    if (aux){                                                       //Seto os valores para o vertice
      PGrafo->TamUltimoVertice++;                                   //Tamanho do ultimo vertice cresce 1
      PGrafo->QtdVertices++;                                        //Quantidade de Vertices cresce 1
      aux->Vert          = PGrafo->TamUltimoVertice;                //O vertice recebe o valor do tamanho do ultimo vertice
      aux->Estrela       = NULL;                                    //Estrela do vertice começa zerada
      aux->UltimaEstrela = NULL;                                    //Ultima Estrela do vertice começa zerada
      aux->prox          = NULL;                                    //Proximo vertice sempre será NULL
      aux->ant           = NULL;                                    //Vertice anterior começa como NULL

      if (!PGrafo->Vertice){                                        //Se não existem vertices no grafo
        PGrafo->Vertice    = aux;                                   //O primeiro e o ultimo vertices do grafo serão o que acabou de ser criado
        PGrafo->UltimoVert = aux;
      }else{                                                        //se já existe vertice no grafo
        aux->ant                 = PGrafo->UltimoVert;              //O novo vertice aponta como anterior o ultimo vertice
        PGrafo->UltimoVert->prox = aux;                             //O proximo do ultimo vertice aponta para o novo vertice criado
        PGrafo->UltimoVert       = aux;                             //O ultimo vertice começa a apontar para o vertic criado
      }
      return (PGrafo->UltimoVert->Vert);
    }else{
      return (0);
    }
  }else{
    return (0);
  }
}

void GcriaEstrela(Grafo PGrafo, NodoAresta aresta){
  NodoVertice vert1 = aresta->Vert1;                                //Variavel recebe o vert1 da aresta
  NodoVertice vert2 = aresta->Vert2;                                //Variavel recebe o vert2 da aresta
  NodoEstrela aux1,aux2;                                            //Estrelas a serem criadas
  aux1           = (NodoEstrela) malloc(sizeof(struct estrela));    //Aloco memoria para a 1 estrela
  aux2           = (NodoEstrela) malloc(sizeof(struct estrela));    //Aloco memoria para a 2 estrela

  aux1->Pertence = aresta;                                          //A 1 estrela pertence a aresta passada
  aux1->ant      = NULL;                                            //A estrela anterior a esta começa como valor NULL
  aux1->prox     = NULL;                                            //A proxima estrela começa como valor NULL

  aux2->Pertence = aresta;                                          //A 2 estrela pertence a aresta passada
  aux2->ant      = NULL;                                            //A estrela anterior a esta começa como valor NULL
  aux2->prox     = NULL;                                            //A proxima estrela começa como valor NULL

  if(!vert1->Estrela){                                              //Caso com 0 estrela no vertice
    vert1->Estrela       = aux1;                                    //Primeira e ultima apontam para a estrela criada
    vert1->UltimaEstrela = aux1;
  }else{                                                            //Se tem alguma estrela
    vert1->UltimaEstrela->prox = aux1;                              //O ultimo Nodo começa a apontar para o novo criado
    aux1->ant                  = vert1->UltimaEstrela;              //O nodo criado .ant começa a apontar para o ultimo
    vert1->UltimaEstrela       = aux1;                              //O novo nodo passa a ser o ultimo nodo
  }
  if(!GBarestaLaco(PGrafo, aresta->Aresta)){                        //caso a aresta não seja um laço será realizado o mesmo processo para o vert 2
    if(!vert2->Estrela){
      vert2->Estrela       = aux2;
      vert2->UltimaEstrela = aux2;
    }else{
      vert2->UltimaEstrela->prox = aux2;
      aux2->ant                  = vert2->UltimaEstrela;
      vert2->UltimaEstrela       = aux2;
    }
  }
}

int GAcriaAresta(Grafo PGrafo, int vert1, int vert2){
  if (PGrafo->TamUltimaAresta < INT_MAX && GBexisteIdVertice(PGrafo,vert1) && GBexisteIdVertice(PGrafo,vert2)){ //Verifica tamanho max e se os vertices existem
    NodoAresta aux = (NodoAresta) malloc(sizeof(struct aresta));      //Aloco memoria para o novo nodo
    if (aux){
      PGrafo->TamUltimaAresta++;                                      //Aumento Tam de ultima aresta
      PGrafo->QtdArestas++;                                           //Aumento quantidade de Arestas
      aux->Aresta = PGrafo->TamUltimaAresta;                          //O indice da aresta recebe o ultimo tamanho
      aux->Vert1  = GVNodoVerdice(PGrafo, vert1);                     //Vert1 da aresta aponta para o endereço do vert1
      aux->Vert2  = GVNodoVerdice(PGrafo, vert2);                     //Vert2 da aresta aponta para o endereço do vert1
      aux->ant    = NULL;                                             //Ponteiro anterior aponta para NULL
      aux->prox   = NULL;                                             //Ponteiro proximo aponta para NULL

      if (!PGrafo->Aresta){                                           //Se não existir arestas no Grafo
        PGrafo->Aresta       = aux;                                   //Inicio e fim de arestas apontam para o nodo
        PGrafo->UltimaAresta = aux;
      }else{                                                          //se já existe aresta no grafo
        aux->ant                   = PGrafo->UltimaAresta;            //O P ant do nodo aponta para o ultimo
        PGrafo->UltimaAresta->prox = aux;                             //P proximo do ultimo aponta para o novo nodo
        PGrafo->UltimaAresta       = aux;                             //o novo nodo passa a ser o ultimo
      }

      GcriaEstrela(PGrafo, PGrafo->UltimaAresta);                     //Cria a estrela correspondente a Aresta
      return (PGrafo->UltimaAresta->Aresta);
    }else{
      return (0);
    }
  }else{
    return (0);
  }
}

int GVdestroiVertice(Grafo PGrafo, int vert){
  if (GBexisteIdVertice(PGrafo, vert)){
    NodoVertice Vert         = GVNodoVerdice(PGrafo, vert);
    NodoEstrela Estrela      = Vert->Estrela;
    NodoVertice VertAnterior = Vert->ant;
    NodoVertice VertProximo  = Vert->prox;

    if (PGrafo->QtdVertices == 1){                                  //Se existe apenas 1 vertice
      if (!Estrela){                                                //Caso vertice sem estrela libero direto
        free(Vert);
        Vert = NULL;
      }else{                                                        //Caso o vertice tenha estrela
        while (Estrela){                                            //Liberar todas as arestas que contém este vertice
          if (!GAdestroiAresta(PGrafo, Estrela->Pertence->Aresta)){ //quando se libera uma aresta a função já libera a estrela correspondente
            Estrela = Vert->Estrela;
          }
        }
        free (Vert);
        Vert = NULL;
      }
      PGrafo->Vertice    = NULL;
      PGrafo->UltimoVert = NULL;
      PGrafo->QtdVertices--;
      return (0);
    }else{
      if (GVNodoVerdice(PGrafo, GVprimeiroVertice(PGrafo)) == Vert){ //Caso sejá o primeiro Vertice
        VertProximo->ant = NULL;
        PGrafo->Vertice  = VertProximo;
        if (!Estrela){
          free(Vert);
          Vert = NULL;
        }else{
          while (Estrela){
            if (!GAdestroiAresta(PGrafo, Estrela->Pertence->Aresta)){
              Estrela = Vert->Estrela;
            }
          }
          free (Vert);
          Vert = NULL;
        }
        PGrafo->QtdVertices--;
        return (0);
      }else{
        if (!VertProximo){                                           //Caso seja o ultimo Vertice
          VertAnterior->prox = NULL;
          PGrafo->UltimoVert = VertAnterior;
          if (!Estrela){
            free (Vert);
            Vert = NULL;
          }else{
            while (Estrela){
              if (!GAdestroiAresta(PGrafo, Estrela->Pertence->Aresta)){
                Estrela = Vert->Estrela;
              }
            }
            free (Vert);
            Vert = NULL;
          }
          PGrafo->QtdVertices--;
          return (0);
        }else{                                                      //Casos restantes, onde o vertice está no meio de dois outros
          VertAnterior->prox = VertProximo;
          VertProximo->ant   = VertAnterior;
          if (!Estrela){
            free (Vert);
            Vert = NULL;
          }else{
            while (Estrela){
              if (!GAdestroiAresta(PGrafo, Estrela->Pertence->Aresta)){
                Estrela = Vert->Estrela;
              }
            }
            free (Vert);
            Vert = NULL;
          }
          PGrafo->QtdVertices--;
          return (0);
        }
      }
    }
  }else{
    return(1);
  }
}

int GEdestroiEstrela(Grafo PGrafo, NodoAresta aresta){
  NodoVertice Vert1    = aresta->Vert1;
  NodoVertice Vert2    = aresta->Vert2;
  NodoEstrela Estrela1 = GENodoEstrela(Vert1, aresta);
  NodoEstrela Estrela2 = GENodoEstrela(Vert2, aresta);

  if (Vert1->Estrela == Vert1->UltimaEstrela){//Caso com apenas uma estrela no vertice
    free (Estrela1);
    Vert1->Estrela       = NULL;
    Vert1->UltimaEstrela = NULL;
  }else{                                      //Caso com a estrela sendo a primeira do vertice
    if (Vert1->Estrela == Estrela1){
      Estrela1->ant  = NULL;
      Vert1->Estrela = Estrela1->prox;
      free (Estrela1);
    }else{                                    //Caso que é a ultima estrela do vertice
      if (!Estrela1->prox){
        Estrela1->ant->prox  = NULL;
        Vert1->UltimaEstrela = Estrela1->ant;
        free (Estrela1);
      }else{                                  //Casos restantes em que a estrela esta no meio de outras duas
        NodoEstrela Estrela1Ant  = Estrela1->ant;
        NodoEstrela Estrela1Prox = Estrela1->prox;
        Estrela1Ant->prox = Estrela1Prox;
        Estrela1Prox->ant = Estrela1Ant;
        free (Estrela1);
      }
    }
  }
  if (!GBarestaLaco(PGrafo, aresta->Aresta)){
    if (Vert2->Estrela == Vert2->UltimaEstrela){
      free (Estrela2);
      Vert2->Estrela       = NULL;
      Vert2->UltimaEstrela = NULL;
    }else{
      if (Vert2->Estrela == Estrela2){
        Estrela2->ant  = NULL;
        Vert2->Estrela = Estrela2->prox;
        free (Estrela2);
      }else{
        if(!Estrela2->prox){
          Estrela2->ant->prox = NULL;
          Vert2->UltimaEstrela = Estrela2->ant;
          free (Estrela2);
        }else{
          NodoEstrela Estrela2Ant  = Estrela2->ant;
          NodoEstrela Estrela2Prox = Estrela2->prox;
          Estrela2Ant->prox = Estrela2Prox;
          Estrela2Prox->ant = Estrela2Ant;
          free (Estrela2);
        }
      }
    }
  }
  return (1);
}

int GAdestroiAresta(Grafo PGrafo, int aresta){
  if (GBexisteIdAresta(PGrafo, aresta)){
    NodoAresta Aresta     = GANodoAresta(PGrafo, aresta);
    NodoAresta ArestaAnt  = Aresta->ant;
    NodoAresta ArestaProx = Aresta->prox;
    if (PGrafo->QtdArestas == 1){                                    //Caso com uma unica aresta
      if (GEdestroiEstrela(PGrafo, Aresta)){                         //Destruo a estrela da aresta correspondente
        free (Aresta);
        PGrafo->Aresta       = NULL;
        PGrafo->UltimaAresta = NULL;
        PGrafo->QtdArestas--;
        return (0);
      }
    }else{
      if (GANodoAresta(PGrafo, GAprimeiraAresta(PGrafo)) == Aresta){ //Caso com a aresta sendo a primeira do grafo
        if (GEdestroiEstrela(PGrafo, Aresta)){                       //Destruo a estrela da aresta correspondente
          ArestaProx->ant = NULL;
          PGrafo->Aresta  = ArestaProx;
          free (Aresta);
          PGrafo->QtdArestas--;
          return (0);
        }
      }else{
        if(!ArestaProx){                                            //Caso em que é a ultima aresta do grafo
          if (GEdestroiEstrela(PGrafo, Aresta)){                    //Destruo a estrela da aresta correspondente
            ArestaAnt->prox      = NULL;
            PGrafo->UltimaAresta = ArestaAnt;
            free (Aresta);
            PGrafo->QtdArestas--;
            return (0);
          }
        }else{                                                      //Casos restantes em que a aresta esta entre outras duas
          if (GEdestroiEstrela(PGrafo, Aresta)){                    //Destruo a estrela da aresta correspondente
            ArestaAnt->prox = ArestaProx;
            ArestaProx->ant = ArestaAnt;
            free (Aresta);
            PGrafo->QtdArestas--;
            return (0);
          }
        }
      }
    }
  }
  return(1);
}

int GBexisteIdVertice(Grafo PGrafo,int vert){
  NodoVertice aux = PGrafo->Vertice;    //Procuro em todas os vertices pelo Indice passado
  while (aux){
    if (aux->Vert == vert){
      return (1);
    }
    aux = aux->prox;
  }
  return (0);
}

int GBexisteIdAresta(Grafo PGrafo,int aresta){
  NodoAresta aux = PGrafo->Aresta;     //Procuro em todas os vertices pelo Indice passado
  while (aux){
    if (aux->Aresta == aresta){
      return (1);
    }
    aux = aux->prox;
  }
  return (0);
}

int GBexisteArestaDir(Grafo PGrafo, int vert1, int vert2){
  if (GBexisteIdVertice(PGrafo, vert1) && GBexisteIdVertice(PGrafo, vert2)){//Verifico se existem os vertices
    NodoAresta Aresta = PGrafo->Aresta;                                     //Percorro todas as arestas buscando por uma que bate com os 2 vertices
    if (Aresta){
      NodoVertice Vert1 = GVNodoVerdice(PGrafo, vert1);
      NodoVertice Vert2 = GVNodoVerdice(PGrafo, vert2);
      while (Aresta){
        if (Vert1 == Aresta->Vert1 && Vert2 == Aresta->Vert2){              //Como é direcionada tem q ser vert1 para o vert2
          return (1);
        }
        Aresta = Aresta->prox;
      }
      return (0);
    }
  }
  return (0);
}

int GBexisteAresta(Grafo PGrafo, int vert1, int vert2){
  if (GBexisteIdVertice(PGrafo, vert1) && GBexisteIdVertice(PGrafo, vert2)){//Verifico se os vertices existem
    NodoAresta aux  = PGrafo->Aresta;                                       //Percorro todas as arestas buscando por uma que bate com os 2 vertices
    if (aux){
      NodoVertice aux1 = GVNodoVerdice(PGrafo, vert1);
      NodoVertice aux2 = GVNodoVerdice(PGrafo, vert2);
      while (aux){                                                          //Esta não é direcionada então não importa se a direçao da aresta
        if ((aux1 == aux->Vert1 && aux2 == aux->Vert2) || (aux2 == aux->Vert1 && aux1 == aux->Vert2)){
          return (1);
        }
        aux = aux->prox;
      }
      return (0);
    }
  }
  return (0);
}

int GApegaArestaDir(Grafo PGrafo, int vert1, int vert2){
  if (GBexisteIdVertice(PGrafo, vert1) && GBexisteIdVertice(PGrafo, vert2)){//Verifico se os vertices existem
    NodoAresta aresta  = PGrafo->Aresta;                                    //Percorro todas as arestas buscando por uma que bate com os 2 vertices
    if (aresta){
      NodoVertice Vert1 = GVNodoVerdice(PGrafo, vert1);
      NodoVertice Vert2 = GVNodoVerdice(PGrafo, vert2);
      while (aresta){
        if (Vert1 == aresta->Vert1 && Vert2 == aresta->Vert2){              //Se a aresta direcionada coincidir com os vertices retorno seu indice
          return (aresta->Aresta);
        }
        aresta = aresta->prox;
      }
      return (0);
    }
  }
  return (0);
}

int GApegaAresta(Grafo PGrafo, int vert1, int vert2){
  if (GBexisteIdVertice(PGrafo, vert1) && GBexisteIdVertice(PGrafo, vert2)){//Verifico se os vertices existem
    NodoAresta aresta  = PGrafo->Aresta;                                    //Percorro todas as arestas buscando por uma que bate com os 2 vertices
    if (aresta){
      NodoVertice Vert1 = GVNodoVerdice(PGrafo, vert1);
      NodoVertice Vert2 = GVNodoVerdice(PGrafo, vert2);
      while (aresta){
        if ((Vert1 == aresta->Vert1 && Vert2 == aresta->Vert2) || (Vert2 == aresta->Vert1 && Vert1 == aresta->Vert2)){
          return (aresta->Aresta);                                          //Se a nao aresta direcionada coincidir com os vertices retorno seu indice
        }
        aresta = aresta->prox;
      }
      return (0);
    }
  }
  return (0);
}

int GVprimeiroVertice(Grafo PGrafo){
  if (PGrafo->Vertice){
    return (PGrafo->Vertice->Vert);
  }
  return (0);
}

int GVproximoVertice(Grafo PGrafo, int vert){
  if (GBexisteIdVertice(PGrafo, vert)){
    NodoVertice aux = GVNodoVerdice(PGrafo, vert);
    if (aux->prox){
      return (aux->prox->Vert);
    }
  }
  return (0);
}

int GAprimeiraAresta(Grafo PGrafo){
  if (PGrafo->Aresta){
    return (PGrafo->Aresta->Aresta);
  }
  return (0);
}

int GAproximaAresta(Grafo PGrafo, int aresta){
  if (GBexisteIdAresta(PGrafo, aresta)){
    NodoAresta aux = GANodoAresta(PGrafo, aresta);
    if (aux->prox){
      return (aux->prox->Aresta);
    }
  }
  return (0);
}

int GInumeroVertices(Grafo PGrafo){
  return (PGrafo->QtdVertices);
}

int GInumeroVerticesMax(Grafo PGrafo){
  return (INT_MAX);
}

int GInumeroArestas(Grafo PGrafo){
  return (PGrafo->QtdArestas);
}

int GInumeroArestasMax(Grafo PGrafo){
  return (INT_MAX);
}

Grafo GGcarregaGrafo(char f[]){
  FILE *Arq;
  int i, QtdVertices, QtdArestas, TamUltimaAresta, TamUltimoVertice, val1, val2, val3, temp;
  Arq = fopen(f, "r");                                              //Abro arquivo para leitura
  if (Arq){
    Grafo PGrafo = GGcriaGrafo();

    fscanf(Arq,"%d %d\n", &QtdVertices, &QtdArestas);             //Leio a quantidade de vertice e arestas do vertice, estas variaveis controlaram um for para ler as proximas linhas
    fscanf(Arq,"%d %d\n", &TamUltimoVertice, &TamUltimaAresta);   //Leio as sementes de vertice e arestas do grafo

    for (i=0; i < QtdVertices; i++){
      fscanf(Arq,"%d\n", &val1);                                  //Leio cada vertice
      temp = GVcriaVertice(PGrafo);                               //Cria o vertice
      while (val1 != temp){                                       //Se o vertice criado não é igual ao vertice lido significa que ele foi apagado anteriormente
        temp = GVdestroiVertice(PGrafo, temp);                    //Então apago o vertice e crio outro e faço a mesma verificação até que seja o vertice
        temp = GVcriaVertice(PGrafo);
        if (!temp){                                               //se o valor de temp é 0 então quer dizer que ouve erro na criação de algum vertice
          GGdestroiGrafo(PGrafo);
          return (NULL);
        }
      }
    }
    while (PGrafo->TamUltimoVertice != TamUltimoVertice){         //Caso a semente ao criar os vertices não seja a mesma lida é necessario criar mais para completar
      temp = GVdestroiVertice(PGrafo, temp);
      temp = GVcriaVertice(PGrafo);
      if (!temp){                                               //se o valor de temp é 0 então quer dizer que ouve erro na criação de algum vertice
        GGdestroiGrafo(PGrafo);
        return (NULL);
      }
    }

    for (i=0; i < QtdArestas; i++){
      fscanf(Arq,"%d %d %d\n", &val1, &val2, &val3);              //Leio cada aresta
      temp = GAcriaAresta(PGrafo,val2,val3);                      //Crio a aresta
      while (val1 != temp){                                       //realizo a mesma verificação dos vertices caso não coincida apago e crio novamente
        temp = GAdestroiAresta(PGrafo, temp);
        temp = GAcriaAresta(PGrafo,val2,val3);
        if (!temp){                                               //se o valor de temp é 0 então quer dizer que ouve erro na criação de alguma aresta
          GGdestroiGrafo(PGrafo);
          return (NULL);
        }
      }
    }
    while (PGrafo->TamUltimaAresta != TamUltimaAresta){           //Caso a semente ao criar as arestas não seja a mesma lida é necessario criar mais para completar
      temp = GVdestroiVertice(PGrafo, temp);
      temp = GVcriaVertice(PGrafo);
      if (!temp){                                               //se o valor de temp é 0 então quer dizer que ouve erro na criação de alguma aresta
        GGdestroiGrafo(PGrafo);
        return (NULL);
      }
    }

    fclose(Arq);
    return (PGrafo);
  }else{
    return (NULL);
  }
}

int GBsalvaGrafo(Grafo PGrafo, char f[]){
  if (PGrafo){
    FILE *Arq;
    Arq = fopen(f,"w");
    if (Arq){
      fprintf(Arq,"%d %d\n",PGrafo->QtdVertices,PGrafo->QtdArestas);            //Escrevo a quantidade de vertices e arestas
      fprintf(Arq,"%d %d\n",PGrafo->TamUltimoVertice,PGrafo->TamUltimaAresta);  //Escrevo a semente de vertices e arestas
      NodoVertice Vert = PGrafo->Vertice;
      while (Vert){                                                             //For escrevendo cada vertice
        fprintf(Arq,"%d\n",Vert->Vert);
        Vert = Vert->prox;
      }
      NodoAresta Aresta = PGrafo->Aresta;
      while (Aresta){                                                           //For escrevendo cada aresta
        fprintf(Arq,"%d %d %d\n",Aresta->Aresta, Aresta->Vert1->Vert, Aresta->Vert2->Vert);
        Aresta = Aresta->prox;
      }
      return (1);
    }else{
      return (0);
    }
  }else{
    return (0);
  }
}

int GIpegaGrau(Grafo PGrafo, int vert){
  if(GBexisteIdVertice(PGrafo, vert)){
    int cont = 0;
    NodoVertice Vert    = GVNodoVerdice(PGrafo, vert);        //Pego endereço do vertice
    NodoEstrela Estrela = Vert->Estrela;                      //Percirro toda a sua estrela contando +1
    while (Estrela){
      cont++;
      if (GBarestaLaco(PGrafo, Estrela->Pertence->Aresta)){   //Se for um laço eu conto +1 novamente
        cont++;
      }
      Estrela = Estrela->prox;
    }
    return (cont);
  }else{
    return (0);
  }
}

int GAprimaAresta(Grafo PGrafo, int vert){
  if (GBexisteIdVertice(PGrafo, vert)){
    NodoVertice aux = GVNodoVerdice(PGrafo, vert);    //Verifica se o vertice existe
    if (aux){
      if(aux->Estrela){
        return (aux->Estrela->Pertence->Aresta);        //se existir estrela no vertice, retorno a aresta a que ele pertence
      }else{
        return (0);
      }
    }else{
      return (0);
    }
  }else{
    return (0);
  }
}

int GAproxAresta(Grafo PGrafo, int vert, int aresta){
  if (GBexisteIdAresta(PGrafo, aresta) && GBexisteIdVertice(PGrafo, vert)){
    NodoAresta Aresta   = GANodoAresta(PGrafo, aresta);   //Pego endereço da aresta
    NodoVertice Vert    = GVNodoVerdice(PGrafo, vert);    //Pego endereço do vertice
    NodoEstrela Estrela = Vert->Estrela;                  //Pego endereço da primeira estrela do vertice
    while (Estrela){                                      //percorro todas as estrelas
      if (Estrela->Pertence->Aresta > Aresta->Aresta){    //procurando por uma que pertença a uma aresta maior que a passada
        return (Estrela->Pertence->Aresta);
      }
      Estrela = Estrela->prox;
    }
    return (0);
  }else{
    return (0);
  }
}

int GAprimaEntrada(Grafo PGrafo, int vert){
  if (GBexisteIdVertice(PGrafo, vert)){
    NodoVertice Vert    = GVNodoVerdice(PGrafo, vert);    //Pego endereço do vertice
    NodoEstrela Estrela = Vert->Estrela;                  //Pego endereço da primeira aresta
    while (Estrela){                                      //Percorro todas as estrelas até encontrar a primeira entrada do vertice
      if (Estrela->Pertence->Vert2 == Vert){
        return (Estrela->Pertence->Aresta);
      }
      Estrela = Estrela->prox;
    }
    return (0);
  }else{
    return (0);
  }
}

int GAproxEntrada(Grafo PGrafo, int vert, int aresta){
  if (GBexisteIdVertice(PGrafo, vert) && GBexisteIdAresta(PGrafo, aresta)){
    NodoVertice Vert    = GVNodoVerdice(PGrafo, vert);    //pego endereço do Vertice
    NodoEstrela Estrela = Vert->Estrela;                  //pego endereço da primeira estrela do Vertice
    while (Estrela){                                      //percorro todas as estrelas do vertice
      if (Estrela->Pertence->Vert2 == Vert && Estrela->Pertence->Aresta > aresta){
        return (Estrela->Pertence->Aresta);               //se encontrar uma entrada do vertie que seja maior que a aresta passada retorno ela
      }
      Estrela = Estrela->prox;
    }
    return (0);
  }else{
    return (0);
  }
}

int GAprimaSaida(Grafo PGrafo, int vert){
  if (GBexisteIdVertice(PGrafo, vert)){
    NodoVertice Vert    = GVNodoVerdice(PGrafo, vert);  //pego endereço do Vertice
    NodoEstrela Estrela = Vert->Estrela;                //pego endereço da primeira estrela da aresta
    while (Estrela){                                    //percorro toda a estrela do vertice
      if (Estrela->Pertence->Vert1 == Vert){            //retorno a primeira saida do vertice na estrela
        return (Estrela->Pertence->Aresta);
      }
      Estrela = Estrela->prox;
    }
    return (0);
  }else{
    return (0);
  }
}

int GAproxSaida(Grafo PGrafo, int vert, int aresta){
  if (GBexisteIdVertice(PGrafo, vert) && GBexisteIdAresta(PGrafo, aresta)){
    NodoVertice Vert    = GVNodoVerdice(PGrafo, vert);    //pego endereço do Vertice
    NodoEstrela Estrela = Vert->Estrela;                  //pego endereço da primeira estrela do vertice
    while (Estrela){                                      //percorro toda a estrela do vertice
      if (Estrela->Pertence->Vert1 == Vert && Estrela->Pertence->Aresta > aresta){
        return (Estrela->Pertence->Aresta);               //retorno a primeira saida que é maior que a aresta passada
      }
      Estrela = Estrela->prox;
    }
    return (0);
  }else{
    return (0);
  }
}

int GBarestaLaco(Grafo PGrafo, int aresta){
  if (GBexisteIdAresta(PGrafo, aresta)){
    NodoAresta aux = GANodoAresta(PGrafo, aresta);      //pego endereço da aresta
    if (aux->Vert1 == aux->Vert2){                      //se o vert1 e o vert2 tem valores iguais então é um laço
      return (1);
    }else{
      return (0);
    }
  }else{
    return (0);
  }
}

int GValfa(Grafo PGrafo, int aresta){
  if (GBexisteIdAresta(PGrafo, aresta)){
    NodoAresta aux = GANodoAresta(PGrafo, aresta);
    return (aux->Vert1->Vert);                     //retorna o vert1 da aresta
  }else{
    return (0);
  }
}

int GVomega(Grafo PGrafo, int aresta){
  if (GBexisteIdAresta(PGrafo, aresta)){
    NodoAresta aux = GANodoAresta(PGrafo, aresta);
    return (aux->Vert2->Vert);                     //retorna o vert2 da aresta
  }else{
    return (0);
  }
}

int GVvizinho(Grafo PGrafo, int aresta, int vert){
  if (GBexisteIdAresta(PGrafo, aresta) && GBexisteIdVertice(PGrafo, vert)){
    NodoVertice aux = GVNodoVerdice(PGrafo, vert);
    NodoAresta aux1 = GANodoAresta(PGrafo, aresta);
    if (aux1->Vert1 == aux){
      return (aux1->Vert2->Vert);
    }else{
      if (aux1->Vert2 == aux){
        return (aux1->Vert1->Vert);
      }else{
        return (0);
      }
    }
  }else{
    return (0);
  }
}
