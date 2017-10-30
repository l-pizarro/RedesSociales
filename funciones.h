#pragma once

//
// Estructura MatrizAdy:
//
// Corresponde a la representacion de una matriz de
// adyacencia. Contiene un arreglo bidimensional binario
// y un número entero que indica el orden de la matriz.
typedef struct {
  int** matriz;
  int ordenMatriz;
} MatrizAdy;

//
// Estructura Adyacentes:
//
// Esta estructura posee un arreglo de números enteros, los
// cuales indican los vértices adyacentes a un determinado
// vértice, además de un número entero que indica la cantidad
// de elementos dentro del arreglo de enteros.
typedef struct {
  int* vertices;
  int largo;
}Adyacentes;

//
// Estructura Lista:
//
// Posee un arreglo de estructuras Adyacentes y la cantidad de
// elementos de dicho arreglo. Cada delemento del arreglo
// contiene la información de los vértices que son adyacentes
// a uno en particular.
typedef struct {
  Adyacentes* adyacentes;
  int cantidad;
}Lista;

// Entrada: - Cantidad de vértices de un grafo.
// Salida:  - Una lista de ayacencia (puntero).
// Descipcion: La función pide espacio en memoria para un puntero
// a estructura lista y para el arreglo de estructuras adyacentes.
Lista* crearLista(int cantidadVertices);


// Entrada: - No posee.
// Salida:  - Un puntero a estructura Lista.
// Descipcion: Esta función abre el archivo Entrada.in, genera listas
//             de adyacencia y agrega los vértices adyacentes a cada uno
//             de los vertices dentro del grafo contenido en el archivo.
Lista* generarListaAdyacencia();

// Entrada: - Un puntero a una lista.
// Salida:  - No posee.
// Descipcion: obtenerCliquesL genera las combinaciones de 4 vértices posibles
//             dentro del grafo. Si una de estas corresponde a un clique
//             imprime por pantalla los números de los vértices junto
//             con el mensaje correspondiente.
void obtenerCliquesL(Lista* lista);

// Entrada: - Un valor a buscar.
//          - Un puntero a estructura adyacentes.
// Salida:  - Un número entero.
// Descipcion: La funcion esAdyacentes recorre el arreglo de
//             enteros dentro de la estructura Adyacentes y si
//             encuentra el valor que se busca retorna un 1, de
//             lo contrario retorna 0.
int esAdyacente(int valor, Adyacentes* adyacentes);

// Entrada: - Un valor a agragar.
//          - Una puntero a estructura Adyacentes.
// Salida:  - No posee.
// Descipcion: agregarAdyacente agrega el valor ingresado en
//             los parametros al arreglo de números de la estructura
//             Adyacentes.
void agregarAdyacente(int valor, Adyacentes* adyacentes);

// Entrada: - Un puntero a estructura Lista.
// Salida:  - No posee.
// Descipcion: La funcion obtenerVinculosL compara la cantidad de
//             grupos antes y después de eliminar un vértice. Si la
//             cantidad después de eliminar es mayor a la inicial. El
//             vértice corresponde a un agente vínculo y se imprime por
//             pantalla el mensaje correspondiente. El proceso se repite
//             para cada vértice del grafo.
void obtenerVinculosL(Lista* lista);

// Entrada: - Un puntero a estructura Lista.
//          - Un número entero correspondiente a un vértice.
// Salida:  - Un entero igual a la cantidad de grupos.
// Descipcion: Esta función calcula la cantidad de grupos dentro de
//             un grafo sin considerar el vértice que se ingresa en
//             los parámetros (eliminado).
int obtenerGruposL(Lista* lista, int eliminado);

// Entrada: - Un número que indica el vértice de búsqueda.
//          - Un puntero a estructura Lista.
//          - Un arreglo de enteros.
//          - El valor de un vértice eliminado.
// Salida:  - No posee.
// Descipcion: La funcion conectarL realiza un busqueda en profundidad
//             partiendo desde el vértice "valor". Cada vez que un
//             vértice que se recorra no esté dentro de "revisados", esta
//             es agregado y se realiza un nuevo llamado recursivo.
void conectarL(int valor, Lista* lista, int** revisados, int eliminado);

// Entrada: - Un puntero a una Lista.
// Salida:  - No posee.
// Descipcion: esta función libera toda la memoria utilizada en la estructura
//             "lista".
void freeLista(Lista* lista);

// Entrada: - No posee.
// Salida:  - Un puntero a matriz de ayacencia.
// Descipcion: La función pide espacio en memoria para un puntero
// a estructura MatrizAdy y define el puntero a entero como nulo.
MatrizAdy* crearMatriz();

// Entrada: - No posee.
// Salida:  - Un puntero a estructura MatrizAdy.
// Descipcion: Esta función abre el archivo Entrada.in, genera una matriz
//             de adyacencia y agrega los unos correspondientes a cada uno
//             de los vértices correspondientes.
MatrizAdy* generarMatrizAdyacencia();

// Entrada: - Un número que indica el vértice de búsqueda.
//          - Un puntero a estructura MatrizAdy.
//          - Un arreglo de enteros.
//          - El valor de un vértice eliminado.
// Salida:  - No posee.
// Descipcion: La funcion conectarM realiza un busqueda en profundidad
//             partiendo desde el vértice "valor". Cada vez que un
//             vértice que se recorra no esté dentro de "revisados", esta
//             es agregado y se realiza un nuevo llamado recursivo.
void conectarM(int valor, MatrizAdy* matriz, int** revisados, int eliminado);

// Entrada: - Un puntero a estructura MatrizAdy.
//          - Un número entero correspondiente a un vértice.
// Salida:  - Un entero igual a la cantidad de grupos.
// Descipcion: Esta función calcula la cantidad de grupos dentro de
//             un grafo sin considerar el vértice que se ingresa en
//             los parámetros (eliminado).
int obtenerGruposM(MatrizAdy* matriz, int eliminado);

// Entrada: - Un puntero a estructura MatrizAdy.
// Salida:  - No posee.
// Descipcion: La funcion obtenerVinculosM compara la cantidad de
//             grupos antes y después de eliminar un vértice. Si la
//             cantidad después de eliminar es mayor a la inicial. El
//             vértice corresponde a un agente vínculo y se imprime por
//             pantalla el mensaje correspondiente. El proceso se repite
//             para cada vértice del grafo.
void obtenerVinculosM(MatrizAdy* matriz);

// Entrada: - Un puntero a una matriz de adyacencia.
// Salida:  - No posee.
// Descipcion: obtenerCliquesM genera las combinaciones de 4 vértices posibles
//             dentro del grafo. Si una de estas corresponde a un clique
//             imprime por pantalla los números de los vértices junto
//             con el mensaje correspondiente.
void obtenerCliquesM(MatrizAdy* matriz);

// Entrada: - Un puntero a una MatrizAdy.
// Salida:  - No posee.
// Descipcion: Esta función libera toda la memoria utilizada en la estructura
//             "matriz".
void freeMatrizAdy(MatrizAdy* matriz);

// Entrada: - Un arreglo de enteros.
//          - El valor a buscar.

// Salida:  - Un entero (1 o 0).
// Descipcion: estaEn busca en el arreglo el valor que se desea,
//             si se encuentra retorna 1, de lo contrario un 0.
int estaEn(int* arreglo, int valor, int largo);

// Entrada: - No posee.
// Salida:  - No posee.
// Descipcion: Esta función organiza el resto de funciones de tal manera
//             que entreguen los resultados de manera clara.
void iniciar();
