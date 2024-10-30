/*##################################################################################################
#                                       Autor: Mateo Maldonado                                     #
#                                         Fecha: 29/10/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                           Tema: Pthread                                          #
#                           Topico: Creación y manejo básico de hilos en C                         #
####################################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/* 
 * Función para ejecutar en cada hilo. 
 * Recibe un argumento que representa el número del trabajo 
 * e imprime el identificador del trabajo.
*/

static void *funcion(void *argumentos){
  size_t job = *(size_t *)argumentos;
  printf("\n\t Job %zu \n", job);
  return NULL;
}

int main (int argc, char *argv[]){
  // Conversión del argumento de entrada en número de hilos a crear
  int N = (int)atoi(argv[1]);

  size_t jobs[N];                // Vector para almacenar el identificador de cada trabajo
  pthread_t hilos[N];            // Vector para almacenar los identificadores de cada hilo

  // Bucle para crear y asignar trabajos a cada hilo
  for(int i = 0; i < N; i++){
    jobs[i] = i;
    // Creación de hilos y asignación de la función a ejecutar
    pthread_create(&hilos[i], NULL, funcion, jobs + i);
  }

  // Bucle para esperar la finalización de cada hilo
  for(int i = 0; i < N; i++){
    pthread_join(hilos[i], NULL);
  }

  return 0;
}
