/*##################################################################################################
#                                       Autor: Mateo Maldonado                                     #
#                                         Fecha: 24/09/2024                                        #
#                                    Materia: Sistemas Operativos                                  #
#                                 Tema: Pipe Named o FIFO o Tuberia                                #
#                               Topico: Comunicacion Uni-Direccional                               #
#                                               Cliente                                            #
####################################################################################################*/

#include <stdio.h>
#include <stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define FIFO_FILE "MYFIFO"
int main() {
  int fd;                 // Descriptor de archivo para abrir la FIFO
  int fin_proceso;        // Indicador para verificar si se ha recibido la señal de "fin"
  int cadena;             // Longitud de la cadena ingresada por el usuario
  char busMensaje[80];    // Buffer para almacenar el mensaje a enviar
  char senalFin[5];       // Buffer para la palabra "fin", que indica el final del proceso

  printf("\n \t\t >>>>>> Inicio Cliente <<<<<<< \n");
  printf("FIFO_CLIENT: Enviando mensajes, infinitamente, para finalizar ingrese \"fin\"\n");

  /* Abrimos la FIFO para escritura, creando el archivo si no existe */
  fd = open(FIFO_FILE, O_CREAT | O_WRONLY, 0666);

  /* Inicializamos la señal de fin como la cadena "fin" */
  strcpy(senalFin, "fin");

  /* Bucle infinito para enviar mensajes al servidor hasta que se ingrese "fin" */
  while (1) {
    /* Solicitar al usuario que ingrese un mensaje */
    printf("Ingrese mensaje: ");

    /* Leer la entrada del usuario desde stdin y almacenarla en busMensaje */
    fgets(busMensaje, sizeof(busMensaje), stdin);

    /* Obtener la longitud de la cadena ingresada */
    cadena = strlen(busMensaje);

    /* Eliminar el carácter de nueva línea ('\n') al final de la cadena */
    busMensaje[cadena - 1] = '\0';

    /* Comparar el mensaje ingresado con la señal de fin ("fin") */
    fin_proceso = strcmp(busMensaje, senalFin);

    /* Mostrar el resultado de la comparación: 0 si son iguales, distinto de 0 si no */
    printf("Resultado de la comparación: %d\n", fin_proceso);

    /* Si el mensaje no es "fin", lo enviamos por la FIFO */
    if (fin_proceso != 0) {
      /* Escribimos el mensaje en la FIFO */
      write(fd, busMensaje, strlen(busMensaje));

      /* Informar que el mensaje ha sido enviado con su tamaño */
      printf("Mensaje Enviado: \"%s\" y el tamaño es %d\n", busMensaje, (int)strlen(busMensaje));
    } 
    /* Si el mensaje es "fin", enviamos la señal de fin, cerramos el descriptor y terminamos el programa */
    else {
      /* Escribir el mensaje "fin" en la FIFO */
      write(fd, busMensaje, strlen(busMensaje));

      /* Informar que el mensaje de fin ha sido enviado */
      printf("Mensaje enviado: \"%s\" y el tamaño es %d\n", busMensaje, (int)strlen(busMensaje));

      /* Cerrar el descriptor de la FIFO */
      close(fd);

      /* Salir del bucle y finalizar el programa */
      break;
    }
  }

  return 0;  
}
