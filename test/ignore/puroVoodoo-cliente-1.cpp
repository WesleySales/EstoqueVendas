#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>

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
    float total;
} ItemCarrinho;

float valor_total = 0.0;//declarei o valor_total aqui para que seja possivel guardar e usar em qualquer parte do codigo - VARIAVEL GLOBAL.

void menuAdm(){
	printf("MENU DO ADMINISTRADOR\n");
	printf("1. CADASTRAR PRODUTO. \n");
	printf("2. VISUALIZAR PRODUTOS CADASTRADOS.\n");
	printf("3. MENU CLIENTE TEMPORARIO\n");
	printf("4. ENCERRAR SESSAO\n");
	printf("5. EDITAR PRODUTOS\n");
	printf("6. VISUALIZAR VENDAS\n");
	
	//printf("\n-----------------\n");
	printf("\nESCOLHA UMA DAS OPCOES: ");
}

//exibir produtos para os clientes, apenas nome e pre�o
void listarProdutos(produto produtos[], int contador_produto){
	printf("*LOJA PURO VOODOO*\n");
	
	for(int i=0;i<contador_produto;i++){
		printf("________________\n");
		printf("\nproduto %d: %s\n",i+1, produtos[i].nome);
		printf("preco: R$ %.2lf\n",produtos[i].preco);
		
	}
}

//função para atualizar o estoque com base nas vendas e tambem acrescimo de produtos. PRECISA SER APRIMORADA
int atualizarEstoque(int estoque){
	//estoque=estoque;
	return estoque;
}

//função para calcular o desconto com base no valor total do carrinho.
float calcularDesconto(float total){
	if(total>=500){	
		total-=total*0.20;
	}
	else if(total>=150){
		total-=total*0.15;
	}
	return total;
}

//declarei a variavel total com desconto seguindo a msm logica do valor total, para que possa ser aproveitada no codigo inteiro.
float totalComDesconto;

//função para adicionar produtos ao carrinho, O VALOR TOTAL DO CARRINHO E O DESCONTO SÃO ALTERADOS AQUI TAMBEM, conforme o carrinho é atualizado pelo usuário.
void adicionarAoCarrinho(ItemCarrinho carrinho[],produto produtos[], int *numItens, int produtoId, int quantidade) {
    int itemExistente = -1;

    for (int i = 0; i < 5; i++) {
        if (carrinho[i].produtoId == produtoId) {
            itemExistente = i;
            break;
        }
    }

    if (itemExistente != -1) {
        // Se o item j� estiver no carrinho, apenas atualiza a quantidade
        
        carrinho[itemExistente].quantidade += quantidade;
    } else {
        // Se o item n�o estiver no carrinho, adiciona um novo item
        	
        	carrinho[*numItens].produtoId = produtoId;
	        carrinho[*numItens].quantidade = quantidade;
	        (*numItens)++;
		
        
    }
    //Atualiza o valor total do carrinho sempre que um produto é adicionado - tirei isso da função exibir carrinho
    for (int j = 0; j < 10; j++) {
        if (produtos[j].id == produtoId) {
            valor_total += produtos[j].preco * quantidade;
            break;
        }
    }
    totalComDesconto = calcularDesconto(valor_total);

}

//função para exibir o carrinho. O cliente pode visualizar o carrinho a qualquer momento para consultar valor, produtos e quantidade. 
//nessa função ja consta O VALOR COM DESCONTO (SE TIVER) E A MENSAGEM DE FRETE GRÁTIS;
void exibirCarrinho(ItemCarrinho carrinho[], int numItens, produto produtos[], int numProdutos) {
    printf("Carrinho de Compras:\n\n");
    
    for (int i = 0; i < numItens; i++) {
        int produtoId = carrinho[i].produtoId;
        int quantidade = carrinho[i].quantidade;
		

        // Encontra o produto pelo ID
        for (int j = 0; j < numProdutos; j++) {
            if (produtos[j].id == produtoId) {
            	float precoTotal = produtos[j].preco * quantidade;
                printf("ID %d  -  Produto: %s - Qtd: %d  -  Pre?o Und: %.2f  -  Pre?o Total: %.2f\n",
                   produtos[j].id,produtos[j].nome, quantidade, produtos[j].preco, precoTotal);
                   break;
            }
        }
    }
    printf("\nValor total do carrinho: R$ %.2lf\n", valor_total );
    printf("\nDesconto aplicado...\nValor total: R$ %.2lf\n\n",totalComDesconto);
    printf("\nFRETE GRÁTIS");
    
}

//função para editar os produtos dentro do carrinho, será possivel mudar a quantidade apenas. TESTADO E FUNCIONANDO CORRETAMENTE, O ERRO ESTAVA NA ATRIBUIÇÃO DA VARIAVEL edit_quantidade.
void editarCarrinho(ItemCarrinho carrinho[], produto produtos[],int numItens, int quantidade, int numProdutos) {
	int edit_carrinho;
	int edit_quantidade;
 	printf("Escolha o produto que deseja editar: ");
 	scanf("%d",&edit_carrinho);
 	
 	for (int j = 0; j < numItens; j++) {
 		if (edit_carrinho == produtos[j].id) {
 		printf("editando produto: %s \n",produtos[j].nome);
 		printf("quantidade atual: %d \n",carrinho[j].quantidade);
 		printf("Altere a quantidade: ");
 		scanf("%d",&edit_quantidade);
 		carrinho[j].quantidade=edit_quantidade;
        }
 	}
 	 
}


//funçao para atualizar o estoque quando a venda é realizada; PRECISA SER APRIMORADA POIS SO FUNCIONA NO PRIMEIRO PRODUTO VENDIDO.
void atualizarEstoqueVenda(ItemCarrinho carrinho[], int numItens, produto produtos[], int numProdutos) {
	 
    for (int i = 0; i < numItens; i++) { //verifica os itens do carrinho
        int produtoId = carrinho[i].produtoId;
        int quantidade = carrinho[i].quantidade;

        for (int j = 0; j < numProdutos; j++) { //verifica os produtos que estão no carrinho e compara com os cadastrados para acessar o estoque
            if (produtos[j].id == produtoId) {
                produtos[j].estoque -= quantidade;//se encontrar o produto cadastrado atualiza o estoque tirando a quantidade de produtos que foi vendida;
                break;
            }
        }
    }
}
//função para cadastro das vendas. Pega o carrinho atualizado pelo cliente e quando ele escolhe finalizar a compra a venda é gerada e atualiza no menu de ADM
void cadastrarVenda(venda vendas[],int contador_venda,produto produtos[],ItemCarrinho carrinho[], float total,int numItens,int numero_pedido,int numProdutos){
		
	vendas[contador_venda].numero_pedido=numero_pedido;
	vendas[contador_venda].valor=totalComDesconto;

	printf("COMPRA CONClUIDA\n\n");
	
	printf("ID DA VENDA: %d\n", vendas[contador_venda].numero_pedido);
	printf("Valor total: R$ %.2lf\n",vendas[contador_venda].valor);
	
	atualizarEstoqueVenda( carrinho, numItens, produtos, numProdutos);
	
    valor_total = 0.0; // alem de zerar a quantidade de produtos no carrinho zeramos o valor total que tava como global;
}

//QUANDO A COMPRA/VENDA É FEIRA O CARRINHO É ZERADO E FICA PRONTO PARA UMA OUTRA VENDA
void zerarCarrinho(ItemCarrinho carrinho[], int *numItens) {
    *numItens = 0; // Zera a quantidade de itens no carrinho
}

float calcularImposto(float faturamento){
	float imposto = faturamento*0.08;
	return imposto;
}

//função para visualizar as vendas cadastradas, ficará no MENU ADM;
//adicionei a parte de calcular o faturmento da loja e tambem o imposto baseado no faturamento; PARA O MENU DE ADM - REQUISITO DO TRABALHO
void visualizarVendas(venda vendas[],int contador_venda){
	float faturamento;
	for(int i=0;i<contador_venda;i++){
		printf("ID DA VENDA: %d  - Valor total: R$ %.2lf\n", vendas[i].numero_pedido,vendas[i].valor);

		faturamento +=vendas[i].valor;
	}	
	printf("FATURAMENTO: R$ %.2lf\n",faturamento);
	printf("Imposto: R$ %.2lf\n",calcularImposto(faturamento));
}


//fun�ao para o administrador cadastrar produtos;
void cadastrarProduto(produto produtos[],int contador_produto,int estoque){
	printf("\nCADASTRO DE PRODUTOS: \n");
	printf("Produto: ");
	scanf("%s",produtos[contador_produto].nome);
	printf("Preco: ");
	scanf("%f",&produtos[contador_produto].preco);
	printf("Estoque: ");
	scanf("%d",&estoque);
	produtos[contador_produto].estoque = atualizarEstoque(estoque);//transformei estoque em fun��o.
	
	produtos[contador_produto].SKU = 20161 + contador_produto;
}

//exibir produtos e todos seus atributos para o administrador (SKU, NOME, PRE�O, ESTOQUE)
void visualizarProdutos(produto produtos[], int contador_produto){
	for(int i=0;i<contador_produto;i++){
		printf("PRODUTO %d\n", 	i+1);
		printf("SKU: %d\n", produtos[i].SKU);
		printf("Produto: %s\n",produtos[i].nome);
		printf("Pre�o: R$ %.2lf\n",produtos[i].preco);
		printf("Estoque: %d\n\n",produtos[i].estoque);
	}
}

//função para editar os produtos, será incrementada com base no squad 3;
void editarProduto(int busca_id, produto produtos[],int numItens){
	
	char edit_nome[MAX];
	int edit_quantidade;
	int edit_estoque;
	float edit_preco;
	
	int indice = busca_id-1;
 			printf("editando...\n");
 			printf("SKU: %d\n", produtos[indice].SKU);
			printf("Produto: %s\n",produtos[indice].nome);
			printf("Pre�o: R$ %.2lf\n",produtos[indice].preco);
			printf("Estoque: %d\n\n",produtos[indice].estoque);
 		
	 		printf("Novo nome: ");
			scanf("%s",produtos[indice].nome);
			fflush(stdin);
			//produtos[j].nome=edit_nome;
			printf("Novo Preco: ");
			scanf("%f",&produtos[indice].preco);
			fflush(stdin);
			//produtos[j].preco=edit_preco;
			printf("Novo Estoque: ");
			scanf("%d",&produtos[indice].estoque);
			fflush(stdin);
	
}

int main(){
	
	produto produtos[20] = {
        {20161,1,"VOODOO SUBLIME", 27.0,50,0},
        {20162,2,"VOODOO CHARD", 51.0,62,1},
        {20163,3,"VOODOO GOLD", 49.0,15,0}
    }; 
    int estoque=0;
    int numProdutos = 3;
	int contador_produto =3;
	int opcao, retorno_menu, produtoId,quantidade;
	int contador_carrinho=0;
	
	float total;
	int busca_id;
	
	ItemCarrinho carrinho[10];
	int numItens = 0;
	
	//CADASTREI ESSAS DUAS VENDAS PARA VER A DINAMICA DA PARTE DE ADM E VERIFICAR SE A NOVA VENDA GERADA SERIA ANEXADA DA FORMA CORRETA.
	venda vendas[5]={ 
					{1,326.45},
					{2,454.65}
					};
	int contador_venda=2;
	int numero_pedido=3;

	
		
		do{
			listarProdutos(produtos, contador_produto);
			printf("\n1. ADICIONAR PRODUTO AO CARRINHO\n2. EXIBIR CARRINHO\n3. FINALIZAR COMPRA\n4. ENCERRAR SESSAO");
			scanf("%d",&opcao);
						
			switch(opcao){
				case 1:
					printf("Digite o ID do produto: ");
           	 		scanf("%d", &produtoId);
		            printf("Digite a quantidade: ");
		            scanf("%d", &quantidade);
		            adicionarAoCarrinho(carrinho, produtos,&numItens, produtoId, quantidade);
		            contador_carrinho++;
		            system("cls");
		            break;
		        case 2:
		            
					exibirCarrinho( carrinho,  numItens,produtos,  numProdutos);	
		    		break;
		        case 3:
		            cadastrarVenda(vendas,contador_venda,produtos,carrinho, numProdutos, numItens,numero_pedido, numProdutos);
		            //printf("\n\nMOSTRANDO VENDAS CADASTRADAS: \n");
		            //visualizarVendas(vendas, contador_venda);//FUNÇÃO DA PARTE DE ADM, COLOQUEI AQUI APENAS PARA VER SE TAVA SAINDO CORRETAMENTE.
		            zerarCarrinho(carrinho, &numItens);
		            contador_venda++;
		            numero_pedido++;
					break;	
												
				default: 
					printf("\n* DIGITE UMA OPCAO VALIDA *\n\n");
				
				}
       			
			
			
			
		} while (opcao!=4);
			
		
			
						
		  
          
		}
	
		  
