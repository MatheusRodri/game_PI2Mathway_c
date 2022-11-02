#include "Logica.h"


/*

op:
1 = +
2 = -
3 = *
4 = /

*/

int logica(char tipo,int nivel, int op, int n1, int n2,double resultado) {
	if (tipo == "i") {
		switch (op) {
		case 1:
				if (resultado == (n1 + n2)) {
					return 0;
				}
				else {
					return -5;
				}
		case 2:
				if (resultado == (n1 - n2)) {
					return 0;
				}
				else {
					return -5;
				}
		case 3:
				if (resultado == (n1 * n2)) {
					return 0;
				}
				else {
					return -5;
				}
		case 4:
				if (resultado == (n1 /n2)) {
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
		double conta = 0;
		switch (nivel){
		case 1:
			conta = (n1 * n2) / 2;
		
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