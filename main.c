#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grafo.h"

int main(int argc, char* argv[]){
	char nomeArquivo[100];	
	scanf("%s", nomeArquivo);	
	FILE* arquivoTexto = fopen(nomeArquivo, "r+");	
	
	Dados** dados;
	dados = recuperaDados(arquivoTexto);

	int erro;
	Grafo* grafo = criaGrafo();
	constroiGrafo(grafo, dados, &erro);

	//loop de execução do programa
	int op;		
	do{
		//login();
		scanf("%d", &op);
	}while(op != '0');

	return 0;
}
