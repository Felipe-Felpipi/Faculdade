/* Avaliação A4: Vendas diárias de uma loja de roupas */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

// struct com os dados por venda
struct Produto{
    int carrinho; // método de validação: 1 - está no carrinho | 0 - não está no carrinho
    int dia;
    int mes;
    int ano;
	char cliente[50]; // método para dividir por cliente
    int codigo;
    char nome[40];
    char marca[30];
    int quantidade;
    float preco_unitario;
    float preco_total;
};

// enum para atribuir o número à sua funcionalidade respectiva
enum opcoes{
    Adicionar = 1,
    Excluir,
    Alterar,
    Exibir,
    ConsultaCodigo,
    ConsultaCliente,
    ConsultaData,
    Encerrar,
};

// função para adicionar os dados de uma venda no arquivo
void adicionar_venda(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    struct Produto produto;
    struct Produto busca;
    char qt[20], resp[4];

	do{
		system("CLS");
	    printf("\n================== ADICIONAR - PRODUTO ==================");

	    // entrada de dados
	    produto.carrinho=1;

	    printf("\n\nData da compra (dd/mm/aaaa): ");
	    scanf("%d/%d/%d", &produto.dia, &produto.mes, &produto.ano);

		getchar();

		printf("\nNome do cliente: ");
	    fgets(produto.cliente, 50, stdin); // função para atribuir a string sem estouro de buffer
	    produto.cliente[strcspn(produto.cliente, "\n")] = 0;  // remove o \n situado no final da string

	    printf("\nCódigo: ");
	    if(scanf("%d", &produto.codigo) != 1 || produto.codigo <= 0) {
	        printf("\nErro: código inválido\n\n");
	        system("PAUSE");
	        system("CLS");
	        return;
	    }

	    getchar();

	    printf("\nProduto: ");
	    fgets(produto.nome, 40, stdin); // função para atribuir a string sem estouro de buffer
	    produto.nome[strcspn(produto.nome, "\n")] = 0;  // remove o \n situado no final da string


	    if(strlen(produto.nome) <= 1){
	        printf("\nErro: Nome do produto inválido\n\n");
	        system("pause");
	        system("cls");
	        return;
	    }


	    printf("\nMarca: ");
	    fgets(produto.marca, 30, stdin); // função para atribuir a string sem estouro de buffer
	    produto.marca[strcspn(produto.marca, "\n")] = 0;  // remove o \n situado no final da string

	    if (strlen(produto.marca) <= 1) {
	        printf("\nErro: Marca do produto inválida\n\n");
	        system("pause");
	        system("cls");
	        return;
	    }

	    fseek(arquivo, 0, SEEK_SET); // Posicionando o cursor para a primeira linha do arquivo

		// verificando se o produto está associado a outro código
	    while (fread(&busca, sizeof(struct Produto), 1, arquivo) == 1) {
	        if (stricmp(produto.nome,busca.nome)==0 && stricmp(produto.marca, busca.marca)==0 && produto.codigo!=busca.codigo){
	            printf("\nErro: Este produto já está atribuído a outro código\n\n");
	            system("PAUSE");
	            system("CLS");
	            return;
	        }
	    }

	    printf("\nQuantidade: ");
	    fgets(qt, sizeof(qt), stdin);
	    // sscanf -> le dados formatados de uma string, especificando com os dados devem ser interpretados
	    if(sscanf(qt, "%d", &produto.quantidade) != 1 || produto.quantidade <= 0) {  // função para definir o produto como inteiro
	        printf("\nErro: quantidade inválida\n\n");
	        system("PAUSE");
	        system("CLS");
	        return;
	    }


	    printf("\nPreço Unitário (Separado por ','): ");
	    if(scanf("%f", &produto.preco_unitario) != 1 || produto.preco_unitario <= 0) {
	        printf("\nErro: preço unitário inválido\n\n");
	        system("PAUSE");
	        system("CLS");
	        return;
	    }

	    getchar();

	    // cálculo do valor total da venda
	    produto.preco_total = produto.quantidade * produto.preco_unitario;

	    if(produto.quantidade >=3){
	        produto.preco_total = produto.preco_total * 0.9;
	    }

	    // gravando os dados coletados no arquivo
	    fwrite(&produto, sizeof(struct Produto), 1, arquivo);

	    printf("\nPRODUTO ADICIONADO\n\n");

	    printf("Deseja adicionar mais um produto (sim ou não)? ");
        fgets(resp, 4, stdin);

	}while(stricmp(resp, "sim")==0);

	printf("\n\n");
    system("PAUSE");
    system("CLS");
}

// função para exibir todos as vendas presentes no arquivo até o momento
void exibir_vendas(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    struct Produto produto;

    printf("\n================== CARRINHO ==================\n\n");

    rewind(arquivo); // move o ponteiro para o início do arquivo

    // loop para leitura de todo o arquivo e exibição de todos os dados das vendas válidas
    while (fread(&produto, sizeof(struct Produto), 1, arquivo) == 1){
        if(produto.carrinho==1){
            printf("******************************\n\n");
            printf("Data: %d/%d/%d\n\n", produto.dia, produto.mes, produto.ano);
            printf("Cliente: %s\n\n", produto.cliente);
            printf("Código: %d\n\n", produto.codigo);
            printf("Produto: %s\n\n", produto.nome);
            printf("Marca: %s\n\n", produto.marca);
            printf("Quantidade: %d\n\n", produto.quantidade);
            printf("Preço unitário: R$ %.2f\n\n", produto.preco_unitario);
            printf("Preço total: R$ %.2f\n\n", produto.preco_total);
            printf("******************************");
            printf("\n\n\n");
        }
    }

    system("PAUSE");
    system("CLS");
}

// função para consultar as vendas de acordo com o código do produto
void consulta_vendas_codigo(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int codigo, encontrado; // encontrado -> método de validação
    struct Produto produto;
    struct Produto disponivel;
    char resp[4];
    long consulta; // armazena a posição no arquivo onde o produto a ser consultado está localizado

    do{
        system("CLS");
        printf("\n================== CONSULTAR - VENDAS (CÓDIGO) ==================\n\n");

        encontrado = 0;

        rewind(arquivo); // move o ponteiro para o início do arquivo

        printf("Códigos até o momento: ");

        // loop para leitura de todo o arquivo e exibição dos códigos validos
        while(fread(&disponivel, sizeof(struct Produto), 1, arquivo) == 1){
            if(disponivel.carrinho==1){
                printf("%d ", disponivel.codigo);
            }
        }


        // entrada do código desejado
        printf("\n\nDigite o código do produto que deseja encontrar: ");
        scanf("%d", &codigo);
		printf("\n\n");

        getchar();

        rewind(arquivo); // move o ponteiro para o início do arquivo

        // é feito um loop para leitura de todo o arquivo em busca do código inserido
        while (fread(&produto, sizeof(struct Produto), 1, arquivo) == 1){
            if(produto.codigo == codigo && produto.carrinho==1){
                printf("******************************\n\n");
	            printf("Data: %d/%d/%d\n\n", produto.dia, produto.mes, produto.ano);
	            printf("Cliente: %s\n\n", produto.cliente);
	            printf("Código: %d\n\n", produto.codigo);
	            printf("Produto: %s\n\n", produto.nome);
	            printf("Marca: %s\n\n", produto.marca);
	            printf("Quantidade: %d\n\n", produto.quantidade);
	            printf("Preço unitário: R$ %.2f\n\n", produto.preco_unitario);
	            printf("Preço total: R$ %.2f\n\n", produto.preco_total);
	            printf("******************************");
	            printf("\n\n\n");
	            encontrado=1;
            }
        }

        if (encontrado==0){
            printf("\nCodigo %d não encontrado!\n", codigo);
            break;
        }

        printf("Deseja consultar outro código (sim ou não)? ");
        fgets(resp, 4, stdin);

      }while(stricmp(resp,"sim")==0); // loop caso o cliente deseje consultar mais de um codigo

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// função para consultar as vendas de acordo com o nome do cliente
void consulta_vendas_cliente(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

	int encontrado; // encontrado -> método de validação
    struct Produto produto;
    struct Produto disponivel;
    char resp[4];
    long consulta; // armazena a posição no arquivo onde o produto a ser consultado está localizado
    char cliente[50];

    do{

        printf("\n================== CONSULTAR - VENDAS (CLIENTE) ==================\n\n");

        encontrado = 0;


        printf("Clientes até o momento:\n\n");

		rewind(arquivo); // move o ponteiro para o início do arquivo

        // loop para leitura de todo o arquivo e exibição dos produtos (incluindo nome e marca) válidos
        while(fread(&disponivel, sizeof(struct Produto), 1, arquivo) == 1){
            if(disponivel.carrinho==1){
                printf("==================\n");
				printf("Nomes: %s\n", disponivel.cliente);
                printf("==================\n\n");

            }
        }

        // entrada do nome desejado
        printf("Digite o nome do cliente que deseja encontrar: ");
    	fgets(cliente, 50, stdin); // função para atribuir a string sem estouro de buffer
    	cliente[strcspn(cliente, "\n")] = 0;  // remove o \n situado no final da string
		printf("\n\n");

		rewind(arquivo); // move o ponteiro para o início do arquivo

        // é feito um loop para leitura de todo o arquivo em busca do nome do cliente
        while (fread(&produto, sizeof(struct Produto), 1, arquivo) == 1){
            if(stricmp(produto.cliente, cliente)==0 && produto.carrinho==1){
                printf("******************************\n\n");
	            printf("Data: %d/%d/%d\n\n", produto.dia, produto.mes, produto.ano);
	            printf("Cliente: %s\n\n", produto.cliente);
	            printf("Código: %d\n\n", produto.codigo);
	            printf("Produto: %s\n\n", produto.nome);
	            printf("Marca: %s\n\n", produto.marca);
	            printf("Quantidade: %d\n\n", produto.quantidade);
	            printf("Preço unitário: R$ %.2f\n\n", produto.preco_unitario);
	            printf("Preço total: R$ %.2f\n\n", produto.preco_total);
	            printf("******************************");
	            printf("\n\n\n");
	            encontrado=1;
            }
        }

        if (encontrado==0){
            printf("\n\nCliente de nome %s não encontrado!\n\n", cliente);
            break;
        }

        printf("Deseja consultar outro cliente (sim ou não)? ");
        fgets(resp, 4, stdin);

        getchar();

      }while(stricmp(resp,"sim")==0); // loop caso o cliente deseje consultar mais de um produto

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// função para consultar as vendas de acordo com a data
void consulta_vendas_data(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int dia, mes, ano, encontrado; // encontrado -> método de validação
    struct Produto produto;
    struct Produto disponivel;
    char resp[4];
    long consulta; // armazena a posição no arquivo onde o produto a ser consultado está localizado

    do{
        system("CLS");
        printf("\n================== CONSULTAR - CARRINHO (DATA) ==================\n\n");

        encontrado = 0;

        rewind(arquivo); // move o ponteiro para o início do arquivo

        printf("Datas até o momento:\n\n");

        // loop para leitura de todo o arquivo e exibição dos códigos validos
        while(fread(&disponivel, sizeof(struct Produto), 1, arquivo) == 1){
            if(disponivel.carrinho==1){
                printf("==================\n");
				printf("DATA: %d/%d/%d\n", disponivel.dia, disponivel.mes, disponivel.ano);
                printf("==================\n\n");
            }
        }


        // entrada do código desejado
        printf("Digite o data que deseja encontrar (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        printf("\n\n");

        getchar();

        rewind(arquivo); // move o ponteiro para o início do arquivo

        // é feito um loop para leitura de todo o arquivo em busca do código inserido
        while (fread(&produto, sizeof(struct Produto), 1, arquivo) == 1){
            if(produto.dia==dia && produto.mes==mes && produto.ano==ano && produto.carrinho==1){
                printf("******************************\n\n");
	            printf("Data: %d/%d/%d\n\n", produto.dia, produto.mes, produto.ano);
	            printf("Cliente: %s\n\n", produto.cliente);
	            printf("Código: %d\n\n", produto.codigo);
	            printf("Produto: %s\n\n", produto.nome);
	            printf("Marca: %s\n\n", produto.marca);
	            printf("Quantidade: %d\n\n", produto.quantidade);
	            printf("Preço unitário: R$ %.2f\n\n", produto.preco_unitario);
	            printf("Preço total: R$ %.2f\n\n", produto.preco_total);
	            printf("******************************");
	            printf("\n\n\n");
	            encontrado=1;
            }
        }

        if (encontrado==0){
            printf("Data %d/%d/%d não encontrada!\n", dia, mes, ano);
            break;
        }

        printf("Deseja consultar outra data (sim ou não)? ");
        fgets(resp, 4, stdin);

      }while(stricmp(resp,"sim")==0); // loop caso o cliente deseje consultar mais de um codigo

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// função para comparar as vendas de acordo com o preço total
int comparar_vendas_valor(const void *a, const void *b){
    struct Produto *produtoA = (struct Produto *)a;
    struct Produto *produtoB = (struct Produto *)b;

    if (produtoA->preco_total < produtoB->preco_total) return 1;
    if (produtoA->preco_total > produtoB->preco_total) return -1;
    return 0;
}

// função para comparar os vendas de acordo com a quantidade
int comparar_vendas_quantidade(const void *a, const void *b){
    struct Produto *produtoA = (struct Produto *)a;
    struct Produto *produtoB = (struct Produto *)b;

    if (produtoA->quantidade < produtoB->quantidade) return 1;
    if (produtoA->quantidade > produtoB->quantidade) return -1;
    return 0;
}

// função para comparar vendas por data
int comparar_vendas_data(const void *a, const void *b){
    struct Produto *produtoA = (struct Produto *)a;
    struct Produto *produtoB = (struct Produto *)b;

    // comparação por ano
    if (produtoA->ano < produtoB->ano) return -1;
    if (produtoA->ano > produtoB->ano) return 1;

    // comparação por mês
    if (produtoA->mes < produtoB->mes) return -1;
    if (produtoA->mes > produtoB->mes) return 1;

    // comparação por dia
    if (produtoA->dia < produtoB->dia) return -1;
    if (produtoA->dia > produtoB->dia) return 1;

    return 0;
}

// função pra verificar se duas vendas têm a mesma data
int mesma_data(struct Produto venda1, struct Produto venda2) {
    return (venda1.dia == venda2.dia && venda1.mes == venda2.mes && venda1.ano == venda2.ano);
}

void relatorio_data(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int total_vendas = 0, i;
    struct Produto produtos[100];
    //struct Produto produto;

    rewind(arquivo); // move o ponteiro para o início do arquivo

    // atribui os dados de cada produto no vetor de struct
    while (fread(&produtos[total_vendas], sizeof(struct Produto), 1, arquivo) == 1) {
        total_vendas++;
    }

    printf("\n================== RELATÓRIO POR DIA ==================\n\n");

    // ordena por data, 1° o ano, depois o mes e por ultimo o dia
    qsort(produtos, total_vendas, sizeof(struct Produto), comparar_vendas_data);

    // loop para imprimir as vendas por cliente
    for (i = 0; i < total_vendas; i++) {

        if (produtos[i].carrinho == 0)  // verifica se o produto esta no carrinho
            continue;

        // pra não repetir a mesma data
        if (i == 0 || !mesma_data(produtos[i], produtos[i - 1])) {
            printf("===========\n");
            printf("Data: %02d/%02d/%02d\n", produtos[i].dia, produtos[i].mes, produtos[i].ano);
            printf("===========\n\n");
        }

        // if(produto.dia==produtos[i].dia && produto.mes==produtos[i].mes && produto.ano==produtos[i].ano && produto.carrinho==1){
        printf("******************************\n\n");
        printf("Cliente: %s\n\n", produtos[i].cliente);
        printf("Código: %d\n\n", produtos[i].codigo);
        printf("Produto: %s\n\n", produtos[i].nome);
        printf("Marca: %s\n\n", produtos[i].marca);
        printf("Quantidade: %d\n\n", produtos[i].quantidade);
        printf("Preço unitário: R$ %.2f\n\n", produtos[i].preco_unitario);
        printf("Preço total: R$ %.2f\n\n", produtos[i].preco_total);
        printf("******************************");
        printf("\n\n\n");
    //}


    }

   /* if (i < total_vendas - 1 && produtos[i].cliente != produtos[i + 1].cliente) {
        	printf("======================================\n\n");
        }*/
}

void relatorio_cliente(FILE *arquivo) {
    setlocale(LC_ALL, "Portuguese");

    struct Produto produtos[100];
    int total_produtos = 0, i, j;

    rewind(arquivo);

    while (fread(&produtos[total_produtos], sizeof(struct Produto), 1, arquivo) == 1) {
        total_produtos++;
    }

    printf("\n================== RELATÓRIO POR CLIENTE ==================\n\n");

    for (i = 0; i < total_produtos; i++) {
        if (produtos[i].carrinho == 0)
            continue;


        int cliente_repetido = 0;
        for (j = 0; j < i; j++) {
            if (strcmp(produtos[i].cliente, produtos[j].cliente) == 0) {
                cliente_repetido = 1;
                break;
            }
        }

        if (cliente_repetido)
            continue;

        printf("******************************\n\n");
        printf("Cliente: %s\n\n", produtos[i].cliente);
        printf("******************************\n\n");

        for (j = 0; j < total_produtos; j++) {
            if (strcmp(produtos[i].cliente, produtos[j].cliente) == 0 && produtos[j].carrinho == 1) {
                printf("Data: %d/%d/%d\n\n", produtos[j].dia, produtos[j].mes, produtos[j].ano);
                printf("Código: %d\n\n", produtos[j].codigo);
                printf("Produto: %s\n\n", produtos[j].nome);
                printf("Marca: %s\n\n", produtos[j].marca);
                printf("Quantidade: %d\n\n", produtos[j].quantidade);
                printf("Preço unitário: R$ %.2f\n\n", produtos[j].preco_unitario);
                printf("Preço total: R$ %.2f\n\n", produtos[j].preco_total);
                printf("_______________________________________\n\n");
            }
        }
    }
}

// função para exibir o relatório geral
void relatorio_geral(FILE *arquivo) {
    setlocale(LC_ALL, "Portuguese");

    int i, j, total_clientes = 0;
    int clientes_registrados[50] = {0};
    struct Produto produtos[100];
    int total_produtos = 0;
    float total_vendas = 0;
    int total_produtos_dia = 0;

    rewind(arquivo); // move o ponteiro para o início do arquivo

	// atribui os dados de cada produto no vetor de struct
    while (fread(&produtos[total_produtos], sizeof(struct Produto), 1, arquivo) == 1) {
        total_produtos++;
    }

	// ordena os itens de acordo com o preço total (definido pela função comparar_vendas_valor)
    qsort(produtos, total_produtos, sizeof(struct Produto), comparar_vendas_valor);

    printf("\n================== RELATÓRIO GERAL ==================\n\n");
	printf("\n-----------------------------\n");
	printf("L I S T A  D E  C O M P R A S");
    printf("\n-----------------------------\n\n");

	// loop para imprimir todos os produtos comprados
    for (i = 0; i < total_produtos; i++) {

    	if (produtos[i].carrinho == 0)  // verifica se o produto esta no carrinho
            continue;

		for(j=0; j < total_produtos; j++){
			if(stricmp(produtos[i].cliente, produtos[j].cliente)!=0){
				total_clientes++;
			}
		}

        printf("******************************\n\n");
        printf("Data: %d/%d/%d\n\n", produtos[i].dia, produtos[i].mes, produtos[i].ano);
        printf("Cliente: %s\n\n", produtos[i].cliente);
        printf("Código: %d\n\n", produtos[i].codigo);
        printf("Produto: %s\n\n", produtos[i].nome);
        printf("Marca: %s\n\n", produtos[i].marca);
        printf("Quantidade: %d\n\n", produtos[i].quantidade);
        printf("Preço unitário: R$ %.2f\n\n", produtos[i].preco_unitario);
        printf("Preço total: R$ %.2f\n\n", produtos[i].preco_total);
        printf("******************************");
        printf("\n\n\n");
        total_vendas += produtos[i].preco_total;
        total_produtos_dia += produtos[i].quantidade;
    }

    printf("===========================================\n\n");

    // ordena os itens de acordo com a quantidade (definido pela função comparar_valor_quantidade)
    qsort(produtos, total_produtos, sizeof(struct Produto), comparar_vendas_quantidade);

    int maxVendido = produtos[0].quantidade;
    int minVendido = produtos[total_produtos-1].quantidade;

   // imprimir os produtos mais vendidos
    printf("- Produto(s) mais vendido(s):\n\n");
    for (i = 0; i < total_produtos; i++){

    	if (produtos[i].carrinho == 0)   // verifica se o produto esta no carrinho
            continue;

        if (produtos[i].quantidade == maxVendido){
            printf("------------------\n");
			printf("Nome: %s\nMarca: %s\n", produtos[i].nome, produtos[i].marca);
            printf("------------------\n");
        }

		else{
            break; // encerra o loop se a quantidade vendida for menor que a quantidade máxima
        }
    }

    // imprimir os produtos menos vendidos
    printf("- Produto(s) menos vendido(s):\n\n");
    for (i = total_produtos - 1; i >= 0; i--){
        if(produtos[i].quantidade == maxVendido){
			continue;
		}
		if (produtos[i].quantidade == minVendido){
            printf("------------------\n");
			printf("Nome: %s\nMarca: %s\n", produtos[i].nome, produtos[i].marca);
            printf("------------------\n");
        }

		else{
            break; // encerra o loop se a quantidade vendida for maior que a quantidade mínima
        }
    }



	printf("\n- Total de clientes: %d\n\n", total_clientes);
	printf("- Quantidade total das vendas: %d\n\n", total_produtos_dia);
	printf("- Valor total das vendas: %.2f\n\n\n", total_vendas);

}

int main(void){
    setlocale(LC_ALL, "Portuguese");

    FILE *arquivo;  // variável de ponteiro de arquivo
    int opcao;
    char resp[4];

    arquivo = fopen("loja_roupa.dat", "w+b"); // abrindo o arquivo para leitura e gravação (caso já exista, o arquivo será sobrescrito)

    // tratamento de erro de abertura do arquivo
    if(arquivo == NULL){
        printf("Erro! Não foi possível abrir o arquivo\n");
        system("PAUSE");
        return 1;
    }

    // apresentação da loja
    printf("\n* * * MEGA STORY * * *\n\n");

    printf("Bem-vindo à Mega Story! A maior loja de vendas online da América Latina. Contamos com um estoque diverso e "
           "\nvasto com roupas do mais alto nível. Garantimos conforto e estilo para quem nós mais nos importamos: VOCÊ!\n\n"
           "Em seguida, você poderá realizar diversas alterações através do nosso menu mega intuitivo. Explore e aproveite!\n\n");

    system("PAUSE");
    system("CLS");

    do{
        // menu com as opções a serem escolhidas pelo cliente
        printf("\nM E N U  - V E N D A \n");
        printf("==========================\n\n"
               "1) Adicionar\n\n"
               "2) Alterar\n\n"
               "3) Excluir\n\n"
               "4) Exibir\n\n"
               "5) Consultar - codigo)\n\n"
               "6) Consultar - cliente\n\n"
               "7) Consultar - data\n\n"
               "8) Encerrar\n\n"
               "==========================\n");

		 // entrada da opção desejado
        printf("\nDigite uma das opções: ");
        scanf("%d", &opcao);

        getchar();

        // switch case para encaminhar a opção digitada para sua respectiva função
        switch(opcao){
            case Adicionar:
                system("CLS");
                adicionar_venda(arquivo);
                break;
            case Alterar:
                system("CLS");
                // função alterar
                break;
            case Excluir:
                system("CLS");
                // função excluir
                break;
            case Exibir:
                system("CLS");
                exibir_vendas(arquivo);
                break;
            case ConsultaCodigo:
                system("CLS");
                consulta_vendas_codigo(arquivo);
                break;
            case ConsultaCliente:
                system("CLS");
                consulta_vendas_cliente(arquivo);
                break;
            case ConsultaData:
                system("CLS");
                consulta_vendas_data(arquivo);
                break;
            case Encerrar:
                printf("\nCOMPRA FINALIZADA!\n\n");
                break;
            default:
                printf("\nOpção inválida\n\n");
                system("PAUSE");
                system("CLS");
                break;
        }
    }while(opcao!=8);

	system("CLS");

    relatorio_data(arquivo);

    system("PAUSE");
    system("CLS");

    relatorio_cliente(arquivo);

    system("PAUSE");
    system("CLS");

    relatorio_geral(arquivo);

    fclose(arquivo); // fechamento do arquivo

    system("PAUSE");

    return 0;
}
