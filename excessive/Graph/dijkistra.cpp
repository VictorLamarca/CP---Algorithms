#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//solves https://judge.yosupo.jp/problem/shortest_path

const int N = 5e5+10;
vector<tuple<ll,ll>> g[N];

template <class T>
using pqt = priority_queue<T,vector<T>,greater<T>>;

vector<pair<int,int>> edges_sp; //edges in shortes path

void dij(int src, int n, ll *dist, int dest = -1){
	vector<int> vis(n);
	vector<int> ant(n,-1);	
	fr(i,n) dist[i] = LLONG_MAX;
	pqt<tuple<ll,ll>> pq;
	pq.emplace(0,src);
	dist[src] = 0;
	while(!pq.empty()){
		ll dac, no; tie(dac,no) = pq.top(); pq.pop();
		if(vis[no]) continue;
		vis[no] = 1;
		for(auto &[it,c] : g[no]){
			if(vis[it]) continue;
			ll dit = dac+c;
			if(dit<dist[it]){
				dist[it] = dit;
				pq.emplace(dit,it);
				ant[it] = no;
			}
		}
	}
	
	//erase following if not necessary:
	//creating the path from src to dest
	if(dest==-1 or dist[dest]==LLONG_MAX) return;
	int cur = dest;
	edges_sp.clear();
	while(ant[cur]!=-1){ 
		edges_sp.emplace_back(ant[cur],cur); 
		cur = ant[cur];
	}
	reverse(all(edges_sp));
}

ll dist[N];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m, src, dest; cin >> n >> m >> src >> dest;
	fr(i,m){
		ll a, b, c; cin >> a >> b >> c;
		g[a].emplace_back(b,c);
	}
	dij(src,n,dist,dest);
	if(dist[dest]==LLONG_MAX){
		cout << -1 << "\n";
	} else{
		cout << dist[dest] << " " << sz(edges_sp) << "\n";
		for(auto &[a,b] : edges_sp){
			cout << a << " " << b << "\n";
		}
	}
}
