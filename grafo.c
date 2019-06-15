#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "grafo.h"

char* strlower(char* s){
	for(int i = 0; s[i]; i++){
		s[i] = tolower(s[i]);
	}
	return s;
}

Vertice* criaVertice(Dados* dados){
	Vertice* v = (Vertice*) malloc(sizeof(Vertice));
	v->dados = (Dados*) malloc(sizeof(Dados));

	v->tamPedidos = 0;	

	v->prox = NULL;	//definimos a lista de amigos como nula		
	v->afinidade = -1; //definimos a afinidade como invalida, por enquanto

	//neste bloco de codigo atribuimos ao campo de dados do vertice os dados passados como parametro lidos no arquivo de texto 
	strcpy(v->dados->nome, dados->nome);
	v->dados->idade = dados->idade;
	strcpy(v->dados->cidade, strlower(dados->cidade));
	strcpy(v->dados->filme, strlower(dados->filme));
	strcpy(v->dados->time, strlower(dados->time));
	strcpy(v->dados->livro, strlower(dados->livro));
	strcpy(v->dados->comida, strlower(dados->comida));
	strcpy(v->dados->hobbie, strlower(dados->hobbie));
	strcpy(v->dados->musica, strlower(dados->musica));
	strcpy(v->dados->atividade, strlower(dados->atividade));

	if (DEBUG) printf("nova pessoa:\nnome: %s\nidade: %d\ncidade: %s\nfilme: %s\ntime: %s\nlivro: %s\ncomida: %s\nhobbie: %s\nmusica: %s\natividades: %s\n\n",
			v->dados->nome, v->dados->idade, v->dados->cidade, v->dados->filme, v->dados->time, v->dados->livro, v->dados->comida, v->dados->hobbie, v->dados->musica, v->dados->atividade);
	return v;
}

Vertice** recuperaDados(FILE* arquivo, int* nVertices){
	if (DEBUG) printf("Recuperando dados\n");
	int npessoas = 0;
	
	fseek(arquivo, 0, SEEK_SET);	
	while(!feof(arquivo)){
		fscanf(arquivo, "%*[^\n]\n");
		npessoas++;
	}
	if (DEBUG) printf("Numero de pessoas calculado: %d\n", npessoas);

	*nVertices = npessoas;

	Dados** d = (Dados**) malloc(sizeof(Dados*) * npessoas);
	for(int i = 0; i < npessoas; i++){
		d[i] = (Dados*) malloc(sizeof(Dados));
	}

	Vertice** vertices = (Vertice**) malloc(sizeof(Vertice*) * npessoas * EXPANSAO);

	fseek(arquivo, 0, SEEK_SET);
	
	int i = 0;
	//le o txt e guarda os campos
	do{
		fscanf(arquivo, "%[^,],%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", d[i]->nome, &(d[i]->idade), d[i]->cidade, d[i]->filme, d[i]->time, 
			d[i]->livro, d[i]->comida, d[i]->hobbie, d[i]->musica, d[i]->atividade);

		if (DEBUG) printf("nova pessoa:\nnome: %s\nidade: %d\ncidade: %s\nfilme: %s\ntime: %s\nlivro: %s\ncomida: %s\nhobbie: %s\nmusica: %s\natividades: %s\n\n",
			d[i]->nome, d[i]->idade, d[i]->cidade, d[i]->filme, d[i]->time, d[i]->livro, d[i]->comida, d[i]->hobbie, d[i]->musica, d[i]->atividade);

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
	if (DEBUG) printf("Grafo criado!\n");	
	
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

int enviaPedido(Grafo* g, int idEnvia, int idRecebe){	
	//aqui verificamos se o id pedido não é inválido, ou seja, não existe na rede	
	if(idRecebe > g->nVertices) return 0;
	//aqui verificamos se a lista de pedidos de quem recebe está cheia
	if(g->vertices[idRecebe]->tamPedidos == MAX_PEDIDOS){
		printf("Infelizmente a lista de pedidos de amizade desta pessoa está cheia, tente novamente mais tarde...\n");
		return 0;
	}
	//aqui verificamos se quem envia o pedido é o mesmo de quem recebe
	if(idEnvia == idRecebe){
		printf("Você não pode se adicionar na rede, tenho certeza que mais alguém te quer como amigo, não desista!\n");
		return 0;
	}

	for(int i = 0; i < g->vertices[idRecebe]->tamPedidos; i++){
		if (g->vertices[idRecebe]->pedidos[i] == NULL){
			g->vertices[idRecebe]->pedidos[i] = g->vertices[idEnvia];
			g->vertices[idRecebe]->tamPedidos++;
			return 1;
		}
	}
	//se chegou aqui é por que a lista nao tem "buracos", entao devemos inserir no final do vetor
	g->vertices[idRecebe]->pedidos[g->vertices[idRecebe]->tamPedidos] = g->vertices[idEnvia];
	g->vertices[idRecebe]->tamPedidos++;	

	return 1;
}

void aceitaPedido(Grafo* g, int idRecebe, int idEnvia, int posVet){
	g->vertices[idRecebe]->pedidos[posVet] = NULL;
	g->vertices[idRecebe]->tamPedidos--;

	//este bloco de codigo adiciona na lista de adjacências do vertice que recebe o vertice que envia, criando uma aresta entre os dois
	Vertice* aux = g->vertices[idRecebe];
	while(aux->prox != NULL){
		aux = aux->prox;
	}		
	aux->prox = g->vertices[idEnvia];
	
	//este bloco de codigo adiciona na lista de adjacências do vertice que envia o vertice que recebe, criando uma aresta entre os dois
	aux = g->vertices[idEnvia];
	while(aux->prox != NULL){
		aux = aux->prox;
	}		
	aux->prox = g->vertices[idRecebe];
}

void mostraPedidos(Grafo* g, int id){
	if (id <= 0 || id > g->nVertices){
		printf("id inválido, tente novamente\n");
		return;
	}
	if(g->vertices[id]->tamPedidos == 0){
		printf("Sua lista de pedidos de amizade está vazia!\n");
		return;
	}	
	for(int i = 0; i < g->vertices[id]->tamPedidos; i++){
		if(g->vertices[id]->pedidos[i] != NULL){
			printf("id: %d, nome: %s\n", g->vertices[id]->pedidos[i]->id, g->vertices[id]->pedidos[i]->dados->nome);
		}
	}

	char escolha;
	int add;
	int posVet;
	short int existe = 0;
	
	printf("Você deseja aceitar algum pedido?\nSe sim, digite \"s\", se não, \"n\"\n");
	scanf(" %c", &escolha);
	if(escolha == 'n') return;

	do{	
		printf("\nOk! Agora digite o id da pessoa que deseja adicionar.\n"); 
		scanf(" %d", &add);
		if (add <= 0 || add > g->nVertices){
			printf("Ocorreu algum erro, tente novamente\n");
			return;
		}
		for(int i = 0; i < g->vertices[id]->tamPedidos; i++){
			if (add == g->vertices[id]->pedidos[i]->id) {
				existe = 1;
				posVet = i;
				break;
			}
		}
		if (existe) aceitaPedido(g, id, add, posVet);
		else printf("o id inserido não lhe enviou solicitação de amizade...\n");
		
		printf("Deseja aceitar outro pedido?\nSe sim, digite \"s\", se não, \"n\"\n");
		scanf(" %d", &escolha);
	}while(escolha != 'n');
}

void criaCadastro(Grafo* g, int* erro){
	Dados* d = (Dados*) malloc(sizeof(Dados));
	printf("Para criar sua conta precisaremos de alguns dados.\nInsira aqui seu nome\n");
	scanf("%s", d->nome);

	printf("Agora insira a sua idade\n");
	scanf("%d", &(d->idade));
	
	printf("Agora insira a cidade onde você mora\n");
	scanf(" %s", d->cidade);

	printf("Para qual time você torce\n");
	scanf("%s", d->time);

	printf("Seu filme favorito\n");
	scanf("%s", d->filme);

	printf("Seu livro favorito\n");
	scanf("%s", d->livro);
	
	printf("Qual seu prato preferido?\n");
	scanf("%s", d->comida);

	printf("Seu hobbie, ou o que você faz nas horas vagas, em poucas palavras\n");
	scanf("%s", d->hobbie);

	printf("Sua música\n");
	scanf("%s", d->musica);

	printf("Agora o que você faz, profissão ou estudos\n");
	scanf("%s", d->atividade);

	Vertice* v = criaVertice(d);
	insereVertice(g, v, erro);
}

void imprimeAmigos(Grafo* g, int id){
	if(g->vertices[id]->prox == NULL){
		printf("Parece que você ainda não possui amigos... Quando voltar ao menu olhe as suas recomendações de amigos baseada em pessoas compatíveis a você e envie um pedido de amizade a elas!\n");
		return;
	}

	Vertice* percorre = g->vertices[id]->prox;
	int namigos = 0;	
	while(percorre != NULL){
		printf("%d:\t%s\n", namigos, g->vertices[id]->dados->nome);
		percorre = percorre->prox;
	}
}

int confereId(Grafo* g, char login[], int id){
	if(g == NULL || login == NULL){
		return 0;
	}
	if (g->vertices[id] == NULL) return 0;
	if (strcmp(g->vertices[id]->dados->nome, login) == 0) return 1;
	return 0;   
}
