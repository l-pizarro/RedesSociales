#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int estaEn(int* arreglo, int valor, int largo) {
  int i;
  for (i = 0; i < largo; i++) {
    if (valor == arreglo[i]) {
      return 1;
    }
  }
  return 0;
}

void ordenarClique(int** arreglo, int largo) {
  int i;
  int j;
  int actual;
  for (i = 0; i < largo; i++) {
    j = 0;
    while ((*arreglo)[j] > (*arreglo)[j + 1] && j < largo) {
      actual           = (*arreglo)[j];
      (*arreglo)[j]    = (*arreglo)[j + 1];
      (*arreglo)[j+ 1] = actual;
      j++;
    }
  }
}

int** generarMatrizAdyacencia(int* ordenMatriz) {

  FILE* archivo;
  int   x;
  int   y;
  int** matriz;

  matriz  = NULL;
  archivo = fopen ("Entrada.in", "r");

  while (archivo == NULL) {
    printf("\n [>] Archivo 'Entrada.in' no encontrado !\n");
    exit(0);
  }

  fscanf(archivo, "%d\n", ordenMatriz);
  matriz = (int **)calloc(*ordenMatriz, sizeof(int*));
  for (x = 0; x < *ordenMatriz; x++) {
    matriz[x] = (int*)calloc(*ordenMatriz, sizeof(int));
  }

  while (fscanf(archivo, "%d %d\n", &x, &y) != EOF) {
    matriz[x-1][y-1] = 1;
    matriz[y-1][x-1] = 1;
  }

  fclose (archivo);
  // printf("El valor error matriz[2][6] es: %d\n", matriz[2][6]);

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

void conectar(int valor, int** matriz, int ordenMatriz, int** revisados, int eliminado) {
  // int x;
  int y;
  // printf("LLamada a conectar con el valor: %d\n", valor +1);
  // printf("\n");

  // for (x = 0; x < ordenMatriz; x ++) {
  //   for (y = 0; y < ordenMatriz; y ++) {
  //     printf("%d ", matriz[x][y]);
  //   }
  //   printf("\n");
  // }
  // printf("\n");

  for (y = 0; y < ordenMatriz; y++) {
    if (y + 1 == eliminado) {
      continue;
    }
    if (matriz[valor][y] == 1) {
      if (!estaEn(*revisados, y + 1, ordenMatriz)) {
        (*revisados)[y] = y + 1;
        // printf("El valor error matriz[%d][%d] es: %d\n", valor,y,matriz[valor][y]);
        // printf("En la conexion se agrega el %d a revisados\n", y + 1);
        conectar(y, matriz, ordenMatriz, revisados, eliminado);
      }
    }
  }
}

int obtenerGrupos(int** matriz, int eliminado, int ordenMatriz) {
  int i;
  int j;
  int cantidadGrupos;
  int* revisados;

  revisados      = (int*)calloc(ordenMatriz, sizeof(int));
  cantidadGrupos = 0;

  for (i = 0; i < ordenMatriz; i++) {
    if (i + 1 == eliminado) {
      continue;
    }
    if (!estaEn(revisados, i + 1, ordenMatriz)) {
      revisados[i] = i+1;
      // printf("Se agrega el %d a revisados\n", i + 1);
      cantidadGrupos ++;
    }
    for (j = 0; j < ordenMatriz; j++) {
      if (j + 1 == eliminado) {
        continue;
      }
      if (matriz[i][j] == 1) {
        if (!estaEn(revisados, j + 1, ordenMatriz)) {
          revisados[j] = j + 1;
          // printf("Se agrega el %d a revisados\n", j + 1);
          // printf("Conectando el %d\n", j + 1);
          conectar(j, matriz, ordenMatriz, &revisados, eliminado);
        }
      }
    }
  }

  return cantidadGrupos;
}

void obtenerVinculos(int** matriz, int ordenMatriz){
  int i;
  int gruposIniciales;
  int gruposLuegoDeEliminar;

  gruposIniciales = obtenerGrupos(matriz, ordenMatriz + 1, ordenMatriz);

  //printf("grupos iniciales: %d\n", gruposIniciales);
  for (i = 0; i < ordenMatriz; i++) {
    //printf("-- %d --\n", i);
    gruposLuegoDeEliminar = obtenerGrupos(matriz, i + 1, ordenMatriz);
    //printf("grupos eliminando %d: %d\n", i + 1, gruposLuegoDeEliminar);
    if (gruposIniciales < gruposLuegoDeEliminar) {
      printf("%d es un agente de vínculo.\n", i + 1);
    }
  }
}

void generarCliques(int** matriz, int ordenMatriz) {
  int i;
  int j;
  int k;
  int l;

  for (i = 0; i < ordenMatriz; i++) {
    for (j = i+1; j < ordenMatriz; j++) {
      for (k = j+1; k < ordenMatriz; k++) {
        for (l = k+1;l < ordenMatriz; l++) {
          if (i != j && matriz[i][j]) {
            if (i != k && matriz[i][k]) {
              if (i != l && matriz[i][l]) {
                if (j != k && matriz[j][k]) {
                  if (j != l && matriz[j][l]) {
                    if (k != l && matriz[k][l]) {
                      printf("%d, %d, %d, %d conforman un grupo de mejores amigos\n",i+1,j+1,k+1,l+1);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void iniciar(){
  int ordenMatriz;
  int** matriz;
  time_t inicioMatriz;
  time_t finalMatriz;
  matriz = generarMatrizAdyacencia(&ordenMatriz);
  time(&inicioMatriz);
  printf("\n\n***** Inicio del Programa *****\n\n");
  obtenerVinculos(matriz, ordenMatriz);
  generarCliques(matriz, ordenMatriz);
  printf("\n***** Fin del Programa *****\n\n");
  time(&finalMatriz);
  printf("Tiempo utilizado: %f\n", difftime(inicioMatriz, finalMatriz));

}
