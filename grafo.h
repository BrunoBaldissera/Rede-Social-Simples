#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>

#define DEBUG 1
#define EXPANSAO 200
#define MAX_PEDIDOS 50

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
	
	struct Vertice_* pedidos[MAX_PEDIDOS];
	int tamPedidos;
}Vertice;

typedef struct Grafo_{
	int nVertices;
	Vertice** vertices;
}Grafo;

char* strlower(char* s);

Vertice* criaVertice(Dados* dados);

Vertice** recuperaDados(FILE* arquivo, int* nVertices);

Grafo* criaGrafo();

Grafo* constroiGrafo(FILE* arquivo, int* erro);

void insereVertice(Grafo* g, Vertice* v, int* erro);

int enviaPedido(Grafo* g, int idEnvia, int idRecebe);

void aceitaPedido(Grafo* g, int idRecebe, int idEnvia, int posVet);

void mostraPedidos(Grafo* g, int id);

void criaCadastro(Grafo* g, int* erro);

void imprimeAmigos(Grafo* g, int id);

int confereId(Grafo* g, char login[], int id);



#endif
