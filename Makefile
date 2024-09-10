all: Con_hilos No_hilos

Con_hilos: Con_hilos.c
	gcc -o Con_hilos Con_hilos.c -lm -lpthread

No_hilos: No_hilos.c
	gcc -o No_hilos No_hilos.c -lm

clean:
	rm Con_hilos No_hilos

