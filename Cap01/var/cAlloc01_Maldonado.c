/*##################################################################################################
#                                    Autor: Mateo Maldonado Diaz                                   #
#                                         Fecha: 13/08/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                      Tema: Gestión de memoria                                    #
#                         Tópico: Reserva de memoria con la función memalloc()                     #
####################################################################################################*/

/*
  Este programa demuestra cómo utilizar la función calloc para reservar memoria dinámica
  para arreglos de enteros, inicializar los valores de los arreglos y luego liberar la memoria.
 
  - Se reserva memoria para tres arreglos de enteros con diferentes tamaños utilizando calloc.
  - Se llena uno de los arreglos con una secuencia de enteros y se imprimen sus valores.
  - Finalmente, se libera la memoria reservada para los arreglos antes de terminar el programa.
 */

#include <stdio.h>
#include <stdlib.h>

int main(){
  // Reserva memoria para un arreglo de 4 enteros usando calloc
  int *p1 = calloc(4,sizeof(int)); 
  // Reserva memoria para un arreglo de 10 enteros usando calloc
  int *puntero = calloc(10,sizeof(int)); 
  // Reserva memoria para un arreglo de 5 enteros usando calloc y utilizando sizeof*p3 para el tamaño de cada elemento
  int *p3 = calloc(5,sizeof*p3); 

  // Mensaje inicial que indica la construcción y cálculo de la secuencia de los primeros 10 términos
  printf("construcción y calculo de la secuencia de los primeros 10 terminos \n");

   // Itera sobre los primeros 10 elementos
  for(int i=0;i<10;i++){  
    // Asigna el valor de i a cada posición del arreglo 'puntero'
    *(puntero+i) = i; 
    // Imprime el valor actual de la secuencia
    printf("El valor de la secuencia es %d\n\n", *(puntero+i));
  }
  // Libera la memoria reservada para los arreglos
  free(puntero);  
  free(p1); 
  free(p3);
  return 0;
}
