#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** generarMatrizAdyacencia(int* ordenMatriz) {

  FILE* archivo;
  int   x;
  int   y;
  int** matriz;
  char  linea[5];

  matriz  = NULL;
  archivo = fopen ("Entrada.in", "r");

  while (archivo == NULL) {
    printf("\n [>] Archivo 'Entrada.in' no encontrado !");
    exit(1);
  }

  fgets(linea, 5, archivo);
  *ordenMatriz = (int)linea[0] - 48;
  printf("%d\n", *ordenMatriz);
  matriz = (int **)calloc(*ordenMatriz, sizeof(int*));
  for (x = 0; x < *ordenMatriz; x++) {
    matriz[x] = (int*)calloc(*ordenMatriz, sizeof(int));
  }

  while (fgets(linea, 5 ,archivo)){
    x            = (int)linea[0] - 49;
    y            = (int)linea[2] - 49;
    matriz[x][y] = 1;
    matriz[y][x] = 1;
  }

  fclose (archivo);

  return matriz;
}

int sumarAmigos(int* persona, int largo) {
   int i;
   int suma;
   suma = 0;
   for (i = 0; i < largo; i++)
   {
	 suma = suma + persona[i];
   }
   return suma;
}

int* obtenerGrupos(int** matriz, int eliminado; int ordenMatriz, int* cantidadGrupos) {
  int i;
  int j;
  int** grupos;
  int amigos;

  grupos          = (int **)calloc(1, sizeof(int*));
  *cantidadGrupos = 0;

  for (i = 0; i < ordenMatriz; i++) {
    if (i == eliminado) {
      continue;
    }
    grupos[i] = (int *)calloc(1, sizeof(int));
    grupos[i] = i + 1;
    amigos    = sumarAmigos(matriz[i]);
    *cantidadGrupos ++;
    if (amigos) {
      printf("[");
      grupos[i] = (int *)realloc(grupos[i], sizeof(int) * (amigos + 1));
      for (j = 0; j < ordenMatriz; j++ ) {
        if (matriz[i][j]) {
          grupos[i][amigos - 1] = matriz[i][j]
          amigos --;
        }
      }
    }
    printf("]\n");
  }
}
