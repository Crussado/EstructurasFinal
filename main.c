#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interprete.h"
#include "Tp2/intervalo.h"
#include "hashSlist/tablahash.h"
#include "hashSlist/slist.h"
#include "Tp2/arbolIntervalo.h"

int iguales(void* casilla, void* clave2) {
  char* c1 = ((CasillaHash *)casilla)->clave, * c2 = clave2;
  return strcmp(c1, c2);
}

unsigned hash(void* clave) {
  char* c = clave;
  return (c[0] - '0');
}

//main es aquella que lleva a cabo la estructura del programa.
//main: Int->Char**->Int.
int main() {
  Accion comando = CREAR;
  TablaHash *th = tablahash_crear(25, hash, iguales);
  Intervalo intervalo;
  TipoConjunto conjuntoPor;
  CasillaHash* casilla;
  char* alias;
  Itree arbol;
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
          alias = malloc(sizeof(char)* (strlen(cadena1) + 1));
          strcpy(alias, cadena1);
          arbol = itree_crear();
          intervalo = inter_crear(conjunto[0], conjunto[1]);
          arbol = itree_insertar_avl(arbol, intervalo);
          tablahash_insertar(th, alias, arbol);
          break;
        case EXTENSION:
          alias = malloc(sizeof(char)* (strlen(cadena1) + 1));
          strcpy(alias, cadena1);
          arbol = itree_crear();
          for(int i = 0; i < largo; i++) {
            intervalo = inter_crear(conjunto[i], conjunto[i]);
            arbol = itree_insertar_avl(arbol, intervalo);
          }
          tablahash_insertar(th, alias, arbol);
          break;
        
        default:
          printf("fallo en el conjunto\n");
          break;
        }
        break;
      case IMPRIMIR:
        casilla = tablahash_buscar(th, cadena1);
        if(casilla == NULL)
          printf("No existe el conjunto\n");
        else {
          printf("%s: ", cadena1);
          arbol = obtener_dato(casilla);
          itree_recorrer_dfs(arbol, ITREE_RECORRIDO_IN);
          puts("");
        }
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
