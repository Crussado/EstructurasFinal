PROGRAMA = main.c
INTERVALO = intervalo.c
ITREE = arbolIntervalo.c

INTERPRETE = interprete.c

BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: programa 

programa: $(PROGRAMA) $(INTERVALO:.c=.o) $(ITREE:.c=.o) $(INTERPRETE:.c=.o)
	gcc -o interprete $(PROGRAMA) $(INTERVALO:.c=.o) $(ITREE:.c=.o) $(INTERPRETE:.c=.o) $(BANDERAS) 
$(INTERVALO:.c=.o): $(INTERVALO) $(INTERVALO:.c=.h)
	gcc -c $(BANDERAS) $(INTERVALO)
$(ITREE:.c=.o): $(ITREE) $(ITREE:.c=.h)
	gcc -c $(BANDERAS) $(ITREE)
$(INTERPRETE:.c=.o): $(INTERPRETE) $(INTERPRETE:.c=.h)
	gcc -c $(BANDERAS) $(INTERPRETE)
clean: 
	rm *.o