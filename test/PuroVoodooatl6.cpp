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
	int contador_produto;
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
	printf("*LOJA PURO VOODOO*\n");
	
	for(int i=0;i<contador_produto;i++){
		printf("________________\n");
		printf("\nproduto %d: %s\n",i+1, produtos[i].nome);
		printf("preco: R$ %.2lf\n",produtos[i].preco);
		
	}
}

int atualizarEstoque(int estoque){
	//estoque=estoque;
	return estoque;
}




void adicionarAoCarrinho(ItemCarrinho carrinho[], int *numItens, int produtoId, int quantidade) {
    int itemExistente = -1;

    for (int i = 0; i < 5; i++) {
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

void editarCarrinho(ItemCarrinho carrinho[], produto produtos[],int numItens, int quantidade) {
	int edit_carrinho;
	int edit_quantidade;
 	printf("Escolha o produto que deseja editar: ");
 	scanf("%d",&edit_carrinho);
 	
 	for (int j = 0; j < numItens; j++) {
 		if (edit_carrinho == produtos[j].id) {
 		printf("editando produto: %s \n",produtos[j].nome);
 		printf("quantidade atual: %d \n",carrinho[j].quantidade);
 		printf("Altere a quantidade: ");
 		scanf("%d",edit_quantidade);
 		carrinho[j].quantidade=edit_quantidade;
        }
 	}
    
}

float calcularDesconto(float total){
	if(total>=250){	
		total-=total*0.15;
	}
	else if(total>=100){
		total-=total*0.15;
	}
	return total;
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
                printf("ID %d  -  Produto: %s - Qtd: %d  -  Preço Und: %.2f  -  Preço Total: %.2f\n",
                   produtos[j].id,produtos[j].nome, quantidade, produtos[j].preco, precoTotal);
                   total+=precoTotal;
                   break;
            }
        }
    }
   // printf("\nID %d  -  Produto: %s - Qtd: %d\n",produtos[1].id,produtos[1].nome, carrinho[1].quantidade);
    printf("\nValor total do carrinho: R$ %.2lf\n",total);
    printf("\nDesconto aplicado...\nValor total: R$ %.2lf\n\n",total);
    
}


void cadastrarVenda(venda vendas[],int contador_venda,produto produtos[],ItemCarrinho carrinho[], int numProdutos,int numItens,float total,int numero_pedido){
		
	exibirCarrinho( carrinho,  numItens,  produtos, numProdutos);
	vendas[contador_venda].numero_pedido= numero_pedido;
	vendas[contador_venda].valor=calcularDesconto(total);

	contador_venda++;
	numero_pedido++;
}

void visualizarVendas(venda vendas[],int contador_venda){
	
	for(int i=0;i<contador_venda;i++){
		printf("ID DA VENDA: %d\n", vendas[i].numero_pedido);
		printf("Valor total: R$ %.2lf\n",vendas[i].valor);
	}
			
}

//funçao para o administrador cadastrar produtos;
void cadastrarProduto(produto produtos[],int contador_produto,int estoque){
	printf("\nCADASTRO DE PRODUTOS: \n");
	printf("Produto: ");
	scanf("%s",produtos[contador_produto].nome);
	printf("Preco: ");
	scanf("%f",&produtos[contador_produto].preco);
	printf("Estoque: ");
	scanf("%d",&estoque);
	produtos[contador_produto].estoque = atualizarEstoque(estoque);//transformei estoque em função.
	
	produtos[contador_produto].SKU = 20161 + contador_produto;
}

//exibir produtos e todos seus atributos para o administrador (SKU, NOME, PREÇO, ESTOQUE)
void visualizarProdutos(produto produtos[], int contador_produto){
	for(int i=0;i<contador_produto;i++){
		printf("SKU: %d\n", produtos[i].SKU);
		printf("Produto: %s\n",produtos[i].nome);
		printf("Preço: R$ %.2lf\n",produtos[i].preco);
		printf("Estoque: %d\n\n",produtos[i].estoque);
	}
}

void editarProduto(){
}

int main(){
	
	produto produtos[20] = {
        {20161,1,"VOODOO SUBLIME", 27.0,50,0},
        {20162,2,"VOODOO CHARD", 51.0,62,1},
        {20163,3,"VOODOO GOLD", 49.0,15,0}
    }; 
    int estoque=0;
    int contador_venda=0;
    int numProdutos = 10;
	int contador_produto =3;
	int opcao, retorno_menu, produtoId,quantidade;
	int contador_carrinho=0;
	
	float total;
	
	
	ItemCarrinho carrinho[10];
	venda vendas[3];
	int numero_pedido=1;
	
    int numItens = 0;
	
	do{
		menuAdm();
		scanf("%d",&retorno_menu);
		switch(retorno_menu){
				
		case 1: 
		do{
			cadastrarProduto(produtos, contador_produto, estoque);
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
			printf("Digite o ID do produto: ");
            scanf("%d", &produtoId);
            printf("Digite a quantidade: ");
            scanf("%d", &quantidade);
            adicionarAoCarrinho(carrinho, &numItens, produtoId, quantidade);
       		system("cls");		
			printf("PRODUTO ADICIONADO!\n\n1. ADICIONAR OUTRO PRODUTO AO CARRINHO\n2. EXIBIR CARRINHO");
			scanf("%d",&opcao);
			contador_carrinho++;
			system("cls");
		} while (opcao!=2);
		      
		  //exibirCarrinho(carrinho, numItens, produtos, numProdutos);
		  cadastrarVenda(vendas,contador_venda,produtos,carrinho, numProdutos, numItens,total,numero_pedido);
		  visualizarVendas(vendas, contador_venda);
         /* editarCarrinho(carrinho, produtos, numItens, quantidade);
          exibirCarrinho(carrinho, numItens, produtos, numProdutos);*/
          printf("\n\n");
          break;
		}
		}while(retorno_menu!=4);
	}
		  
