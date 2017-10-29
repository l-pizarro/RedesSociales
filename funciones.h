#pragma once

typedef struct MatrizAdy {
  int** matriz;
  int ordenMatriz;
} MatrizAdy;

typedef struct Adyacentes {
  int* vertices;
  int largo;
}Adyacentes;

typedef struct Lista {
  Adyacentes* adyacentes;
  int cantidad;
}Lista;


Lista* crearLista();
Adyacentes* crearAdyacentes();
Lista* generarListaAdyacencia();
void obtenerCliquesL(Lista* lista);
int esAdyacente(int valor, Adyacentes* adyacentes);
void agregarAdyacente(int valor, Adyacentes* adyacentes);
void obtenerVinculosL(Lista* lista);
int obtenerGruposL(Lista* lista, int eliminado);
void conectarL(int valor, Lista* lista, int** revisados, int eliminado);

MatrizAdy* crearMatriz();
MatrizAdy* generarMatrizAdyacencia();
void conectarM(int valor, MatrizAdy* matriz, int** revisados, int eliminado);
int obtenerGruposM(MatrizAdy* matriz, int eliminado);
void obtenerVinculosM(MatrizAdy* matriz);
void obtenerCliquesM(MatrizAdy* matriz);
void freeMatrizAdy(MatrizAdy* matriz);

void iniciar();
int estaEn(int* arreglo, int valor, int largo);
