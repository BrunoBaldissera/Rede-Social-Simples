#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>

#define DEBUG 1
#define EXPANSAO 200

typedef struct Dados_{
	char nome[200];
	int idade;
	char cidade[200];
	char filme[200];
	char time[200];
	char livro[200];
	char comida[200];
	char hobbie[200];
	char musica[200];
	char atividade[200];	
}Dados;

typedef struct Vertice_{
	struct Vertice_* prox;
	double afinidade;
	int id;	
	
	Dados* dados;
	
	struct Vertice_** pedidos;
}Vertice;

typedef struct Grafo_{
	int nVertices;
	Vertice** vertices;
}Grafo;

Dados** recuperaDados(FILE* arquivo);

Vertice* criaVertice(Dados* dados);

Grafo* criaGrafo();

void constroiGrafo(Grafo* g, Dados** dados, int* erro);

void insereVertice(Grafo* g, Vertice* v, int* erro);

void enviaPedido(Grafo* g, int idEnvia, int idRecebe);

#endif
