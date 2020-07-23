#ifndef __TABLAHASH_H__
#define __TABLAHASH_H__

#include "slist.h"
#include <stddef.h>
/**
 * Tipo de las funciones hash a ser consideradas por las tablas hash.
 */
#ifndef __FUNCIONHASH__
#define __FUNCIONHASH__
typedef unsigned (*FuncionHash)(void *);
typedef void (*FuncionElimClave)(void *);
typedef void (*FuncionElimDato)(void *);
#endif

#ifndef __FUNCIONIGUALDAD__
#define __FUNCIONIGUALDAD__
typedef int (*FuncionIgualdad)(void *, void *);
#endif
#ifndef __FUNCIONELIMINAR__
#define __FUNCIONELIMINAR__
typedef void (*FuncionEliminar)(void *, void *);
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
  FuncionElimClave elimClave;
  FuncionElimDato elimDato;
} TablaHash;

/**
 * Crea una nueva tabla Hash vacía, con la capacidad dada.
 */
void* casilla_obtener_clave(CasillaHash* casilla);

void* casilla_obtener_dato(CasillaHash* casilla);

TablaHash* tablahash_crear(unsigned capacidad, FuncionHash fun, FuncionIgualdad igual, FuncionElimDato elimDato, FuncionElimClave elimClave);

void destruir_clave(void* clave);

void destruir_dato(void* dato);

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
