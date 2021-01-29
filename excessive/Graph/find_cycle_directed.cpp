#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()

const int N = 1e6+10;
vector<int> g[N];

//directed graph
namespace find_cycle{

int found_cycle = 0;
int first_node = -1;
vector<int> nodes_in_cycle;
int vis[N], ativ[N];

void reset(int n){
	fr(i,n){
		vis[i] = ativ[i] = 0;
		g[i].clear();
	}
	nodes_in_cycle.clear();
	found_cycle = 0;
	first_node = -1;
}

int dfs(int no){
	if(found_cycle) return 0;
	if(vis[no] and !ativ[no]) return 0;
	vis[no] = 1;
	ativ[no] = 1;
	
	for(auto it : g[no]){
	
		if(ativ[it]){
			nodes_in_cycle.push_back(no);
			first_node = it;
			found_cycle = 1;
			return 1;
		}
		if(dfs(it)){
			nodes_in_cycle.push_back(no);
			if(no==first_node){ 
				reverse(all(nodes_in_cycle));
				return 0;
			}
			return 1;
		}
	}	
	
	ativ[no] = 0;
	
	return 0;
}

bool go_find(int n){
	fr(i,n){
		if(!vis[i]){
			dfs(i);
			if(found_cycle) return 1;
		}
	}
	return 0;
}

};

//tested in https://codeforces.com/contest/1476/submission/105919213

#define prinv(v) cout << #v << " = "; for(auto &it : v) cout << it << ","; cout << endl;

int main(){
	g[0].push_back(2);
	g[2].push_back(1);
	g[1].push_back(3);
	g[3].push_back(2);
	if(find_cycle::go_find(4)){
		prinv(find_cycle::nodes_in_cycle);
	}
	find_cycle::reset(4);
	g[0].push_back(1);
	g[2].push_back(1);
	if(find_cycle::go_find(4)){
		prinv(find_cycle::nodes_in_cycle);
	}
}
