#include "slist.h"
#include <stdlib.h>
#include <stdio.h>
#include "tablahash.h"

SList slist_crear() {
  return NULL;
}

void slist_destruir(SList lista, FuncionEliminar elim) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    elim(nodoAEliminar->dato);
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar(SList lista, void* dato, void* clave, FuncionIgualdad comparar, unsigned* cantElem) {
  SList aux = lista;
  int termine = 0;
  for(; aux != NULL && !termine; aux = aux->sig) {
    if(comparar(lista->dato, clave) == 0) {
      actualizar_dato(lista->dato, dato);
      destruir_clave(clave);
      termine = 1;
    }
  }
  if(!termine) {
    SNodo *nuevoNodo = malloc(sizeof(SNodo));
    nuevoNodo->dato = crear_casilla(clave, dato);
    nuevoNodo->sig = lista;
    return nuevoNodo;
    *cantElem = *cantElem + 1;
  }
  return lista;
}

int slist_longitud(SList lista){
  int cont=0;
  for(;lista!=NULL;lista = lista->sig,cont++);
  return cont;
}

SList slist_eliminar(SList lista, void* clave, FuncionIgualdad comparar, FuncionEliminar elim, unsigned* cant){
  if(lista==NULL)
    return NULL;

  if(comparar(lista->dato, clave) == 0){
    SList aux = lista->sig;
    elim(lista->dato);
    free(lista);
    *cant = *cant - 1;
    return aux;
  }

  SList padre = lista, hijo = padre->sig;
  int encontrado = 0;

  while(hijo != NULL && !encontrado) {
    if(comparar(hijo->dato, clave) == 0)
      encontrado = 1;
    else {
      hijo = hijo->sig;
      padre = padre->sig;
    }
  }
  if(encontrado) {
    padre->sig = hijo->sig;
    elim(hijo->dato);
    free(hijo);
    *cant = *cant - 1;
  }
  return lista;
}

void* slist_contiene(SList lista, void* clave, FuncionIgualdad comparar){
  void* aux = NULL;

  for(; lista != NULL && aux == NULL; lista = lista->sig)
    if(comparar(lista->dato, clave) == 0)
      aux = lista->dato;
  return aux;
}
