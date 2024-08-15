/*##################################################################################################
#                                    Autor: Mateo Maldonado Diaz                                   #
#                                         Fecha: 13/08/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                      Tema: Gestión de memoria                                    #
#                            Reserva de memoria con la función memalloc()                          #
####################################################################################################*/

/*
  Este programa demuestra cómo utilizar la función malloc para reservar memoria dinámica
  para arreglos de enteros, manipular y acceder a los valores almacenados, y luego liberar la memoria.
 
  - Se reserva memoria para dos arreglos de enteros usando malloc.
  - Se inicializan y muestran los valores del primer arreglo.
  - Se asigna un valor a una posición específica en el segundo arreglo y se muestra.
  - Finalmente, se libera la memoria reservada para ambos arreglos antes de terminar el programa.
 */

#include <stdio.h>
#include <stdlib.h>

int main(){
  // Reserva memoria para un arreglo de 4 enteros usando malloc
  int *bloque00 = malloc(4*sizeof(int)); 
  // Reserva memoria para un arreglo de 15 enteros usando malloc
  int *puntero = malloc(15*sizeof(*puntero));

  // Inicializa y muestra los valores del arreglo 'bloque00'
  for(int i=0; i<4; i++){
    bloque00[i] = i*2;
    printf("El valor de memoria reservada de Bloque00[%d] = %d\n\n", i, bloque00[i]);
  }

   // Verifica si la memoria para 'puntero' se reservó correctamente
  if(puntero!= NULL){
    // Asigna un valor a la 9na posición del arreglo 'puntero'
    *(puntero+8) = 9889; 
    // Muestra el valor asignado usando notación de puntero
    printf("El valor de la 9na posición de puntero[%d] = %d\n\n", *(puntero+8));
    // Muestra el valor asignado usando notación de índice
    printf("El valor de la 9na posición de puntero[%d] = %d\n\n", puntero[8]);
  }

  // Libera la memoria reservada para los arreglos
  free(bloque00);
  free(puntero);

  return 0;
}
