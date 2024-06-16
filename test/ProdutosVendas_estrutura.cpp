#include <stdio.h>
#include <locale.h>
#include <string.h>

#define TAM 3
#define MAX 30


struct produto{
	int SKU;
	char nome[MAX];
	float preco;
	int estoque;
	int contador_produto;
};

typedef struct produto produto;

void cadastrarProduto(produto produtos[TAM]){
	for(int i=0;i<TAM;i++){
		printf("Digite o nome do produto: ");
		scanf("%s",produtos[i].nome);
		printf("Digite o preço: ");
		scanf("%lf",produtos[i].preco);
		printf("Digite a quantidade: ");
		scanf("%d",produtos[i].estoque);
	}
}

void listarProdutos(produto produtos[TAM]){
	for(int i=0;i<TAM;i++){
		printf(produtos[i].nome);
		printf(produtos[i].preco);
		printf(produtos[i].estoque);
	}
}

int main(){
	
	produto produtos[TAM];
	
	cadastrarProduto(produtos[]);
	
	
	
	
}
