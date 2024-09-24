/*##################################################################################################
#                             Autores: Mateo Maldonado y Edward Quintero                           #
#                                         Fecha: 17/09/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                            Tema: Procesos y comunicación entre procesos                          #
#   Apertura de ficheros y valores con el formato "./taller_procesos N1 archivo00 N2 archivo01"    #
####################################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// Función para leer un archivo y cargar el arreglo dinámico
int *leer_fichero(const char *nombre_fichero, int N) {
  FILE *fichero = fopen(nombre_fichero, "r");
  if (!fichero) {
    perror("Error al abrir el fichero");
    exit(EXIT_FAILURE);
  }

  int *arreglo = (int *)malloc(N * sizeof(int));
  if (!arreglo) {
    perror("Error al reservar memoria");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < N; i++) {
    fscanf(fichero, "%d", &arreglo[i]);
  }

  fclose(fichero);
  return arreglo;
}

// Función para calcular la suma de un arreglo
int calcular_suma(int *arreglo, int N) {
  int suma = 0;
  for (int i = 0; i < N; i++) {
    suma += arreglo[i];
  }
  return suma;
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Parseamos los argumentos
  int N1 = atoi(argv[1]);
  char *archivo00 = argv[2];
  int N2 = atoi(argv[3]);
  char *archivo01 = argv[4];

  // Leemos los arreglos desde los ficheros
  int *arreglo00 = leer_fichero(archivo00, N1);
  int *arreglo01 = leer_fichero(archivo01, N2);

  // Pipes para la comunicación entre procesos
  int pipe_sumaA[2], pipe_sumaB[2], pipe_suma_total[2];
  pipe(pipe_sumaA);
  pipe(pipe_sumaB);
  pipe(pipe_suma_total);

  pid_t pid1, pid2, pid3;

  // Primer hijo: calcula la sumaA (arreglo00)
  if ((pid1 = fork()) == 0) {
    int sumaA = calcular_suma(arreglo00, N1);
    write(pipe_sumaA[1], &sumaA, sizeof(sumaA));
    exit(0);
  }

  // Segundo hijo: calcula la sumaB (arreglo01)
  if ((pid2 = fork()) == 0) {
    int sumaB = calcular_suma(arreglo01, N2);
    write(pipe_sumaB[1], &sumaB, sizeof(sumaB));
    exit(0);
  }

  // Tercer hijo: calcula la suma total (suma de arreglo00 + arreglo01)
  if ((pid3 = fork()) == 0) {
    int suma_total =
        calcular_suma(arreglo00, N1) + calcular_suma(arreglo01, N2);
    write(pipe_suma_total[1], &suma_total, sizeof(suma_total));
    exit(0);
  }

  // Proceso padre: espera los resultados de los hijos
  int sumaA, sumaB, suma_total;
  read(pipe_sumaA[0], &sumaA, sizeof(sumaA));
  read(pipe_sumaB[0], &sumaB, sizeof(sumaB));
  read(pipe_suma_total[0], &suma_total, sizeof(suma_total));

  // Imprime los resultados
  printf("Suma del archivo00: %d\n", sumaA);
  printf("Suma del archivo01: %d\n", sumaB);
  printf("Suma total: %d\n", suma_total);

  // Esperar a que los procesos hijos terminen
  wait(NULL);
  wait(NULL);
  wait(NULL);

  // Liberar la memoria
  free(arreglo00);
  free(arreglo01);

  return 0;
}
