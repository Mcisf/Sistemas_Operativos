/*##################################################################################################
#                                 Pontificia Universidad Javeriana                                 #
#                                    Autor: Mateo Maldonado Diaz                                   #
#                                         Fecha: 06/08/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                      Tema: Evaluacion del rendimiento de Sistemas de Computo                     #
####################################################################################################*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Definición del tamaño de la reserva de memoria para las matrices.
#define DATA_RESERVA (1024*1024*64*3)
static double MEM_CHUNK[DATA_RESERVA];

/******** Función para multiplicar las matrices ********
 * Mult_Matriz realiza la multiplicación de dos matrices cuadradas y almacena el resultado en una tercera matriz.
 *
 * Parámetros:
 * - int SZ: Tamaño de la matriz (la matriz es de tamaño SZxSZ).
 * - double *a: Puntero a la primera matriz.
 * - double *b: Puntero a la segunda matriz.
 * - double *c: Puntero a la matriz de resultados.
 */
void Mult_Matriz(int SZ, double *a, double *b, double *c){
  int i, j, k;
  for(i=0;i<SZ;i++){
    for(j=0;j<SZ;j++){
      double *pA, *pB, SumaTemp;
      SumaTemp = 0.0;
      pA = a+(i*SZ); // Puntero a la fila i de la matriz 'a'
      pB = b+j;      // Puntero a la columna j de la matriz 'b'
      for(k=SZ;k>0;k--, pA++, pB+=SZ){
        SumaTemp += (*pA * *pB);
      }
      c[i*SZ+j] = SumaTemp; // Almacena el resultado en la matriz 'c'
    }
  }
}

/******** Función para inicializar las matrices ********
 * Init_Matriz inicializa dos matrices con valores específicos y la tercera matriz con un valor fijo.
 *
 * Parámetros:
 * - int SZ: Tamaño de la matriz (la matriz es de tamaño SZxSZ).
 * - double *a: Puntero a la primera matriz que será inicializada con 2.3*(j+k).
 * - double *b: Puntero a la segunda matriz que será inicializada con 3.2*(j-k).
 * - double *c: Puntero a la matriz de resultados que será inicializada con 1.3.
 */
void Init_Matriz(int SZ, double *a, double *b, double *c){
  int i, j, k;
  for(k=0;k<SZ;k++){
    for(j=0;j<SZ;j++){
      a[j+k*SZ] = 2.3*(j+k);
      b[j+k*SZ] = 3.2*(j-k);
      c[j+k*SZ] = 1.3;
    }
  }
}

/******** Función para imprimir la matriz ********
 * Print_Matriz imprime una matriz en formato de tabla.
 *
 * Parámetros:
 * - int SZ: Tamaño de la matriz (la matriz es de tamaño SZxSZ).
 * - double *a: Puntero a la matriz que se va a imprimir.
 */
void Print_Matriz(int SZ, double *a){
  int j, k;
  for(k=0;k<SZ;k++){
    for(j=0;j<SZ;j++){
      printf(" %f ", a[j+k*SZ]);
    }
    printf("\n");
  }
  printf("----------------------------------------------\n");
}

int main(int argc, char *argv[]){
// Verifica si se han proporcionado los argumentos necesarios
  if (argc < 2){
    printf(" ./MatMult MatrizSize NumHilos ....\n\n");
    return -1;
  }
  // Lee el tamaño de la matriz y el número de hilos desde los argumentos de la línea de comandos
  int N = (int) atof(argv[1]);
  int h = (int) atof(argv[2]);
  // Punteros para las matrices
  double *A, *B, *C;
  /*Reserva de memoria inicial de las matrices*/
  A = MEM_CHUNK;
  B = A + N*N;
  C = B + N*N;
  // Imprime los valores ingresados
  printf("Valores ingresados: \n");
  printf("Matriz Size (NxN): %dx%d \n",N, N);
  printf("Numero de Hilos (h): %d \n", h);
  // Inicializa las matrices
  Init_Matriz(N, A, B, C);
  // Imprime las matrices si el tamaño es menor a 9
  if (N<9){
    Print_Matriz(N, A);
    Print_Matriz(N, B);
  }
  // Realiza la multiplicación de matrices
  Mult_Matriz(N, A, B, C);
  // Imprime la matriz resultado si el tamaño es menor a 9
  if (N<9){
    Print_Matriz(N, C);
  }
  return 0;
}
