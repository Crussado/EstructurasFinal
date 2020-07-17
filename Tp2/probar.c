#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main () {
  char comando, ingreso[255], resto[255];
  double x, y;
  //scanf("%s", ingreso);
  //strcpy(ingreso, "i [2.2, 8.3]");
  //printf("%d\n", sscanf(ingreso, "%c [%lf, %lf%s", &comando, &x, &y, resto));
  //printf("%c\n", comando);
  /*scanf("%s", ingreso);
  printf("%d\n", sscanf(ingreso, "%c [%lf, %lf%s", &comando, &x, &y, resto));
  printf("%c\n", comando);
  printf("%f\n", x);
  printf("%f\n", y);
  if(strlen(resto) == 1)
    printf("bien");
  else
    printf("mal");*/
  fgets(ingreso, 50, stdin);
  sscanf(ingreso, "%c [%lf, %lf%s", &comando, &x, &y, resto); 
  int largo = strlen(ingreso);
  printf("%c", ingreso[largo-2]);
  printf("%c\n", comando);
  printf("%f\n", x);
  printf("%f\n", y);
  return 0;
}


