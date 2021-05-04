#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//solves https://judge.yosupo.jp/problem/scc
//similar submission: https://codeforces.com/contest/894/submission/43550201

const int N = 5e5+10;
vector<int> g[N];

vector<int> comp_to_nos[N];

int tempo;
int disc[N]; //primeiro tempo em que nó foi descoberto
int low[N]; //minimo entre disc[no] e low[v] dos vizinhos

//stack e size of stack
int st[N], ss; 

//componente do noh i (0 se ainda nao pertence a componente)
//comp[no] : [1,ncomp]
int comp[N], ncomp;

int dfs(int no){
	disc[no] = low[no] = ++tempo;
	st[ss++] = no;
	for(auto it : g[no]){
		if(!disc[it]) low[no] = min(low[no],dfs(it));
		else if(!comp[it]) low[no] = min(low[no],disc[it]);
	}
	if(low[no]==disc[no]){
		comp[no] = ++ncomp;
		while(st[ss-1]!=no) comp[st[--ss]] = comp[no];
		ss--;
	}
	return low[no];
}

//---------------

vector<int> ans;
int vis[N];
namespace sol{
void dfs(int cp){
	if(vis[cp]) return;
	vis[cp] = 1;
	for(auto &no : comp_to_nos[cp]){
		for(auto &it : g[no]){
			if(comp[it]!=comp[no]) dfs(comp[it]);
		}
	}
	ans.push_back(cp);
}
};

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	fr(i,m){
		int a, b; cin >> a >> b;
		g[a].push_back(b);
	}
	
	//rodar tarjan e definir comps de cada no
	fr(i,n) if(!disc[i]) dfs(i);
	
	//comp_to_nos, nem sempre necessario, comp 1-indexado
	fr(i,n) comp_to_nos[comp[i]].push_back(i);
	
	//-----------------------
	
	for(int cp = 1; cp<=ncomp; cp++){
		sol::dfs(cp);
	}
	reverse(all(ans));
	cout << sz(ans) << "\n";
	for(auto &cp : ans){
		cout << sz(comp_to_nos[cp]);
		for(auto &no : comp_to_nos[cp]) cout << " " << no;
		cout << "\n";
	}
}
