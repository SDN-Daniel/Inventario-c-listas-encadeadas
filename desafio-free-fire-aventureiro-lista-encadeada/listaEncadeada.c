#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_STR_NOME 30
#define TAM_STR_TIPO 20
#define MAX_ITENS 10

// Definição da struct 
typedef struct Item {
	char nome[TAM_STR_NOME];
	char tipo[TAM_STR_TIPO];
	int quantidade;
	struct Item* proximo; // Ponteiro para o próximo item na lista encadeada
} Item;

// Prototipos das funções principais
Item* alocarItem(char nome[TAM_STR_NOME], char tipo[TAM_STR_TIPO], int quantidade);
void exibirMenu(int totalItens, int* opcao);
Item* inserirItem(Item* cabeca, int* totalItens);
Item* removerItem(Item* cabeca, int* totalItens);

// Prototipos das funçoes utilitarias
void lerItensMochila(Item* cabeca, int totalItens);
Item* buscarItem(Item* cabeca);
void limparBuffer();
void pressioneEnter();
void liberarMemoria(Item* cabeca);

int main() {
	int totalItens = 0;

	Item* cabeca = NULL; // Ponteiro para o início da lista encadeada

	int opcao;

	do {
		exibirMenu(totalItens, &opcao);

		switch (opcao) {
		case 1:
			printf("Opção escolhida: 1-Adicionar Item\n");
			cabeca = inserirItem(cabeca ,&totalItens);
			break;
		case 2:
			printf("Opção escolhida: 2-Remover Item\n");
			cabeca = removerItem(cabeca, &totalItens);
			break;
		case 3:
			printf("Opção escolhida: 3-Listar Itens\n");
			lerItensMochila(cabeca, totalItens);
			break;
		case 0:
			printf("Saindo do programa...\n");
			liberarMemoria(cabeca); // Libera a memória alocada 
			break;
		default:
			printf("Opção inválida! \nTente novamente.\n");
			break;
		}
	} while (opcao != 0);

	return 0;
}

// --- Funções Principais ---

// Função para alocar memória para um novo item na mochila
Item* alocarItem(char nome[TAM_STR_NOME], char tipo[TAM_STR_TIPO], int quantidade) {
	Item* novoNo = (Item*)malloc(sizeof(Item)); // Aloca memória para um novo item

	if (novoNo == NULL) {
		printf("Erro ao alocar memória para o novo item!\n");
		exit(1);
	}

	// Inicializa os campos do novo item
	strcpy(novoNo->nome, nome);
	strcpy(novoNo->tipo, tipo);
	novoNo-> quantidade = quantidade;
	novoNo-> proximo = NULL; // Inicializa o ponteiro para o próximo item como NULL

	return novoNo;
}

// Função para inserir um novo item na mochila
Item* inserirItem(Item* cabeca, int* totalItens) {
	char nome[TAM_STR_NOME];
	char tipo[TAM_STR_TIPO];
	int quantidade;

	if (*totalItens >= MAX_ITENS) {
		printf("Mochila cheia! Não é possível adicionar mais itens.\n");
		printf("Tente remover algum item primeiro.\n");
		pressioneEnter();
		return cabeca;
	}

	// Capturando os dados do novo item
	printf("\n--- Adicionar Novo Item ---\n");

	printf("Digite o nome do item: ");
	fgets(nome, TAM_STR_NOME, stdin);
	nome[strcspn(nome, "\n")] = '\0';

	printf("Digite o tipo do item (arma, munição, cura, etc.): ");
	fgets(tipo, TAM_STR_TIPO, stdin);
	tipo[strcspn(tipo, "\n")] = '\0';

	printf("Digite a quantidade do item: ");
	scanf("%d", &quantidade);
	limparBuffer();

	// Alocando memória para o novo item
	Item* novoItem = alocarItem(nome, tipo, quantidade);
	Item* atual = NULL;
	
	// Costurando ponteiros para formar a lista encadeada simples

	if (cabeca == NULL) // cabeca vem da main, se for NULL significa que a lista está vazia
	{
		cabeca = novoItem; // se a lista estiver vazia, o novo item se torna a cabeça da lista
	} else 
	{
		atual = cabeca; // atual e cabeca guardam o mesmo endereço de memória

		while (atual->proximo != NULL) // percorre a lista até o último item válido, o item que "proximo" aponta para NULL
		{
			atual = atual->proximo;
		}
		atual->proximo = novoItem; // adiciona o novo item no final da lista
	}

	(*totalItens)++;
	printf("%s adicionado com sucesso!\n", novoItem->nome);

	lerItensMochila(cabeca, *totalItens);
	return cabeca;
}

// Função para exibir o menu principal
void exibirMenu(int totalItens, int* opcao) {
	printf("\n=== MOCHILA DE SOBREVIVÊNCIA ===\n");
	printf("Itens na mochila: %d/%d\n", totalItens, MAX_ITENS);
	printf("\n");
	printf("1. Adicionar Item\n");
	printf("2. Remover Item\n");
	printf("3. Listar Itens na Mochila\n");
	printf("0. Sair\n");
	printf("\n");

	do {
		printf("Escolha uma opção: ");
		(void)scanf("%d", opcao);
		limparBuffer();

		if (*opcao < 0 || *opcao > 3) {
			printf("Opção inválida! \nTente novamente.\n");
		}
	} while (*opcao < 0 || *opcao > 3);
} 

// Função para remover um item da mochila
//modificar
Item* removerItem(Item* cabeca, int* totalItens) {
	if (cabeca == NULL) {
		printf("\nA mochila está vazia! Não há itens para remover.\n");
		pressioneEnter();
		return cabeca;
	}

	Item* itemParaRemover = buscarItem(cabeca); // buscarItem retorna o ponteiro para o item encontrado ou NULL se não encontrado

	if (itemParaRemover == NULL) {
		printf("Item não encontrado na mochila. Tente novamente.\n");
		pressioneEnter();
		return cabeca;
	} 
	else if (itemParaRemover == cabeca) { // se o item a ser removido for o primeiro da lista, atualiza a cabeça da lista
		cabeca = cabeca->proximo; 
		(*totalItens)--;
		free(itemParaRemover); // Libera a memória do item removido
	} 
	else { // se o item a ser removido não for o primeiro da lista
		Item* itemParaCosturar = cabeca;
		while (itemParaCosturar -> proximo != itemParaRemover && itemParaCosturar -> proximo != NULL) {
			itemParaCosturar = itemParaCosturar -> proximo;
		}

		printf("Item '%s' removido com sucesso!\n", itemParaRemover->nome);

		itemParaCosturar -> proximo = itemParaRemover -> proximo; // Costura o item anterior ao item removido com o próximo item
		free(itemParaRemover); // Libera a memória do item removido
		(*totalItens)--;
	}

	pressioneEnter();
	lerItensMochila(cabeca, *totalItens);

	return cabeca;
} 

// --- Funções Utilitárias ---

// Função para buscar um item na mochila pelo nome // retorna o ponteiro para o item encontrado ou NULL se não encontrado
Item* buscarItem(Item* cabeca) {
	char nomeItem[TAM_STR_NOME];
	int encontrado = 0;
	Item* leitor = cabeca;

		printf("Digite o nome do item que deseja buscar: ");
		fgets(nomeItem, TAM_STR_NOME, stdin);
		nomeItem[strcspn(nomeItem, "\n")] = '\0';

		while (leitor != NULL) {
			if (strcmp(leitor->nome, nomeItem) == 0) { // se o nome do item for igual ao nome digitado, retorna o ponteiro para o item encontrado
				return leitor;
			}
			leitor = leitor->proximo;
		}

		if (encontrado == 0) {
			printf("Item '%s' não encontrado na mochila. Tente novamente.\n", nomeItem);
			pressioneEnter();
			leitor = NULL;
			return leitor;
		}

	
}

// Função para ler e exibir os itens na mochila
void lerItensMochila(Item* cabeca, int totalItens) {
	Item* leitor = cabeca;

	if (leitor != NULL) // se leitor for NULL, significa que a mochila está vazia
	{
		printf("\n=== ITENS NA MOCHILA (%d/%d)===\n", totalItens, MAX_ITENS);
		while (leitor != NULL) {
			printf("--------------------------------------------------\n");
			printf("NOME             | TIPO              | QUANTIDADE\n");
			printf("--------------------------------------------------\n");
			printf("%s             | %s             | %d\n", leitor->nome, leitor->tipo, leitor->quantidade);

			leitor = leitor->proximo;
		}
	}
	else {
		printf("\nA mochila está vazia!\n");
		return;
	}
	pressioneEnter();
}

// Função para liberar a memória alocada para a mochila
void liberarMemoria(Item* cabeca) {
	Item* atual = cabeca;
	Item* proximo;
	while (atual != NULL) {
		proximo = atual->proximo;
		free(atual);
		atual = proximo;
	}
}
// Função para limpar o buffer do teclado
void limparBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

// Função para pausar a execução até que o usuário pressione [ENTER]
void pressioneEnter() {
	printf("\nPressione [ENTER] para continuar...");
	getchar();
}