#include "intervalo.h"
#include <stdlib.h>
#include <stdio.h>

//inter_crear crea un intervalo de doubles.
//inter_crear: Int->Int->Intervalo
Intervalo inter_crear (int x, int y) {
   Intervalo intervalo;
   intervalo.compx = x;
   intervalo.compy = y;
   return intervalo;
}

//inter_x toma un intervalo y devuelve su primer componente.
//inter_x Intervalo->Int
int inter_x(Intervalo intervalo) {
  return intervalo.compx;
}

//inter_y toma un intervalo y devuelve su segunda componente.
//inter_y Intervalo->Int
int inter_y(Intervalo intervalo) {
  return intervalo.compy;
}

//inter_eliminar se encarga de eliminar un intervalo dado.
//inter_eliminar: PIntervalo->NULL
void inter_eliminar(PIntervalo intervalo) {
  free(intervalo);
}

Intervalo inter_intersectar(Intervalo intervalo1, Intervalo intervalo2) {
  Intervalo interseccion;
  if(inter_x(intervalo1) <= inter_x(intervalo2) && inter_y(intervalo1) >= inter_x(intervalo2)) {
    if(inter_y(intervalo2) <= inter_y(intervalo1))
      interseccion = intervalo2;
    else 
      interseccion = inter_crear(inter_x(intervalo2), inter_y(intervalo1));
  }
  if(inter_x(intervalo2) <= inter_x(intervalo1) && inter_y(intervalo2) >= inter_x(intervalo1)) {
    if(inter_y(intervalo1) <= inter_y(intervalo2))
      interseccion = intervalo1;
    else 
      interseccion = inter_crear(inter_x(intervalo1), inter_y(intervalo2));
  }
  return interseccion;
}


//inter_intersectar se encarga de dados 2 intervalos ver si los mismos se intersectan.
//inter_intersectar: Intervalo->Intervalo->Int
int inter_puede_intersectar(Intervalo intervalo, Intervalo nuevo) {
  if(inter_x(intervalo) <= inter_x(nuevo) && inter_y(intervalo) >= inter_x(nuevo))
    return 1;
  if(inter_x(nuevo) <= inter_x(intervalo) && inter_y(nuevo) >= inter_x(intervalo))
    return 1;
  return 0;
}

//inter_imprimir se encarga de imprimir un intervalo.
//inter_imprimir: Intervalo->NULL
void inter_imprimir(Intervalo intervalo) {
  if(inter_x(intervalo) == inter_y(intervalo))
    printf("%d ", inter_x(intervalo));
  else
  printf("%d:%d ", inter_x(intervalo), inter_y(intervalo));
}

//inter_comparar se encarga de dados dos intervalos, comparar sus respectivas componentes.
//inter_comparar: Intervalo->Intervalo->Int
int inter_comparar(Intervalo i1, Intervalo i2) {
  if(inter_x(i1) == inter_x(i2) && inter_y(i1) == inter_y(i2))
    return 0;
  if(inter_x(i1) == inter_x(i2)) {
    if(inter_y(i1) > inter_y(i2))
      return 1;//1 significa izquierda
    return 2;//2 significa derecha
  }
  if(inter_x(i1) > inter_x(i2))
    return 1; 
  return 2; 
}

//inter_puedo_unir toma dos intervalos y verifica si se pueden "unir".
//inter_puedo_unir: Intervalo->Intervalo->Int
int inter_puedo_unir(Intervalo i1, Intervalo i2) {
  int a = inter_x(i1), b = inter_y(i1), c = inter_x(i2), d = inter_y(i2);
  int puedo = 0;
  if(a <= c && b >= c)
    puedo = 1;
  else if(c <= a && d >= a)
    puedo = 1;
  else if((b + 1) == c)
    puedo = 1;
  else if((d + 1) == a)
    puedo = 1;
  return puedo;
}

//inter_union dados dos intervalos se encarga de unirlos.
//inter_union: Intervalo->Intervalo->Intervalo
Intervalo inter_union(Intervalo i1, Intervalo i2) {
  Intervalo unir;
  int a = inter_x(i1), b = inter_y(i1), c = inter_x(i2), d = inter_y(i2);
  if(a <= c && b >= c) {
    if(d >= b)
      unir = inter_crear(a, d);
    else
      unir = i1;
  }
  else if(c <= a && d >= a) {
    if(b <= d)
      unir = i2;
    else
      unir = inter_crear(c, b);
  }
  else if((b + 1) == c)
    unir = inter_crear(a, d);
  else if((d + 1) == a)
    unir = inter_crear(c, b);
  else
    unir = i1;  
  return unir;
}

