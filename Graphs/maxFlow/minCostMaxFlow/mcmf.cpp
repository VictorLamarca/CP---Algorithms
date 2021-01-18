#include <bits/stdc++.h>
using namespace std;
 
#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define rmin(a,b) a = min<ll>(a,b)
typedef long long ll;

//solves problem C from WF 2015: https://codeforces.com/gym/101239/attachments
 
const int maxN = 210;
const double eps = 1e-6;
#define mset(v,x) memset(v,x,sizeof(v))
 
template<class T> bool lessT(const T &a, const T &b) { return a < b; }
template<> bool lessT(const double &a, const double &b) { return a < b - eps; }
template<class T> bool equalT(const T &a, const T &b) { return a == b; }
template<> bool equalT(const double &a, const double &b) { return fabs(a - b) < eps; }
 
/*
	Algoritmo de mincost maxflow
	Vertices são zero indexados 
	(na vdd internamente sao 1-indexed, por isso que uso o u++,v++)
	Flow é um inteiro e o custo o template T (geralmente ou double ou ll)
*/
template<typename T> struct costFlow {
  struct edge_t {
    int v, r, next; T w;
    edge_t(int v, int r, T w, int next) : v(v), r(r), w(w), next(next) { }
  };
  vector<edge_t> edges;
  int h[maxN], vis[maxN];
  T d[maxN];
 
  void clear() {
    edges.clear(); mset(h, -1);
  }
 
	//r é o flow e w o custo
  void addE(int u, int v, int r, T w) {
  	u++,v++;
    edges.push_back(edge_t(v, r, w, h[u]));
    h[u] = sz(edges)-1;
    edges.push_back(edge_t(u, 0, -w, h[v]));
    h[v] = sz(edges)-1;
  }
 
  void spfa(int s, int t, int n) {
    queue<int> q;
    fill(d + 1, d + 1 + n, numeric_limits<T>::max());
    fill(vis + 1, vis + 1 + n, false);
    d[s] = 0, q.push(s), vis[s] = true;
    while (!q.empty()) {
      int u = q.front();
      q.pop(), vis[u] = false;
      for (int i = h[u]; i != -1; i = edges[i].next) {
        const edge_t &e = edges[i];
        if (e.r and lessT(d[u] + e.w, d[e.v])) {
          d[e.v] = d[u] + e.w;
          if (!vis[e.v]) {
            q.push(e.v);
            vis[e.v] = true;
          }
        }
      }
    }
    for (int i = 1; i <= n; ++i) {
      if (i != t) d[i] = d[t] - d[i];
    }
    d[t] = 0;
  }
 
  int augment(int u, int t, int flow) {
    if (u == t) return flow;
    vis[u] = true;
    int ret = 0;
    for (int i = h[u]; i != -1; i = edges[i].next) {
      int v = edges[i].v, r = edges[i].r; T w = edges[i].w;
      if (r and !vis[v] and equalT(d[v] + w, d[u])) {
        int temp = augment(v, t, min(flow, r));
        if (temp) {
          edges[i].r -= temp, edges[i ^ 1].r += temp;
          ret += temp, flow -= temp;
          if (flow == 0) break;
        }
      }
    }
    return ret;
  }
 
  bool adjust(int n) {
    T delta = numeric_limits<T>::max();
    for (int u = 1; u <= n; ++u) {
      if (!vis[u]) continue;
      for (int i = h[u]; i != -1; i = edges[i].next) {
        const edge_t &e = edges[i];
        if (e.r and !vis[e.v] and lessT(d[u], d[e.v] + e.w)) {
          delta = min(delta, d[e.v] + e.w - d[u]);
        }
      }
    }
    if (delta == numeric_limits<T>::max()) return false;
    for (int i = 1; i <= n; ++i) {
      if (vis[i]) d[i] += delta;
    }
    mset(vis,0);
    return true;
  }
 
 
  pair<int, T> minCostMaxFlow(int s, int t, int n) {
  	s++,t++;
    int temp, flow = 0;
    T cost = 0;
    spfa(s, t, n);
    do {
      while (temp = augment(s, t, INT_MAX)) {
        flow += temp;
        mset(vis,0);
      }
    } while (adjust(n));
    for (int i = 1; i < (int) edges.size(); i += 2) cost += edges[i].r * edges[i - 1].w;
    return make_pair(flow, cost);
  }
};
 
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, k; cin >> n >> k;
	rmin(k,n);
	costFlow<ll> cf;
	cf.clear();
	fr(i,n){
		fr(j,n-i){
			int cost; cin >> cost;
			int ide = i+j+1;
			cf.addE(i,n-1+ide,1,cost);
		}
	}
	int src = 2*n, sink = 2*n+1;
	cf.addE(src,0,k,0);
	for(int i = 1; i<n; i++){
		cf.addE(src,i,1,0);
	}
	fr(i,n){
		cf.addE(n+i,sink,1,0);
	}
	
	cout << cf.minCostMaxFlow(src,sink,2*n+2).second << "\n";
}
