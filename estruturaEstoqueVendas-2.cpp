#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

#define TAM 3
#define MAX 30

struct venda{
	int numero_pedido;
	float valor;
};

typedef struct venda venda;

struct produto{
	int SKU;
	char nome[MAX];
	float preco;
	int estoque;
	int contador_produto=0;
};

typedef struct produto produto;

void menuAdm(){
	printf("MENU DO ADMINISTRADOR\n");
	printf("1. CADASTRAR PRODUTO. \n");
	printf("2. VISUALIZAR PRODUTOS CADASTRADOS.\n");
	printf("3. TEMPORARIO MENU CLIENTE\n");
	printf("4. ENCERRAR SESSAO\n");
	//printf("\n-----------------\n");
	printf("\nESCOLHA UMA DAS OPCOES: ");
}

//exibir produtos para os clientes, apenas nome e preço
void listarProdutos(produto produtos[], int contador_produto){
	printf("*    LOJA PURO VOODOO    *\n");
	
	for(int i=0;i<contador_produto;i++){
		printf("________________\n");
		printf("\nproduto %d: %s\n",i+1, produtos[i].nome);
		printf("preco: R$ %.2lf\n",produtos[i].preco);
		
	}
}

void adicionarCarrinho(produto produtos[], int escolher_produto){
			
}

void finalizarCompra(){
}


//funçao para o administrador cadastrar produtos;
void cadastrarProduto(produto produtos[],int contador_produto){
	printf("\nCADASTRO DE PRODUTOS: \n");
	printf("Produto: ");
	scanf("%s",produtos[contador_produto].nome);
	printf("Preco: ");
	scanf("%f",&produtos[contador_produto].preco);
	printf("Estoque: ");
	scanf("%d",&produtos[contador_produto].estoque);
	produtos[contador_produto].SKU = 20161 + contador_produto;
}

//exibir produtos e todos seus atributos para o administrador (SKU, NOME, PREÇO, ESTOQUE)
void visualizarProdutos(produto produtos[], int contador_produto){
	for(int i=0;i<contador_produto;i++){
		printf("SKU: %d\n", produtos[i].SKU);
		printf("Produto: %s\n",produtos[i].nome);
		printf("Preço: R$ %.2lf\n",produtos[i].preco);
		printf("Estoque: %5d\n\n",produtos[i].estoque);
	}
}

void editarProduto(){
}

int main(){
	
	produto produtos[10];
	int contador_produto =0;
	int opcao, retorno_menu, escolher_produto;
	int quantidade_compra;
	float total;
	
	do{
		menuAdm();
		scanf("%d",&retorno_menu);
		switch(retorno_menu){
				
		case 1: 
		do{
			cadastrarProduto(produtos, contador_produto);
			printf("Deseja continuar? \n1. SIM\n2. NAO");
			scanf("%d",&opcao);
			contador_produto++;
			system("cls");
		} while(opcao!=2);
		
		break;
		
		case 2:
		visualizarProdutos(produtos, contador_produto);
		break;
		
		case 3: 
		do{
			listarProdutos(produtos, contador_produto);
			scanf("%d",&escolher_produto);
			
			printf("Produto: %s\n",produtos[escolher_produto-1].nome);
			printf("Preço: R$ %.2lf\n",produtos[escolher_produto-1].preco);
			printf("Escolha a quantidade: ");
			scanf("%d",&quantidade_compra);
			total=produtos[escolher_produto-1].preco*quantidade_compra;
			
			printf("%d  -  %s  -  R$ %.2lf x %d = R$ %.2lf", produtos[escolher_produto-1].SKU, produtos[escolher_produto-1].nome,produtos[escolher_produto-1].preco, quantidade_compra, total);
						
			printf("\n1. ADICIONAR OUTRO PRODUTO AO CARRINHO\n2. FINALIZAR COMPRA");
			scanf("%d",&opcao);
			system("cls");
		} while (opcao!=2);
			
			finalizarCompra();
				
	
		}
		
	} while(retorno_menu!=4);
}