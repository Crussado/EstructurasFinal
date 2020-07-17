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

  if(strcmp(conjunto, "}") == 0){
    *largo = 0;
    return EXTENSION;
  }
  
  int a, b;
  char var1[MAX_BUFF], var2[MAX_BUFF], resto[MAX_BUFF];
  if(sscanf(conjunto, "%s : %d <= %s <= %d%[^\n]", var1, &a, var2, &b, resto) == 5) {
    if((strcmp(var1, var2) == 0) && (strcmp(resto, "}") == 0)) {
      listaConjunto[0] = a;
      listaConjunto[1] = b;
      *largo = 2;
      return COMPRESION;
    }
    else
      return ERROR;      
  }
  char* sobras = conjunto;
  int falla = 0, termine = 0;
  *largo = 0;
  while (!falla && !termine) {
    listaConjunto[*largo] = strtol(sobras, &sobras, 10);
    *largo = *largo + 1;
    if(sobras[0] == ',' && sobras[1] != ',')
      sobras++;
    else if(strcmp(sobras, "}") == 0)
      termine = 1;
    else 
      falla = 1;
  }
  if(falla)
    return ERROR;
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
    return FALLO;
  }

  if(sscanf(ingreso, "%s = ~%[^\n]", cadena1, cadena2) == 2) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2))
      return COMPLEMENTO;
    return FALLO;
  }

  if(sscanf(ingreso, "%s = %s - %[^\n]", cadena1, cadena2, cadena3) == 3) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2) && verificar_alias(cadena3))
      return RESTAR;
    return FALLO;
  }

  if(sscanf(ingreso, "%s = %s & %[^\n]", cadena1, cadena2, cadena3) == 3) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2) && verificar_alias(cadena3))
      return INTERSECTAR;
    return FALLO;
  }

  if(sscanf(ingreso, "%s = %s | %[^\n]", cadena1, cadena2, cadena3) == 3) {
    if(verificar_alias(cadena1) && verificar_alias(cadena2) && verificar_alias(cadena3))
      return UNIR;
    return FALLO;
  }

  if(sscanf(ingreso, "%s = {%[^\n]", cadena1, cadena2) == 2)
    if(verificar_alias(cadena1))
      return CREAR;
  return FALLO;
}