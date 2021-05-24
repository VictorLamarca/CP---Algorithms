#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define all(v) (v).begin(),(v).end()
typedef long long ll;
#define rmax(a,b) a = max<ll>(a,b)

/*
	Implementação de HLD com seg iterativa
		Seg precisa ser com template<int N>
		
	Essa implementação faz queries de maximo em subarvore e em caminho,
	mas updates só um ponto (em um unico vertice)
*/
struct node{
	ll val, id;
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
	//build(); 
}

void upd(int pos, node val){
	for(s[pos+=n]=val;pos>1;pos>>=1) 
		s[pos>>1] = oper(s[pos],s[pos^1]);
}

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
	node querySubtree(int v){
		node ans = tree.qry(pos[v]+IN_EDGES,pos[v]+sz[v]);
		return ans;
	}
	template <class Op>
	void processPath(int u, int v, Op op) {
		for (; root[u] != root[v]; v = pai[root[v]]) {
			if (d[root[u]] > d[root[v]]) swap(u, v);
			op(pos[root[v]], pos[v]); }
		if (d[u] > d[v]) swap(u, v);
		op(pos[u]+IN_EDGES, pos[v]); 
	}
	node queryPath(int u, int v) { //modificacoes geralmente vem aqui (para hld soma)
		node res; processPath(u,v,[this,&res](int l,int r) { 
			res = oper(tree.qry(l,r+1),res); });
		return res; 
	}
};

//solves https://codeforces.com/contest/1528/problem/C
//other submission, dsu tree: https://codeforces.com/contest/1416/submission/97959862

const int N = 3e5+10;
vector<int> g1[N], g2[N];
int vat[N];
int lvl[N];

HLD<N,false> hld;

int ans = 0;
int cur = 0;

void ativ(int no){
	node fi = hld.querySubtree(no);
	if(fi.val==0){
		vat[no] = 1;
		node pai = hld.queryPath(no,0);
		if(pai.val and vat[pai.id]){
			vat[pai.id] = 0;
		} else{
			cur++;
		}
	}
	hld.changeNode(no,node(hld.d[no]+1,no));
}

void desativ(int no){
	hld.changeNode(no,node(0,no));
	if(vat[no]){
		vat[no] = 0;
		cur--;
		node pai = hld.queryPath(no,0);
		if(pai.val){
			hld.changeNode(pai.id,node(0,pai.id));
			ativ(pai.id);
		}
	}
}

void dfs(int no){
	ativ(no);
	rmax(ans,cur);
	for(auto &it : g1[no]){
		dfs(it);
	}
	desativ(no);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	fr(tt,t){
		int n; cin >> n;
		fr(i,n) g1[i].clear(), g2[i].clear();
		fr(i,n) vat[i] = 0;
		fr(i,n-1){
			int pai; cin >> pai; pai--;
			g1[pai].push_back(i+1);
			//g1[i+1].push_back(pai);
		}
		fr(i,n-1){
			int pai; cin >> pai; pai--;
			g2[pai].push_back(i+1);
			g2[i+1].push_back(pai);
		}
		hld.init(0,g2);
		ans = 0;
		cur = 0;
		dfs(0);
		cout << ans << "\n";
	}
}
