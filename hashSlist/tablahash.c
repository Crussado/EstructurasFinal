#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "slist.h"
#include "../Tp2/arbolIntervalo.h"
/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */

void destruir_clave(void* clave) {
  free(clave);
}

void destruir_dato(void* dato) {
  itree_destruir(dato);
}

void eliminarCasilla (void* casilla) {
  destruir_clave(((CasillaHash *)casilla)->clave);
  destruir_dato(((CasillaHash *)casilla)->dato);
}

void* obtener_clave(CasillaHash* casilla) {
  return casilla->clave;
}

void* obtener_dato(CasillaHash* casilla) {
  return casilla->dato;
}

void actualizar_dato(CasillaHash* casilla, void* dato) {
  destruir_dato(casilla->dato);
  casilla->dato = dato;
}

CasillaHash* crear_casilla(void* clave, void* dato) {
  CasillaHash* casilla = malloc(sizeof(CasillaHash));
  casilla->dato = dato;
  casilla->clave = clave;
  return casilla;
}

TablaHash* tablahash_crear(unsigned capacidad, FuncionHash hash, FuncionIgualdad igual) {
  // Pedimos memoria para la estructura principal y las casillas.
  TablaHash* tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(SList) * capacidad);
  tabla->numElems = 0;
  tabla->igual = igual;

  // Inicializamos las casillas con datos nulos.
  for (unsigned idx = 0; idx < capacidad; ++idx)
    tabla->tabla[idx] = slist_crear();

  return tabla;
}

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  printf("2");
  tabla->tabla[idx] = slist_agregar(tabla->tabla[idx], dato, clave, tabla->igual, &(tabla->numElems));
}

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  CasillaHash* casillaBuscada = slist_contiene(tabla->tabla[idx], clave, tabla->igual);
  return casillaBuscada;
}

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave) {
  // Calculamos la posición de la clave dada, de acuerdo a la función hash.
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  tabla->tabla[idx] = slist_eliminar(tabla->tabla[idx], clave, tabla->igual, eliminarCasilla, &(tabla->numElems));
}

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla) {
  for(unsigned i = 0; i < tabla->capacidad; i++)
    slist_destruir(tabla->tabla[i], eliminarCasilla);
  free(tabla->tabla);
  free(tabla);
}
