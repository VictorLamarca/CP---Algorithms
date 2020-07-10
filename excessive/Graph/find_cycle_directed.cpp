#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

const int N = 1e7+10;
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

/*
	Not tested
	
	But works in this test case from here https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
	
	Not submitted because requires to write a funcion
	
3
2 2
0 1 0 0
4 3
0 1 1 2 2 3
4 3
0 1 2 3 3 2
	
	https://practice.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1
*/


int main(){
	int t; scanf("%d", &t);
	
	fr(tt,t){
		int n, m; scanf("%d%d", &n, &m);
		
		fr(i,m){
			int a, b; scanf("%d%d", &a, &b);
			g[a].push_back(b);
		}
		
		if(find_cycle::go_find(n)){
			puts("1");
		} else puts("0");
		
		find_cycle::reset(n);
	}
}
