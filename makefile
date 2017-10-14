HEADERS = funciones.h

all: RedesSociales.c $(HEADERS)
	gcc -o RedesSociales RedesSociales.c funciones.c -Wall

clean:
	-rm -f RedesSociales
run:
	./RedesSociales
