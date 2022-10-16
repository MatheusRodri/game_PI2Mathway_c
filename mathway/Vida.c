#include "Vida.h"
#include <stdio.h>

int vida(int vida,int ponto) {
	printf("Voce tem %i pontos de vida\n ",vida);
	if (vida == 0) {
		printf("Voce ficou sem vidas. Tente novamente\n");
	}
	else {
		if (ponto < 0) {
			vida += ponto;
			printf("Ohh, voce perdeu %i agora voce so tem %i\n", ponto, vida);
			return vida;
		}
		else {
			vida += ponto;
			printf("Parabeéns, você conseguiu %i agora voce tem %i\n", ponto, vida);
			return vida;
		}
	}
	
}