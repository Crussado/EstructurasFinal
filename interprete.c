#include "interprete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//verificar_alias toma un alias y verifica que sea correcto
//verificar_alaias: Char*->Int
int verificar_alias (char* alias) {
  int noFalla = 1;
  for(int i = 0; alias[i] != '\0' && noFalla; i++)
    if(!isalpha(alias[i]) && !isdigit(alias[i]))
      noFalla = 0;
  return noFalla;
}

TipoConjunto verificar_conjunto (char* conjunto, int* listaConjunto, int* largo) {
  if(strcmp(conjunto, " ") == 0){
    *largo = 0;
    return EXTENSION;
  }
  int a, b;
  char var1[MAX_BUFF], var2[MAX_BUFF], resto[MAX_BUFF];
  if(sscanf(conjunto, "%s : %d <= %s <= %d%[^\n]", var1, &a, var2, &b, resto) == 4) { // RESTO DESPUES DEL ULTIMO VALOR???????!?!?!!?!?
    if((strcmp(var1, var2) == 0)) {
      listaConjunto[0] = a;
      listaConjunto[1] = b;
      *largo = 2;
      return COMPRESION;
    }
    else
      return ERROR;      
  }
  int falla = 0, cont = 0, i;
  *largo = 0;
  for(i = 0; conjunto[i] != '\0' && !falla; i++) {
    if(isdigit(conjunto[i])) {
      var1[cont] = conjunto[i];
      cont++;
    }
    else if(conjunto[i] == ',') {
      var1[cont] = conjunto[i];   //PUEDEN INGRESAR NUMEROS MUY GRANDES?!?!???????????
      listaConjunto[*largo] = atoi(var1);
      *largo = *largo + 1;
      cont = 0;
    }
    else
      falla = 1;
  }
  if(falla)
    return ERROR;

  var1[cont] = conjunto[i];
  listaConjunto[*largo] = atoi(var1);
  *largo = *largo + 1;
  return EXTENSION;
}

//analizar_comando toma un comando ingresado, lo analiza verificando si es correcto,
//y devuelve una accion dependiendo de cual sea el caso. Ademas de almacenar las cadenas
//necesarias para esa accion.
//analizar_comando: Char*->Char**->Char**->Char**->Accion
Accion analizar_comando(char *ingreso, char* cadena1, char* cadena2, char* cadena3) {

  if(strcmp(ingreso, "salir\n") == 0)
    return SALIR;
  
  if(sscanf(ingreso, "imprimir %[^\n]", cadena1) == 1) {
    if(verificar_alias(cadena1))
      return IMPRIMIR;
    else 
      return FALLO;
  }

  if(sscanf(ingreso, "%s = ~%[^\n]", cadena1, cadena2) == 2) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2))
      return COMPLEMENTO;
    else 
      return FALLO;
  }

  if(sscanf(ingreso, "%s = %s - %[^\n]", cadena1, cadena2, cadena3) == 3) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2) && verificar_alias(cadena3))
      return RESTAR;
    else 
      return FALLO;
  }

  if(sscanf(ingreso, "%s = %s & %[^\n]", cadena1, cadena2, cadena3) == 3) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2) && verificar_alias(cadena3))
      return INTERSECTAR;
    else 
      return FALLO;
  }

  if(sscanf(ingreso, "%s = %s | %[^\n]", cadena1, cadena2, cadena3) == 3) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2) && verificar_alias(cadena3))
      return UNIR;
    else 
      return FALLO;
  }

  if(sscanf(ingreso, "%s = {%[^}]%[^\n]", cadena1, cadena2, cadena3) == 3)
    if(verificar_alias(cadena1) && (strcmp(cadena3, "}") == 0))
      return CREAR;
  return FALLO;
}