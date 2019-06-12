#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grafo.h"

int main(int argc, char* argv[]){
	char nomeArquivo[100];	
	scanf("%s", nomeArquivo);	
	FILE* arquivoTexto = fopen(nomeArquivo, "r+");	

	int erro;
	Grafo* g = constroiGrafo(arquivoTexto, &erro);

	//loop de execução do programa
	char login[200];
	char op;		
	while(1){
		printf("\nBem vindo ao Tinderbook\nPor favor insira seu nome de usuário abaixo!\nSe desejar sair, digite \"s\"\n");
		scanf("%s", login);
		if (strcmp(login, "s") == 0) return 0;
		
		printf("Olá %s!\n", login);
			
		do{	
			printf("\nSe quiser ver seus amigos, digite \"v\"\nSe quiser ver recomendações de amigos digite \"r\"\nSe quiser enviar um pedido de amizade digite \"a\"\nPara ver sua lista de pedidos de amizade digite \"p\"\nPara sair, digite\"s\"\n");
			scanf(" %c", &op);

			switch (op){
				case 'v':
					
					break;

				case 'r':
					
					break;
				case 'a':
					
					break;
				case 'p':
					
					break;
				case 's':					
					break;
				default:
					printf("Opção inválida, tente novamente...");
					break; 
			}
	
		}while(op != 's');	
	}

	return 0;
}
