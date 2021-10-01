/*
Nome: Ramon Oliveira de Azevedo
DRE: 120023419
Ciências da Computação			3° Período
*/

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
			/* percorre a lista*/
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
	
	/*verifica a quantidade existente de um elemento na lista*/
	int qtd_existente(int valor){
		No* c = cabeca;
		int i = 0;
		
		while(c){
			if(c->obterValor() == valor){
				i++;
			}
			c = c->obterProx();
		}
		return i;
	}

	/*remove da lista, remoção do final (semelhante a pop_back da list)*/
	void remover(){
		if(!vazia()){
			/*se houver só 1 elemento*/
			if(cabeca->obterProx() == NULL)
				cabeca = NULL;
			else if(cabeca->obterProx()->obterProx() == NULL) /* 2 elementos */
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

class Grafo{
private:
	Lista adj[7];

public:
	int n;
	/*construtor*/
	Grafo(int n){
		this->n = n;
	}
	void adicionarAresta (int num_vertice, int vizinho){
		adj[num_vertice].inserir_final(vizinho);
	}
	
	int obterGrauDeSaida(int num_vertice){
		return adj[num_vertice].tamanho();
	}
	
	void mostrarListaDeAdjacencias(){
		int i = 0;
		for (i = 1; i <= n; i++){
			printf("Vertice: \t%d\n", i);
			adj[i].mostrar();
			cout << "\n";
		}
	}
	
	
	void ordenacaoTopologica(){
		int i, j, pos, v;
		int grauEnt[n];
		int ordem[n];
		/*Inicializando o vetor grauEnt*/
		for (i = 0; i <= n; i++){
			grauEnt[i] = 0;
		}
		
		/*Inicializando o vetor ordem*/
		for (i = 0; i <= n; i++){
			ordem[i] = i;
		}
		
		/*Calculando os graus de entrada de cada vértice*/
		for(i = 1; i <= n; i++){
			for (j = 1; j <= n; j++){
				if(adj[i].existe(j)){
					grauEnt[j]++;
				}
			}
		}
		
		pos = 0;
		for (v = 1; v < n; v++){
			if (grauEnt[v] == 0){
				ordem[pos] = v;
				pos++;
			}
		}
		
		i = 0;
		while (i < pos){
			/*desconta do grau de entrada*/
			for (v = 1; v <= n; v++){
				if(adj[ordem[i]].existe(v)){
					grauEnt[v]--;
					if (grauEnt[v] == 0){
						ordem[pos] = v;
						pos++;
					}
				}
			}
			i++;
		}
		for (v = 0; v < n; v++){
			cout << ordem[v];
			if(v != (n - 1)){
				cout << " ";
			}
		}
	}
	
};

int main(int argc, char *argv[]){
	char *linha = NULL;
	size_t tamLinha = 0;
	int vertices, arestas;
	scanf("%d %d\n", &vertices, &arestas);
	
	Grafo grafo(vertices);
	
	for(int i = 1; i <= vertices; i++){
		getline(&linha, &tamLinha, stdin);
		int pos = 0;
		int numLido = 0;
		int numChars;
		
		while (sscanf(&linha[pos], " %d %n", &numLido, &numChars) > 0) {
			pos += numChars;
			if(strlen(linha) != 0){
				grafo.adicionarAresta(i, numLido); 
			}
		}
	}
	
	
	/*
	grafo.mostrarListaDeAdjacencias();
	*/
	
	grafo.ordenacaoTopologica();
	
	/*
	for (i = 1; i <= v; i++){
		printf ("Grau de saida do vertice %d:\t%d\n", i, grafo.obterGrauDeSaida(i));
	}
	*/
	
	return 0;
}
