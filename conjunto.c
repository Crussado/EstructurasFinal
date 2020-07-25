#include "Tp2/arbolIntervalo.h"
#include "Tp2/intervalo.h"
#include "hashSlist/tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conjunto.h"

int iguales(void* casilla, void* clave2) {
  char* c1 = ((CasillaHash *)casilla)->clave, * c2 = clave2;
  return strcmp(c1, c2);
}

unsigned hash(void* clave) {
  char* c = clave;
  return (c[0] - '0');
}

void eliminarDato(void* arbol) {
  Itree a = arbol;
  itree_destruir(a);
}

void eliminarClave(void* clave) {
  free(clave);
}

void conjuntos_destruir(Conjuntos* conjunto) {
  tablahash_destruir(conjunto->tabla);
  free(conjunto);
}

Conjuntos* conjuntos_crear() {
  Conjuntos* conjuntos = malloc(sizeof(Conjuntos));
  conjuntos->tabla = tablahash_crear(25, hash, iguales, eliminarDato, eliminarClave);
  return conjuntos;
}

void conjuntos_imprimir(Conjuntos* conjunto, char* alias) {
  CasillaHash* casillaBuscada = tablahash_buscar(conjunto->tabla, alias);
  if(casillaBuscada != NULL) {
    //printf("%s = {", alias);
    itree_recorrer_dfs(casilla_obtener_dato(casillaBuscada), ITREE_RECORRIDO_IN);
    puts("");
  }
  else
  printf("No existe el conjunto\n");
  
}

void conjuntos_insertar(Conjuntos* conjunto, char* alias, int* numeros, int longitud, int forma) {
  Intervalo intervalo;
  Itree arbol = itree_crear();
  char* nombre = malloc(sizeof(char)* (strlen(alias) + 1));
  strcpy(nombre, alias);
  if(forma == 1) { //comprension
    if(longitud != 0) {
      intervalo = inter_crear(numeros[0], numeros[1]);
      arbol = itree_insertar_avl(arbol, intervalo);
    }
  }
  else { //extension
    for(int i = 0; i < longitud; i++) {
      intervalo = inter_crear(numeros[i], numeros[i]);
      arbol = itree_insertar_avl(arbol, intervalo);
    }
  }
  tablahash_insertar(conjunto->tabla, nombre, arbol);
}

void conjuntos_unir(Conjuntos* conjunto, char* alias1, char* alias2, char* alias3) {
  Itree arbol2, arbol3, arbol1;
  CasillaHash* casilla2, * casilla3;
  casilla2 = tablahash_buscar(conjunto->tabla, alias2);
  casilla3 = tablahash_buscar(conjunto->tabla, alias3);
  if(casilla3 == NULL || casilla2 == NULL)
    printf("No existen los conjuntos\n");
  else {
    arbol2 = casilla_obtener_dato(casilla2);
    arbol3 = casilla_obtener_dato(casilla3);
    if(arbol2 == arbol3) {
      if(strcmp(alias1, alias2) == 0) // A = A U A
        return;
      else  // B = A U A
        arbol1 = itree_copiar(arbol2);
    }
    else if(strcmp(alias1, alias2) == 0) // A = A U B
      arbol1 = itree_unir(arbol2, arbol3);
    else if(strcmp(alias1, alias3) == 0) // A = B U A
      arbol1 = itree_unir(arbol3, arbol2);
    else { // A = B U C
      arbol1 = itree_copiar(arbol3);
      arbol1 = itree_unir(arbol1, arbol2);
    }
    char* nombre = malloc(sizeof(char)* (strlen(alias1) + 1));
    strcpy(nombre, alias1);
    tablahash_insertar(conjunto->tabla, nombre, arbol1);
  }
}

void conjuntos_intersectar(Conjuntos* conjunto, char* alias1, char* alias2, char* alias3) {
  Itree arbol2, arbol3, arbol1;
  CasillaHash* casilla2, * casilla3;
  casilla2 = tablahash_buscar(conjunto->tabla, alias2);
  casilla3 = tablahash_buscar(conjunto->tabla, alias3);
  if(casilla3 == NULL || casilla2 == NULL)
    printf("No existen los conjuntos\n");
  else {
    arbol2 = casilla_obtener_dato(casilla2);
    arbol3 = casilla_obtener_dato(casilla3);
    if(arbol2 == arbol3) {
      if(strcmp(alias1, alias2) == 0) // A = A n A
        return;
      else  // B = A n A
        arbol1 = itree_copiar(arbol2);
    }
    else {
      arbol1 = itree_crear();
      arbol1 = itree_intersectar(arbol1, arbol2, arbol3);
    }
    char* nombre = malloc(sizeof(char)* (strlen(alias1) + 1));
    strcpy(nombre, alias1);
    tablahash_insertar(conjunto->tabla, nombre, arbol1);
  }
}
