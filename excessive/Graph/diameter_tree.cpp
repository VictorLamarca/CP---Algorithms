#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()
#define rmin(a,b) a = min(a,b)
#define rmax(a,b) a = max(a,b)

typedef long long ll;

//solves https://www.urionlinejudge.com.br/judge/en/problems/view/1499

const int N = 1e5+10;

namespace diametro_space{
int n;
vector<int> *g;
 
void dfs(int no, int from, int dac, ll d[]){
	d[no] = dac;
	for(auto it : g[no]){
		if(it!=from) dfs(it,no,dac+1,d);
	}
}
 
int max_dist_glob = 0; // diametro da arvore

int get_most_dist(int no, ll d[]){
	dfs(no,-1,0,d);
	int max_dist_cur = -1;
	int no_max_dist = -1;
	fr(i,n){
		if(d[i]>max_dist_cur){
			max_dist_cur = d[i];
			no_max_dist = i;
		}
	}
	max_dist_glob = max(max_dist_glob,max_dist_cur);
	return no_max_dist;
}

vector<int> nos_diam;

int no0, no1;

//retorna diametro em numero de arestas! (ou seja, vertices -1)
ll find_diametro(vector<int> _g[N], int _n, ll vd[2][N]){
	g = _g;
	n = _n;
	max_dist_glob = 0;
	
	no1 = get_most_dist(0,vd[0]);
	no0 = get_most_dist(no1,vd[1]);
	
	//commentar se listar os nos no diametro nao eh necessario
	get_most_dist(no0,vd[0]);
	fr(i,n) 
		if(vd[0][i]+vd[1][i]==max_dist_glob) 
			nos_diam.push_back(i);
	//-------------------------
	
	return max_dist_glob;
}

}; //end space diametro

vector<int> g[2][N];
ll vdist[2][2][N];

int main(){
	ll n[2];
	while(scanf("%lld%lld", n, n+1)!=EOF){
		fr(cor,2){
			fr(i,n[cor]-1){
				int a, b; scanf("%d%d", &a, &b); a--,b--;
				g[cor][a].push_back(b);
				g[cor][b].push_back(a);
			}
		}
		ll max_diam = 0;
		fr(cor,2) rmax(max_diam,diametro_space::find_diametro(g[cor],n[cor],vdist[cor]));
		
		fr(cor,2) fr(i,n[cor]) g[cor][i].clear();
		
		vector<ll> v[2];
		fr(cor,2){
			fr(i,n[cor]){
				v[cor].push_back(max(vdist[cor][0][i],vdist[cor][1][i]));
			}
			sort(all(v[cor]));
		}
		
		vector<ll> soma_suf(n[1]);
		for(int i = n[1]-1; i>=0; i--){
			soma_suf[i] = v[1][i];
			if(i+1<n[1]) soma_suf[i]+=soma_suf[i+1];
		}
		
		ll soma = 0;
		int j = n[1];
		fr(i,n[0]){
			while(j-1>=0 and v[1][j-1]+v[0][i]+1>=max_diam) j--;
			ll tam_suf = n[1]-j;
			
			soma += (n[1]-tam_suf)*max_diam;
			if(tam_suf) soma += tam_suf*v[0][i] + soma_suf[j] + tam_suf;
		}
		
		printf("%.3lf\n", (double)soma/(n[1]*n[0]));
	}
}
