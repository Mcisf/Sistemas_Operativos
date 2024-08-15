/*##################################################################################################
#                                    Autor: Mateo Maldonado Diaz                                   #
#                                         Fecha: 30-07-2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                  Tema: Argumentos de entrada en c                                #
####################################################################################################*/

/*
 Este programa muestra cómo trabajar con diferentes tipos de datos en C,
 incluyendo enteros, flotantes, dobles, caracteres, booleanos y punteros.
  
 - Declara e inicializa variables de varios tipos de datos.
 - Usa un puntero para mostrar la dirección de una variable.
 - Imprime los valores y las direcciones de las variables en un formato tabular.
 */

#include <stdio.h>
#include <stdbool.h>

/* Crear una tabla con cada tipo de dato en C */

int main(int argc, char *argv[]) {
    // Declaración e inicialización de variables
    int entero = 5;
    float flotante = 3.4;
    double doble = 4.3;
    char caracter = 's';
    bool boleano = false;
    long long largo = 35357263576358629;
    // Declaración de un puntero a entero y asignación de la dirección de 'entero'
    int *p = &entero; 

    // Impresión de los valores y direcciones de las variables en formato tabular
    printf("##############################\n");
    printf("# Tipo       | Valor         #\n");
    printf("##############################\n");
    printf("# Entero     | %d            #\n", entero);
    printf("# Flotante   | %f            #\n", flotante);
    printf("# Doble      | %f            #\n", doble);
    printf("# Char       | %c            #\n", caracter);
    printf("# Bool       | %d            #\n", boleano);
    printf("# Long long  | %lld          #\n", largo);
    printf("# Puntero    | %p            #\n", (void *)p);
    printf("##############################\n");

    return 0;
}
