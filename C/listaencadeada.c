/*

TRABALHO 1 - COMPONENTES DO GRUPO:
  
- Davi Pinto Queiroz de Oliveira | 
- Felipe Almeida da Silva | 
- Guilherme Teixeira de Sales da Silva | 
- João Fernando Marinho Magalhães Leocádio | 
- Renan Passos das Neves | 
- Ronaldo Lippi Sa Junior | 

*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// estrutura de cada elemento (no) da Lista
typedef struct no{
	int num;
	struct no *prox;
}No;

// função para adicionar um elemento no começo da lista
void adicionar_no_inicio(No **Lista, int valor){
	No *novo_elemento = malloc(sizeof(No)); // cria um novo no

	// estrutura condicional para verificar se o novo no foi criado com sucesso
	if(novo_elemento){
		novo_elemento->num = valor; // atribuição do valor inserido pelo usuário
		novo_elemento->prox = *Lista; // o próximo elemento será o antigo primeiro elemento da lista (Ex: NULL, em caso de apenas um elemento)
		*Lista = novo_elemento; // a lista aponta para o novo elemento criado
	}

	else{
		printf("\nErro! Não possível inserir um novo elemento\n");
	}

}

// função para adicionar um elemento ao final da lista
void adicionar_no_final(No **Lista, int valor){
	No *novo_elemento = malloc(sizeof(No)); // cria um novo no
	No *aux = *Lista; // cria um ponteiro auxiliar para manter o conteúdo da Lista

	// estrutura condicional para verificar se o novo no foi criado com sucesso
	if(novo_elemento){
		novo_elemento->num = valor; // atribuição do valor inserido pelo usuário
		novo_elemento->prox = NULL; // como este será sempre o último elemento da lista, o próximo será sempre NULL;

		// em caso de lista vazia, não terá diferença em adicionar no início ou final
		if(*Lista == NULL){
			*Lista = novo_elemento;
		}

		// o ponteiro auxiliar percorre todo o conteúdo da lista até chegar no último elemento
		else{
			while(aux->prox){
				aux = aux->prox;
			}

			aux->prox = novo_elemento; // o próximo no do antigo último elemento será o atual último elemento
		}
	}

	else{
		printf("Erro! Não possível inserir um novo elemento");
	}
}

// função para adicionar um elemento em uma posição especifica
void adicionar_ponto_especifico(No** Lista, int valor, int posicao) {

    No *novo_elemento = malloc(sizeof(No)); // cria um novo no
    novo_elemento->num = valor; // atribui o valor ao novo no
    novo_elemento->prox = NULL;

    if (posicao == 0 || posicao == 1 || *Lista == NULL) {  // adiciona no inicio, se a posição for 0 ou 1 ou a lista vazia
        novo_elemento->prox = *Lista;
        *Lista = novo_elemento; // atualiza o inicio da lista pra ser o novo elemento
    }
	else {
        No *aux = *Lista; // ponteiro auxiliar q percorre a lista
        int i = 1;     // o valor * i * diz em q posição a lista começa

        while (aux != NULL && i < posicao - 1) { // percorre a lista ate o no anterior a posição escolhida pelo usuario
            aux = aux->prox; // avança pro proximo no na lista
            i++;
        }

        if (aux != NULL) {   // verifica se a posição especificada é valida na lista
            novo_elemento->prox = aux->prox;
            aux->prox = novo_elemento;
        }
		else {      // add no final caso a posição escolhida seja maior q a lista
			aux = *Lista;
			while(aux->prox != NULL){ // percorre a lista ate o ultimo no

            	aux = aux->prox;
        	}
        	aux->prox = novo_elemento; // adiciona o novo elemento depois do ultimo no encontrado
    	}
    }

}

// função para exibir os elementos da Lista até o momento
void listar_todos_elementos(No *Lista){

	No *aux = Lista; // cria um ponteiro auxiliar para manter o conteúdo da Lista

	// o ponteiro auxiliar irá percorrer e imprimir todo os elementos presentes na Lista
	while(aux){
		printf("%d ", aux->num);
		aux=aux->prox;
	}
}

// função para listar um elemento específico da lista
void listar_elemento_especifico(No *Lista, int valor){
	No *aux = Lista; // cria um ponteiro auxiliar para manter o conteúdo da Lista

	// percorre a lista em busca do elemento
	while(aux){
		if(aux->num == valor){
			printf("\nElemento encontrado: %d\n", aux->num);
			return;
		}
		aux = aux->prox;
	}
	printf("\nElemento %d não encontrado na lista.\n", valor);
}

// função para excluir o primeiro elemento da lista
No* excluir_inicio(No **Lista){

    No *remover = NULL; // ponteiro onde ficará alocado o elemento a ser removido
	No *aux = *Lista; // cria um ponteiro auxiliar para manter o conteúdo da Lista

	if(*Lista){
		if((*Lista)->prox == NULL){  // condicional caso o elemento a ser removido seja o único no da Lista
			remover = *Lista;
			*Lista = NULL;
		}

		else{
                remover = aux; // atribui ao ponteiro o primeiro elemento
                *Lista = (*Lista)->prox;// atribui ao ponteiro o segundo nó passando agora ser o primeiro
		    }
        }
    return remover;
}

// função para excluir o último elemento da lista
No* excluir_final(No **Lista){
	No *remover = NULL; // ponteiro onde ficará alocado o elemento a ser removido
	No *aux = *Lista; // cria um ponteiro auxiliar para manter o conteúdo da Lista

	// condicional para verificar se a lista não está vazia
	if(*Lista){
		if((*Lista)->prox == NULL){  // condicional caso o elemento a ser removido seja o único no da Lista
			remover = *Lista;
			*Lista = NULL;
		}

		else{

			while(aux->prox->prox != NULL){  // percorre o conteúdo da Lista até o penúltimo elemento
				aux = aux->prox;
			}

			remover = aux->prox; // atribui ao ponteiro remover o último elemento que será excluído
			aux->prox = NULL; // o ponteiro auxiliar apontará para NULL (ignora o último elemento a ser retirado da lista)
		}
	}

	return remover;
}

// função para selecionar o elemento da lista a ser excluído pelo usuário
No* excluir_ponto_especifico(No **Lista, int valor_a_remover){
	No *remover = NULL; // ponteiro onde ficará alocado o elemento a ser removido
	No *aux = *Lista; // cria um ponteiro auxiliar para manter o conteúdo da Lista

	// condicional para verificar se a lista não está vazia
	if(*Lista){
		if((*Lista)->num == valor_a_remover){  // condicional caso o elemento a ser removido seja o primeiro no da Lista
			remover = *Lista;
			*Lista = remover->prox;
		}

		else{

			while(aux->prox && aux->prox->num != valor_a_remover){  // percorre o conteúdo da Lista em busca do elemento inserido pelo usuário
				aux = aux->prox;
			}

			if(aux->prox){
				remover = aux->prox; // atribui ao ponteiro remover o elemento que será excluído
				aux->prox = remover->prox; // o ponteiro auxiliar apontará para o próximo elemento do no a ser removido (ignora o elemento a ser retirado da lista)
			}
		}
	}

	return remover;
}

// função para liberar todos os elementos da lista
void liberar_lista(No **Lista){

	No *aux;

    // Itera pela lista, liberando cada no
    while(*Lista != NULL){
        aux = *Lista;
        *Lista = (*Lista)->prox;
        free(aux); // Libera a memória alocada para o no atual
    }
}

int main(void){
	setlocale(LC_ALL, "Portuguese");

	No *Lista = NULL; // cria a Lista
	No *remover; // ponteiro onde a função a ser excluída será alocada

	int op, numero, posicao;
	char resp;

	do{

	op=0, numero=0;

	printf("\n-------------------------------------------------"
	       "\n                 MENU DE OPÇÕES"
	       "\n-------------------------------------------------"
	       "\n[1] Adicionar no início da lista"
	       "\n[2] Adicionar no final da lista"
	       "\n[3] Adicionar em um ponto específico da lista"
	       "\n[4] Listar todos os elementos da lista"
	       "\n[5] Listar um elemento específico da lista"
	       "\n[6] Excluir do início da lista"
	       "\n[7] Excluir do final da lista"
	       "\n[8] Excluir de um ponto específico da lista"
	       "\n[9] Liberar os elementos e mostrar a lista vazia"
	       "\n[0] Terminar"
	       "\n-------------------------------------------------");

	printf("\n\nQual a sua opção? ");
	scanf("%d", &op);
	getchar();

	switch (op){
		case 1:
			printf("\nDigite o elemento que deseja acrescentar no início: ");
			scanf("%d", &numero);
			getchar();
			adicionar_no_inicio(&Lista, numero);
		    break;

		case 2:
			printf("\nDigite o elemento que deseja acrescentar no final: ");
			scanf("%d", &numero);
			getchar();
			adicionar_no_final(&Lista, numero);
		    break;

		case 3:
			printf("\nElementos da lista até o momento:\n\n");
			listar_todos_elementos(Lista);
			printf("\n");
			printf("\nDigite o número que deseja acrescentar: ");
            scanf("%d", &numero);
            getchar();
            printf("\nDigite a posição onde deseja acrescentar: ");
            scanf("%d", &posicao);
            getchar();
            adicionar_ponto_especifico(&Lista, numero, posicao);
            break;

		case 4:
			printf("\nElementos da lista até o momento:\n\n");
			listar_todos_elementos(Lista);
			printf("\n");
			break;

		case 5:
		    printf("\nDigite o elemento que deseja buscar: ");
		    scanf("%d", &numero);
		    getchar();
		    listar_elemento_especifico(Lista, numero);
		    break;
        case 6:
		    remover = excluir_inicio(&Lista);
            if(remover){
                printf("\nPrimeiro elemento a ser removido: %d\n", remover->num);
                free(remover);
            }
            break;

		case 7:
			remover = excluir_final(&Lista);
			if(remover){
				printf("\nÚltimo elemento a ser removido: %d\n", remover->num);
				free(remover);
			}
		    break;

		case 8:
			printf("\nElementos da lista até o momento:\n\n");
			listar_todos_elementos(Lista);
			printf("\n");
			printf("\nDigite o elemento que deseja remover da lista: ");
			scanf("%d", &numero);
			getchar();
			remover = excluir_ponto_especifico(&Lista, numero);
			if(remover){
				printf("\nElemento a ser removido: %d\n", remover->num);
				free(remover);
			}
		    break;

		case 9:
			liberar_lista(&Lista);
			printf("\nOs elementos da lista foram liberados!\n");
			break;

		case 0:
			printf("\nElementos finais da lista:\n\n");
			listar_todos_elementos(Lista);
			printf("\n\n");
			system("PAUSE");
			return 1;
			break;

		default:
			printf("\nOpção inválida!\n");
	}

	printf("\nDeseja realizar uma nova opção (s ou n): ");
	scanf("%c", &resp);

	system("CLS");

	}while(resp == 's' || resp == 'S');

	return 0;
}
