#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cerr << #a << " = " << a << endl
#define prinv(v) cerr << #v << " = "; for(auto it : v) cerr << it << ", "; cerr << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min<ll>(a,b)
#define rmax(a,b) a = max<ll>(a,b)

#define fi first
#define se second

//solves https://codeforces.com/contest/1416/problem/D

struct node{
	ll val, id;
	//lembrar de redefinir valor default (para nulo na inicializacao)
	node(ll _val = 0, ll _id = 0) : val(_val), id(_id) {}
};

node oper(node a, node b){
	if(a.val>b.val) return a;
	return b;
}

template<int N>
struct Seg{
	int n = N;
	vector<node> s;
	
void build(){
	for(int i = n-1;i>0;i--){ 
		s[i] = oper(s[i<<1],s[i<<1|1]);
	}
}

Seg(){
	n = N;
	s = vector<node>(2*n);
	build();
}

//pos 0-indexed (atualiza, nao incrementa)
void upd(int pos, node val){
	for(s[pos+=n]=val;pos>1;pos>>=1) 
		s[pos>>1] = oper(s[pos],s[pos^1]);
}

//array é abstraido para 0-indexed (nas folhas da seg) e [l,r)
node qry(int l, int r){
	node ans;
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = oper(ans,s[l++]);
		if(r&1) ans = oper(ans,s[--r]);
	}
	return ans;
}
	
};

template<int N, bool IN_EDGES> struct HLD {
	int t;
	vector<int> *g;
	int pai[N], sz[N], d[N];
	int root[N], pos[N]; /// vi rpos;
	void dfsSz(int no) {
		if (~pai[no]) g[no].erase(find(all(g[no]),pai[no]));
		sz[no] = 1;
		for(auto &it : g[no]) {
			pai[it] = no; d[it] = d[no]+1;
			dfsSz(it); sz[no] += sz[it];
			if (sz[it] > sz[g[no][0]]) swap(it, g[no][0]);
		}
	}
	void dfsHld(int no) {
		pos[no] = t++; /// rpos.pb(no);
		for(auto &it : g[no]) {
			root[it] = (it == g[no][0] ? root[no] : it);
			dfsHld(it); }
	}
	void init(int nor, vector<int> *_g) {
		g = _g;
		root[nor] = d[nor] = t = 0; pai[nor] = -1;
		dfsSz(nor); dfsHld(nor); }
	Seg<N> tree; //lembrar de ter build da seg sem nada
	void changeNode(int v, node val){
		tree.upd(pos[v],val);
	}
	ll querySubtree(int v){
		node ans = tree.qry(pos[v]+IN_EDGES,pos[v]+sz[v]);
		if(ans.val){ 
			changeNode(ans.id,node(0,ans.id));
		}
		return ans.val;
	}
};

//-----------------------------------------------------------

const int N = 4e5+10;
int tempo[N];

namespace lca_space{
int nlog;
int n;
vector<int> *g;
int pai[N], dist[N]; //pai do nó i (raiz = -1)
int st[N][20]; //sparse table - st[i][j] = pai 2^j niveis acima do nó i

void dfs(int no, int from, int dac){
	dist[no] = dac;
	for(auto it : g[no]){
		if(it==from) continue;
		pai[it] = no;
		dfs(it,no,dac+1);
	}
}

void make(vector<int> _g[N], int _n, int root){
	g = _g;
	n = _n;

	pai[root] = -1;
	dfs(root,-1,0);
	
	nlog = 1;
	while((1<<nlog)<n) nlog++;
	assert(nlog<20);
	
	fr(i,n) fr(j,nlog+1) st[i][j] = -1;
	fr(i,n) st[i][0] = pai[i];
	
	for(int j = 1; j<=nlog; j++){
		fr(i,n){
		    int ant_pai = st[i][j-1];
		    if(ant_pai!=-1) st[i][j] = st[ant_pai][j-1];
		}
	}
}

//pega ancestor mais acima de v cujo tempo>=tt
int get_anc(int v, int tt){
	assert(tempo[v]>=tt);
	for(int i = nlog; i>=0;i--){
		if(st[v][i]!=-1 and tempo[st[v][i]]>=tt) v = st[v][i];
	}
	return v;
}	
};

HLD<N,false> hld;
vector<int> g[N];
void add_edge(int u, int v){
	g[u].push_back(v);
	g[v].push_back(u);
}

int id_nn;
int pai[N];
int rep(int u){
	return pai[u]<0? u : pai[u] = rep(pai[u]);
}
void merge(int u, int v, int tt){
	u = rep(u), v = rep(v);
	if(u!=v){
		pai[u] = id_nn;
		pai[v] = id_nn;
		add_edge(id_nn,u), add_edge(id_nn,v);
		tempo[id_nn] = tt;
		id_nn++;
	}
}

int val[N];
int idq_edge[N];
vector<pair<int,int>> qry, edges;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m, q; cin >> n >> m >> q;
	id_nn = n;
	fr(i,n) tempo[i] = q;
	fr(i,N) pai[i] = -1;
	
	fr(i,n) cin >> val[i];
	fr(i,m){
		int a, b; cin >> a >> b; a--,b--;
		edges.emplace_back(a,b);
		idq_edge[i] = q;
	}
	fr(i,q){
		int a, b; cin >> a >> b; b--;
		if(a==2){
			idq_edge[b] = i;
		}
		qry.emplace_back(a,b);
	}
	vector<tuple<int,int,int>> edge_q;
	fr(i,m){
		int a, b; tie(a,b) = edges[i];
		edge_q.emplace_back(idq_edge[i],a,b);
	}
	sort(all(edge_q)); reverse(all(edge_q));
	
	for(auto &[idq,a,b] : edge_q){
		merge(a,b,idq);
	}
	for(int i = 1; i<n; i++){
		merge(0,i,-1);
	}
	hld.init(id_nn-1,g);
	fr(i,n) hld.changeNode(i,node(val[i],i));
	lca_space::make(g,id_nn,id_nn-1);
	
	fr(i,sz(qry)){
		int tipo, no; tie(tipo,no) = qry[i];
		if(tipo==1){
			int pp = lca_space::get_anc(no,i);
			cout << hld.querySubtree(pp) << "\n";
		}
	}
}
