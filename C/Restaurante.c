/*
Avaliacao A4: Vendas diarias de um Restaurante a Quilo
- Renan Passos das Neves  |  
- Guilherme Teixeira de Sales da Silva  |  
- Felipe Almeida da Silva  |  
- Mateus Teixeirao Pontes Nader  |  
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h>

// struct com os dados por pedido
struct Refeicao{
	int compra;
	int dia;
	int mes;
	char cliente[50];
	int pedido;
	char prato[30];
	float peso;
	float preco_prato;
	char bebida[30];
	float preco_unitario_bebida;
	int quantidade_bebida;
	float preco_total_bebida;
	float preco_total;
};

// enum para atribuir o numero a sua funcionalidade respectiva
enum opcoes{
	Adicionar=1,
	Alterar,
	Excluir,
	Exibir,
	ConsultaData,
	ConsultaCliente,
	ConsultaPedido,
	Encerrar
};

// funcao para adicionar os dados de um pedido no arquivo
void adicionar_pedido(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    struct Refeicao refeicao;
    struct Refeicao busca;
    char qt[20], resp1[4], resp2[4], resp3[4], resp4[4];

	do{
		system("CLS");
		refeicao.dia = 0, refeicao.mes = 0, refeicao.preco_total = 0;
	    printf("\n================== ADICIONAR - PEDIDO ==================");

		refeicao.compra=1;

		// entrada dos dados do pedido
		printf("\n\nData da compra (dd/mm): ");
	    scanf("%d/%d", &refeicao.dia, &refeicao.mes);
		if(refeicao.dia <=0 || refeicao.mes <=0){
			printf("\nErro: Data invalida\n\n");
	        system("PAUSE");
	        system("CLS");
	        return;
		}

		getchar();

		printf("\nNome do(a) cliente: ");
	    fgets(refeicao.cliente, 50, stdin); // funcao para atribuir a string sem estouro de buffer
	    refeicao.cliente[strcspn(refeicao.cliente, "\n")] = 0;  // remove o \n situado no final da string
		if (strlen(refeicao.cliente) <= 1) {
	        printf("\nErro: Nome do cliente invalido\n\n");
	        system("PAUSE");
	        system("CLS");
	        return;
	    }


		printf("\nNumero do pedido: ");
	    if(scanf("%d", &refeicao.pedido) != 1 || refeicao.pedido <= 0) {
	        printf("\nErro: Pedido invalido\n\n");
	        system("PAUSE");
	        system("CLS");
	        return;
	    }

		fseek(arquivo, 0, SEEK_SET); // Posicionando o cursor para a primeira linha do arquivo

	    // Realizando uma busca para certificar de que o codigo nao exista nos dados existentes
	    while (fread(&busca, sizeof(struct Refeicao), 1, arquivo) == 1) {
	        if(busca.pedido == refeicao.pedido && busca.compra==1){
	            printf("\nErro: Pedido de numero %d ja realizado\n\n", refeicao.pedido);
	            system("PAUSE");
	            system("CLS");
	            return;
	        }
	    }

	    getchar();


	    printf("\n===================================================");
	    printf("\n\nDeseja comprar um prato de comida (sim ou nao)? ");
	    fgets(resp1, 4, stdin);

	    if(stricmp(resp1, "sim")==0){
	    	getchar();
	    	printf("\nQuentinha (sim ou nao)? ");
	    	fgets(resp2, 4, stdin);

			if(stricmp(resp2, "sim")==0){
				strcpy(refeicao.prato, "Quentinha");
				refeicao.peso=0;

				refeicao.preco_prato=20.50; // R$ 20,00 (Preço fixo) + R$0,50 (Embalagem)
			}

			else{
				strcpy(refeicao.prato, "Balanca");
				printf("\nDigite o peso do prato (Em KG: N,NNN): ");
				if(scanf("%f", &refeicao.peso) != 1 || refeicao.peso <= 0) {
		        printf("\nErro: peso invalido\n\n");
		        system("PAUSE");
		        system("CLS");
		        return;
		   	 	}
				refeicao.preco_prato = refeicao.peso * 40.00; // calculado conforme o peso do prato com preço por kg de R$40,00
		    }
		}

		getchar();

		printf("\n===================================================");
		printf("\n\nDeseja comprar bebida (sim ou nao)? ");
	    fgets(resp3, 4, stdin);

	    getchar();

	    if(stricmp(resp3, "sim")==0){
	    	printf("\nNome da bebida: ");
	    	fgets(refeicao.bebida, 30, stdin);
	    	refeicao.bebida[strcspn(refeicao.bebida, "\n")] = 0;

		    if(strlen(refeicao.bebida) <= 1){
		        printf("\nErro: Nome da bebida invalido\n\n");
		        system("PAUSE");
		        system("CLS");
		        return;
		    }
			printf("\nPreço unitario: ");
			if(scanf("%f", &refeicao.preco_unitario_bebida) != 1 || refeicao.preco_unitario_bebida <= 0) {
		        printf("\nErro: preço unitario invalido\n\n");
		        system("PAUSE");
		        system("CLS");
		        return;
	    	}

			getchar();

			printf("\nQuantidade: ");
			fgets(qt, sizeof(qt), stdin);
	    	// sscanf -> le dados formatados de uma string, especificando com os dados devem ser interpretados
	    	if(sscanf(qt, "%d", &refeicao.quantidade_bebida) != 1 || refeicao.quantidade_bebida <= 0){  // funcao para definir o produto como inteiro
		        printf("\nErro: quantidade invalida\n\n");
		        system("PAUSE");
		        system("CLS");
		        return;
	    	}

			refeicao.preco_total_bebida = refeicao.preco_unitario_bebida * refeicao.quantidade_bebida;
		}

		if(refeicao.quantidade_bebida>0){
			refeicao.preco_total+=refeicao.preco_total_bebida;
		}

		if(stricmp(refeicao.prato, "Balanca")==0 || stricmp(refeicao.prato, "Quentinha")==0){
			refeicao.preco_total+=refeicao.preco_prato;
		}

		printf("\n===================================================");

		// tratamento de erro para evitar o caso de nao serem selecionados pratos e bebidas
		if(stricmp(resp1, "sim")!=0 && stricmp(resp3, "sim")!=0){
			printf("\n\nNenhuma incrementacao realizada!\n\n");
			system("PAUSE");
			system("CLS");
			return;
		}
		else{
			fwrite(&refeicao, sizeof(struct Refeicao), 1, arquivo);
			printf("\n\n\nVENDA FINALIZADA, BOM-APETITE!\n\n\n");
		}

		printf("Deseja adicionar mais um pedido (sim ou nao)? ");
        fgets(resp4, 4, stdin);

	}while(stricmp(resp4, "sim")==0);

    system("CLS");
}

// funcao para alterar uma venda
void alterar_venda(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int pedido, encontrado; // encontrado = metodo de validacao
    struct Refeicao refeicao;
    struct Refeicao disponivel;
    struct Refeicao busca;
    char resp1[4], resp1_1[4], resp1_2[4], resp1_3[4], resp2[4], t[20];
    long alterar; // armazena a posicao no arquivo onde a venda a ser alterada esta localizada

    do{
        system("CLS");
        printf("\n================== ALTERAR - VENDA ==================\n\n");

        encontrado = 0;

        rewind(arquivo); // move o ponteiro para o inicio do arquivo

        printf("Pedidos ate o momento: ");

		rewind(arquivo);

        // loop para leitura de todo o arquivo e exibicao dos codigos validos
        while(fread(&disponivel, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(disponivel.compra==1){
                printf("%d ", disponivel.pedido);
            }
        }

        // entrada do codigo desejado
        printf("\n\nDigite o numero do pedido que deseja alterar: ");
        scanf("%d", &pedido);
		printf("\n\n");

        getchar();

        rewind(arquivo);

         while (fread(&refeicao, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(refeicao.compra==1 && refeicao.pedido==pedido){
                alterar = ftell(arquivo) - sizeof(struct Refeicao); // armazena a posicao do inicio do registro a ser alterado (no arquivo)
                encontrado = 1;
            }
        }

        if (encontrado==0){
            printf("Pedido de numero %d nao encontrado!\n\n", pedido);
            break;
        }

        system("CLS");

        printf("\n================== ALTERAR - VENDA ==================\n\n");

		fseek(arquivo, alterar, SEEK_SET); // move o ponteiro para o inicio do registro a ser alterado (definido pela variavel alterar)

        // e feita a leitura do produto a ser alterado
        fread(&refeicao, sizeof(struct Refeicao), 1, arquivo);
        printf("*************************************************\n\n");
		printf("Data: %02d/%02d\n\n", refeicao.dia, refeicao.mes);
	    printf("Cliente: %s\n\n", refeicao.cliente);
	    printf("Pedido: %d\n\n", refeicao.pedido);

		if(stricmp(refeicao.prato, "Balanca")==0){
			printf("Prato: %s\n\n", refeicao.prato);
	        printf("Peso - Prato (em KG): %.3f\n\n", refeicao.peso);
	        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);
	    }

	    if(stricmp(refeicao.prato, "Quentinha")==0){
	    	printf("Prato: %s\n\n", refeicao.prato);
	        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);

		}


	    if (refeicao.quantidade_bebida > 0) {
	    	printf("----------------------------\n");
	        printf("Bebida: %s\n\n", refeicao.bebida);
	        printf("Preco unitario: R$ %.2f\n\n", refeicao.preco_unitario_bebida);
	        printf("Quantidade: %.d\n\n", refeicao.quantidade_bebida);
	        printf("Preco - Bebida: R$ %.2f\n", refeicao.preco_total_bebida);
	        printf("----------------------------\n\n");
		}

		if(refeicao.preco_prato > 0 && refeicao.quantidade_bebida > 0){
			printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicao.preco_total);
		}
		printf("*************************************************");
	    printf("\n\n\n");

		printf("Deseja alterar o pedido (sim ou nao)? ");
		fgets(resp1, 4, stdin);

		if(stricmp(resp1,"sim")==0){
			system("CLS");
			refeicao.dia = 0, refeicao.mes = 0, refeicao.preco_total = 0;

	    	printf("\n================== ALTERAR - VENDA ==================\n\n");
		    refeicao.compra=1;

			// entrada dos dados do pedido
			printf("\nData da compra (dd/mm): ");
		    scanf("%d/%d", &refeicao.dia, &refeicao.mes);
			if(refeicao.dia <=0 || refeicao.mes <=0){
				printf("\nErro: Data invalida\n\n");
		        system("PAUSE");
		        system("CLS");
		        return;
			}

			getchar();

			printf("\nNome do(a) cliente: ");
		    fgets(refeicao.cliente, 50, stdin); // funcao para atribuir a string sem estouro de buffer
		    refeicao.cliente[strcspn(refeicao.cliente, "\n")] = 0;  // remove o \n situado no final da string

			printf("\nNumero do pedido: ");
		    if(scanf("%d", &refeicao.pedido) <= 0) {
		        printf("\nErro: Pedido invalido\n\n");
		        system("PAUSE");
		        system("CLS");
		        return;
		    }

			fseek(arquivo, 0, SEEK_SET); // Posicionando o cursor para a primeira linha do arquivo

		    // Realizando uma busca para certificar de que o codigo nao exista nos dados existentes
		    while (fread(&busca, sizeof(struct Refeicao), 1, arquivo) == 1) {
		        if (busca.pedido == refeicao.pedido){
		            printf("\nErro: Pedido de numero %d ja realizado\n\n", refeicao.pedido);
		            system("PAUSE");
		            system("CLS");
		            return;
		        }
		    }

		    getchar();


		    printf("\n===================================================");
		    printf("\n\nDeseja comprar um prato de comida (sim ou nao)? ");
		    fgets(resp1_1, 4, stdin);

		    if(stricmp(resp1_1, "sim")==0){
		    	getchar();
		    	printf("\nQuentinha (sim ou nao)? ");
		    	fgets(resp1_2, 4, stdin);

				if(stricmp(resp1_2, "sim")==0){
					strcpy(refeicao.prato, "Quentinha");
					refeicao.peso=0;

					refeicao.preco_prato=20.50; // R$ 20,00 (Preco fixo) + R$0,50 (Embalagem)
				}

				else{
					strcpy(refeicao.prato, "Balanca");
					printf("\nDigite o peso do prato (Em KG: N,NNN): ");
					if(scanf("%f", &refeicao.peso) != 1 || refeicao.peso <= 0) {
			        printf("\nErro: peso invalido\n\n");
			        system("PAUSE");
			        system("CLS");
			        return;
			   	 	}
					refeicao.preco_prato = refeicao.peso * 40.00; // calculado conforme o peso do prato com preco por kg de R$40,00
			    }
			}

			getchar();

			printf("\n===================================================");
			printf("\n\nDeseja comprar bebida (sim ou nao)? ");
		    fgets(resp1_3, 4, stdin);

		    getchar();

		    if(stricmp(resp1_3, "sim")==0){
		    	printf("\nNome da bebida: ");
		    	fgets(refeicao.bebida, 30, stdin);
		    	refeicao.bebida[strcspn(refeicao.bebida, "\n")] = 0;

			    if(strlen(refeicao.bebida) <= 1){
			        printf("\nErro: Nome da bebida invalido\n\n");
			        system("PAUSE");
			        system("CLS");
			        return;
			    }
				printf("\nPreco unitario: ");
				scanf("%f", &refeicao.preco_unitario_bebida);

				getchar();

				printf("\nQuantidade: ");
				scanf("%d", &refeicao.quantidade_bebida);

				refeicao.preco_total_bebida = refeicao.preco_unitario_bebida * refeicao.quantidade_bebida;
			}

			if(refeicao.quantidade_bebida>0){
				refeicao.preco_total+=refeicao.preco_total_bebida;
			}

			if(stricmp(refeicao.prato, "Balanca")==0 || stricmp(refeicao.prato, "Quentinha")==0){
				refeicao.preco_total+=refeicao.preco_prato;
			}

			printf("\n===================================================");

			// tratamento de erro para evitar o caso de nao serem selecionados pratos e bebidas
			if(stricmp(resp1_1, "sim")!=0 && stricmp(resp1_3, "sim")!=0){
				printf("\n\nNenhuma incrementacao realizada!\n\n");
				system("PAUSE");
				system("CLS");
				return;
			}
			else{
				fseek(arquivo, alterar, SEEK_SET); // move o ponteiro para o inicio do registro a ser alterado (definido pela variavel alterar)
				fwrite(&refeicao, sizeof(struct Refeicao), 1, arquivo);
				printf("\n\nVENDA FINALIZADA, BOM-APETITE!\n\n");
			}

		}

		else{
			break;
		}

        printf("Deseja alterar outro pedido (sim ou nao)? ");
        fgets(resp2, 4, stdin);

      }while(stricmp(resp2,"sim")==0); // loop caso o cliente deseje alterar mais de uma venda

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// funcao para excluir uma venda
void excluir_venda(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int pedido, encontrado; // encontrado = metodo de validacao
    struct Refeicao refeicao;
    struct Refeicao disponivel;
    struct Refeicao busca;
    char resp1[4], resp2[4], t[20];
    long excluir; // armazena a posicao no arquivo onde a venda a ser alterada esta localizada

    do{
        system("CLS");
        printf("\n================== EXCLUIR - VENDA ==================\n\n");

        encontrado = 0;

        rewind(arquivo); // move o ponteiro para o inicio do arquivo

        printf("Pedidos ate o momento: ");

		rewind(arquivo);

        // loop para leitura de todo o arquivo e exibicao dos codigos validos
        while(fread(&disponivel, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(disponivel.compra==1){
                printf("%d ", disponivel.pedido);
            }
        }

        // entrada do codigo desejado
        printf("\n\nDigite o numero do pedido que deseja excluir: ");
        scanf("%d", &pedido);
		printf("\n\n");

        getchar();

        rewind(arquivo);

         while (fread(&refeicao, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(refeicao.compra==1 && refeicao.pedido==pedido){
                excluir = ftell(arquivo) - sizeof(struct Refeicao); // armazena a posicao do inicio do registro a ser alterado (no arquivo)
                encontrado = 1;
            }
        }

        if (encontrado==0){
            printf("Pedido de numero %d nao encontrado!\n\n", pedido);
            break;
        }

        system("CLS");

        printf("\n================== EXCLUIR - VENDA ==================\n\n");

		fseek(arquivo, excluir, SEEK_SET); // move o ponteiro para o inicio do registro a ser alterado (definido pela variavel alterar)

        // e feita a leitura do produto a ser alterado
        fread(&refeicao, sizeof(struct Refeicao), 1, arquivo);
        printf("*************************************************\n\n");
		printf("Data: %02d/%02d\n\n", refeicao.dia, refeicao.mes);
	    printf("Cliente: %s\n\n", refeicao.cliente);
	    printf("Pedido: %d\n\n", refeicao.pedido);

		if(stricmp(refeicao.prato, "Balanca")==0){
			printf("Prato: %s\n\n", refeicao.prato);
	        printf("Peso - Prato (em KG): %.3f\n\n", refeicao.peso);
	        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);
	    }

	    if(stricmp(refeicao.prato, "Quentinha")==0){
	    	printf("Prato: %s\n\n", refeicao.prato);
	        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);

		}


	    if (refeicao.quantidade_bebida > 0) {
	    	printf("----------------------------\n");
	        printf("Bebida: %s\n\n", refeicao.bebida);
	        printf("Preco unitario: R$ %.2f\n\n", refeicao.preco_unitario_bebida);
	        printf("Quantidade: %.d\n\n", refeicao.quantidade_bebida);
	        printf("Preco - Bebida: R$ %.2f\n", refeicao.preco_total_bebida);
	        printf("----------------------------\n\n");
		}

		if(refeicao.preco_prato > 0 && refeicao.quantidade_bebida > 0){
			printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicao.preco_total);
		}
		printf("*************************************************");
	    printf("\n\n\n");

		printf("Deseja excluir o pedido (sim ou nao)? ");
		fgets(resp1, 4, stdin);

		getchar();

		if(stricmp(resp1,"sim")==0){
			fseek(arquivo, excluir, SEEK_SET);  // move o ponteiro para o inicio do registro a ser excluido (definido pela variavel excluir)

            refeicao.compra = 0; // seu metodo de validacao e atribuido com 0 (nao esta no carrinho)

            fwrite(&refeicao, sizeof(struct Refeicao), 1, arquivo); // gravando os dados atualizados no arquivo

            printf("\nEXCLUSaO REALIZADA!\n\n");
		}

		else{
			break;
		}

        printf("Deseja excluir outro pedido (sim ou nao)? ");
        fgets(resp2, 4, stdin);

      }while(stricmp(resp2,"sim")==0); // loop caso o cliente deseje alterar mais de uma venda

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// funcao para exibir todos os dados dos pedidos presentes no arquivo ate o momento (conforme cliente e dia)
void exibir_compra(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    struct Refeicao refeicao;

    printf("\n================== VENDAS (ate O MOMENTO) ==================\n\n");

    rewind(arquivo); // move o ponteiro para o inicio do arquivo

	 // loop para leitura de todo o arquivo e exibicao de todos os dados dos pedidos validos
    while (fread(&refeicao, sizeof(struct Refeicao), 1, arquivo) == 1){
    	if(refeicao.compra==1){
			printf("*************************************************\n\n");
			printf("Data: %02d/%02d\n\n", refeicao.dia, refeicao.mes);
		    printf("Cliente: %s\n\n", refeicao.cliente);
		    printf("Pedido: %d\n\n", refeicao.pedido);

			if(stricmp(refeicao.prato, "Balanca")==0){
				printf("Prato: %s\n\n", refeicao.prato);
		        printf("Peso - Prato (em KG): %.3f\n\n", refeicao.peso);
		        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);
		    }

		    if(stricmp(refeicao.prato, "Quentinha")==0){
		    	printf("Prato: %s\n\n", refeicao.prato);
		        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);

			}


		    if (refeicao.quantidade_bebida > 0) {
		    	printf("----------------------------\n");
		        printf("Bebida: %s\n\n", refeicao.bebida);
		        printf("Preco unitario: R$ %.2f\n\n", refeicao.preco_unitario_bebida);
		        printf("Quantidade: %.d\n\n", refeicao.quantidade_bebida);
		        printf("Preco - Bebida: R$ %.2f\n", refeicao.preco_total_bebida);
		        printf("----------------------------\n\n");
			}

			if(refeicao.preco_prato > 0 && refeicao.quantidade_bebida > 0){
				printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicao.preco_total);
			}
			printf("*************************************************");
		    printf("\n\n\n");
		}
    }

    system("PAUSE");
    system("CLS");
}

// funcao para consultar as vendas de acordo com a data
void consulta_vendas_data(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int dia, mes, encontrado; // encontrado = metodo de validacao
    struct Refeicao refeicao;
    struct Refeicao disponivel;
    char resp[4];

    do{
    	dia=0, mes=0;
        system("CLS");
        printf("\n================== CONSULTAR - VENDAS (DATA) ==================\n\n");

        encontrado = 0;

        rewind(arquivo); // move o ponteiro para o inicio do arquivo

        printf("Datas ate o momento:\n\n");

        // loop para leitura de todo o arquivo e exibicao das datas validas
        while(fread(&disponivel, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(disponivel.compra==1){
                printf("==================\n");
				printf("DATA: %02d/%02d\n", disponivel.dia, disponivel.mes);
                printf("==================\n\n");
            }
        }


        // entrada do codigo desejado
        printf("Digite o data que deseja encontrar (dd/mm): ");
        scanf("%d/%d", &dia, &mes);
        printf("\n\n");

        getchar();

        rewind(arquivo); // move o ponteiro para o inicio do arquivo

        // e feito um loop para leitura de todo o arquivo em busca do codigo inserido
        while (fread(&refeicao, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(refeicao.dia==dia && refeicao.mes==mes && refeicao.compra==1){
                printf("*************************************************\n\n");
				printf("Data: %02d/%02d\n\n", refeicao.dia, refeicao.mes);
			    printf("Cliente: %s\n\n", refeicao.cliente);
			    printf("Pedido: %d\n\n", refeicao.pedido);

				if(stricmp(refeicao.prato, "Balanca")==0){
					printf("Prato: %s\n\n", refeicao.prato);
			        printf("Peso - Prato (em KG): %.3f\n\n", refeicao.peso);
			        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);
			    }

			    if(stricmp(refeicao.prato, "Quentinha")==0){
			    	printf("Prato: %s\n\n", refeicao.prato);
			        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);

				}


			    if (refeicao.quantidade_bebida > 0) {
			    	printf("----------------------------\n");
			        printf("Bebida: %s\n\n", refeicao.bebida);
			        printf("Preco unitario: R$ %.2f\n\n", refeicao.preco_unitario_bebida);
			        printf("Quantidade: %.d\n\n", refeicao.quantidade_bebida);
			        printf("Preco - Bebida: R$ %.2f\n", refeicao.preco_total_bebida);
			        printf("----------------------------\n\n");
				}

				if(refeicao.preco_prato > 0 && refeicao.quantidade_bebida > 0){
					printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicao.preco_total);
				}
				printf("*************************************************");
			    printf("\n\n\n");
			    encontrado=1;
			}
		}

        if (encontrado==0){
            printf("Data %02d/%02d nao encontrada!\n\n", dia, mes);
            break;
        }

        printf("Deseja consultar outra data (sim ou nao)? ");
        fgets(resp, 4, stdin);

      }while(stricmp(resp,"sim")==0); // loop caso o cliente deseje consultar mais de um codigo

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// funcao para consultar as vendas de acordo com o nome do cliente
void consulta_vendas_cliente(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

	int encontrado; // encontrado = metodo de validacao
    struct Refeicao refeicao;
    struct Refeicao disponivel;
    char resp[4];
    char cliente[50];

    do{
		system("CLS");
        printf("\n================== CONSULTAR - VENDAS (CLIENTE) ==================\n\n");

        encontrado = 0;


        printf("Clientes ate o momento:\n\n");

		rewind(arquivo); // move o ponteiro para o inicio do arquivo

        // loop para leitura de todo o arquivo e exibicao dos clientes validos
        while(fread(&disponivel, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(disponivel.compra==1){
                printf("==================\n");
				printf("Nomes: %s\n", disponivel.cliente);
                printf("==================\n\n");

            }
        }

        // entrada do nome desejado
        printf("Digite o nome do(a) cliente que deseja encontrar: ");
    	fgets(cliente, 50, stdin); // funcao para atribuir a string sem estouro de buffer
    	cliente[strcspn(cliente, "\n")] = 0;  // remove o \n situado no final da string
		printf("\n\n");

		rewind(arquivo); // move o ponteiro para o inicio do arquivo

        // e feito um loop para leitura de todo o arquivo em busca do nome do cliente
        while (fread(&refeicao, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(stricmp(refeicao.cliente, cliente)==0 && refeicao.compra==1){
                printf("*************************************************\n\n");
				printf("Data: %02d/%02d\n\n", refeicao.dia, refeicao.mes);
			    printf("Cliente: %s\n\n", refeicao.cliente);
			    printf("Pedido: %d\n\n", refeicao.pedido);

				if(stricmp(refeicao.prato, "Balanca")==0){
					printf("Prato: %s\n\n", refeicao.prato);
			        printf("Peso - Prato (em KG): %.3f\n\n", refeicao.peso);
			        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);
			    }

			    if(stricmp(refeicao.prato, "Quentinha")==0){
			    	printf("Prato: %s\n\n", refeicao.prato);
			        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);

				}


			    if (refeicao.quantidade_bebida > 0) {
			    	printf("----------------------------\n");
			        printf("Bebida: %s\n\n", refeicao.bebida);
			        printf("Preco unitario: R$ %.2f\n\n", refeicao.preco_unitario_bebida);
			        printf("Quantidade: %.d\n\n", refeicao.quantidade_bebida);
			        printf("Preco - Bebida: R$ %.2f\n", refeicao.preco_total_bebida);
			        printf("----------------------------\n\n");
				}

				if(refeicao.preco_prato > 0 && refeicao.quantidade_bebida > 0){
					printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicao.preco_total);
				}
				printf("*************************************************");
			    printf("\n\n\n");
			    encontrado=1;
			}
        }

        if (encontrado==0){
            printf("Cliente de nome %s nao encontrado!\n\n", cliente);
            break;
        }

        printf("Deseja consultar outro cliente (sim ou nao)? ");
        fgets(resp, 4, stdin);

        getchar();

      }while(stricmp(resp,"sim")==0); // loop caso o cliente deseje consultar mais de um produto

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// funcao para consultar as vendas de acordo com o pedido
void consulta_vendas_pedido(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int pedido, encontrado; // encontrado = metodo de validacao
    struct Refeicao refeicao;
    struct Refeicao disponivel;
    char resp[4];

    do{
        system("CLS");
        printf("\n================== CONSULTAR - VENDAS (PEDIDO) ==================\n\n");

        encontrado = 0;

        rewind(arquivo); // move o ponteiro para o inicio do arquivo

        printf("Pedidos ate o momento: ");

        // loop para leitura de todo o arquivo e exibicao dos pedidos validos
        while(fread(&disponivel, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(disponivel.compra==1){
                printf("%d ", disponivel.pedido);
            }
        }


        // entrada do pedido desejado
        printf("\n\nDigite o codigo do produto que deseja encontrar: ");
        scanf("%d", &pedido);
		printf("\n\n");

        getchar();

        rewind(arquivo); // move o ponteiro para o inicio do arquivo

        // e feito um loop para leitura de todo o arquivo em busca do pedido inserido
        while (fread(&refeicao, sizeof(struct Refeicao), 1, arquivo) == 1){
            if(refeicao.pedido == pedido && refeicao.compra==1){
                printf("*************************************************\n\n");
				printf("Data: %02d/%02d\n\n", refeicao.dia, refeicao.mes);
			    printf("Cliente: %s\n\n", refeicao.cliente);
			    printf("Pedido: %d\n\n", refeicao.pedido);

				if(stricmp(refeicao.prato, "Balanca")==0){
					printf("Prato: %s\n\n", refeicao.prato);
			        printf("Peso - Prato (em KG): %.3f\n\n", refeicao.peso);
			        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);
			    }

			    if(stricmp(refeicao.prato, "Quentinha")==0){
			    	printf("Prato: %s\n\n", refeicao.prato);
			        printf("Preco - Prato: %.2f\n\n", refeicao.preco_prato);

				}


			    if (refeicao.quantidade_bebida > 0) {
			    	printf("----------------------------\n");
			        printf("Bebida: %s\n\n", refeicao.bebida);
			        printf("Preco unitario: R$ %.2f\n\n", refeicao.preco_unitario_bebida);
			        printf("Quantidade: %.d\n\n", refeicao.quantidade_bebida);
			        printf("Preco - Bebida: R$ %.2f\n", refeicao.preco_total_bebida);
			        printf("----------------------------\n\n");
				}

				if(refeicao.preco_prato > 0 && refeicao.quantidade_bebida > 0){
					printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicao.preco_total);
				}
				printf("*************************************************");
			    printf("\n\n\n");
			    encontrado=1;
			}
        }

        if (encontrado==0){
            printf("Pedido %d nao encontrado!\n\n", pedido);
            break;
        }

        printf("Deseja consultar outro pedido (sim ou nao)? ");
        fgets(resp, 4, stdin);

      }while(stricmp(resp,"sim")==0); // loop caso o cliente deseje consultar mais de um pedido

    printf("\n");
    system("PAUSE");
    system("CLS");
}

// funcao para comparar as vendas de acordo com o preco total
int comparar_produtos_valor(const void *a, const void *b) {
    struct Refeicao *produtoA = (struct Refeicao *)a;
    struct Refeicao *produtoB = (struct Refeicao *)b;

    if (produtoA->preco_total < produtoB->preco_total) return 1;
    if (produtoA->preco_total > produtoB->preco_total) return -1;
    return 0;
}

// funcao para comparar vendas por data
int comparar_vendas_data(const void *a, const void *b){
    struct Refeicao *refeicaoA = (struct Refeicao *)a;
    struct Refeicao *refeicaoB = (struct Refeicao *)b;

    // comparacao por mes
    if (refeicaoA->mes < refeicaoB->mes) return -1;
    if (refeicaoA->mes > refeicaoB->mes) return 1;

    // comparacao por dia
    if (refeicaoA->dia < refeicaoB->dia) return -1;
    if (refeicaoA->dia > refeicaoB->dia) return 1;

    return 0;
}

// funcao pra verificar se duas vendas tem a mesma data
int mesma_data(struct Refeicao venda1, struct Refeicao venda2) {
    return (venda1.dia == venda2.dia && venda1.mes == venda2.mes);
}

// funcao para exibir o relatorio por dia
void relatorio_dia(FILE *arquivo) {
    setlocale(LC_ALL, "Portuguese");

    int total_vendas = 0, i;
    struct Refeicao refeicoes[100];

    rewind(arquivo);

    while (fread(&refeicoes[total_vendas], sizeof(struct Refeicao), 1, arquivo) == 1) {
        total_vendas++;
    }

    printf("\n================== RELATORIO POR DIA ==================\n\n");

    qsort(refeicoes, total_vendas, sizeof(struct Refeicao), comparar_vendas_data);

    int clientes_do_dia = 0;
    float valor_total_do_dia = 0;
    int novo_dia = 1;

    for (i = 0; i < total_vendas; i++) {
        if (refeicoes[i].compra == 0)
            continue;

        if (i == 0 || !mesma_data(refeicoes[i], refeicoes[i - 1])) {
            if (i != 0) {

                printf("==========================================================\n");
                printf("Total de clientes do dia: %d\n", clientes_do_dia);
                printf("Valor total de vendas do dia: R$ %.2f\n", valor_total_do_dia);
                printf("==========================================================\n\n");


                clientes_do_dia = 0;
                valor_total_do_dia = 0;
            }

            printf("==========================================================\n");
            printf("                        %02d/%02d\n", refeicoes[i].dia, refeicoes[i].mes);
            printf("==========================================================\n\n");
        }

        clientes_do_dia++;
        valor_total_do_dia += refeicoes[i].preco_total;

        printf("*************************************************\n\n");
        printf("Data: %02d/%02d\n\n", refeicoes[i].dia, refeicoes[i].mes);
        printf("Cliente: %s\n\n", refeicoes[i].cliente);
        printf("Pedido: %d\n\n", refeicoes[i].pedido);

        if (stricmp(refeicoes[i].prato, "Balanca") == 0) {
            printf("Prato: %s\n\n", refeicoes[i].prato);
            printf("Peso - Prato (em KG): %.3f\n\n", refeicoes[i].peso);
            printf("Preco - Prato: %.2f\n\n", refeicoes[i].preco_prato);
        }

        if (stricmp(refeicoes[i].prato, "Quentinha") == 0) {
            printf("Prato: %s\n\n", refeicoes[i].prato);
            printf("Preco - Prato: %.2f\n\n", refeicoes[i].preco_prato);
        }

        if (refeicoes[i].quantidade_bebida > 0) {
            printf("----------------------------\n");
            printf("Bebida: %s\n\n", refeicoes[i].bebida);
            printf("Preco unitario: R$ %.2f\n\n", refeicoes[i].preco_unitario_bebida);
            printf("Quantidade: %.d\n\n", refeicoes[i].quantidade_bebida);
            printf("Preco - Bebida: R$ %.2f\n", refeicoes[i].preco_total_bebida);
            printf("----------------------------\n\n");
        }

        if (refeicoes[i].preco_prato > 0 && refeicoes[i].quantidade_bebida > 0) {
            printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicoes[i].preco_total);
        }

        printf("*************************************************\n\n");
    }


    if (total_vendas > 0) {
        printf("==========================================================\n");
        printf("Total de clientes do dia: %d\n", clientes_do_dia);
        printf("Valor total de vendas do dia: R$ %.2f\n", valor_total_do_dia);
        printf("==========================================================\n\n");
    }
}

void relatorio_mes(FILE *arquivo) {
    setlocale(LC_ALL, "Portuguese");

    int total_vendas = 0, i;
    struct Refeicao refeicoes[100];

    rewind(arquivo);

    while (fread(&refeicoes[total_vendas], sizeof(struct Refeicao), 1, arquivo) == 1) {
        total_vendas++;
    }

    printf("\n================== RELATORIO POR MES ==================\n\n");

    qsort(refeicoes, total_vendas, sizeof(struct Refeicao), comparar_vendas_data);

    int clientes_do_mes = 0;
    float valor_total_do_mes = 0;
    int mes_atual = -1;

    for (i = 0; i < total_vendas; i++) {
        if (refeicoes[i].compra == 0)
            continue;

        if (mes_atual == -1 || refeicoes[i].mes != mes_atual) {
            if (mes_atual != -1) {

                printf("==========================================================\n");
                printf("Total de clientes do mes %d: %d\n", mes_atual, clientes_do_mes);
                printf("Valor total de vendas do mes %d: R$ %.2f\n", mes_atual, valor_total_do_mes);
                printf("==========================================================\n\n");


                clientes_do_mes = 0;
                valor_total_do_mes = 0;
            }

            mes_atual = refeicoes[i].mes;
            printf("==========================================================\n");
            printf("                        MES %d\n", mes_atual);
            printf("==========================================================\n\n");
        }

        clientes_do_mes++;
        valor_total_do_mes += refeicoes[i].preco_total;

        printf("*************************************************\n");
        printf("Data: %02d/%02d\n", refeicoes[i].dia, refeicoes[i].mes);
        printf("Cliente: %s\n", refeicoes[i].cliente);
        printf("Pedido: %d\n", refeicoes[i].pedido);

        if (stricmp(refeicoes[i].prato, "Balanca") == 0) {
            printf("Prato: %s\n", refeicoes[i].prato);
            printf("Peso - Prato (em KG): %.3f\n", refeicoes[i].peso);
            printf("Preco - Prato: %.2f\n", refeicoes[i].preco_prato);
        }

        if (stricmp(refeicoes[i].prato, "Quentinha") == 0) {
            printf("Prato: %s\n", refeicoes[i].prato);
            printf("Preco - Prato: %.2f\n", refeicoes[i].preco_prato);
        }

        if (refeicoes[i].quantidade_bebida > 0) {
            printf("----------------------------\n");
            printf("Bebida: %s\n", refeicoes[i].bebida);
            printf("Preco unitario: R$ %.2f\n", refeicoes[i].preco_unitario_bebida);
            printf("Quantidade: %d\n", refeicoes[i].quantidade_bebida);
            printf("Preco - Bebida: R$ %.2f\n", refeicoes[i].preco_total_bebida);
            printf("----------------------------\n");
        }

        if (refeicoes[i].preco_prato > 0 && refeicoes[i].quantidade_bebida > 0) {
            printf("Preco total (incluindo prato e bebida): R$ %.2f\n", refeicoes[i].preco_total);
        }

        printf("*************************************************\n\n");
    }


    if (mes_atual != -1) {
        printf("==========================================================\n");
        printf("Total de clientes do mes %d: %d\n", mes_atual, clientes_do_mes);
        printf("Valor total de vendas do mes %d: R$ %.2f\n", mes_atual, valor_total_do_mes);
        printf("==========================================================\n\n");
    }
}

/*// funcao para exibir o relatorio por dia
void relatorio_cliente(FILE *arquivo) {
    setlocale(LC_ALL, "Portuguese");

    struct Refeicao refeicoes[100];
    int total_vendas = 0, i, j;

    rewind(arquivo);  // move o ponteiro para o inicio do arquivo

	// atribui os dados de cada produto no vetor de struct
    while (fread(&refeicoes[total_vendas], sizeof(struct Refeicao), 1, arquivo) == 1) {
        total_vendas++;
    }

    printf("\n================== RELATORIO POR CLIENTE ==================\n\n");

	 // loop para imprimir as vendas por cliente
    for (i = 0; i < total_vendas; i++) {

        if (refeicoes[i].compra == 0) // verifica se o pedido esta no carrinho
            continue;


        int cliente_repetido = 0;
        for (j = 0; j < i; j++) {
            if (strcmp(refeicoes[i].cliente, refeicoes[j].cliente) == 0) {
                cliente_repetido = 1;
                break;
            }
        }

        if (cliente_repetido)
            continue;

        printf("==========================================================\n");
		printf("                         %s\n", refeicoes[i].cliente);
    	printf("==========================================================\n\n");


        for (j = 0; j < total_vendas; j++) {
            if (strcmp(refeicoes[i].cliente, refeicoes[j].cliente) == 0 && refeicoes[j].compra == 1) {
            	printf("*************************************************\n\n");
				printf("Data: %02d/%02d\n\n", refeicoes[i].dia, refeicoes[i].mes);
			    printf("Cliente: %s\n\n", refeicoes[i].cliente);
			    printf("Pedido: %d\n\n", refeicoes[i].pedido);

				if(stricmp(refeicoes[i].prato, "Balanca")==0){
					printf("Prato: %s\n\n", refeicoes[i].prato);
			        printf("Peso - Prato (em KG): %.3f\n\n", refeicoes[i].peso);
			        printf("Preco - Prato: %.2f\n\n", refeicoes[i].preco_prato);
			    }

			    if(stricmp(refeicoes[i].prato, "Quentinha")==0){
			    	printf("Prato: %s\n\n", refeicoes[i].prato);
			        printf("Preco - Prato: %.2f\n\n", refeicoes[i].preco_prato);

				}


			    if (refeicoes[i].quantidade_bebida > 0) {
			    	printf("----------------------------\n");
			        printf("Bebida: %s\n\n", refeicoes[i].bebida);
			        printf("Preco unitario: R$ %.2f\n\n", refeicoes[i].preco_unitario_bebida);
			        printf("Quantidade: %.d\n\n", refeicoes[i].quantidade_bebida);
			        printf("Preco - Bebida: R$ %.2f\n", refeicoes[i].preco_total_bebida);
			        printf("----------------------------\n\n");
				}

				if(refeicoes[i].preco_prato > 0 && refeicoes[i].quantidade_bebida > 0){
					printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicoes[i].preco_total);
				}
				printf("*************************************************");
			    printf("\n\n\n");
            }
        }
    }
}*/

// funcao para exibir o relatorio geral
void relatorio_geral(FILE *arquivo){
    setlocale(LC_ALL, "Portuguese");

    int i, j, total_clientes = 0;
    struct Refeicao refeicao[100];
    int total_pedidos = 0;
    float total_preco_pedidos = 0;
    int total_bebidas = 0;
    int total_pratos = 0;

    rewind(arquivo); // move o ponteiro para o inicio do arquivo

	// atribui os dados de cada produto no vetor de struct
    while (fread(&refeicao[total_pedidos], sizeof(struct Refeicao), 1, arquivo) == 1) {
        total_pedidos++;
    }

	// ordena os pedidos de acordo com o preco total (definido pela funcao comparar_produtos_valor)
    qsort(refeicao, total_pedidos, sizeof(struct Refeicao), comparar_produtos_valor);

    printf("\n================== RELATORIO GERAL (ano) ==================\n\n");
	 printf("==========================================================\n");
	printf("                L I S T A  D E  C O M P R A\n");
	printf("==========================================================\n\n");

	// loop para imprimir todos os pedidos realizados
    for (i = 0; i < total_pedidos; i++) {

		if (refeicao[i].compra == 0)  // verifica se o produto esta no carrinho
            continue;


		int cliente_repetido = 0;
		for(j=0; j<total_clientes;j++){
			if(strcmp(refeicao[i].cliente, refeicao[j].cliente)==0){
				cliente_repetido = 1;
				break;
			}
		}

		if(cliente_repetido==0){
			total_clientes++;
		}

	    printf("*************************************************\n\n");
		printf("Data: %02d/%02d\n\n", refeicao[i].dia, refeicao[i].mes);
	    printf("Cliente: %s\n\n", refeicao[i].cliente);
	    printf("Pedido: %d\n\n", refeicao[i].pedido);

		if(stricmp(refeicao[i].prato, "Balanca")==0){
			printf("Prato: %s\n\n", refeicao[i].prato);
	        printf("Peso - Prato (em KG): %.3f\n\n", refeicao[i].peso);
	        printf("Preco - Prato: %.2f\n\n", refeicao[i].preco_prato);
	    }

	    if(stricmp(refeicao[i].prato, "Quentinha")==0){
	    	printf("Prato: %s\n\n", refeicao[i].prato);
	        printf("Preco - Prato: %.2f\n\n", refeicao[i].preco_prato);

		}


	    if (refeicao[i].quantidade_bebida > 0) {
	    	printf("----------------------------\n");
	        printf("Bebida: %s\n\n", refeicao[i].bebida);
	        printf("Preco unitario: R$ %.2f\n\n", refeicao[i].preco_unitario_bebida);
	        printf("Quantidade: %.d\n\n", refeicao[i].quantidade_bebida);
	        printf("Preco - Bebida: R$ %.2f\n", refeicao[i].preco_total_bebida);
	        printf("----------------------------\n\n");
		}

		if(refeicao[i].preco_prato > 0 && refeicao[i].quantidade_bebida > 0){
			printf("Preco total (incluindo prato e bebida): R$ %.2f\n\n", refeicao[i].preco_total);
		}

		printf("*************************************************");
	    printf("\n\n\n");

		if(strlen(refeicao[i].bebida) > 0){
	    	total_bebidas += refeicao[i].quantidade_bebida;
		}

	    if(stricmp(refeicao[i].prato, "Quentinha")==0 || stricmp(refeicao[i].prato, "Balanca")==0){
	    	total_pratos++;
		}

	    total_preco_pedidos += refeicao[i].preco_total;

	}

	printf("==========================================================\n\n");

	printf("\n- Total de clientes: %d\n\n", total_clientes);
	printf("- Quantidade total de pedidos: %d\n\n", total_pedidos);

	if(total_bebidas>=1){
		printf("- Quantidade total de bebidas: %d\n\n", total_bebidas);
	}

	if(total_pratos>=1){
		printf("- Quantidade total de pratos: %d\n\n", total_pratos);
	}

	printf("- Valor total das vendas: %.2f\n\n\n", total_preco_pedidos);

}

int main(void){
	setlocale(LC_ALL, "Portuguese");

    FILE *arquivo; // variavel de ponteiro de arquivo
    int opcao, n_pedido=0; // n = numero de clientes | n_pedido = numero de pedidos | dia = numero de dias
    char resp1[4], resp2[4];

    arquivo = fopen("taste_food.dat", "w+b"); // abrindo o arquivo para leitura e gravacao (caso ja exista, o arquivo sera sobrescrito)

    // tratamento de erro de abertura do arquivo
    if(arquivo == NULL){
        printf("Erro! Nao foi possivel abrir o arquivo\n");
        system("PAUSE");
        return 1;
    }

	// apresentacao do Restaurante
    printf("\n* * * TASTE FOOD * * *\n\n");

    printf("Bem-vindo a TASTE FOOD! Um dos restaurantes mais reconhecidos do Brasil. Comida caseira e de qualidade"
           "\ne a chave para um cliente feliz! Se delicie em nosso self-service com opcoes para todos os gostos!\n\n"
           "====================\n"
           "PESO POR KG: R$40,00\n"
           "====================\n\n"
           "Em seguida, voce podera realizar diversas aplicacoes atraves do nosso menu mega intuitivo. Explore e aproveite!\n\n");

    system("PAUSE");
    system("CLS");

    do{
		// menu com as opcoes a serem escolhidas pelo cliente
	    printf("\nM E N U - V E N D A S");
	    printf("\n===============================\n\n"
	           "1) Adicionar prato(s) e/ou bebida(s)\n\n"
	           "2) Alterar prato(s) e/ou bebida(s)\n\n"
	           "3) Excluir prato(s) e/ou bebida(s)\n\n"
	           "4) Exibir todos os prato(s) e/ou bebida(s)\n\n"
	           "5) Consultar pedido por data\n\n"
	           "6) Consultar pedido por cliente\n\n"
	           "7) Consultar pedido por codido\n\n"
	           "8) Encerrar programa de vendas e mostrar relatorios\n\n"
	           "===============================\n");

		// entrada da opcao desejado
	    printf("\nDigite uma das opcoes: ");
	    scanf("%d", &opcao);

	    getchar();

		// switch case para encaminhar a opcao digitada para sua respectiva funcao
	    switch(opcao){
	        case Adicionar:
	            system("CLS");
	           	adicionar_pedido(arquivo);
	            break;
	        case Alterar:
	            system("CLS");
	           	alterar_venda(arquivo);
	            break;
	        case Excluir:
	            system("CLS");
	           	excluir_venda(arquivo);
	            break;
	        case Exibir:
	            system("CLS");
	            exibir_compra(arquivo);
	            break;
	        case ConsultaData:
	            system("CLS");
	            consulta_vendas_data(arquivo);
	            break;
	        case ConsultaCliente:
	            system("CLS");
	            consulta_vendas_cliente(arquivo);
	            break;
	        case ConsultaPedido:
	            system("CLS");
	            consulta_vendas_pedido(arquivo);
	            break;
	        case Encerrar:
	            printf("\nCOMPRA FINALIZADA, BOM-APETITE!\n\n");
	            break;
	        default:
	            printf("\nOpcao invalida\n\n");
	            system("PAUSE");
	            system("CLS");
	            break;
	    }
    }while(opcao!=8);

	system("CLS");

	relatorio_dia(arquivo);

	system("PAUSE");
	system("CLS");

    relatorio_mes(arquivo);

	system("PAUSE");
	system("CLS");

	//relatorio_cliente(arquivo);

	//system("PAUSE");
	//system("CLS");


	relatorio_geral(arquivo);

	system("PAUSE");
	system("CLS");

	fclose(arquivo); // fechamento do arquivo

	system("CLS");
    printf("\n* * * OBRIGADO * * *\n\n");
    printf("Agradecemos por utilizar o nosso menu de vendas. Ele foi desenvolvido para facilitar o entendimento e \nnavegacao do comeco ao fim. Obrigado por confiar na Taste Food!\n\n\n");
	printf("DESENVOLVEDORES\n");
 	printf("-----------------------------------------------------\n\n"
           "- Renan Passos das Neves  |  1230109874\n\n"
           "- Guilherme Teixeira de Sales da Silva  |  1230107116\n\n"
           "- Felipe Almeida da Silva  |  1230106979\n\n"
           "- Mateus Teixeirao Pontes Nader  |  1230202583\n\n"
           "-----------------------------------------------------\n\n\n");

	system("PAUSE");

    return 0;
}
