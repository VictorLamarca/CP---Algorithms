#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//solves 

const int N = 1e5+10;

vector<int> g[N]; 
vector<int> ct[N];
int rootct;
int subsize[N];
int jact[N];

vector<vector<pair<int,int>>> dist_part[N]; // dist_part[no_centroide][i] = vetor de pares (d,it) que representa que it esta a distancia d de no_centroide, mas dos its, apenas os que estao na subarvore i (em que i eh o iesimo filho direto da centroide tree de root no_centroide, ou seja, faco um agrupamento para distinguir que nos de diferentes i tem lca = no_centroide, e nos de msm i tem lca mais abaixo)

int n, k;

vector<pair<int,int>> v_dist;
void get_dist(int no, int from, int ac){
	if(ac>k) return; //Atencao aqui, nesse em problema em particular nao precisava olhar para dist maior q k
	v_dist.emplace_back(ac,no);
	for(auto &it : g[no]){
		if(it==from or jact[it]) continue;
		get_dist(it,no,ac+1);
	}
}

int mksubsize(int no, int from){
	int tam = 1;
	for(auto &it : g[no]){
		if(it==from or jact[it]) continue;
		tam+=mksubsize(it,no);
	}
	subsize[no] = tam;
	return tam;
}

int findc(int no, int from, int tam){
	for(auto &it : g[no]){
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
	for(auto &it : g[cur]){
		if(it==from or jact[it]) continue;
		get_dist(it,cur,1);
		dist_part[cur].push_back(v_dist);
		v_dist.clear();
		mkct(it,cur);
	}
	dist_part[cur].push_back(vector<pair<int,int>>(1,{0,cur}));
	return;
}

ll freq_dist[N], pref_dist[N];
ll ans[N];

int main(){
	scanf("%d%d", &n, &k);
	fr(i,n-1){
		int a, b;
		scanf("%d%d", &a, &b); a--,b--;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	mkct(0,-1);
	
	fr(no,n){
		
		int idu = 0;
		for(auto &v : dist_part[no]){
			for(auto &par : v){
				int d, it; tie(d,it) = par;
				freq_dist[d]++;
				idu = max(idu,d);
			}
		}
		fr(i,idu+1){
			pref_dist[i] = freq_dist[i];
			if(i) pref_dist[i]+=pref_dist[i-1];
		}
		for(auto &v : dist_part[no]){
			int idu_cur = 0;
			for(auto &par : v){
				int d, it; tie(d,it) = par;
				idu_cur = max(idu_cur,d);
			}
			vector<int> freq_cur(idu_cur+1), pref_cur(idu_cur+1);
			for(auto &par : v){
				int d, it; tie(d,it) = par;
				freq_cur[d]++;
			}
			fr(i,idu_cur+1){
				pref_cur[i] = freq_cur[i];
				if(i) pref_cur[i]+=pref_cur[i-1];
			}
			for(auto &par : v){
				int d, it; tie(d,it) = par;
				int idc = min(k-d,idu);
				int idc_cur = min(idc,idu_cur);
				ans[it]+= pref_dist[idc] - pref_cur[idc_cur];
			}
		}
		fr(i,idu+1){
			pref_dist[i] = freq_dist[i] = 0;
		}
		
	}
	fr(i,n) printf("%lld\n", ans[i]+1);
}
