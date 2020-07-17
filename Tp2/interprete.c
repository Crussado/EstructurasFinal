#include "interprete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//analizar_comando toma un comando ingresado, lo analiza verificando si es correcto,
//y devuelve una bandera dependiendo de cual sea el caso. Ademas de almacenar el intervalo
//si es necesario.
//analizar_comando: Char*->Double*->Double*->Int
int analizar_comando(char *ingreso, int* x, int* y) {
  if(strcmp(ingreso, "salir\n") == 0)
    return 6;
  if(strcmp(ingreso, "dfs\n") == 0) 
    return 4;
  if(strcmp(ingreso, "bfs\n") == 0) 
    return 5;
  char comando, resto[50], espacio;
  if(sscanf(ingreso, "%c%c[%d, %d%s", &comando, &espacio, x, y, resto) == 5){
    if((strcmp(resto, "]") == 0) && (*x <= *y) && (espacio == ' ')) {
      if(comando == 'i')
        return 1;
      if(comando == 'e')
        return 2;
      if(comando == '?')
        return 3;
      printf("Comando invalido\n");  
    }
    else if ((strcmp(resto, "]") != 0) || (espacio != ' '))
      printf("Comando invalido\n");
    else 
      printf("Rango invalido\n");
  }
  else
    printf("Comando invalido\n");
  
  return 7;
}