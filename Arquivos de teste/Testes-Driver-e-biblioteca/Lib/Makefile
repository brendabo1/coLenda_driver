all: imagem

imagem: imagem.c colenda.o
	gcc -o imagem imagem.c colenda.o -std=c99

colenda.o: colenda.c colenda.h
	gcc -c colenda.c -std=c99

clean:
	rm -f *.o