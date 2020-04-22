#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()
typedef long long ll;

template<int N> struct Seg{
ll s[4*N], lazy[4*N];
void build(int no = 1, int l = 0, int r = N){
    if(r-l==1){
        s[no] = 0;
        return;
    }
    int mid = (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = max(s[2*no],s[2*no+1]);
}
Seg(){
	build();
}
void updlazy(int no, int l, int r, ll x){
    s[no] += x;
    lazy[no] += x;
}
void pass(int no, int l, int r){
    int mid = (l+r)/2;
    updlazy(2*no,l,mid,lazy[no]);
    updlazy(2*no+1,mid,r,lazy[no]);
    lazy[no] = 0;
}
void upd(ll x, int lup, int rup, int no = 1, int l = 0, int r = N){
    if(rup<=l or r<=lup) return;
    if(lup<=l and r<=rup){
        updlazy(no,l,r,x);
        return;
    }   
    pass(no,l,r);
    int mid = (l+r)/2;
    upd(x,lup,rup,2*no,l,mid);
    upd(x,lup,rup,2*no+1,mid,r);
    s[no] = max(s[2*no],s[2*no+1]);
}
ll query(int lq, int rq, int no = 1, int l = 0, int r = N){
    if(rq<=l or r<=lq) return -LLONG_MAX;
    if(lq<=l and r<=rq){
        return s[no];
    } 
    pass(no,l,r);
    int mid = (l+r)/2;
    return max(query(lq,rq,2*no,l,mid),query(lq,rq,2*no+1,mid,r));
}
};

template<int N, bool IN_EDGES> struct HLD { 
	vector<int> g[N];
	int pai[N], sz[N], d[N];
	int root[N], pos[N]; /// vi rpos;
	void ae(int a, int b) { g[a].push_back(b), g[b].push_back(a); }
	void dfsSz(int no = 1) {
		if (pai[no]) g[no].erase(find(all(g[no]),pai[no]));
		sz[no] = 1;
		for(auto &it : g[no]) {
			pai[it] = no; d[it] = d[no]+1;
			dfsSz(it); sz[no] += sz[it];
			if (sz[it] > sz[g[no][0]]) swap(it, g[no][0]);
		}
	}
	void dfsHld(int no = 1) {
		static int t = 0; pos[no] = t++; /// rpos.pb(no);
		for(auto &it : g[no]) {
			root[it] = (it == g[no][0] ? root[no] : it);
			dfsHld(it); }
	}
	void init() {
		root[1] = 1; pai[1] = d[1] = 0; 
		dfsSz(); dfsHld(); }
	Seg<N> tree;
	template <class BinaryOp>
	void processPath(int u, int v, BinaryOp op) {
		for (; root[u] != root[v]; v = pai[root[v]]) {
			if (d[root[u]] > d[root[v]]) swap(u, v);
			op(pos[root[v]], pos[v]); }
		if (d[u] > d[v]) swap(u, v);
		op(pos[u]+IN_EDGES, pos[v]); 
	}
	void modifyPath(int u, int v, int val) { 
		processPath(u,v,[this, &val](int l,int r) { 
			tree.upd(val,l,r+1); }); }
	void modifySubtree(int v, int val) { 
		tree.upd(val,pos[v]+IN_EDGES,pos[v]+sz[v]); }
	ll queryPath(int u, int v) { 
		ll res = -LLONG_MAX; processPath(u,v,[this,&res](int l,int r) { 
			res = max(tree.query(l,r+1),res); });
		return res; }
};

//solves https://www.hackerrank.com/challenges/subtrees-and-paths/problem

const int N = 1e5+10;
char str[100];
int main(){
	HLD<N,false> hld;
	int n;
	cin >> n;
	
	fr(i,n-1){
		int u, v;
		scanf("%d%d", &u, &v);
		hld.ae(u,v);
	}
	hld.init();
	int q;
	scanf("%d", &q);
	fr(qq,q){
		scanf("%s", str);
		if(str[0]=='a'){
			int t, val;
			scanf("%d%d", &t, &val);
			hld.modifySubtree(t,val);
		} else{
			int u, v;
			scanf("%d%d", &u, &v);
			printf("%lld\n", hld.queryPath(u,v));
		}
	}
}
