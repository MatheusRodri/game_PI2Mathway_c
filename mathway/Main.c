#include <stdlib.h>
#include <stdio.h>
#include "Ataque.h"
#include "Vida.h"


int main() {
	int vidaInicial = 100;
	int ponto = ataque(1, 5, 5);
	
	vidaInicial = vida(vidaInicial,ponto);

	printf("Sua vida agora %i", vidaInicial);
	return 0;
}