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
 * Este programa demuestra cómo manejar la entrada de argumentos de línea de comandos y entrada estándar.
 * 
 * - Lee argumentos de línea de comandos para edad, mes y nombre.
 * - Solicita al usuario que ingrese más información mediante la entrada estándar (color de cabello, año y día de nacimiento, color favorito y comida favorita).
 * - Imprime los datos ingresados para su verificación.
 */

int main(int argc, char *argv[]){
  int nacimiento=0, dia=0;
  char color[100], colorfav[100], comida[100];
  // Imprime el número de argumentos de línea de comandos ingresados
  printf("\n Ha ingresado [%d]: \n\n", argc);
  // Imprime los argumentos de línea de comandos
  printf("Ha ingresado la edad: %s\n\n", argv[1]);
  printf("\n Ha ingresado el mes: %s \n\n", argv[2]);
  printf("\n Ha ingresado el nombre: %s \n\n", argv[3]);
   // Solicita al usuario que ingrese su color de cabello
  printf("Digite su color de cabello: ");
  scanf("%s", color);
  // Solicita al usuario que ingrese su año de nacimiento
  printf("Digite su año de nacimiento: ");
  scanf("%d", &nacimiento);
  // Solicita al usuario que ingrese su día de nacimiento
  printf("Digite su dia de nacimiento: ");
  scanf("%d", &dia);
  // Solicita al usuario que ingrese su color favorito
  printf("Digite su color favorito: ");
  scanf("%s", colorfav);
  // Solicita al usuario que ingrese su comida favorita
  printf("Digite su comida favorita: ");
  scanf("%s", comida);
  
  printf("\n");
  return 0;
}
