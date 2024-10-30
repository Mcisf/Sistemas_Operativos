/*##################################################################################################
#                                       Autor: Mateo Maldonado                                     #
#                                         Fecha: 29/10/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                          Tema: Conocimiento de standard POSIX - Pthreads                         #
#                              Topico:Productor consumidor con Pthreads                            #
####################################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int counter = 0;                // Contador compartido entre hilos productores y consumidores
int max = 4;                    // Número máximo de hilos productores y consumidores

// Declaración e inicialización de mutex y variables de condición para sincronización
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex para proteger el acceso a 'counter'
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex para el productor
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex para el consumidor
pthread_mutex_t condVarProd = PTHREAD_MUTEX_INITIALIZER;    // Variable de condición para el productor
pthread_mutex_t condVarCons = PTHREAD_MUTEX_INITIALIZER;    // Variable de condición para el consumidor

void *consumidor();  // Declaración de la función consumidor
void *productor();   // Declaración de la función productor

int main(int argc, char *argv[]){
    pthread_t prodHilo[max];     // Vector de hilos productores
    pthread_t consHilo[max];     // Vector de hilos consumidores

    // Creación de hilos productores y consumidores
    for(int i = 0; i < max; i++){
        pthread_create(&prodHilo[i], NULL, &productor, NULL);
        pthread_create(&consHilo[i], NULL, &consumidor, NULL);
    }

    // Espera la finalización de todos los hilos productores y consumidores
    for(int i = 0; i < max; i++){
        pthread_join(prodHilo[i], NULL);
        pthread_join(consHilo[i], NULL);
    }

    return 0;
}

/*
 * Función productor: incrementa el contador 'counter' mientras sea menor a 10.
 * Usa una variable de condición para esperar si el contador es igual o mayor a 10.
 * Notifica a los consumidores cuando el contador es incrementado.
 * Si el contador excede 7, el productor hace una pausa de 4 segundos.
*/
void *productor(){
  while(1){
      pthread_mutex_lock(&condp_mutex);
      while(counter >= 10) 
          pthread_cond_wait(&condVarProd, &condp_mutex);  // Espera hasta que 'counter' sea menor a 10
      pthread_mutex_unlock(&condp_mutex);

      pthread_mutex_lock(&counter_mutex);
      counter++;
      pthread_cond_signal(&condVarCons);  // Notifica al consumidor que el contador ha sido incrementado
      printf("Soy el PRODUCTOR %d || Contador = %d\n", pthread_self(), counter);
      pthread_mutex_unlock(&condp_mutex);
      pthread_mutex_unlock(&counter_mutex);

      if(counter > 7)
          sleep(4);  // Pausa de 4 segundos si el contador supera 7
  }
}

/*
 * Función consumidor: decrementa el contador 'counter' si es mayor a 0.
 * Usa una variable de condición para esperar si el contador es 0.
 * Notifica a los productores cuando el contador es decrementado.
*/
void *consumidor(){
  while(1){
      sleep(1);  // Pausa de 1 segundo entre cada intento de consumir

      pthread_mutex_lock(&condc_mutex);
      while(counter <= 0){
          pthread_cond_signal(&condVarProd);              // Notifica al productor si el contador es 0
          pthread_cond_wait(&condVarCons, &condc_mutex);  // Espera hasta que 'counter' sea mayor a 0
      }
      pthread_mutex_unlock(&condc_mutex);

      pthread_mutex_lock(&counter_mutex);
      if(counter > 0){
          printf("Soy el CONSUMIDOR %d || Contador = %d\n", pthread_self(), counter);
          counter--;
          pthread_cond_signal(&condVarProd);  // Notifica al productor que el contador ha sido decrementado
      }
      pthread_mutex_unlock(&counter_mutex);
      pthread_mutex_unlock(&condc_mutex);
  }
}
