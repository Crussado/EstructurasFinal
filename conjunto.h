#ifndef __CONJUNTO_H__
#define __CONJUNTO_H__

#include <stddef.h>
#include "Tp2/arbolIntervalo.h"
#include "Tp2/intervalo.h"
#include "hashSlist/tablahash.h"

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

typedef struct {
  TablaHash* tabla;
} Conjuntos;

void conjuntos_eliminar(Conjuntos* conjunto);

Conjuntos* conjuntos_crear();

Itree* conjuntos_buscar(Conjuntos* conjunto, char* alias);

void conjuntos_insertar(Conjuntos* conjunto, char* alias, int* numeros, int longitud, int forma);

void conjuntos_unir(Conjuntos* conjunto, char* alias1, char* alias2, char* alias3);

void conjuntos_intersectar(Conjuntos* conjunto, char* alias1, char* alias2, char* alias3);

#endif /* __CONJUNTO_H__ */