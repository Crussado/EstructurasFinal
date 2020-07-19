#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "slist.h"
#include <stddef.h>
/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
typedef unsigned (*FuncionHash)(void *);

#ifndef __FUNCIONIGUALDAD__
#define __FUNCIONIGUALDAD__
typedef int (*FuncionIgualdad)(void *, void *);
#endif

/**
 * Casillas en la que almacenaremos los datos de la tabla hash.
 */
typedef struct {
  void* dato;
  void* clave;
} CasillaHash;

/**
 * Estructura principal que representa la tabla hash.
 */ 
typedef struct {
  SList* tabla;
  unsigned numElems;
  unsigned capacidad;
  FuncionHash hash;
  FuncionIgualdad igual;
} TablaHash;

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
TablaHash* tablahash_crear(unsigned capacidad, FuncionHash fun, FuncionIgualdad igual);

void eliminarCasilla (void* casilla);

void destruir_clave(void* clave);

void destruir_dato(void* dato);

void* obtener_clave(CasillaHash* casilla);

void* obtener_dato(CasillaHash* casilla);

void actualizar_dato(CasillaHash* casilla, void* dato);

CasillaHash* crear_casilla(void* clave, void* dato);

/**
 * Inserta el dato en la tabla, asociado a la clave dada.
 */
void tablahash_insertar(TablaHash* tabla, void* clave, void* dato);

/**
 * Busca un elemento dado en la tabla, y retorna un puntero al mismo.
 * En caso de no existir, se retorna un puntero nulo.
 */
void* tablahash_buscar(TablaHash* tabla, void* clave);

/**
 * Elimina un elemento de la tabla.
 */
void tablahash_eliminar(TablaHash* tabla, void* clave);

/**
 * Destruye la tabla.
 */
void tablahash_destruir(TablaHash* tabla);

#endif /* __TABLAHASH_H__ */
