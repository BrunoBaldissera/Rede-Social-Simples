
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grafo.h"

void imprimeRede(Grafo *g){
	for(int i = 0; i < g->nVertices; i++){
		printf("id: %d, nome: %s\n", g->vertices[i]->id, g->vertices[i]->dados->nome);
	}
}

int main(int argc, char* argv[]){
	char nomeArquivo[100];
	printf("\nDigite o nome do arquivo que contem os dados dos usuarios\n");
	scanf("%s", nomeArquivo);
	fflush(stdin);
	printf("\n");
	
	FILE* arquivoTexto = fopen(nomeArquivo, "r+");
	if (arquivoTexto == NULL){
		printf("O arquivo não existe.\n");
		return 0;
	}

	int erro;
	Grafo* g = constroiGrafo(arquivoTexto, &erro);
	if (DEBUG) printf("O tamanho do grafo criado é %d\n", g->nVertices);

	printf("Imprimindo membros da rede!\n\n");
	imprimeRede(g);

	//loop de execução do programa
	char login[200];
	int id;
	char op;		
	while(1){
		printf("\nBem vindo ao Tinderbook\nPor favor insira seu nome de usuário abaixo!\nSe desejar sair, digite \"s\"\n");
		
		scanf(" %[^\n]%*c", login);
		
		if (strcmp(login, "s") == 0) return 0;
		
		printf("Agora insira seu id!\n");
		scanf(" %d", &id);
	
		if(id >= g->nVertices){
			printf("\nAparentemente você não possui um cadastro no Tinderbook ainda...\nGostaria de fazer um?\nDigite \"s\" se sim e \"n\" se não.\n");
			scanf(" %c", &op);
			
			if(op == 'n') continue;
			else {
				criaCadastro(g, &erro);
				system("clear");
				printf("Parabéns, o seu id criado foi %d\nAgora você pode logar à rede com seu id e nome\n", g->nVertices - 1);
			}
			continue;
		}
	
		if(!confereId(g, login, id)){
			printf("Ocorreu algum erro, reinsira seus dados de cadastro\n");
			continue;
		}
		system("clear");	
		printf("Olá %s!\n", login);
		genteErrada(g, id);
			
		do{	
			printf("\nSe quiser ver seus amigos, digite \"v\"\nSe quiser ver recomendações de amigos digite \"r\"\nSe quiser enviar um pedido de amizade digite \"a\"\nPara ver sua lista de pedidos de amizade digite \"p\"\nPara sair, digite \"s\"\n");
			scanf(" %c", &op);
			system("clear");

			switch (op){
				case 'v':
					imprimeAmigos(g, id);
					break;

				case 'r':
					similaridade(g, id);
					break;
				case 'a':
					imprimeRede(g);
					printf("\nInsira aqui o id da pessoa que você quer adicionar!\n");
					int idRecebe;
					scanf("%d", &idRecebe);
					
					if(enviaPedido(g, id, idRecebe)) printf("Pedido enviado com sucesso!\n");
					else printf("Ocorreu algum erro ao enviar o pedido, tente novamente\n");
					
					break;
				case 'p':
					mostraPedidos(g, id);
					break;
				case 's':					
					break;
				default:
					printf("Opção inválida, tente novamente...\n");
					break; 
			}
	
		}while(op != 's');
		system("clear");	
	}

	return 0;
}