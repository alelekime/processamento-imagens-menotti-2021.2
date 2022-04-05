CFLAGS = -Wall -lm


object = acesso.o processamento.o comando.o auxiliares.o

all: pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao

processamento.o: processamento.c source/processamento.h
	gcc -c processamento.c 

acesso.o: acesso.c source/acesso.h
	gcc -c acesso.c -Wall

comando.o: comando.c source/comando.h
	gcc -c comando.c -Wall

auxiliares.o: auxiliares.c source/auxiliares.h
	gcc -c auxiliares.c -Wall

pgmlbp: $(object)
	gcc $(object) $(CFLAGS) pgmlbp.c -o pgmlbp 

pgmlimiar: $(object)
	gcc $(object) $(CFLAGS) pgmlimiar.c -o pgmlimiar 

pgmmedia: $(object)
	gcc $(object) $(CFLAGS) pgmmedia.c -o pgmmedia 

pgmmediana: $(object)
	gcc $(object) $(CFLAGS) pgmmediana.c -o pgmmediana 	

pgmnega: $(object)
	gcc $(object) $(CFLAGS) pgmnega.c -o pgmnega 

pgmrotacao: $(object)
	gcc $(object) $(CFLAGS) pgmrotacao.c -o pgmrotacao 


clean:
	rm -f *.o pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao

purge:	pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao
	rm -f $(all)