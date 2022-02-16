LIBS = -lGL -lGLU -lglut
CC=gcc

ejercicio : ejercicio.c
	$(CC) -o $@ $< $(LIBS)