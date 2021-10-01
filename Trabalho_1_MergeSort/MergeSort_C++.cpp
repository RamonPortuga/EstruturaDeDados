/*
Nome: Ramon Oliveira de Azevedo
DRE: 120023419
Ciências da Computação			3° Período
*/

#include <iostream>

using namespace std;

/*classe No*/
class No{
private:
	int v;
	No* prox;
public:
	/*construtor*/
	No(int v){
		this->v = v;
		this->prox = NULL;
	}

	/*obtém o valor*/
	int obterValor(){
		return v;
	}

	/*obtém o próximo No*/
	No* obterProx(){
		return prox;
	}
	
	/*seta o próximo No*/
	void setProx(No* p){
		prox = p;
	}
	
	/*Setter de valor*/
	void setValor(int v){
		this->v = v;
	}
};

/*classe Lista*/
class Lista{
private:
	No* cabeca; /*primeiro elemento*/
	No* cauda; /*último elemento*/

public:
	Lista(){
		/*se não passar elemento, então cabeca e cauda são NULL*/
		cabeca = NULL;
		cauda = NULL;
	}

	Lista(int v){
		/*se passar elemento, então cria novo No*/
		cabeca = new No(v);
		cauda = cabeca;
	}

	/*destrutor*/
	virtual ~Lista() {
		delete cabeca;
	}

	/*mostra todos os elementos da lista*/
	void mostrar() {
		/*cout << "\nImprimindo todos os elementos...\n";*/
		No* c = cabeca;

		if(vazia())
			cout << "A lista NAO possui elementos!!\n";
		else{
			// percorre a lista
			while(c){
				cout << c->obterValor() << endl;
				c = c->obterProx();
			}
		}
	}
	
	/*Realiza busca por índice, parecido com v[i]*/
	int busca_indice(int indice){
		No* c = cabeca;
		int i = 0;
		
		if(vazia()){
			cout << "A lista NAO possui elementos!!\n";
		}
		else{
			/*percorre a lista atrás do índice referido*/
			while(c){
				if (i == indice){
					return c->obterValor();
				}
				i++;
				c = c->obterProx();
			}
		}
		return 0;
	}

	/*verifica se a lista está vazia*/
	bool vazia(){
		return (cabeca == NULL);
	}

	/*insere no início (semelhante a push_front da list)*/
	void inserir_inicio(int v){
		No* novo_no = new No(v);
		if(vazia()){
			cabeca = novo_no;
			cauda = novo_no;
		}
		else{
			novo_no->setProx(cabeca);
			cabeca = novo_no;
		}
	}

	/*insere no final (semelhante a push_back da list)*/
	void inserir_final(int v){
		No* novo_no = new No(v);
		if(vazia()){
			cabeca = novo_no;
			cauda = novo_no;
		}
		else{
			cauda->setProx(novo_no);
			cauda = novo_no;
		}
	}
	
	/*insere no indice indicado*/
	void inserir_no_indice(int indice, int valor){
		No* c = cabeca;
		int i = 0;
		
		if(vazia()){
			cout << "A lista NAO possui elementos!!\n";
		}
		else{
			/*percorre a lista atrás do índice referido*/
			while(c){
				if (i == indice){
					c->setValor(valor);
				}
				i++;
				c = c->obterProx();
			}
		}
	}

	/*retorna o tamanho da lista*/
	int tamanho(){
		if(vazia()) /*se for vazia, então retorna 0*/
			return 0;

		No* c = cabeca;
		int tam = 0;
		
		/*percorre a lista*/
		do{
			c = c->obterProx();
			tam++;
		}
		while(c);
		
		return tam;
	}

	/*verifica se um elemento existe na lista*/
	bool existe(int v){
		No* c = cabeca;
		
		while(c){
			if(c->obterValor() == v)
				return true;
			c = c->obterProx();
		}
		return false;
	}

	/*remove da lista, remoção do final (semelhante a pop_back da list)*/
	void remover(){
		if(!vazia()){
			/*se houver só 1 elemento*/
			if(cabeca->obterProx() == NULL)
				cabeca = NULL;
			else if(cabeca->obterProx()->obterProx() == NULL) // 2 elementos
				cabeca->setProx(NULL);
			else{ /*> 2 elementos*/
				No* ant_ant = cabeca;
				No* ant = cabeca->obterProx();
				No* corrente = cabeca->obterProx()->obterProx();

				while(corrente){
					No* aux = ant;
					ant = corrente;
					ant_ant = aux;
					corrente = corrente->obterProx();
				}
				delete ant_ant->obterProx(); /*libera memória*/
				ant_ant->setProx(NULL); /*seta o prox como NULL*/
				cauda = ant_ant; /*atualiza a cauda*/
			}
		}
	}
};

void mergeSort (Lista &left, Lista &right, Lista &bars){
	int nL = left.tamanho();
	int nR = right.tamanho();
	int i = 0, j = 0, k = 0;
	
	while(j < nL && k < nR){
		if(left.busca_indice(j) < right.busca_indice(k)){
			/*fazer um inserir no índice*/
			bars.inserir_no_indice(i, left.busca_indice(j));
			j++;
		}
		else{
			bars.inserir_no_indice(i, right.busca_indice(k));
			k++;
		}
		i++;
	}
	
	while(j < nL){
		bars.inserir_no_indice(i, left.busca_indice(j));
		j++;
		i++;
	}
	
	while(k < nR){
		bars.inserir_no_indice(i, right.busca_indice(k));
		k++;
		i++;
	}
}

void sort (Lista &bar){
	int j = 0;
	if (bar.tamanho() <= 1){
		return;
	}
	
	int meio = bar.tamanho() / 2;
	Lista left;
	Lista right;
	
	for (j = 0; j < meio; j++){
		left.inserir_final(bar.busca_indice(j));
	}
	for (j = 0; j < (bar.tamanho() - meio); j++){
		right.inserir_final(bar.busca_indice(meio + j));
	}
	
	sort(left);
	sort(right);
	mergeSort(left, right, bar);
}

int main(int argc, char *argv[]){
	Lista lista;
	
	int valor;
	
	while(cin >> valor){
		lista.inserir_final(valor);
	}
	
	sort(lista);
	
	lista.mostrar();
	
	return 0;
}
