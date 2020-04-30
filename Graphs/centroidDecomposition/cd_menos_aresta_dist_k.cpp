#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

//solves https://wcipeg.com/problem/ioi1112

const int N = 2e5+10;

vector<pair<int,int>> g[N]; 
vector<int> ct[N];
int rootct;
int subsize[N];
int jact[N];

vector<vector<pair<int,int>>> dist_part[N];

int n, k;

vector<pair<int,int>> v_dist;
void get_dist(int no, int from, int ac_len,int ac_edge){
	if(ac_len>k) return; //Atencao aqui, nesse em problema em particular nao precisava olhar para dist maior q k
	v_dist.emplace_back(ac_len,ac_edge);
	for(auto &par : g[no]){
		int it,curd; tie(it,curd) = par;
		if(it==from or jact[it]) continue;
		get_dist(it,no,ac_len+curd,ac_edge+1);
	}
}

int mksubsize(int no, int from){
	int tam = 1;
	for(auto &par : g[no]){
		int it; tie(it,ignore) = par;
		if(it==from or jact[it]) continue;
		tam+=mksubsize(it,no);
	}
	subsize[no] = tam;
	return tam;
}

int findc(int no, int from, int tam){
	for(auto &par : g[no]){
		int it; tie(it,ignore) = par;
		if(it==from or jact[it]) continue;
		if(subsize[it]>tam/2) return findc(it,no,tam);
	}
	return no;
}

void mkct(int root, int from){
	mksubsize(root,-1);	
	
	int cur = findc(root,-1,subsize[root]);
	
	if(from==-1) rootct = cur;
	else{
		ct[from].push_back(cur);
		ct[cur].push_back(from);
	}
	jact[cur] = 1;
	
	for(auto &par : g[cur]){
		int it,cdist; tie(it,cdist) = par;
		if(it==from or jact[it]) continue;
		get_dist(it,cur,cdist,1);
		dist_part[cur].push_back(v_dist);
		v_dist.clear();
		mkct(it,cur);
	}
	dist_part[cur].push_back(vector<pair<int,int>>(1));
	return;
}

const int M = 1e6+10;
multiset<int> num_edges[M];
int main(){
	scanf("%d%d", &n, &k);
	fr(i,n-1){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		g[a].emplace_back(b,c);
		g[b].emplace_back(a,c);
	}
	mkct(0,-1);
	
	int ans = INT_MAX;
	fr(no,n){
		for(auto &v : dist_part[no]){
			for(auto &p : v){
				int dist_len, dist_edge; tie(dist_len,dist_edge) = p;
				num_edges[dist_len].insert(dist_edge);
			}
		}
		for(auto &v : dist_part[no]){
			for(auto &p : v){
				int dist_len, dist_edge; tie(dist_len,dist_edge) = p;
				num_edges[dist_len].erase(num_edges[dist_len].find(dist_edge));
			}
			for(auto &p : v){
				int dist_len, dist_edge; tie(dist_len,dist_edge) = p;
				if(!num_edges[k-dist_len].empty()){
					ans = min(ans, dist_edge+*num_edges[k-dist_len].begin());
				}
			}
		}
		for(auto &v : dist_part[no]){
			for(auto &p : v){
				int dist_len, dist_edge; tie(dist_len,dist_edge) = p;
				num_edges[dist_len].clear();
			}
		}
	}
	if(ans==INT_MAX) puts("-1");
	else printf("%d\n", ans);
}
