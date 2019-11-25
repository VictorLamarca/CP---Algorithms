#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()
#define eb emplace_back
#define fi first
#define se second

/*
	Ahu Tree isomorphism in O(n*lgn)
	Can be optmized for O(n) with radix sort
	
	solves: https://www.spoj.com/problems/TREEISO/
*/

namespace ncent{

int n;
vector<vector<int>> g;
vector<int> tam;

void dfs(int no, int pai){
	tam[no] = 1;
	for(auto &it : g[no]){
		if(it==pai) continue;
		dfs(it,no);
		tam[no]+=tam[it];
	}
}

vector<int> jump(int no, int p){
	for(auto &it : g[no]){
		if(it==p) continue;
		if(2*tam[it]>n) return jump(it,no);
		if(2*tam[it]==n) return {no,it};
	}
	return {no};
}

vector<int> get_cent(vector<vector<int>> &go){
	g = go;
	n = g.size();
	assert(n);
	tam = vector<int>(n,0);
	dfs(0,-1);
	return jump(0,-1);
}
};

namespace niso{

int n;
int nl;
vector<vector<int>> g[2];
vector<int> lvl[2];
vector<vector<int>> ltn[2];
vector<int> hash[2];
vector<vector<int>> hashv[2];
int cent[2];

void dfs(int cor, int no, int p,int l){
	lvl[cor][no] = l;
	nl = max(l,nl);
	for(auto &it : g[cor][no]){
		if(it==p) continue;
		dfs(cor,it,no,l+1);
	}
}

int corg;

struct cmp{
bool operator()(int a, int b){
	return hashv[corg][a]<hashv[corg][b];
}
};

bool check(){
	nl = 0;
	fr(cor,2){
		lvl[cor].assign(n,0);
		hash[cor].assign(n,0);
		ltn[cor].assign(n,vector<int>());
		hashv[cor].assign(n,vector<int>());
	}
	
	fr(cor,2){
		dfs(cor,cent[cor],-1,0);
	}	
	fr(cor,2){
		fr(i,n) ltn[cor][lvl[cor][i]].eb(i);
	}
	for(int l = nl; l>=0;l--){
		fr(cor,2){
			for(auto &no : ltn[cor][l]){
				for(auto &it : g[cor][no]) if(lvl[cor][it]==l+1) hashv[cor][no].eb(hash[cor][it]);
				sort(all(hashv[cor][no]));
			}
			corg = cor;
			sort(all(ltn[cor][l]),cmp());
			int h = 0;
			
			for(int i = 1; i<ltn[cor][l].size();i++){
				if(hashv[cor][ltn[cor][l][i]]!=hashv[cor][ltn[cor][l][i-1]]) h++;
				hash[cor][ltn[cor][l][i]] = h;
			}
		}
		if(ltn[0][l].size()!=ltn[1][l].size()) return 0;
		fr(i,ltn[0][l].size()){
			if(hashv[0][ltn[0][l][i]]!=hashv[1][ltn[1][l][i]]) return 0;
		}
	}
	return 1;
}	

bool iso(array<vector<vector<int>>,2> &go){
	fr(cor,2){
		g[cor] = go[cor];
	}
	if(g[0].size()!=g[1].size()) return 0;
	n = g[0].size();
	vector<int> vc[2];
	
	fr(cor,2) vc[cor] = ncent::get_cent(g[cor]);
	cent[1] = vc[1][0];
	for(auto &c1 : vc[0]){
		cent[0] = c1;
		if(check()) return 1;
	}
	return 0;
}
}

int main(){

	int t;
	cin >> t;
	
	fr(tt,t){
		int n;
		cin >> n;
		
		array<vector<vector<int>>,2> g;
		
		fr(cor,2) g[cor].resize(n);
		
		fr(cor,2) fr(i,n-1){
			int u, v;
			scanf("%d%d", &u, &v);
			u--,v--;
			g[cor][u].eb(v);
			g[cor][v].eb(u);
		}
		
		if(niso::iso(g)) puts("YES");
		else puts("NO");
	}
	
}
