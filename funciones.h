#pragma once

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
Lista* generarListaAdyacencia(int ordenMatriz);
void obtenerCliquesL(Lista* lista);
int esAdyacente(int valor, Adyacentes* adyacentes);
void agregarAdyacente(int valor, Adyacentes* adyacentes);
void obtenerVinculosL(Lista* lista);


int estaEn(int* arreglo, int valor, int largo);
int** generarMatrizAdyacencia();
void conectar(int valor, int** matriz, int ordenMatriz, int** revisados, int eliminado);
int obtenerGrupos(int** matriz, int eliminado, int ordenMatriz);
void obtenerVinculosM(int** matriz, int ordenMatriz);
void obtenerCliquesM(int** matriz, int ordenMatriz);


void iniciar();
