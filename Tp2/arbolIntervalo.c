#include <stdio.h>
#include <stdlib.h>
#include "arbolIntervalo.h"
#include "intervalo.h"

//Itree se encarga de crear un arbol de intervalo.
//itree_crear: NULL->Itree
Itree itree_crear() {
  return NULL;
}

//itree_destruir se encarga de destruir un arbol de intervalo.
//itree_destruir: Itree->NULL
void itree_destruir(Itree arbol) {
  if (arbol != NULL) {
    itree_destruir(arbol->left);
    itree_destruir(arbol->right);
    free(arbol);
  }
}

//itree_empty se encarga de de verificar si el arbol es vacio.
//itree_empty: Itree->Int
int itree_empty(Itree arbol) {
  return arbol == NULL;
}

//maximo se encarga de elegir el numero mas grande entre dos.
//maximo: Int->Int->Int
int maximo (int a, int b){
  if (a > b)
    return a;
  return b;
}

//itree_recorrer_dfs se encarga de llevar a cabo el recorrido por profundidad del árbol.
//itree_recorrer_dfs: Itree->BTRecorrido->NULL
void itree_recorrer_dfs(Itree arbol, BTRecorrido orden) {
  if(arbol == NULL)
    return;
  if(orden == ITREE_RECORRIDO_PRE) {
      inter_imprimir(arbol->intervalo);
      itree_recorrer_dfs(arbol->left, orden);
      itree_recorrer_dfs(arbol->right, orden);
  }
  else if(orden == ITREE_RECORRIDO_IN) {
      itree_recorrer_dfs(arbol->left, orden);
      inter_imprimir(arbol->intervalo);
      itree_recorrer_dfs(arbol->right, orden);
  }
  else {
    itree_recorrer_dfs(arbol->left, orden);
    itree_recorrer_dfs(arbol->right, orden);
    inter_imprimir(arbol->intervalo);
  }
}

//itree_altura se encarga de obtener la altura de un arbol.
//itree_altura: Itree->Int
int itree_altura(Itree arbol) {
  if (arbol == NULL)
    return -1;
  return arbol->altura;
}

//actualizar_altura se encarga de actualizar la altura de un arbol.
//actualizar_altura: Itree->NULL
void actualizar_altura (Itree arbol) {
  if(arbol != NULL)
    arbol->altura = maximo(itree_altura(arbol->left), itree_altura(arbol->right)) + 1;
}

//compy_mayor se encarga de obtener la mayor de las segundas componentes de un intervalo en el arbol.
//compy_mayor: Itree->Int
int compy_mayor (Itree arbol) {
   if (arbol == NULL)
    return 0;
  return arbol->maxDerecha;
}

//actualizar_compy_mayor se encarga de obtener la mayor de las segundas componentes de un intervalo actualizada.
//actualizar_compy_mayor: Itree->NULL
void actualizar_compy_mayor(Itree arbol) {
  if(arbol!= NULL) {
    if (arbol->left == NULL && arbol->right != NULL)
      arbol->maxDerecha = maximo(compy_mayor(arbol->right), inter_y(arbol->intervalo));
    else if (arbol->left != NULL && arbol->right == NULL)
      arbol->maxDerecha = maximo(compy_mayor(arbol->left), inter_y(arbol->intervalo)) ;
    else
      arbol->maxDerecha = maximo(maximo(compy_mayor(arbol->left), compy_mayor(arbol->right)), inter_y(arbol->intervalo));
  }
}

//dif_altura se encarga de hacer la diferencia entre la altura del arbol derecho y la del arbol izquierdo.
//dif_altura: Itree->Int
int dif_altura (Itree arbol) {
  return itree_altura(arbol->right) - itree_altura(arbol->left);
}

//itree_rotacion_izq se encarga de hacer la rotación simple izquierda a un arbol, cambiando así de lugar los nodos del mismo.
//itree_rotacion_izq: Itree->Itree
Itree itree_rotacion_izq (Itree arbol) {
  Itree arbolN = arbol->right;
  arbol->right = arbolN->left;
  arbolN->left = arbol;
  actualizar_altura(arbol);
  actualizar_altura(arbolN);
  actualizar_compy_mayor(arbol);
  actualizar_compy_mayor(arbolN);
  return arbolN;
}

//itree_rotacion_der se encarga de hacer la rotación simple derecha a un arbol, cambiando así de lugar los nodos del mismo.
//itree_rotacion_der: Itree->Itree
Itree itree_rotacion_der (Itree arbol) {
  Itree arbolN = arbol->left;
  arbol->left = arbolN->right;
  arbolN->right = arbol;
  actualizar_altura(arbol);
  actualizar_altura(arbolN);
  actualizar_compy_mayor(arbol);
  actualizar_compy_mayor(arbolN);
  return arbolN;
}

//balancear se encarga de balancear un arbol.
//balancear: Itree->Itree
Itree balancear (Itree arbol) {
  int dif = dif_altura(arbol);
  if (abs(dif) <= 1)
    return arbol;
  if (dif == -2) {
    if (dif_altura(arbol->left) == 1) {
      arbol->left = itree_rotacion_izq(arbol->left);
      arbol = itree_rotacion_der(arbol);
    }
    else
      arbol = itree_rotacion_der(arbol);
  }
  else {
      if(dif_altura(arbol->right) == -1) {
        arbol->right = itree_rotacion_der(arbol->right);
        arbol = itree_rotacion_izq(arbol);
      }
      else
        arbol = itree_rotacion_izq(arbol);
  }
  return arbol;
}

//elim_minimo se encarga de: 1) obtener el minimo intervalo y 2) eliminarlo posteriormente.
//elim_minimo: Itree->Int*->Int*->Itree
Itree elim_minimo (Itree arbol, int* a, int* b) {
  if(arbol != NULL) {
    if(arbol->left == NULL) {
      *a = inter_x(arbol->intervalo);
      *b = inter_y(arbol->intervalo);
      Itree aux = arbol;
      arbol = arbol->right;
      free (aux);
    }
    else {
      arbol->left = elim_minimo(arbol->left, a, b);
      actualizar_compy_mayor(arbol);
      actualizar_altura(arbol);
      arbol = balancear(arbol);
    }
  }
  return arbol;
}

//Itree_eliminar se encarga de eliminar un intervalo de un arbol de intervalos.
//itree_eliminar: Itree->Intervalo->Itree
Itree itree_eliminar (Itree arbol, Intervalo intervalo) {
  if(arbol == NULL) 
    return arbol;
  int bandera = inter_comparar (arbol->intervalo, intervalo);
  if(bandera == 0) {
    Itree aux;
    if(arbol->left == NULL || arbol->right == NULL) {
      aux = arbol;
      if(arbol->left == NULL)
        arbol = arbol->right;
      else
        arbol = arbol->left;
      free(aux);
    }
    else {
      int a, b;
      arbol->right = elim_minimo(arbol->right, &a, &b);
      arbol->intervalo = inter_crear(a, b);
      actualizar_compy_mayor(arbol);
      actualizar_altura(arbol);
      arbol = balancear(arbol);
    }
    return arbol;
  }
  if(bandera == 1)
    arbol->left = itree_eliminar(arbol->left, intervalo);
  else
    arbol->right = itree_eliminar(arbol->right, intervalo);
  
  actualizar_compy_mayor(arbol);
  actualizar_altura(arbol);
  arbol = balancear(arbol);
  return arbol;
}

//itree_insertar_avl se encarga de insertar un elemento en el arbol.
//itree_insertar_avl: Itree->Intervalo->Itree
Itree itree_insertar_avl (Itree arbol, Intervalo intervalo) {
  if(arbol == NULL) {
    arbol = malloc(sizeof(BTIntervalo));
    arbol->left = NULL;
    arbol->right = NULL;
    arbol->altura = 0;
    arbol->intervalo = intervalo;
    arbol->maxDerecha = inter_y(intervalo);
    return arbol;
  }
  int puedoUnir = inter_puedo_unir(arbol->intervalo, intervalo);
  if(puedoUnir) {
      Intervalo unionIntervalos = inter_union(arbol->intervalo, intervalo);
      if(inter_comparar(unionIntervalos, arbol->intervalo) != 0) {
        arbol = itree_eliminar(arbol, arbol->intervalo);
        arbol = itree_insertar_avl(arbol, unionIntervalos);
      }
    return arbol;
  }
  int bandera = inter_comparar(arbol->intervalo, intervalo);
  if(bandera == 1)
    arbol->left = itree_insertar_avl(arbol->left, intervalo);
  else
    arbol->right = itree_insertar_avl(arbol->right, intervalo);
 
  actualizar_compy_mayor(arbol); 
  actualizar_altura(arbol);
  arbol = balancear(arbol);
  return arbol;
}

Itree itree_copiar_nodo(Itree nodo) {
  if(itree_empty(nodo))
    return itree_crear();
  Itree copia = malloc(sizeof(BTIntervalo));
  copia->intervalo = nodo->intervalo;
  copia->maxDerecha = nodo->maxDerecha;
  copia->altura = nodo->altura;
  return copia;
}

Itree itree_copiar(Itree arbol) {
  Itree nuevoArbol = itree_crear();
  if(itree_empty(arbol))
    return nuevoArbol;
  //Intervalo intervalo = arbol->intervalo;
  //nuevoArbol = itree_insertar_avl(nuevoArbol, intervalo);
  nuevoArbol = itree_copiar_nodo(arbol);
  nuevoArbol->right = itree_copiar(arbol->right);
  nuevoArbol->left = itree_copiar(arbol->left);
  return nuevoArbol;
}

Itree itree_unir(Itree arbol1, Itree arbol2) {
  if(itree_empty(arbol2))
    return arbol1;
  Intervalo intervalo = arbol2->intervalo;
  arbol1 = itree_insertar_avl(arbol1, intervalo);
  arbol1 = itree_unir(arbol1, arbol2->left);
  arbol1 = itree_unir(arbol1, arbol2->right);
  return arbol1;
}

int hay_posibilidad(Itree arbol, Intervalo intervalo) {
  if(itree_empty(arbol))
    return 0;
  if(arbol->maxDerecha >= inter_x(intervalo))
    return 1;
  return 0;
}

//itree_intersectar se encarga de dado un intervalo ver si existe algun intervalo
//con el cual haya interseccion y de devolver el mismo. Casi contrario, devuelve NULL.
//itree_intersectar: Itree->PIntervalo->Itree
Itree itree_intersectar_base(Itree arbol, Itree arbol1, Intervalo intervalo) {
  if(!hay_posibilidad(arbol1, intervalo))
    return arbol;
  if(inter_puede_intersectar(arbol1->intervalo, intervalo)) {
    Intervalo interseccion = inter_intersectar(arbol1->intervalo, intervalo);
    arbol = itree_insertar_avl(arbol, interseccion);
  }
  if(inter_y(intervalo) > inter_y(arbol1->intervalo) && hay_posibilidad(arbol1->right, intervalo))
    arbol = itree_intersectar_base(arbol, arbol1->right, intervalo);
  if(inter_x(intervalo) < inter_x(arbol1->intervalo) && hay_posibilidad(arbol1->left, intervalo))
    arbol = itree_intersectar_base(arbol, arbol1->left, intervalo);
  return arbol;
}

Itree itree_intersectar(Itree arbol, Itree arbol1, Itree arbol2) {
  if(itree_empty(arbol1) || itree_empty(arbol2))
    return arbol;
  arbol = itree_intersectar_base(arbol, arbol1, arbol2->intervalo);
  arbol = itree_intersectar(arbol, arbol1, arbol2->left);
  arbol = itree_intersectar(arbol, arbol1, arbol2->right);
  return arbol;
}