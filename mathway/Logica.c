#include "Logica.h"


/*
op:
1 = +
2 = -
3 = *
4 = /
5 = potencia
*/

int logica(int op, int n1, int n2, int resultado) {
	int x, y;
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
		if (resultado == (n1 / n2)) {
			return 0;
		}
		else {
			return -5;
		}
	case 5:
		x = n1 * n1 * n1;
		y = 12;
		if (resultado == (x + y)) {
			return 0;
		}
		else {
			return -5;
		}
	default:
		break;
	}
}