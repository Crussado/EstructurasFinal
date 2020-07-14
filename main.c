#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interprete.h"

//main es aquella que lleva a cabo la estructura del programa.
//main: Int->Char**->Int.
int main() {
  Accion comando = CREAR;
  TipoConjunto conjuntoPor;
  int conjunto[MAX_BUFF], largo;
  char ingreso[MAX_BUFF], cadena1[MAX_BUFF], cadena2[MAX_BUFF], cadena3[MAX_BUFF];
  while(comando != SALIR) {
    printf("Introduzca el comando: ");
    fgets(ingreso, MAX_BUFF, stdin);
    comando = analizar_comando(ingreso, cadena1, cadena2, cadena3); 
    switch(comando) {
      case CREAR: 
        conjuntoPor = verificar_conjunto(cadena2, conjunto, &largo);
        switch (conjuntoPor) {
        case COMPRESION:
          printf("el conjunto %s por compresion es: %d %d\n", cadena1, conjunto[0], conjunto[1]);
          break;
        case EXTENSION:
          printf("el conjunto %s por extension es: \n", cadena1);
          for(int i = 0; i < largo; i++)
            printf("%d, ", conjunto[i]);
            printf("\n%d",largo);
          break;
        
        default:
          printf("fallo en el conjunto");
          break;
        }
        break;
      case IMPRIMIR: 
        printf("imprimo el conjunto %s", cadena1);
        break;
      case UNIR: 
        printf("%s = %s union %s\n", cadena1, cadena2, cadena3);
        break;
      case INTERSECTAR: 
        printf("%s = %s interseccion %s\n", cadena1, cadena2, cadena3);
        break;
      case RESTAR: 
        printf("%s = %s menos %s\n", cadena1, cadena2, cadena3);
        break;
      case COMPLEMENTO:
        printf("%s = complemento de %s\n", cadena1, cadena2); 
        break;
      case FALLO:
        printf("error en el comando\n");
        break;
      default:
        printf("no vimo\n");
        break;
    }
  }
  return 0;
}
