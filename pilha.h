//=====================================================
// Arquivo: pilha.h
//
// Autor: Guilherme Cardoso Silva 0022545
// Data: 27/07/2016
// Disciplina: Programacao II
// Atividade: Trabalho 2
//=====================================================

#ifndef TadPilhaXxX
#define TadPilhaXxX

typedef struct pilha *Pilha;

extern
  Pilha criaPilha(void);
  void inserePilha(Pilha pilha, int v);
  int retiraPilha(Pilha pilha);
  void destroiPilha(Pilha pilha);
  int PilhaVazia(Pilha pilha);

#endif
