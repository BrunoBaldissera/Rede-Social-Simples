#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grafo.h"

Dados* recuperaDados(FILE* arquivo){
	Dados* d = (Dados*) malloc(sizeof(Dados));
	//le o txt e guarda os campos

	return d;
}

Vertice* criaVertice(Dados* dados){
	Vertice* v = (Vertice*) malloc(sizeof(Vertice));
	
	//neste bloco de codigo atribuimos ao campo de dados do vertice os dados passados como parametro lidos no arquivo de texto 
	strcpy(v->dados->nome, dados->nome);
	v->dados->idade = dados->idade;
	strcpy(v->dados->cidade, dados->cidade);
	strcpy(v->dados->filme, dados->filme);
	strcpy(v->dados->time, dados->time);
	strcpy(v->dados->livro, dados->livro);
	strcpy(v->dados->comida, dados->comida);
	strcpy(v->dados->hobbie, dados->hobbie);
	strcpy(v->dados->musica, dados->musica);
	strcpy(v->dados->atividade, dados->atividade);

	return v;
}

Grafo* criaGrafo(){
	Grafo* g = (Grafo*) malloc(sizeof(Grafo));
	
	g->nVertices = 0;
	g->vertices = (Vertice**) malloc(sizeof(Vertice*) * EXPANSAO);		

	return g;
}

void insereVertice(Grafo* g, Vertice* v, int* erro){
	//tratamentos de erros, caso o grafo ou vertice nao exista marcamos existencia de erro e finalizamos a funcao	
	if(g == NULL || v == NULL){
		*erro = 1;
		return;
	}
	
	/*	Este proximo bloco verifica se precisamos alocar mais espaço para o vetor de vertices do grafo,
		realizando operacoes com o numero de vertices atual. Se preciso, realocamos mais n bytes, sendo n
		um define EXTENSAO
	*/
	int nAumentos = (g->nVertices / EXPANSAO) + 1;
	if(g->nVertices == (nAumentos * EXPANSAO) - 1){
		g->nVertices = (Vertices**) realloc(g->nVertices, (nAumentos + 1) * EXPANSAO * sizeof(Vertice*) );
	}

	//caso especial de primeira insercao no grafo
	if (g->nVertices == 0){
		//definimos o id do primeiro membro da rede		
		v->id = 1;
		
		g->inicio = v;
		g->ultimo = v;
		g->ultimo->prox = NULL;
		
		g->nVertices++;
		return;
	}
	//definimos o id do membro, baseado no ultimo membro da rede
	v->id = g->ultimo->id + 1;		
	
	g->ultimo->prox = v;
	g->ultimo = v;
	g->ultimo->prox = NULL;

	g->nVertices++;
}

void enviaPedido(Grafo* g, int idEnvia, int idRecebe){	

}

