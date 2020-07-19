#include <stdio.h>
#include <stdlib.h>
#include "tablahash.h"
#include "slist.h"

int iguales(void* clave1, void* clave2) {
  int* p = clave1;
  int* q = clave2;
  return *p == *q;
}

int iguales2(void* dato, void* clave) {
  CasillaHash* estructura = dato;
  int* c1 = estructura->clave;
  int* c2 = clave;
  return *c2 == *c1;
}

unsigned hash(void* clave) {
  int* p = clave;
  return *p;
}

int main(void) {
  int x = 42, y = 42, z = 3;
  TablaHash *th = tablahash_crear(10, hash, iguales2);

  tablahash_insertar(th, &x, &z);

  printf("z : %d\n", *((int *)tablahash_buscar(th, &x)));
  printf("z : %d\n", *((int *)tablahash_buscar(th, &y)));

  tablahash_eliminar(th, &x);

  tablahash_destruir(th);

  return 0;
}
