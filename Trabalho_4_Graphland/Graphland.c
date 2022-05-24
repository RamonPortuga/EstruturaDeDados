/*
Nome: Ramon Oliveira de Azevedo
DRE: 120023419
Ciências da Computação			3° Período
*/

/*Observações: Olá professor, tudo bem? Devido ao atoleiro desse
final de período, acabei me enrolando com a quantidade excessiva
de trabalhos. Agradeço por ter alongado consideravelmente o
prazo, mas acabei não conseguindo arrumar tempo hábil para fazer
tudo que foi pedido na questão. Tô entregando tudo que consegui
fazer na esperança de conseguir alguns pontos. Pra piorar, hoje
(26) é o meu aniversário então, não me leve a mal, acabei focando
em comemorar e tô aqui feito louco tentando terminar.

OBS 2: Eu não deixei pra última hora, mas não deu pra fazer um
speedrun com esse trabalho para entender os conceitos e finalizar.
Tive nesse meio tempo uma PF, três listas valendo nota, um rela-
tório e por fim esse trabalho pra fazer. Pra quem fazia tudo, esse
final de período foi bem desastroso. Enfim, agradeço se me der algu-
ma coisa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Extremos{
	int src;
	int dest;
	int weight;
};
typedef struct Extremos Extremos;

struct Grafo{
    int vertices, arestas;
    Extremos *extremos;
};
typedef struct Grafo Grafo;

struct Conjuntos{
	int parentes;
	int rankeamento;
};
typedef struct Conjuntos Conjuntos;

/*Função feita para criar o grafo*/
Grafo* criaGrafo(int vertices, int arestas){
	Grafo *g;
	g = (Grafo *) malloc(sizeof(Grafo));
	g->vertices = vertices;
	g->arestas = arestas;
	
	g->extremos = (Extremos*) malloc (sizeof(Extremos) * arestas);
	
	return g;
}

/*Código feito com base no algoritmo dado em aula*/
int find (Conjuntos conj [], int x){
	int y = x;
	/*
	while (conj[y] != x = y){
		y = conj[y];
	}
	while(conj[x] != y){
		pai = conj[x];
		conj[x] = y;
		x = pai;
		return y;
	}
	*/
	if (conj[y].parentes != y){
		conj[y].parentes = find(conj, conj[y].parentes);
	}
	return conj[y].parentes;
}

/*Código feito com base no algoritmo dado em aula*/
void une (Conjuntos conj[], int x, int y){
	int novo_x = find(conj, x);
	int novo_y = find(conj, y);
	
	if(x != conj[x] || b != conj[y]){
		printf("ERRO");
	}
	
	if(x == y){
		//return?
	}
	
	if(conj[novo_x].rankeamento < conj[novo_y].rankeamento){
		conj[novo_x].parentes = novo_y;
	}
	else if (conj[novo_x].rankeamento > conj[novo_y].rankeamento){
		conj[novo_y].parentes = novo_x;
	}
	else{
		conj[novo_y].parentes = novo_x;
		conj[novo_x].rankeamento++;
	}
}

int comparadorDosTamanhos(void *x, void *y){
	Extremos *x1 = (Extremos *) x;
	Extremos *y1 = (Extremos *) y;
	
	return x1->weight > y1->weight;
}

int calculaDistancia(int x1, int x2, int y1, int y2){
	float distancia = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	int distancia_arredondada = round (distancia);
	return distancia_arredondada;
}

void algoritmoDeKruskal(Grafo *g){
	int vertices = g->vertices;
	Extremos resultado[vertices];
	int i, minimo, k;
	
	qsort(g->extremos, g->arestas, sizeof(g->extremos[0]), comparadorDosTamanhos);
	
	Conjuntos conj = (Conjuntos *)malloc(vertices * sizeof(Conjuntos));
	
	for (i = 0; i < vertices; i++){
		conj[i].parentes = vertices;
		conj[i].rankeamento = 0;
	}
	
	i = 0;
	
	while(k < (vertices - 1) && i < g->arestas){
		Extremos prox = g->extremos[i + 1];
		i++;
		
		int coord_x = find(conj, prox.src);
		int coord_y = find(conj, prox.dest);
		
		if(coord_x != coord_y){
			resultado[k] = prox;
			une(conj, coord_x, coord_y);
			k++;
		}
	}
	i = 0;
}

int main(){
	Grafo *g;
	
	int vertices = 3;
	int arestas = 4;
	
	g = criaGrafo(vertices, arestas);
	
	return 0;
}
