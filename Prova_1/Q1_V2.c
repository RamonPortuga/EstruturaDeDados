/*Primeiramente, irei declarar as bibliotecas*/
#include <stdio.h>
#include <stdlib.h>

struct No{
	int valor;
	struct No *prox;
};
typedef struct No No;

No* insere_ordenado (No *lista, int valor){
	No *aux, *ant;
	
	if (lista == NULL){
		lista = (No *) malloc(sizeof(No));
		lista->valor = valor;
		lista->prox = NULL;
		return lista;
	}
	
	aux = lista;
	
	if (valor < lista->valor){
		lista = (No *) malloc (sizeof(No));
		lista->valor = valor;
		lista->prox = aux;
		return lista;
	}
	
	while(valor > aux->valor && aux->prox != NULL){
		ant = aux;
		aux = aux->prox;
	}
	
	if(valor > aux->valor){
		aux->prox = (No *)malloc(sizeof(No));
		aux = aux->prox;
		aux->valor = valor;
		aux->prox = NULL;
	}
	
	ant->prox = (No *)malloc(sizeof(No));
	ant = ant->prox;
	ant->valor = valor;
	ant->prox = aux;
	aux = NULL;
	ant = aux;
	return lista;
}

void mostra_lista (No *lista){
	No *aux;
	aux = lista;
	while (aux != NULL){
		printf("%d\t", aux->valor);
		aux = aux->prox;
	}
	printf ("\n");
}

int main(){
	No *lista = NULL;
	
	lista = inserir_ordenado (lista, 7);
	lista = inserir_ordenado (lista, 4);
	lista = inserir_ordenado (lista, 8);
	lista = inserir_ordenado (lista, 1);
	lista = inserir_ordenado (lista, 3);
	lista = inserir_ordenado (lista, 5);
	lista = inserir_ordenado (lista, 15);
	lista = inserir_ordenado (lista, 11);
	
	mostra_lista (lista);
	
	return 0;
}
