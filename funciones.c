#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funciones.h"

// LISTA DE ADYACENCIA
Lista* crearLista(int cantidadVertices) {
  int i;
  Lista* lista = (Lista*)calloc(1, sizeof(Lista));

  lista->adyacentes = (Adyacentes*)calloc(cantidadVertices, sizeof(Adyacentes));
  lista->cantidad   = cantidadVertices;
  for (i = 0; i < cantidadVertices; i++) {
    lista->adyacentes[i].vertices = (int*)calloc(1,sizeof(int));
    lista->adyacentes[i].largo    = 0;
  }
  return lista;
}

Lista* generarListaAdyacencia(int ordenMatriz) {

  FILE* archivo;
  Lista* lista;
  int x;
  int y;

  archivo = fopen ("Entrada.in", "r");

  while (archivo == NULL) {
    printf("\n [>] Archivo 'Entrada.in' no encontrado !\n");
    exit(0);
  }

  fscanf(archivo, "%d\n", &x);

  lista  = NULL;
  lista  = crearLista(ordenMatriz);

  while (fscanf(archivo, "%d %d\n", &x, &y) != EOF) {
    agregarAdyacente(y, &(lista->adyacentes[x-1]));
    agregarAdyacente(x, &(lista->adyacentes[y-1]));
  }

  fclose (archivo);

  return lista;
}

void agregarAdyacente(int valor, Adyacentes* adyacentes) {
  adyacentes->vertices                    = (int*)realloc(adyacentes->vertices, (adyacentes->largo + 1) * sizeof(int));
  adyacentes->vertices[adyacentes->largo] = valor;
  adyacentes->largo ++;
}

int esAdyacente(int valor, Adyacentes* adyacentes) {

  int i;
  for (i = 0; i < adyacentes->largo; i++) {
    if (adyacentes->vertices[i] == valor) {
      return 1;
      break;
    }
  }
  return 0;
}

void obtenerCliquesL(Lista* lista) {

  int i;
  int j;
  int k;
  int l;

  for (i = 0; i < lista->cantidad; i++) {
    for (j = i + 1; j < lista->cantidad; j++) {
      for (k = j + 1; k < lista->cantidad; k++) {
        for (l = k + 1; l < lista->cantidad; l++) {
          if (i != j && esAdyacente(i + 1, &(lista->adyacentes[j]))) {
            if (i != k && esAdyacente(i + 1, &(lista->adyacentes[k]))) {
              if (i != l && esAdyacente(i + 1, &(lista->adyacentes[l]))) {
                if (j != k && esAdyacente(j + 1, &(lista->adyacentes[k]))) {
                  if (j != l && esAdyacente(j + 1, &(lista->adyacentes[l]))) {
                    if (k != l && esAdyacente(k + 1, &(lista->adyacentes[l]))) {
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

void obtenerVinculosL(Lista* lista) {

}

int conectar(Lista* lista, int actual, int eliminado, int* ocupados) {
  
}
// MATRIZ DE ADYACENCIA
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

int estaEn(int* arreglo, int valor, int largo) {
  int i;
  for (i = 0; i < largo; i++) {
    if (valor == arreglo[i]) {
      return 1;
    }
  }
  return 0;
}

void conectar(int valor, int** matriz, int ordenMatriz, int** revisados, int eliminado) {

  int y;

  for (y = 0; y < ordenMatriz; y++) {
    if (y + 1 == eliminado) {
      continue;
    }
    if (matriz[valor][y] == 1) {
      if (!estaEn(*revisados, y + 1, ordenMatriz)) {
        (*revisados)[y] = y + 1;
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
      cantidadGrupos ++;
    }
    for (j = 0; j < ordenMatriz; j++) {
      if (j + 1 == eliminado) {
        continue;
      }
      if (matriz[i][j] == 1) {
        if (!estaEn(revisados, j + 1, ordenMatriz)) {
          revisados[j] = j + 1;
          conectar(j, matriz, ordenMatriz, &revisados, eliminado);
        }
      }
    }
  }

  return cantidadGrupos;
}

void obtenerVinculosM(int** matriz, int ordenMatriz) {
  int i;
  int gruposIniciales;
  int gruposLuegoDeEliminar;

  gruposIniciales = obtenerGrupos(matriz, ordenMatriz + 1, ordenMatriz);

  for (i = 0; i < ordenMatriz; i++) {
    gruposLuegoDeEliminar = obtenerGrupos(matriz, i + 1, ordenMatriz);
    if (gruposIniciales < gruposLuegoDeEliminar) {
      printf("%d es un agente de vínculo.\n", i + 1);
    }
  }
}

void obtenerCliquesM(int** matriz, int ordenMatriz) {
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


// FUNCION INICIO
void iniciar() {

  // MATRIZ DE ADYACENCIA
  int** matriz;
  int ordenMatriz;
  matriz = generarMatrizAdyacencia(&ordenMatriz);
  time_t inicioMatriz;
  time_t finalMatriz;

  printf("\n\n***** Inicio del Programa *****\n\n");
  time(&inicioMatriz);
  obtenerVinculosM(matriz, ordenMatriz);
  obtenerCliquesM(matriz, ordenMatriz);
  time(&finalMatriz);
  printf("\n***** Fin del Programa *****\n\n");
  printf("Tiempo utilizado matriz: %f\n", difftime(inicioMatriz, finalMatriz));

  // LISTA DE ADYACENCIA
  Lista* lista;
  time_t inicioLista;
  time_t finalLista;
  printf("\n\n***** Inicio del Programa *****\n\n");
  time(&inicioLista);
  lista = generarListaAdyacencia(ordenMatriz);
  obtenerCliquesL(lista);
  time(&finalLista);
  printf("\n***** Fin del Programa *****\n\n");
  printf("Tiempo utilizado lista: %f\n", difftime(inicioLista, finalLista));
}
