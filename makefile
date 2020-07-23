PROGRAMA = main.c
INTERPRETE = interprete.c
CARPETAARBOL = Tp2/
CARPETAHASH = hashSlist/
ARBOL = arbolIntervalo.o
INTERVALO = intervalo.o
TABLA = tablahash.o
SLIST = slist.o
CONJUNTOS = conjunto
BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: programa 

programa: $(PROGRAMA) $(INTERPRETE:.c=.o) $(CONJUNTOS).o arbol hash
	gcc -o programa $(PROGRAMA) $(INTERPRETE:.c=.o) $(CARPETAARBOL)$(ARBOL) $(CARPETAARBOL)$(INTERVALO:.c=.o) $(CARPETAHASH)$(TABLA:.c=.o) $(CARPETAHASH)$(SLIST:.c=.o) $(CONJUNTOS).o $(BANDERAS)
$(INTERPRETE:.c=.o): $(INTERPRETE) $(INTERPRETE:.c=.h)
	gcc -c $(BANDERAS) $(INTERPRETE)
$(CONJUNTOS).o: $(CONJUNTOS).c $(CONJUNTOS).h arbol hash
	gcc -c $(BANDERAS) $(CONJUNTOS).c
arbol: 
	cd $(CARPETAARBOL) && make
hash: 
	cd $(CARPETAHASH) && make

clean: 
	rm *.o