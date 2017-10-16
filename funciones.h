#pragma once

int estaEn(int* arreglo, int valor, int largo);

int seRelacionan(int* arregloA, int* arregloB, int largo);

void ordenarClique(int** arreglo, int largo);

int** generarMatrizAdyacencia();

int sumarAmigos(int* persona, int largo);

void conectar(int valor, int** matriz, int ordenMatriz, int** revisados, int eliminado);

int obtenerGrupos(int** matriz, int eliminado, int ordenMatriz);

void obtenerVinculos(int** matriz, int ordenMatriz);

int** generarCliques(int matriz, int ordenMatriz);

void iniciar();
