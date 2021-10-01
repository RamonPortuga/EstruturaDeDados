/*
Nome: Ramon Oliveira de Azevedo
DRE: 120023419
Ci�ncias da Computa��o			3� Per�odo
*/

/*Primeiramente, a declara��o das bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Estrutura respons�vel pela manipula��o da �rvore*/
struct No{
    int chave;
    int alt;
    struct No *esq;
    struct No *dir;
};
typedef struct No NoArv;

/*Fun��o auxiliar que serve para definir a maior altura*/
/*Feita com base no algortimo feito em aula*/
int max (int esq, int dir){
	if(esq > dir){
		return esq;
	}
	else{
		return dir;
	}
}

/*Fun��o auxiliar que serve para retornar a altura do lado desejado*/
int altura(NoArv *NoArv){
	if(NoArv != NULL){
		return NoArv->alt;
	}
	return 0;
}

/*Cria o primeiro n� da �rvore quando a mesma estiver vazia */
NoArv* criaNoArv (NoArv *ptraiz, int x){
	if(ptraiz == NULL){
		NoArv *aux = malloc(sizeof(NoArv));
        aux->chave = x;
        aux->alt = 1;
        aux->esq = NULL;
        aux->dir = aux->esq;
        return aux;
	}
	return NULL;
}

/*Rotaciona a �rvore para direita*/
NoArv* rotacaoParaDireita(NoArv *ptraiz){
	NoArv *aux = ptraiz->esq;
	NoArv *auxDois = aux->dir;
	
	aux->dir = ptraiz;
	ptraiz->esq = auxDois;
	
	ptraiz->alt = max(altura(ptraiz->esq), altura(ptraiz->dir)) + 1;
	aux->alt = max(altura(aux->esq), altura(aux->dir)) + 1;
	
	return aux;
}

/*Rotaciona a �rvore para a esquerda*/
NoArv* rotacaoParaEsquerda(NoArv *ptraiz){
	NoArv *aux = ptraiz->dir;
	NoArv *auxDois = aux->esq;
	
	aux->esq = ptraiz;
	ptraiz->dir = auxDois;
	
	ptraiz->alt = max(altura(ptraiz->esq), altura(ptraiz->dir)) + 1;
	aux->alt = max(altura(aux->esq), altura(aux->dir)) + 1;
	
	return aux;
}

/*Aqui, � onde a inser��o em AVL � realizada*/
NoArv* insereAVL(NoArv *ptraiz, int chave){
	if (ptraiz == NULL){
		return (criaNoArv(ptraiz, chave));
	}
	else{
		if (chave == ptraiz->chave){
			return ptraiz;
		}
		if(chave < ptraiz->chave){
			ptraiz->esq = insereAVL(ptraiz->esq, chave);
		}
		else if(chave > ptraiz->chave){
			ptraiz->dir = insereAVL(ptraiz->dir, chave);
		}
		else{
			return ptraiz;
		}
		
		/*Calculo da altura feito com bas eno algoritmo apresentado
		em aula*/
		ptraiz->alt = (max(altura(ptraiz->esq), altura(ptraiz->dir)) + 1);
		
		int reg = 0;
		
		/*Define o valor reg, que ir� definir a diferen�a de altura
		entre o ramo esquerdo e o ramo direito. Com isso, o seu va-
		lor ser� essencial para definir o balanceamento e rotacio-
		nar a �rvore*/
		/*Caso ptraiz seja igual a NULL, vale lembrar que reg con-
		tinua valendo ZERO*/
		if (ptraiz != NULL){
			reg = altura(ptraiz->esq) - altura(ptraiz->dir);
		}
		
		if(reg > 1 && chave < ptraiz->esq->chave){
			return rotacaoParaDireita(ptraiz);
		}
		
		else if(reg > 1 && chave > ptraiz->esq->chave){
			ptraiz->esq = rotacaoParaEsquerda(ptraiz->esq);
			return rotacaoParaDireita(ptraiz);
		}
		
		else if (reg < -1 && chave > ptraiz->dir->chave){
			return rotacaoParaEsquerda(ptraiz);
		}
		
		else if (reg < -1 && chave < ptraiz->dir->chave){
			ptraiz->dir = rotacaoParaDireita(ptraiz->dir);
			return rotacaoParaEsquerda(ptraiz);
		}
	}
	return ptraiz;
}

/*Realiza a impress�o da �rvore no formato de Pr�-Ordem*/
void imprimePreOrdem(NoArv *ptraiz){
    if(ptraiz != NULL){
        printf("%d(%d) ", ptraiz->chave, ptraiz->alt);
        imprimePreOrdem(ptraiz->esq);
        imprimePreOrdem(ptraiz->dir);
   }
}

/*Libera os espa�os de mem�ria da �rvore AVL*/
void liberaArvore(NoArv *ptraiz) {
    if(ptraiz != NULL) {
        liberaArvore(ptraiz->esq);
        liberaArvore(ptraiz->dir);
        free(ptraiz);
    }
}

/*Main do programa, onde se encontrar� todas as chamadas
e testes do mesmo*/
int main(){
	NoArv *ptraiz = NULL;
	char str[5];
	int num;
	
	/*C�digo de Leitura feito com base no algoritmo apresentado
	em aula*/
	while(!feof(stdin)) {
        if(scanf("%s", str) == 1) {
            if(str[0] == 'p') {
                imprimePreOrdem(ptraiz);
                printf("\n");
            }
            if(str[0] == 'i') {
                if(scanf("%d", &num) == 1) {
                    ptraiz = insereAVL(ptraiz, num);
                }
            }
        }
    }
    
    liberaArvore(ptraiz);
	
	return 0;
}
