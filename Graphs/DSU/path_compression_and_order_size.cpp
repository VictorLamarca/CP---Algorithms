#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;

/*
    DSU com path compression e order by size (nao rank)
    
    -Operacoes amortizadamnt quase constantes
    
    -Nao da pra dizer quais os nós de certo
    conjunto, apenas de qual conjunto certo nó é 
    (pq nao uso o vetor vector<int> fi[N])
    (da pra dizer quais os nós de certo conjunto em O(n)
    mas não em O(tamanho do conjunto))
    
    -pai[no] diz quem é o no reŕesentante do set que o no
    pertence, é negativo se o no é o próprio representante
    se negativo, -pai[no] diz qnts nos estao no set que ele
    representa
    
*/
int pai[N];

int root(int v){
    if(pai[v]<0) return v;
    //ERRO AQUI, rep[u] = pai(rep[u]), nao rep[u] = pai(u) RECURSAO NUNCA CHAA EXATAMNT IGUAL A SI
    return (pai[v] = root(pai[v]));
    
}

void merge(int x,int y){
    if((x = root(x)) == (y = root(y)) return ;
    
    //order by size
	if(pai[y] < pai[x])	swap(x, y);
	pai[x] += pai[y];
	pai[y] = x;
}

int main(){
    memset(pai,-1,sizeof(pai));
    
    //ler input, fazer merges e reponder se dois elementos sao do msm componente
}

