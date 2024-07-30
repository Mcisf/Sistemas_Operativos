/*##################################################################################################
#                                    Autor: Mateo Maldonado Diaz                                   #
#                                         Fecha: 30-07-2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                  Tema: Argumentos de entrada en c                                #
####################################################################################################*/

#include <stdio.h>

/*Al inicio debe enviar el programa con el valor de la edad*/
/*Se presentan una serie de preguntas que el usuario debe responder*/

int main(int argc, char *argv[]){
  int nacimiento=0, dia=0;
  char color[100], colorfav[100], comida[100];
  printf("\n Ha ingresado [%d]: \n\n", argc);
  printf("Ha ingresado la edad: %s\n\n", argv[1]);
  printf("\n Ha ingresado el mes: %s \n\n", argv[2]);
  printf("\n Ha ingresado el nombre: %s \n\n", argv[3]);
  printf("Digite su color de cabello: ");
  scanf("%s", color);
  printf("Digite su año de nacimiento: ");
  scanf("%d", &nacimiento);
  printf("Digite su dia de nacimiento: ");
  scanf("%d", &dia);
  printf("Digite su color favorito: ");
  scanf("%s", colorfav);
  printf("Digite su comida favorita: ");
  scanf("%s", comida);
  
  printf("\n");
  return 0;
}
