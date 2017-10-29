#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funciones.h"

// FUNCIONES LISTA DE ADYACENCIA
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

int obtenerGruposL(Lista* lista, int eliminado) {
  int i;
  int j;
  int cantidadGrupos;
  int* revisados;

  revisados      = (int *)calloc(lista->cantidad, sizeof(int));
  cantidadGrupos = 0;

  for (i = 0; i < lista->cantidad; i++) {
    if (i + 1 == eliminado) {
      continue;
    }
    if (!estaEn(revisados, i + 1, lista->cantidad)) {
      revisados[i] = i+1;
      cantidadGrupos ++;
    }
    for (j = 0; j < lista->adyacentes[i].largo; j++) {
      if (lista->adyacentes[i].vertices[j] == eliminado) {
        continue;
      }
      if (!estaEn(revisados, lista->adyacentes[i].vertices[j], lista->cantidad)) {
        revisados[lista->adyacentes[i].vertices[j] - 1] = lista->adyacentes[i].vertices[j];
        conectarL(lista->adyacentes[i].vertices[j] - 1, lista, &revisados, eliminado);
      }
    }
  }

  free(revisados);

  return cantidadGrupos;
}

void conectarL(int valor, Lista* lista, int** revisados, int eliminado) {

  int x;

  for (x = 0; x < lista->adyacentes[valor].largo; x++) {
    if (lista->adyacentes[valor].vertices[x] == eliminado) {
      continue;
    }
    if (!estaEn(*revisados, lista->adyacentes[valor].vertices[x], lista->cantidad)) {
      (*revisados)[lista->adyacentes[valor].vertices[x] - 1] = lista->adyacentes[valor].vertices[x];
      conectarL(lista->adyacentes[valor].vertices[x] - 1, lista, revisados, eliminado);
    }
  }
}

void obtenerVinculosL(Lista* lista) {

  int i;
  int gruposIniciales;
  int gruposLuegoDeEliminar;

  gruposIniciales = obtenerGruposL(lista, lista->cantidad + 1);

  for (i = 0; i < lista->cantidad; i++) {
    gruposLuegoDeEliminar = obtenerGruposL(lista, i + 1);
    if (gruposIniciales < gruposLuegoDeEliminar) {
      printf("  %d es un agente de vínculo. Crea %d componente(s) conexa(s).\n", i + 1, gruposLuegoDeEliminar);
    }
  }
}

void obtenerCliquesL(Lista* lista) {

  int i;
  int j;
  int k;
  int l;

  for (i = 0; i < lista->cantidad - 3; i++) {
    for (j = i + 1; j < lista->cantidad - 2; j++) {
      for (k = j + 1; k < lista->cantidad - 1; k++) {
        for (l = k + 1; l < lista->cantidad; l++) {
          if (i != j && esAdyacente(i + 1, &(lista->adyacentes[j]))) {
            if (i != k && esAdyacente(i + 1, &(lista->adyacentes[k]))) {
              if (i != l && esAdyacente(i + 1, &(lista->adyacentes[l]))) {
                if (j != k && esAdyacente(j + 1, &(lista->adyacentes[k]))) {
                  if (j != l && esAdyacente(j + 1, &(lista->adyacentes[l]))) {
                    if (k != l && esAdyacente(k + 1, &(lista->adyacentes[l]))) {
                      printf("  %d, %d, %d, %d conforman un grupo de mejores amigos.\n",i+1,j+1,k+1,l+1);
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

void freeLista(Lista* lista) {
  int i;

  for (i = 0; i < lista->cantidad; i++) {
    free(lista->adyacentes[i].vertices);
  }
  free(lista->adyacentes);
  free(lista);
}


// FUNCIONES MATRIZ DE ADYACENCIA
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

int obtenerGruposM(int** matriz, int eliminado, int ordenMatriz) {
  int i;
  int j;
  int cantidadGrupos;
  int* revisados;

  revisados      = (int *)calloc(ordenMatriz, sizeof(int));
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
          conectarM(j, matriz, ordenMatriz, &revisados, eliminado);
        }
      }
    }
  }
  free(revisados);
  return cantidadGrupos;
}

void conectarM(int valor, int** matriz, int ordenMatriz, int** revisados, int eliminado) {

  int x;

  for (x = 0; x < ordenMatriz; x++) {
    if (x + 1 == eliminado) {
      continue;
    }
    if (matriz[valor][x] == 1) {
      if (!estaEn(*revisados, x + 1, ordenMatriz)) {
        (*revisados)[x] = x + 1;
        conectarM(x, matriz, ordenMatriz, revisados, eliminado);
      }
    }
  }
}

void obtenerVinculosM(int** matriz, int ordenMatriz) {
  int i;
  int gruposIniciales;
  int gruposLuegoDeEliminar;

  gruposIniciales = obtenerGruposM(matriz, ordenMatriz + 1, ordenMatriz);

  for (i = 0; i < ordenMatriz; i++) {
    gruposLuegoDeEliminar = obtenerGruposM(matriz, i + 1, ordenMatriz);
    if (gruposIniciales < gruposLuegoDeEliminar) {
      printf("  %d es un agente de vínculo. Crea %d componente(s) conexa(s).\n", i + 1, gruposLuegoDeEliminar);
    }
  }
}

void obtenerCliquesM(int** matriz, int ordenMatriz) {
  int i;
  int j;
  int k;
  int l;

  for (i = 0; i < ordenMatriz - 3; i++) {
    for (j = i+1; j < ordenMatriz - 2; j++) {
      for (k = j+1; k < ordenMatriz - 1; k++) {
        for (l = k+1;l < ordenMatriz; l++) {
          if (i != j && matriz[i][j]) {
            if (i != k && matriz[i][k]) {
              if (i != l && matriz[i][l]) {
                if (j != k && matriz[j][k]) {
                  if (j != l && matriz[j][l]) {
                    if (k != l && matriz[k][l]) {
                      printf("  %d, %d, %d, %d conforman un grupo de mejores amigos.\n",i+1,j+1,k+1,l+1);
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

void freeMatriz(int** matriz, int ordenMatriz) {

  int i;
  for (i = 0; i < ordenMatriz; i++) {
    free(matriz[i]);
  }
  free(matriz);

}

// FUNCION GENERALES
int estaEn(int* arreglo, int valor, int largo) {
  int i;
  for (i = 0; i < largo; i++) {
    if (valor == arreglo[i]) {
      return 1;
    }
  }
  return 0;
}

void iniciar() {

  // MATRIZ DE ADYACENCIA
  int** matriz;
  int ordenMatriz;
  matriz = generarMatrizAdyacencia(&ordenMatriz);
  time_t inicioMatriz;
  time_t finalMatriz;

  printf("\n\n***** Inicio del Programa *****\n\n");
  printf("> Implementación mediante matriz de adyacencia ...\n\n");
  inicioMatriz = clock();
  obtenerVinculosM(matriz, ordenMatriz);
  obtenerCliquesM(matriz, ordenMatriz);
  finalMatriz = clock();
  printf("\n Tiempo ejecución = %f\n\n\n", (double)(finalMatriz - inicioMatriz)/CLOCKS_PER_SEC);
  freeMatriz(matriz, ordenMatriz);


  // LISTA DE ADYACENCIA
  Lista* lista;
  time_t inicioLista;
  time_t finalLista;

  printf("> Implementación mediante lista de adyacencia ...\n\n");
  lista = generarListaAdyacencia(ordenMatriz);
  inicioLista = clock();
  obtenerVinculosL(lista);
  obtenerCliquesL(lista);
  finalLista = clock();
  printf("\n Tiempo ejecución = %f\n\n\n", (double)(finalLista - inicioLista)/CLOCKS_PER_SEC);
  printf("\n***** Fin del Programa *****\n\n");
  freeLista(lista);
}
