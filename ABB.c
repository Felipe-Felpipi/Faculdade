/*

TRABALHO 3 - COMPONENTES DO GRUPO:
  
- Davi Pinto Queiroz de Oliveira | 
- Felipe Almeida da Silva | 
- Guilherme Teixeira de Sales da Silva | 
- João Fernando Marinho Magalhães Leocádio | 
- Renan Passos das Neves | 
- Ronaldo Lippi Sa Junior | 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// struct com as informações de cada palavra
typedef struct{
	char conteudo[15]; 
	int frequencia; // número de ocorrências
}Palavra;

// struct com as informações de cada elemento/no
typedef struct no{
	Palavra palavra; 
	struct no *esquerdo, *direito;
}No;

// função para atribuir as informações de um novo no
No* registrarNo(char p[15]){
	No *registro = malloc(sizeof(No)); // cria um novo no
	
	// condicional para verificar se o novo no foi criado com sucesso
	if(registro!=NULL){
		strcpy(registro->palavra.conteudo, p); // atribui a palavra inserida
		registro->palavra.frequencia = 1; // como é a primeira vez que ela é inserida, recebe o número de ocorrência como 1
		registro->esquerdo = NULL; // inicia o ponteiro esquerdo como nulo (sem subárvore á esquerda)
		registro->direito = NULL; // inicia o ponteiro direito como nulo (sem subárvore á direita)
	}
	
	else{
		printf("\nNão foi possível registrar a palavra!\n");
	}
	
	return registro;
}

// função para inserir uma nova palavra na árvore
No *inserir(No *raiz, char p[15]){
	// caso a árvore esteja vazia
	if(raiz == NULL){
		return registrarNo(p); // cria e retorna um novo no
	}
	
	// insere as palavras na árvor em ordem alfabética ou adiciona +1 ao número de ocorrências em caso de repetição
	else{
		if(strcmp(p, raiz->palavra.conteudo) < 0){
			raiz->esquerdo = inserir(raiz->esquerdo, p);
		}
		
		else if(strcmp(p, raiz->palavra.conteudo) > 0){
			raiz->direito = inserir(raiz->direito, p);
		}
		
		else{
			raiz->palavra.frequencia++;
		}
	}
	
	return raiz;
}

// função para imprimir os elementos/palavras da árvore em ordem alfabética
void imprimir_ordem_alfabetica(No *raiz){
	// caso esteja vazia
	if(raiz == NULL){
		return;
	}
	
	// imprime a subárvore esquerda
	imprimir_ordem_alfabetica(raiz->esquerdo);
	
	// imprime o no atual
	printf("%s (%d)\n\n", raiz->palavra.conteudo, raiz->palavra. frequencia);
	
	//imprime a subárvore direita
	imprimir_ordem_alfabetica(raiz->direito);
}

// função responsável por construir a árvore binária de busca com base na lista de palavras inseridas pelo usuário
void processarPalavras(char *str[]){
	No *raiz = NULL;
	int i = 0;
	
	// insere todas as palavras da lista na árvore
	while(str[i] != NULL){
		raiz = inserir(raiz, str[i]);
		i++;
	}
	
	imprimir_ordem_alfabetica(raiz);
}

int main(void){
	setlocale(LC_ALL, "Portuguese");
	char *lista_palavras[100];
	char palavra[15];
	int op, i = 0;
	
	
	do{
		op=0;
		
		printf("\n-----------------------------"
		       "\n       MENU DE OPÇÕES"
		       "\n-----------------------------"
		       "\n[1] Adicionar palavra"
		       "\n[2] Imprimir"
		       "\n[3] Finalizar"
		       "\n-----------------------------");
		printf("\nDigite a sua opção: ");
		scanf("%d", &op);
		getchar();
		
		switch(op){
			case 1:
				printf("\nDigite uma palavra: ");
				fgets(palavra, 15, stdin);
				palavra[strcspn(palavra, "\n")] = '\0'; // remove o \n situado no final da palavra, substituindo por '\0'
				lista_palavras[i] = (char *)malloc((strlen(palavra) + 1) * sizeof(char)); // função responsável por alocar a quantidade necessária de memória para a palavra e o '\0' 
                strcpy(lista_palavras[i], palavra); // insere a palavra na lista
                i++;
                lista_palavras[i] = NULL; // define o final da lista
				break;
				
			case 2:
				printf("\nPalavras até o momento:\n\n");
				processarPalavras(lista_palavras);
				printf("\n\n");
				system("PAUSE");
				break;
				
			case 3:
				printf("\nPalavras inseridas:\n\n");
				processarPalavras(lista_palavras);
				printf("\n\n");
				system("PAUSE");
				break;
				
			default:
				printf("\nOpção não disponível!\n");
				break;
		}
		
		system("CLS");
		
	}while(op != 3);
	
	printf("\n");
	
	return 0;
}
