#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()


//LEMBRAR DE POR O MAKE DEPOIS DE MONTAR A ARVORE
const int N = 5e5+10;

namespace lca_space{
int nlog;
int n;
vector<int> *g;
int pai[N], dist[N]; //pai do nó i (raiz = -1)
int st[N][25]; //sparse table - st[i][j] = pai 2^j niveis acima do nó i

void dfs(int no, int from, int dac){
	dist[no] = dac;
	for(auto it : g[no]){
		if(it==from) continue;
		pai[it] = no;
		dfs(it,no,dac+1);
	}
}

void make(vector<int> _g[N], int _n){
	g = _g;
	n = _n;

	int root = 0;
	pai[root] = -1;
	dfs(root,-1,0);
	
	nlog = 1;
	while((1<<nlog)<n) nlog++;
	assert(nlog<25);
	
	fr(i,n) fr(j,nlog+1) st[i][j] = -1;
	fr(i,n) st[i][0] = pai[i];
	
	for(int j = 1; j<=nlog; j++){
		fr(i,n){
		    int ant_pai = st[i][j-1];
		    if(ant_pai!=-1) st[i][j] = st[ant_pai][j-1];
		}
	}
}

int lca(int p, int q){
	if(dist[p]<dist[q]) swap(p,q);
	
	for(int i = nlog; i>=0;i--){
		if(dist[p]-dist[q] >= (1<<i) ) p = st[p][i];	
	}
	
	if(p==q) return p;
	
	for(int i = nlog; i>=0; i--){
		if(st[p][i]!=st[q][i]){
			p = st[p][i];
			q = st[q][i];
		}
	}
	
	return pai[q];
}	

int get_dist(int u, int v){
	return dist[u]+dist[v]-2*dist[lca(u,v)];
}

};

//solves https://judge.yosupo.jp/problem/lca
vector<int> g[N];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, q; cin >> n >> q;
	fr(i,n-1){
		int id_pai; cin >> id_pai;
		g[id_pai].push_back(i+1);
		g[i+1].push_back(id_pai);
	}	
	
	lca_space::make(g,n);
	
	fr(qq,q){
		int a, b; cin >> a >> b;
		cout << lca_space::lca(a,b) << "\n";
	}
}
