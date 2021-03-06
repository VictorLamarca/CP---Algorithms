#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

//Solves: https://www.urionlinejudge.com.br/judge/pt/problems/view/2887

//LEMBRAR DE POR O MAKE DEPOIS DE MONTAR A ARVORE
const int N = 1e5+10;

namespace lca_space{
int nlog;
int n;
vector<int> *g;
int pai[N], dist[N]; //pai do nó i (raiz = -1)
int st[N][25]; //sparse table - st[i][j] = pai 2^j niveis acima do nó i

void dfs(int no, int from, int dac){
	dist[no] = dac;
	for(auto it : g[no]){
		if(it==from) continue;
		pai[it] = no;
		dfs(it,no,dac+1);
	}
}

void make(vector<int> _g[N], int _n){
	g = _g;
	n = _n;

	int root = 0;
	pai[root] = -1;
	dfs(root,-1,0);
	
	nlog = 1;
	while((1<<nlog)<n) nlog++;
	assert(nlog<25);
	
	fr(i,n) fr(j,nlog+1) st[i][j] = -1;
	fr(i,n) st[i][0] = pai[i];
	
	for(int j = 1; j<=nlog; j++){
		fr(i,n){
		    int ant_pai = st[i][j-1];
		    if(ant_pai!=-1) st[i][j] = st[ant_pai][j-1];
		}
	}
}

int lca(int p, int q){
	if(dist[p]<dist[q]) swap(p,q);
	
	for(int i = nlog; i>=0;i--){
		if(dist[p]-dist[q] >= (1<<i) ) p = st[p][i];	
	}
	
	if(p==q) return p;
	
	for(int i = nlog; i>=0; i--){
		if(st[p][i]!=st[q][i]){
			p = st[p][i];
			q = st[q][i];
		}
	}
	
	return pai[q];
}	

int get_dist(int u, int v){
	return dist[u]+dist[v]-2*dist[lca(u,v)];
}

};

vector<int> g[N];

int no_to_id[N];
int vlca[4][4];

int flca(int u, int v){
    u = no_to_id[u];
    v = no_to_id[v];
    return vlca[u][v];
}

int is(int u1, int u2, int v1, int v2){
    if(lca_space::dist[flca(u1,u2)]<lca_space::dist[flca(v1,v2)]) swap(u1,v1), swap(u2,v2);
    
    int ans = 0;
    
    fr(cor,2){
        int lca_outro = flca(u1,v1);
        if(lca_space::dist[flca(u1,v2)]>lca_space::dist[flca(u1,v1)]) lca_outro = flca(u1,v2);
        ans+= max(0, lca_space::dist[lca_outro]-lca_space::dist[flca(u1,u2)]+1);
        swap(u1,u2);
    }   
    
    if(ans) ans--;
    return ans;
}

int main(){
    int n, q;
    cin >> n >> q;
    
    fr(i,n-1){
        int u, v;
        scanf("%d%d", &u, &v);;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    lca_space::make(g,n);
    
    fr(qq,q){
        vector<int> v(4);
        fr(i,4) scanf("%d", &v[i]), v[i]--;
        fr(i,4) no_to_id[v[i]] = i;
        fr(i,4) fr(j,i){
            vlca[i][j] = vlca[j][i] = lca_space::lca(v[i],v[j]);
        }
        fr(i,4) vlca[i][i] = v[i];
        printf("%d\n", is(v[0],v[1],v[2],v[3]));
    }
}
