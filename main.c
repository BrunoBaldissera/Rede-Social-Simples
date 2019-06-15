#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grafo.h"

int main(int argc, char* argv[]){
	char nomeArquivo[100];	
	scanf("%s", nomeArquivo);	
	FILE* arquivoTexto = fopen(nomeArquivo, "r+");
	if (arquivoTexto == NULL){
		printf("O arquivo não existe.\n");
		return 0;
	}

	int erro;
	Grafo* g = constroiGrafo(arquivoTexto, &erro);
	if (DEBUG) printf("o tamanho do grafo criado é %d\n", g->nVertices);

	//loop de execução do programa
	char login[200];
	int id;
	char op;		
	while(1){
		printf("\nBem vindo ao Tinderbook\nPor favor insira seu nome de usuário abaixo!\nSe desejar sair, digite \"s\"\n");
		scanf("%s", login);
		
		if (strcmp(login, "s") == 0) return 0;
		
		printf("Agora insira seu id!\n");
		scanf(" %d", &id);
	
		if(id > g->nVertices){
			printf("\nAparentemente você não possui um cadastro no Tinderbook ainda...\nGostaria de fazer um?\nDigite \"s\" se sim e \"n\" se não.\n");
			scanf(" %c", &op);
			
			if(op == 'n') continue;
			else {
				criaCadastro(g, &erro);
				printf("Parabéns, o seu id criado foi %d\nAgora você pode logar à rede com seu id e nome", g->nVertices);
			}
			continue;
		}
	
		if(!confereId(g, login, id)){
			printf("Ocorreu algum erro, reinsira seus dados de cadastro\n");
			continue;
		}
				
		printf("Olá %s!\n", login);
			
		do{	
			printf("\nSe quiser ver seus amigos, digite \"v\"\nSe quiser ver recomendações de amigos digite \"r\"\nSe quiser enviar um pedido de amizade digite \"a\"\nPara ver sua lista de pedidos de amizade digite \"p\"\nPara sair, digite \"s\"\n");
			scanf(" %c", &op);
			system("clear");

			switch (op){
				case 'v':
					imprimeAmigos(g, id);
					break;

				case 'r':
					
					break;
				case 'a':
					printf("Insira aqui o id da pessoa que você quer adicionar!\n");
					int idRecebe;
					scanf("%d", &idRecebe);
					
					if(enviaPedido(g, id, idRecebe)) printf("Pedido enviado com sucesso!\n");
					else printf("Ocorreu algum erro ao enviar o pedido, tente novamete\n");

					break;
				case 'p':
					mostraPedidos(g, id);
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
