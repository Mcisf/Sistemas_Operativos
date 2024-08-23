/*##################################################################################################
#                                    Autor: Mateo Maldonado Diaz                                   #
#                                         Fecha: 23/08/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                      Tema: Gestión de memoria                                    #
#          redimension dinámica de un array en tiempo de ejecución con la funcion realloc()        #
####################################################################################################*/

#include <stdio.h>
#include <stdlib.h>

// Este programa asigna un array dinámicamente, lo redimensiona con realloc y muestra los valores antes y después.
int main() {
    int *array;
    int i;

    // Asignamos memoria para 5 enteros con la funcion malloc()
    array = (int *)malloc(5 * sizeof(int));
    if (array == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    // Inicializamos el array con valores
    for (i = 0; i < 5; i++) {
        array[i] = i + 1;
    }

    // Mostramos el contenido inicial del array
    printf("Contenido inicial del array:\n");
    for (i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Reasignamos memoria para 10 enteros
    int new_size = 10;
    int *temp = realloc(array, new_size * sizeof(int));
    if (temp == NULL) {
        printf("Error al reasignar memoria.\n");
        free(array); // Liberamos la memoria original
        return 1;
    }
    array = temp;

    // Inicializamos los nuevos elementos del array
    for (i = 5; i < new_size; i++) {
        array[i] = i + 1;
    }

    // Mostramos el contenido del array después de realloc
    printf("Contenido del array después de realloc:\n");
    for (i = 0; i < new_size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Liberamos la memoria cuando ya no se necesita
    free(array);

    return 0;
}
