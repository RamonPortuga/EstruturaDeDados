/*
Nome: Ramon Oliveira de Azevedo
DRE: 120023419
Ciências da Computação			3° Período
*/

/*Primeiramente, irei declarar as bibliotecas*/
#include <stdio.h>
#include <stdlib.h>

/*Declaração da struct*/
struct No{
	int valor;
	struct No *prox;
};
typedef struct No No;

/*Função que vai realizar a inserção no ordenado*/
No* inserir_ordenado (No *lista, int valor){
	No *aux, *ant;
	
	if (lista == NULL){
		lista = (No *) malloc(sizeof(No));
		lista->valor = valor;
		lista->prox = NULL;
		return lista;
	}
	else{
		aux = lista;
		
		/*Lógica para o início*/
		if (valor < lista->valor){
			lista = (No *) malloc (sizeof(No));
			lista->valor = valor;
			lista->prox = aux;
			return lista;
		}
		
		/*Lógica para percorrer o meio e chegar até o final*/
		while(valor > aux->valor && aux->prox != NULL){
			ant = aux;
			aux = aux->prox;
		}
		
		/*Lógica para o fim*/
		if(valor > aux->valor){
			aux->prox = (No *)malloc(sizeof(No));
			aux = aux->prox;
			aux->valor = valor;
			aux->prox = NULL;
			return lista;
		}
		
		/*Lógica para o meio*/
		ant->prox = (No *)malloc(sizeof(No));
		ant = ant->prox;
		ant->valor = valor;
		ant->prox = aux;
		aux = NULL;
		ant = aux;
		return lista;
	}
}

/*Função que serve para mostrar a lista na tela*/
void mostra_lista (No *lista){
	No *aux;
	aux = lista;
	while (aux != NULL){
		printf("%d\t", aux->valor);
		aux = aux->prox;
	}
	printf ("\n");
}

/*Função que serve para liberar a memória ocupada pela lista*/
void libera_lista(No *lista){
	No *aux = lista;
	if(lista != NULL){
		lista = lista->prox;
		aux->prox = NULL;
		free(aux);
		libera_lista(lista);
	}
}

/*E aqui, o main da função, onde as interações são feitas*/
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
	
	libera_lista (lista);
	
	return 0;
}
