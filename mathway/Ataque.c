#include "Ataque.h"
#include <stdio.h>


int ataque(int nivel,int n1,int n2) {
	int resultado;
	int valorUser;
	switch (nivel){
	case 1:
		printf("Informe o resultado do seguinte codigo %i + %i  ", n1, n2);
		scanf_s("%i", &valorUser);
		resultado = n1 + n2;
		
		if (resultado == valorUser)  {
			return 5;
		}
		else {
			return -5;
		}
	break;
	
	case 2:
		printf("Informe o resultado do seguinte codigo %i x %i ", n1, n2);
		scanf_s("%i", &valorUser);
		resultado = n1 * n2;


		if (resultado == valorUser) {
			printf("Informe o resultado do seguinte codigo %i / %i ", n1, n2);
			scanf_s("%i", &valorUser);

			resultado = n1 / n2;

			if (resultado == valorUser) {
				printf("Ok 2");
			}
		}
		
	default:
		break;
	}
}