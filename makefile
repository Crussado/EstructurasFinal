PROGRAMA = main.c
INTERPRETE = interprete.c

BANDERAS = -Wall -Wextra -Werror -g -std=c99

armar: programa 

programa: $(PROGRAMA)  $(INTERPRETE:.c=.o)
	gcc -o programa $(PROGRAMA) $(INTERPRETE:.c=.o) $(BANDERAS)
$(INTERPRETE:.c=.o): $(INTERPRETE) $(INTERPRETE:.c=.h)
	gcc -c $(BANDERAS) $(INTERPRETE)
clean: 
	rm *.o