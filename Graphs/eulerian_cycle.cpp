#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min<ll>(a,b)
#define rmax(a,b) a = max<ll>(a,b)

#define fi first
#define se second

//solves https://cses.fi/problemset/task/1691/

const int N = 1e5+10;
vector<pair<int,int>> g[N];

namespace eulerpath_space{
vector<int> path;
vector<int> idit, used_edge;

void dfs(int no){
	while(1){
		int &id = idit[no];
		while(id<sz(g[no]) and used_edge[g[no][id].second]) id++;
		if(id==sz(g[no])) break;
		used_edge[g[no][id].second] = 1;
		int it = g[no][id++].first;
		dfs(it);
	}
	path.push_back(no);
}

/*
	For undirected graph g (adjacency list with of pair (it,id_edge))
	True if graph has eulerian cycle
	If true, path will have the nodes in the order of a cycle
	
	For directed version check if outdegree==indegree for every node
	(except initial and final node if eulerian path) and other changes
	submission: https://cses.fi/problemset/result/1981318/
*/
bool has_cycle(int n, int m){
	int inic = 0, nimp = 0;
	fr(i,n) if(sz(g[i])&1) nimp++, inic = i;
	
	//to change to eulerian path instead of cycle allow nimp==2
	if(nimp>0) return 0;
	
	path.clear();
	idit = vector<int>(n);
	used_edge = vector<int>(m);
	dfs(inic);
	if(sz(path)==m+1) return 1;
	return 0;
}
}; //end hpath_space

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	
	fr(i,m){
		int a, b; cin >> a >> b; a--,b--;
		g[a].emplace_back(b,i);
		g[b].emplace_back(a,i);
	}
	
	if(eulerpath_space::has_cycle(n,m)){
		vector<int> ans = eulerpath_space::path;
		fr(i,sz(ans)){
			if(i) cout << " ";
			cout << ans[i]+1;
		}
		cout << "\n";
	} else {
		cout << "IMPOSSIBLE\n";
	}
}
