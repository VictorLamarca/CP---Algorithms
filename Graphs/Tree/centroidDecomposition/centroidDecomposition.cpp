#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

const int N = 1e5+10;

vector<int> g[N]; //grafo original
vector<int> ct[N]; //arvore da decomposicao em centroide
int pai[N]; //pai de cada no na decomposicao em centroide
int rootct; 
int subsize[N];
bool jact[N];

int mksubsize(int no, int from){
	int tam = 1;
	for(auto &it : g[no]){
		if(it==from or jact[it]) continue;
		tam+=mksubsize(it,no);
	}
	subsize[no] = tam;
	return tam;
}

int findc(int no, int from, int tam){
	for(auto &it : g[no]){
		if(it==from or jact[it]) continue;
		if(subsize[it]>tam/2) return findc(it,no,tam);
	}
	return no;
}


void mkct(int root, int from){
	mksubsize(root,-1);	
	
	int cur = findc(root,-1,subsize[root]);
	
	if(from==-1) rootct = cur;
	else ct[from].push_back(cur);
	pai[cur] = from;
	jact[cur] = 1;
	
	for(auto &it : g[cur]){
		if(jact[it]) continue;
		mkct(it,cur);
	}
	return;
}

//By adapting this code, solves: https://www.spoj.com/problems/QTREE4/

//--------TESTE-----------------------------
// a partir do grafo ct, faz a matriz mat para visualizar levels da centroid tree
vector<vector<int>> mat;

void fazmat(int no, int from, int d){
	if(d==mat.size()) mat.push_back(vector<int>(1,no));
	else mat[d].push_back(no);
	for(auto &it : ct[no]){
		if(it==from) continue;
		fazmat(it,no,d+1);
	}
}
//-----------------------------------------

int main(){
	int n;
	cin >> n;
	
	fr(i,n-1){
		int u,v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	mkct(1,-1);
	
	//----PRINTANDO CENTROID TREE----------
	fazmat(rootct,-1,0);
	
	for(auto &v : mat){
		for(auto it : v) cout << it << " ";
		cout << endl;
	}
	//----------------------------------
	
	return 0;
}


/*tutorial com imagem do teste a seguir:
https://www.geeksforgeeks.org/centroid-decomposition-of-tree/

16
1 4
2 4
3 4
4 5
5 6
6 7
8 7
9 7
6 10
10 11
11 12
11 13
12 14
15 13
13 16
*/

