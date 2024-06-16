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
	int id;
	char nome[MAX];
	float preco;
	int estoque;
	int contador_produto=0;
};

typedef struct produto produto;

typedef struct {
    int produtoId;
    int quantidade;
} ItemCarrinho;

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
	
	for(int i=0;i<3;i++){
		printf("________________\n");
		printf("\nproduto %d: %s\n",i+1, produtos[i].nome);
		printf("preco: R$ %.2lf\n",produtos[i].preco);
		
	}
}

void adicionarAoCarrinho(ItemCarrinho carrinho[], int *numItens, int produtoId, int quantidade) {
    int itemExistente = -1;

    // Verifica se o item já está no carrinho
    for (int i = 0; i < 3; i++) {
        if (carrinho[i].produtoId == produtoId) {
            itemExistente = i;
            break;
        }
    }

    if (itemExistente != -1) {
        // Se o item já estiver no carrinho, apenas atualiza a quantidade
        carrinho[itemExistente].quantidade += quantidade;
    } else {
        // Se o item não estiver no carrinho, adiciona um novo item
        carrinho[*numItens].produtoId = produtoId;
        carrinho[*numItens].quantidade = quantidade;
        (*numItens)++;
    }
}

void exibirCarrinho(ItemCarrinho carrinho[], int numItens, produto produtos[], int numProdutos) {
    printf("Carrinho de Compras:\n\n");
    float total=0;
    
    for (int i = 0; i < numItens; i++) {
        int produtoId = carrinho[i].produtoId;
        int quantidade = carrinho[i].quantidade;
		

        // Encontra o produto pelo ID
        for (int j = 0; j < numProdutos; j++) {
            if (produtos[j].id == produtoId) {
            	float precoTotal = produtos[j].preco * quantidade;
                printf("Produto: %s, Quantidade: %d, Preço Unitário: %.2f, Preço Total: %.2f\n",
                   produtos[j].nome, quantidade, produtos[j].preco, precoTotal);
                   total+=precoTotal;
                   break;
            }
        }
    }
    printf("Valor total do carrinho: %.2lf\n\n",total);
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
	for(int i=0;i<3;i++){
		printf("SKU: %d\n", produtos[i].SKU);
		printf("Produto: %s\n",produtos[i].nome);
		printf("Preço: R$ %.2lf\n",produtos[i].preco);
		printf("Estoque: %5d\n\n",produtos[i].estoque);
	}
}

void editarProduto(){
}

int main(){
	
	produto produtos[3] = {
        {1254,1,"UVA", 10.0,50,0},
        {1255,2,"MANGA", 20.0,62,1},
        {1256,3,"LIMAO", 30.0,15,0}
    };
    int numProdutos = 3;
	int contador_produto =0;
	int opcao, retorno_menu, produtoId,quantidade;
	int contador_carrinho=0;
	
	
	ItemCarrinho carrinho[10];
    int numItens = 0;
	
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
		/*printf("Produto: %s\n",produtos[escolher_produto-1].nome);
			printf("Preço: R$ %.2lf\n",produtos[escolher_produto-1].preco);
			printf("Escolha a quantidade: ");
			scanf("%d",&quantidade_compra);*/
			//total=produtos[escolher_produto-1].preco*quantidade_compra;
			
			printf("Digite o ID do produto: ");
            scanf("%d", &produtoId);
            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);
            adicionarAoCarrinho(carrinho, &numItens, produtoId, quantidade);
       				
			printf("\n1. ADICIONAR OUTRO PRODUTO AO CARRINHO\n2. FINALIZAR COMPRA");
			scanf("%d",&opcao);
			contador_carrinho++;
			system("cls");
		} while (opcao!=2);
		      
		  exibirCarrinho(carrinho, numItens, produtos, numProdutos);
           
		}
		}while(retorno_menu!=4);
	}
		  
