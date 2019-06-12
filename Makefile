make:
	gcc -g grafo.c grafo.h main.c -o redeSocial -Wall
run:
	./redeSocial
test:
	gcc -g grafo.c grafo.h main.c -o redeSocial -Wall
	./redeSocial < teste.in


