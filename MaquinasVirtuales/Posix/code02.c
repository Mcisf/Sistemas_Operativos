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

int counter = 0;                // Contador compartido entre productor y consumidor
int max = 4;                    // Número máximo de hilos productores y consumidores

// Declaración e inicialización de mutex y variables de condición para sincronización
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;  // Mutex para proteger el acceso a 'counter'
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex para el productor
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex para el consumidor
pthread_mutex_t condVarProd = PTHREAD_MUTEX_INITIALIZER;    // Variable de condición para el productor
pthread_mutex_t condVarCons = PTHREAD_MUTEX_INITIALIZER;    // Variable de condición para el consumidor

void *consumidor();            // Declaración de la función consumidor
static void *productor();      // Declaración de la función productor

int main (int argc, char *argv[]){
  pthread_t prodHilo[max];     // Vector de hilos productores
  pthread_t consHilo[max];     // Vector de hilos consumidores

  // Creación de hilos de productores y consumidores
  for(int i = 0; i < max; i++){
    pthread_create(&prodHilo[i], NULL, &productor, NULL);
    pthread_create(&consHilo[i], NULL, &consumidor, NULL);
  }

  // Espera a la finalización de todos los hilos de productores y consumidores
  for(int i = 0; i < max; i++){
    pthread_join(prodHilo[i], NULL);
    pthread_join(consHilo[i], NULL);
  }

  return 0;
}

/*
 * Función productor: incrementa el contador 'counter' cuando está por debajo de 10.
 * Utiliza una variable de condición para esperar cuando 'counter' es 10 o más.
 * Cuando el contador es incrementado, se envía una señal al consumidor.
 * Si el contador llega a 5, el productor duerme por 2 segundos.
*/
static void *productor(){
  while(1){
    pthread_mutex_lock(&condp_mutex);
    while(counter >= 10){
      pthread_cond_wait(&condVarProd, &condp_mutex);   // Espera hasta que 'counter' sea menor que 10
    }
    pthread_mutex_unlock(&condp_mutex);

    pthread_mutex_lock(&counter_mutex);
    counter++;
    pthread_cond_signal(&condVarCons);  // Notifica al consumidor que el contador ha sido incrementado
    printf("Soy el Productor %d || Contador = %d\n", pthread_self(), counter);
    pthread_mutex_unlock(&condp_mutex);
    pthread_mutex_unlock(&counter_mutex);

    if(counter == 5)
      sleep(2);  // Pausa de 2 segundos si el contador llega a 5
  }
}

/*
 * Función consumidor: decrementa el contador 'counter' si es mayor a 0.
 * Usa una variable de condición para esperar si el contador está en 0.
 * Notifica al productor cuando 'counter' es decrementado.
*/
void *consumidor(){
  while(1){
    sleep(1);  // Pausa de 1 segundo entre cada intento de consumir

    pthread_mutex_lock(&condp_mutex);
    while(counter <= 0){
      pthread_cond_signal(&condVarProd);              // Notifica al productor si el contador está en 0
      pthread_cond_wait(&condVarCons, &condc_mutex);  // Espera hasta que 'counter' sea mayor a 0
    }
    pthread_mutex_unlock(&condc_mutex);

    pthread_mutex_lock(&counter_mutex);
    if(counter > 0){
      printf("Soy el Consumidor %d || Contador = %d\n", pthread_self(), counter);
      counter--;
      pthread_cond_signal(&condVarProd);  // Notifica al productor que el contador ha sido decrementado
    }
    pthread_mutex_unlock(&counter_mutex);
    pthread_mutex_unlock(&condc_mutex);
  }  
}
