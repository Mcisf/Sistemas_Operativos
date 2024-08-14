/*##################################################################################################
#                                    Autor: Mateo Maldonado Diaz                                   #
#                                         Fecha: 30-07-2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                  Tema: Argumentos de entrada en c                                #
####################################################################################################*/

#include <stdio.h>

/*Al inicio debe enviar el programa con el valor de la edad*/
/*Se presentan una serie de preguntas que el usuario debe responder*/

/*
 Este programa demuestra el uso de argumentos de línea de comandos y punteros en C.
  
 - Imprime los argumentos de línea de comandos recibidos al ejecutar el programa.
 - Muestra el valor y la dirección de una variable entera utilizando punteros.
 - Calcula y muestra la diferencia en posiciones entre dos punteros que apuntan a elementos en un arreglo.
 */

int main(int argc, char *argv[]){
  int nacimiento=0, dia=0;
  char color[100], colorfav[100], comida[100];
  // Imprime el número de argumentos de línea de comandos
  printf("\n Ha ingresado [%d]: \n\n", argc);
  // Imprime el primer argumento (edad)
  printf("Ha ingresado la edad: %s\n\n", argv[1]);
  // Imprime el segundo argumento (mes)
  printf("\n Ha ingresado el mes: %s \n\n", argv[2]);

  // Inicializa una variable entera
  int x=102;
  // Declara un puntero a entero y le asigna un valor entero
  int *p=x;
  // Imprime el valor de la variable x
  printf("\n El valor de X es de: %d \n", x);
  // Imprime la dirección de la variable x usando el puntero
  printf("\n La direccion de X es: %p \n\n",p);

  // Inicializa un arreglo de enteros
  int vector[] = {5,10,20,30,40,50,80};
  // Declara punteros para el inicio del arreglo y para una posición fuera del rango del arreglo
  int *p1=vector;
  int *p2=vector+20;
  // Calcula la diferencia en posiciones entre los dos punteros
  int diferencia=p2-p1;
  // Imprime los valores de los punteros
  printf("\n El valor de p1 es de: %p \n", p1);
  printf("\n El valor de p2 es de: %p \n", p2);
  // Imprime la diferencia en posiciones entre los punteros
  printf("\n El valor resta de: %d \n", diferencia);
    
  return 0;
}
