/***************************************************************************
Pontificia Universidad Javeriana
Autor: Mateo Maldonado
Fecha: 23/07/2024
Materia: Sistemas Operativos
Tema: Programacion en C
Requerimientos:
        - Función que sume 2 enteros
        - Función que calcule el área de una circunferencia
        - Función que de la bienvenida
***************************************************************************/

#include <stdio.h>

/**Funcion que de la bienvenida**/
void bienvenida(){
  printf("Hola Mundo...\n");
  printf("\t\tBienvenidos a mi clase de SISTEMAS OPERATIVOS  :) \n");
}
/**Funcion que sume 2 enteros**/
void suma2enteros(){
  int prim=0, seg=0;
  printf("Primer entero es: ");
  scanf("%d",&prim);
  printf("Segundo entero es: ");
  scanf("%d",&seg);
  int suma=prim+seg;
  printf("El resultado es: %d\n", suma);
}
/**Función que calcule el área de una circunferencia**/
void areacircunferencia(){
  int radio = 0;
  float pi = 3.14;
  printf("El radio es: ");
  scanf("%d",&radio);
  float area = radio*radio*pi;
  printf("El area es: %f\n", area);
}

int main(int argc, char *argv[]){
  bienvenida();
  suma2enteros();
  areacircunferencia();
  
  
  return 0;
}