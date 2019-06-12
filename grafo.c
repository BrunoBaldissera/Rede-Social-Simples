#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grafo.h"

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

Vertice** recuperaDados(FILE* arquivo, int* nVertices){
	int npessoas = 0;
	
	fseek(arquivo, 0, SEEK_SET);	
	while(!feof(arquivo)){
		fscanf(arquivo, "%*[^\n]\n");
		npessoas++;
	}	

	*nVertices = npessoas;

	Dados** d = (Dados**) malloc(sizeof(Dados*) * npessoas);

	Vertice** vertices = (Vertice**) malloc(sizeof(Vertice*) * npessoas * EXPANSAO);
	fseek(arquivo, 0, SEEK_SET);
	
	int i = 0;
	//le o txt e guarda os campos
	do{
		fscanf(arquivo, "%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", d[i]->nome, &(d[i]->idade), d[i]->cidade, d[i]->filme, d[i]->time, 
			d[i]->livro, d[i]->comida, d[i]->hobbie, d[i]->musica, d[i]->atividade);

			vertices[i] = criaVertice(d[i]);
		i++;
	}while(!feof(arquivo));

	return vertices;
}

Grafo* criaGrafo(){
	Grafo* g = (Grafo*) malloc(sizeof(Grafo));
	
	g->nVertices = 0;
	g->vertices = (Vertice**) malloc(sizeof(Vertice*) * EXPANSAO);		

	return g;
}

Grafo* constroiGrafo(FILE* arquivo, int* erro){
	Grafo* g = criaGrafo();

	g->vertices = recuperaDados(arquivo, &(g->nVertices));

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
		g->vertices = (Vertice**) realloc(g->vertices, (nAumentos + 1) * EXPANSAO * sizeof(Vertice*) );
	}

	//definimos o id do membro, baseado no ultimo membro da rede
	v->id = g->nVertices + 1;		

	g->vertices[g->nVertices] = v;	

	g->nVertices++;
}

void enviaPedido(Grafo* g, int idEnvia, int idRecebe){	

}

