#include <stdio.h> // Eliminar include por los prints
#include "funciones.h"

int main(int argc, char const *argv[]) {
  int i;
  int j;
  int orden;
  int** matriz;
  matriz = generarMatrizAdyacencia(&orden);

  for (i=0; i < orden; i++) {
    for (j = 0 ; j < orden; j++) {
      printf("  %d  ", matriz[i][j]);
    }
    printf("\n\n");
  }

  return 0;
}
