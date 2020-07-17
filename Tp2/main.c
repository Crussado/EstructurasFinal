#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "intervalo.h"
#include "arbolIntervalo.h"
#include "interprete.h"

//main es aquella que lleva a cabo la estructura del programa.
//main: Int->Char**->Int.
int main() {
    
  char ingreso[50];
  int caso = 0;
  Intervalo insertar;
  Itree arbol = itree_crear();
  Intervalo aux;
  int x, y;
  while(caso != 6) {
    printf("Introduzca el comando: ");
    fgets(ingreso, 50, stdin);
    caso = analizar_comando(ingreso, &x, &y); 
    switch(caso) {
      case 1: 
        insertar = inter_crear(x, y);
        arbol = itree_insertar_avl(arbol, insertar);
        break;
      case 2: 
        aux.compx = x;
        aux.compy = y;
        arbol = itree_eliminar(arbol, aux);
        break;
      /*case 3: 
        aux.compx = x;
        aux.compy = y;
        interseccion = itree_intersectar(arbol, &aux);
        if(interseccion == NULL)
          printf("No\n");
        else {
          printf("Si, ");
          inter_imprimir(interseccion->intervalo);
          puts("");
        }
        break;*/
      case 4: 
        itree_recorrer_dfs(arbol, ITREE_RECORRIDO_IN);
        puts("");
        break;
      default:
        break;
    }
  }
  itree_destruir(arbol);
  return 0;
}
