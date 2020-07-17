#ifndef __ARBOLINTERVALO_H__
#define __ARBOLINTERVALO_H__

#include <stddef.h>
#include "intervalo.h"

typedef enum {
  ITREE_RECORRIDO_IN,
  ITREE_RECORRIDO_PRE,
  ITREE_RECORRIDO_POST
} BTRecorrido;

typedef struct _BTIntervalo {
  int maxDerecha;
  int altura;
  struct _BTIntervalo *left;
  struct _BTIntervalo *right;
  Intervalo intervalo;
} BTIntervalo;

typedef BTIntervalo *Itree;

Itree itree_crear ();

void itree_destruir(Itree arbol);
 
Itree itree_insertar_avl(Itree arbol, Intervalo dato);

Itree itree_eliminar(Itree arbol, Intervalo dato);

Itree itree_intersectar(Itree arbol, PIntervalo dato);

void itree_recorrer_dfs(Itree arbol, BTRecorrido orden);

int itree_altura(Itree arbol);

#endif /* __ARBOLINTERVALO_H__ */
