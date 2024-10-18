/*##################################################################################################
#                                      Autores: Mateo Maldonado                                    #
#                                         Fecha: 17/10/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                     Tema: Computacion modular                                    #
#Apertura de ficheros y valores con el formato "./taller_procesos N1 archivo00 N2 archivo01 modulo"#
####################################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

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
        fclose(fichero);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++) {
        if (fscanf(fichero, "%d", &arreglo[i]) != 1) {
            perror("Error al leer del fichero");
            free(arreglo);
            fclose(fichero);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fichero);
    return arreglo;
}

// Función para calcular la suma modular de un arreglo
int calcular_suma_modular(int *arreglo, int N, int modulo) {
    int suma = 0;
    for (int i = 0; i < N; i++) {
        suma = (suma + arreglo[i]) % modulo;  // Suma modular
    }
    return suma;
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Uso: %s N1 archivo00 N2 archivo01 modulo\n", argv[0]); //Modulo hace referencia a el valor del módulo a aplicar en la suma.
        exit(EXIT_FAILURE);
    }

    // Parsear los argumentos
    int N1 = atoi(argv[1]);
    char *archivo00 = argv[2];
    int N2 = atoi(argv[3]);
    char *archivo01 = argv[4];
    int modulo = atoi(argv[5]);

    // Leer los arreglos desde los ficheros
    int *arreglo00 = leer_fichero(archivo00, N1);
    int *arreglo01 = leer_fichero(archivo01, N2);

    // Crear pipes para la comunicación entre procesos
    int pipe_sumaA[2], pipe_sumaB[2];
    if (pipe(pipe_sumaA) == -1 || pipe(pipe_sumaB) == -1) {
        perror("Error al crear el pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid1, pid2;

    // Primer hijo: calcula la suma modular del primer arreglo (arreglo00)
    if ((pid1 = fork()) == 0) {
        close(pipe_sumaA[0]);  // Cerrar el lado de lectura del pipe
        int sumaA_modular = calcular_suma_modular(arreglo00, N1, modulo);
        write(pipe_sumaA[1], &sumaA_modular, sizeof(sumaA_modular));
        close(pipe_sumaA[1]);  // Cerrar el lado de escritura después de usarlo
        exit(0);
    } else if (pid1 < 0) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    // Segundo hijo: calcula la suma modular del segundo arreglo (arreglo01)
    if ((pid2 = fork()) == 0) {
        close(pipe_sumaB[0]);  // Cerrar el lado de lectura del pipe
        int sumaB_modular = calcular_suma_modular(arreglo01, N2, modulo);
        write(pipe_sumaB[1], &sumaB_modular, sizeof(sumaB_modular));
        close(pipe_sumaB[1]);  // Cerrar el lado de escritura después de usarlo
        exit(0);
    } else if (pid2 < 0) {
        perror("Error en fork");
        exit(EXIT_FAILURE);
    }

    // Proceso padre: espera los resultados de los hijos
    int sumaA_modular, sumaB_modular;
    close(pipe_sumaA[1]);  // Cerrar el lado de escritura del pipe
    close(pipe_sumaB[1]);

    read(pipe_sumaA[0], &sumaA_modular, sizeof(sumaA_modular));
    read(pipe_sumaB[0], &sumaB_modular, sizeof(sumaB_modular));

    close(pipe_sumaA[0]);  // Cerrar el lado de lectura después de usarlo
    close(pipe_sumaB[0]);

    // Calcular la suma total modular
    int suma_total_modular = (sumaA_modular + sumaB_modular) % modulo;

    // Imprime los resultados
    printf("Suma modular del archivo00: %d\n", sumaA_modular);
    printf("Suma modular del archivo01: %d\n", sumaB_modular);
    printf("Suma total modular: %d\n", suma_total_modular);

    // Esperar a que los procesos hijos terminen
    wait(NULL);
    wait(NULL);

    // Liberar la memoria reservada
    free(arreglo00);
    free(arreglo01);

    return 0;
}
