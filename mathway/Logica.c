#include "Logica.h"


/*

op:
1 = +
2 = -
3 = *
4 = /

*/

int logica(char tipo, int nivel, int op, int n1, int n2) {
	double resultado = 0;
	if (tipo == "i") {
		switch (op) {
		case 1:
			//Colocar a caixa de dialogo aqui informando N1 + N2
			//Aqui vem a variavel resultado = entrada do usuario
				if (resultado == (n1 + n2)) {
					return 0;
				}
				else {
					return -5;
				}
		case 2:
			//Colocar a caixa de dialogo aqui informando N1 e N2
			//Aqui vem a variavel resultado = entrada do usuario
				if (resultado == (n1 - n2)) {
					return 0;
				}
				else {
					return -5;
				}
		case 3:
			//Colocar a caixa de dialogo aqui informando N1 e N2
			//Aqui vem a variavel resultado = entrada do usuario
				if (resultado == (n1 * n2)) {
					return 0;
				}
				else {
					return -5;
				}
		case 4:
			//Colocar a caixa de dialogo aqui informando N1 e N2
			//Aqui vem a variavel resultado = entrada do usuario
				if (resultado == (n1 / a n2)) {
					return 0;
				}
				else {
					return -5;
				}
		default:
			break;
		}
	}
	else {
		double resultado = 0;
		double conta = 0;
		switch (nivel){
		case 1:
			conta = (n1 * n2) / 2;
			//Aqui vem a variavel resultado = entrada do usuario
			if (resultado == conta) {
				return 0;
			}
			else {
				return 1;
			}
		default:
			break;
		}
	}


}