//=====================================================
// Arquivo: grafo.h
//
// Autores: Guilherme Cardoso Silva 0022545
//          Flavia Ribeiro Santos   0022651
// Data: 27/05/2016
// Disciplina: Programacao II
// Atividade: Trabalho1
//=====================================================

#ifndef TadGrafoXxX
#define TadGrafoXxX

typedef struct grafo *Grafo;

extern
    /*Operações com Grafo*/
    Grafo GGcriaGrafo(int vertice,int aresta);
    Grafo GGdestroiGrafo(Grafo PGrafo);
    int GVcriaVertice(Grafo PGrafo);
    int GAcriaAresta(Grafo PGrafo,int vert1,int vert2);
    int GBexisteIdVertice(Grafo PGrafo,int vert);
    int GBexisteIdAresta(Grafo PGrafo,int aresta);
    int GBexisteArestaDir(Grafo PGrafo,int vert1,int vert2);
    int GBexisteAresta(Grafo PGrafo,int vert1,int vert2);
    int GApegaArestaDir(Grafo PGrafo,int vert1,int vert2);
    int GApegaAresta(Grafo PGrafo,int vert1,int vert2);
    int GVprimeiroVertice(Grafo PGrafo);
    int GVproximoVertice(Grafo PGrafo,int vert);
    int GAprimeiraAresta(Grafo PGrafo);
    int GAproximaAresta(Grafo PGrafo,int aresta);
    int GInumeroVertices(Grafo PGrafo);
    int GInumeroVerticesMax(Grafo PGrafo);
    int GInumeroArestas(Grafo PGrafo);
    int GInumeroArestasMax(Grafo PGrafo);
    Grafo GGcarregaGrafo(char f[]);
    int GBsalvaGrafo(Grafo PGrafo, char f[]);

    /*Operações com Vertices*/
    int GIpegaGrau(Grafo PGrafo,int vert);
    int GAprimaAresta(Grafo PGrafo,int vert);
    int GAproxAresta(Grafo PGrafo,int vert,int aresta);
    int GAprimaEntrada(Grafo PGrafo,int vert);
    int GAproxEntrada(Grafo PGrafo,int vert,int aresta);
    int GAprimaSaida(Grafo PGrafo,int vert);
    int GAproxSaida(Grafo PGrafo,int vert,int aresta);

    /*Operações com Arestas*/
    int GBarestaLaco(Grafo PGrafo,int aresta);
    int GValfa(Grafo PGrafo,int aresta);
    int GVomega(Grafo PGrafo,int aresta);
    int GVvizinho(Grafo PGrafo,int aresta,int vert);

    void Gcaminho(Grafo PGrafo, int *pesos, int a, int b);
#endif
