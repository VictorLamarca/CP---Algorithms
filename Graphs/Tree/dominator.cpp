#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define all(v) (v).begin(),(v).end()

const int N = 1e5+10;
vector<int> g[N];

//solves https://codeforces.com/gym/102920/problem/F

/*
	Dado grafo g global, tam n e root
	retorna vetor de tamanho n idom[no] = imediate dominator de no wrt to root
		-1 se nao tem dominator (root e nos nao alcançaveis sao -1)
	0-indexado msm
*/
vector<int> dominators(int n, int root)
{
	vector<int> ord, rank(n, n), prev(n, n), anc(n, n), idom(n, n), semi(n), low(n);
	vector<vector<int>> g_rev(n), dom(n);
	function<void(int)> dfs = [&](int u)
	{
		rank[u] = ord.size();
		ord.emplace_back(u);
		for (int v : g[u])
		{
			g_rev[v].emplace_back(u);
			if (rank[v] < n) continue;
			prev[v] = u;
			dfs(v);
		}
	};
	dfs(root);
	for (int i = 0; i < n; ++i) semi[i] = low[i] = i;
	function<int(int)> eval = [&](int v)
	{
		if (anc[v] < n && anc[anc[v]] < n)
		{
			int x = eval(anc[v]);
			if (rank[semi[low[v]]] > rank[semi[x]]) low[v] = x;
			anc[v] = anc[anc[v]];
		}
		return low[v];
	};
	for (int i = (int) ord.size() - 1; i >= 1; --i)
	{
		int w = ord[i];
		for (int v : g_rev[w])
		{
			int u = eval(v);
			if (rank[semi[w]] > rank[semi[u]]) semi[w] = semi[u];
		}
		dom[semi[w]].emplace_back(w);
		anc[w] = prev[w];
		for (int v : dom[prev[w]])
		{
			int u = eval(v);
			idom[v] = (rank[prev[w]] > rank[semi[u]] ? u : prev[w]);
		}
		dom[prev[w]].clear();
	}
	for (int i = 1; i < sz(ord); ++i)
	{
		int w = ord[i];
		if (idom[w] != semi[w]) idom[w] = idom[idom[w]];
	}
	for (int u = 0; u < n; ++u)
		if (idom[u] >= n) idom[u] = -1;
	return idom;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, n_esp, n_edge; cin >> n >> n_esp >> n_edge;
	fr(i,n_edge){
		int a, b; cin >> a >> b;
		g[a].push_back(b);
	}
	fr(i,n_esp) g[0].push_back(i+1);
	int ans = 0;
	vector<int> idom = dominators(n+1,0);
	for(int i = 1; i<=n; i++) if(idom[i]==0) ans++;
	cout << ans << "\n";
}
