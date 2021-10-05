/*
Nome: Ramon Oliveira de Azevedo
DRE: 120023419
Ci�ncias da Computa��o			3� Per�odo
*/

/*Primeiramente, irei declarar as bibliotecas*/
#include <stdio.h>
#include <stdlib.h>

/*Estrutura que ser� utilizada e servir� como base para
a �rvore Bin�ria*/
struct No{
	int valor;
	struct No *esq;
	struct No *dir;
	int soma;
};
typedef struct No NoArv;

/*Fun��o de inser��o "simples" na �rvore Bin�ria, que
serve como parte para a quest�o 2.1*/
NoArv* insereArvBin (int valor, NoArv *ptraiz){
	if (ptraiz == NULL){
		NoArv *no = (NoArv *)malloc(sizeof(NoArv));
		no->valor = valor;
		no->esq = NULL;
		no->dir = no->esq;
		no->soma = 0;
		return no;
	}
	else{
		if (valor == ptraiz->valor){
			return ptraiz;
		}
		else if(valor < ptraiz->valor){
			ptraiz->esq = insereArvBin(valor, ptraiz->esq);
		}
		else if(valor > ptraiz->valor){
			ptraiz->dir = insereArvBin(valor, ptraiz->dir);
		}
	}
	return ptraiz;
}

/*Calcula a soma total dos n�s da �rvore.*/
NoArv* calculaSomaTotal (NoArv *ptraiz){
	if(ptraiz != NULL){
		ptraiz->soma = calculaSoma (ptraiz->esq) + calculaSoma(ptraiz->dir)
						+ ptraiz->valor;
	}
	return ptraiz;
}

/*Calcula as somas "parciais". */
int calculaSoma(NoArv *ptraiz){
	int soma = 0;
	
	if(ptraiz != NULL){
		if (ptraiz->soma != 0){
			return ptraiz->soma;
		}
		
		soma += calculaSoma (ptraiz->esq);
		soma += calculaSoma (ptraiz->dir);
		ptraiz->soma = ptraiz->valor + soma;
		
		return ptraiz->soma; 
	}
	return 0;
}

/*Fun��o que insere na �rvore Bin�ria no formato no
qual foi pedido na quest�o 2.2*/
NoArv* insereCalculandoSoma (int valor, NoArv *ptraiz){
	if (ptraiz == NULL){
		NoArv *no = (NoArv *)malloc(sizeof(NoArv));
		no->valor = valor;
		no->esq = NULL;
		no->dir = no->esq;
		no->soma = 0;
		return no;
	}
	else{
		if(valor == ptraiz->valor){
			return ptraiz;
		}
		else{
			if(valor < ptraiz->valor){
				ptraiz->esq = insereCalculandoSoma (valor, ptraiz->esq);
				ptraiz->soma = calculaSoma(ptraiz->esq) + calculaSoma (ptraiz->dir) 
							+ ptraiz->valor;
			}
			else if(valor > ptraiz->valor){
				ptraiz->dir = insereCalculandoSoma (valor, ptraiz->dir);
				ptraiz->soma = calculaSoma(ptraiz->esq) + calculaSoma(ptraiz->dir)
							+ ptraiz->valor;
			}
		}
	}
	return ptraiz;
}

/*Libera os espa�os de mem�ria ocupados pela
�rvore Bin�ria*/
void liberaArvore(NoArv *ptraiz){
	if(ptraiz != NULL){
		liberaArvore (ptraiz->esq);
		liberaArvore (ptraiz->dir);
		free(ptraiz);
	}
}

/*Fun��o que serve para mostrar a �rvore Bin�ria
na tela no formato de Pr�-Ordem*/
void imprimeArvBinPreOrdem(NoArv *ptraiz){
    if(ptraiz != NULL){
    	printf("%d(%d) ", ptraiz->valor, ptraiz->soma);
        imprimeArvBinPreOrdem(ptraiz->esq);
        imprimeArvBinPreOrdem(ptraiz->dir);
   }
}

/*E aqui, o main da fun��o, onde as intera��es s�o feitas*/
int main(){
	NoArv *ptraiz = NULL;
	
	ptraiz = insereCalculandoSoma (8, ptraiz);
	ptraiz = insereCalculandoSoma (3, ptraiz);
	ptraiz = insereCalculandoSoma (15, ptraiz);
	ptraiz = insereCalculandoSoma (23, ptraiz);
	ptraiz = insereCalculandoSoma (10, ptraiz);
	ptraiz = insereCalculandoSoma (12, ptraiz);
	
	ptraiz = calculaSomaTotal(ptraiz);
	
	printf("Soma total dos elementos presentes na %crvore: \t%d\n\n", 
			160, ptraiz->soma);
	
	imprimeArvBinPreOrdem(ptraiz);
	
	liberaArvore(ptraiz);
	
	return 0;
}
