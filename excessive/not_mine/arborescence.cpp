#include <bits/stdc++.h>
using namespace std;

#define prin(a) cout << #a << " = " << a << endl

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define trav(a,x) for (auto& a: x)

#define rep(i,a,b) for(int i = a; i<(b);i++)
#define all(v) begin(x),end(x)
#define sz(v) (int)(v.size())
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

struct DSU {
	vi e; void init(int N) { e = vi(N,-1); }
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); } 
	bool sameSet(int a, int b) { return get(a) == get(b); }
	int size(int x) { return -e[get(x)]; }
	bool unite(int x, int y) { // union by size
		x = get(x), y = get(y); if (x == y) return 0;
		if (e[x] > e[y]) swap(x,y);
		e[x] += e[y]; e[y] = x; return 1;
	}
};

struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node *l, *r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node *merge(Node *a, Node *b) {
	if (!a || !b) return a ?: b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node*& a) { a->prop(); a = merge(a->l, a->r); }

/*
Acha menor arborescencia (menor soma de arestas) referente 
ao no r de um grafo g com n vertices
Ou seja, tal que no r alcance todos
ou -1 se não há
*/
ll dmstKACTL(int n, int r, const vector<Edge>& g) {
	DSU dsu; dsu.init(n);
	vector<Node*> heap(n);
	trav(e, g) heap[e.b] = merge(heap[e.b], new Node{e});
	ll res = 0;
	vi seen(n, -1), path(n); seen[r] = r;
	F0R(s,n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			path[qi++] = u, seen[u] = s;
			if (!heap[u]) return -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			res += e.w, u = dsu.get(e.a);
			if (seen[u] == s) {
				Node* cyc = 0;
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (dsu.unite(u, w));
				u = dsu.get(u);
				heap[u] = cyc, seen[u] = -1;
			}
		}
	}
	return res;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	vector<Edge> edges;
	vector<tuple<int,int,int>> vtup = {{0,1,10},{0,2,10},{0,4,15},{2,3,5},{4,3,5}};
	for(auto [a,b,w] : vtup){
		
		Edge e; e.a = a, e.b = b, e.w = w;
		edges.emplace_back(e);
	}	
	prin(dmstKACTL(5,1,edges));
}
