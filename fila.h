//=====================================================
// Arquivo: fila.h
//
// Autor: Guilherme Cardoso Silva 0022545
// Data: 27/07/2016
// Disciplina: Programacao II
// Atividade: Trabalho 2
//=====================================================

#ifndef TadFilaXxX
#define TadFilaXxX

typedef struct fila *Fila;

extern
  Fila criaFila(void);
  void insereFila(Fila fila, int v);
  int retiraFila(Fila fila);
  void destroiFila(Fila fila);
  int FilaVazia(Fila fila);

#endif
