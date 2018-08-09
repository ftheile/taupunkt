/** \file
 * Test Taupunktberechnung.
 */
#include "taupunkt.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	if (argc == 3) {
		struct Tp tp;
		float T = atof(argv[1]);
		float r = atof(argv[2]);
		Tp_Init(&tp, T, r);
		Tp_Print(&tp);
		return 0;
	} else {
		printf("Taupunktberechnung aus Temperatur und rel. Luftfeuchte.\n\n");
		printf("%s T r\n", argv[0]);
		printf("  T  Temperatur [°C]\n");
		printf("  r  rel. Luftfeuchte [%%]\n\n");
		return -1;
	}
}
