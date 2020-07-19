PROGRAMA = main2.c
TABLAHASH = tablahash.c
SLIST = slist.c
ARBOL = arbolIntervalo.o
RUTAARBOL = ../Tp2/
BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: $(TABLAHASH:.c=.o)

$(TABLAHASH:.c=.o): $(TABLAHASH) $(TABLAHASH:.c=.h) $(SLIST:.c=.o) $(RUTAARBOL)$(ARBOL)
	gcc -c $(BANDERAS) $(TABLAHASH)
$(SLIST:.c=.o): $(SLIST) $(SLIST:.c=.h)
	gcc -c $(BANDERAS) $(SLIST)
$(RUTAARBOL)$(ARBOL):
	cd $(RUTAARBOL) && make
clean: 
	rm *.o