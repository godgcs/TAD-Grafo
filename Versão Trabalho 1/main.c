#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main()
{
	Grafo Graf1;
	Graf1=GGcarregaGrafo("grafo1.txt");

  int pesos[9];
  pesos[0]=0;
  pesos[1]=5;
  pesos[2]=10;
  pesos[3]=2;
  pesos[4]=10;
  pesos[5]=8;
  pesos[6]=3;
	pesos[7]=2;
	pesos[8]=1;
  Gcaminho(Graf1,pesos,1,4);

	Gcaminho(Graf1,pesos,1,5);

	pesos[0]=0;
  pesos[1]=4;
  pesos[2]=2;
  pesos[3]=1;
  pesos[4]=5;
  pesos[5]=3;
  pesos[6]=5;
	pesos[7]=4;
	pesos[8]=3;
	Gcaminho(Graf1,pesos,1,5);

	Gcaminho(Graf1,pesos,1,4);

	Gcaminho(Graf1,pesos,1,6);
	return(0);
}
