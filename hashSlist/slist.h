#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include "tablahash.h"


#ifndef __FUNCIONIGUALDAD__
#define __FUNCIONIGUALDAD__
typedef int (*FuncionIgualdad)(void *, void *);
#endif

#ifndef __FUNCIONELIMINAR__
#define __FUNCIONELIMINAR__
typedef void (*FuncionEliminar)(void *);
#endif

#ifndef __LISTA__
#define __LISTA__
typedef struct _SNodo {
  void* dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;
#endif
/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista, FuncionEliminar elim);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar(SList lista, void* dato);

int slist_longitud(SList lista);

SList slist_eliminar(SList lista, void* dato, FuncionIgualdad comparar, FuncionEliminar elim, unsigned* cantElem);

/**
 *Determina si un elemento esta en una lista dada.
 */
void* slist_contiene(SList lista, void* dato, FuncionIgualdad comparar);

#endif /* __SLIST_H__ */












