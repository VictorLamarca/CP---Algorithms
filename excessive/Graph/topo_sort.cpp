#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()

const int N = 1e5+10;
vector<int> g[N];

namespace topo_sort{
vector<int> p;
bool vis[N];

void dfs(int no){
	if(vis[no]) return;
	vis[no] = 1;
	for(auto &it : g[no]){
		dfs(it);
	}
	p.push_back(no);
}

vector<int> get_topo(int n){
	fr(i,n) vis[i] = 0;//reset
	p.clear();
	
	fr(i,n) dfs(i);
	reverse(all(p));
	return p;
}

}

//tested in https://codeforces.com/contest/1476/submission/105957239

#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	g[2].push_back(1);
	g[2].push_back(0);
	g[0].push_back(1);
	vector<int> p = topo_sort::get_topo(3);
	prinv(p);
}
