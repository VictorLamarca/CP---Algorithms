#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;

#define fi first
#define se second

#define all(a) a.begin() a.end()

#define fr(i,n) for(int i = 0; i<n;i++)
#define frr(i,a,b) for(int i = a;i<=b;i++)
#define pb push_back

bool debug = 1;
#define prin(a) if(debug) cout << #a << " = " << a << endl;

//prob F - illuminatin
//http://codeforces.com/gym/101201

const int N = 2e6+10;

int tempo, ncomp, ss;
int disc[N], st[N], low[N], comp[N];

vector<int> g[N];

const int M = 1e3+10;
int mat[M][M];

int dfs(int no){
	disc[no] = low[no] = ++tempo;
	st[ss++] = no;
	for(auto it : g[no]){
		if(!disc[it]) low[no] = min(low[no],dfs(it));
		else if(!comp[it]) low[no] = min(low[no],disc[it]);
		//pode ser low[it], mas melhor manter disc[it] q tmb funciona e eh indicado pelo editorial
	}
	if(low[no]==disc[no]){
		comp[no] = ++ncomp;
		while(st[ss-1]!=no){
			comp[st[--ss]] = comp[no];
		}
		ss--;
	}
	return low[no];
}

int main(){
	int n, r, l;
	cin >> n >> r >> l;
	
	frr(i,1,l){
		int u, v;
		scanf("%d%d", &u, &v);
		mat[u][v] = i;
	}
	
	frr(i,1,n){
		frr(j,1,n){
			if(mat[i][j]){
				int u, v;
				
				frr(id,i+1,min(n,i+r)){
					if(mat[id][j]){
						u = 2*(mat[i][j]-1);
						v= 2*(mat[id][j]-1)+1;
						g[u].pb(v);
					}
				}
				
				frr(id,max(1,i-r),i-1){
					if(mat[id][j]){
						u = 2*(mat[i][j]-1);
						v= 2*(mat[id][j]-1)+1;
						g[u].pb(v);
					}
				}	
				
				frr(jd,j+1,min(n,j+r)){
					if(mat[i][jd]){
						u = 2*(mat[i][j]-1)+1;
						v= 2*(mat[i][jd]-1);
						g[u].pb(v);
					}
				}
				
				frr(jd,max(j-r,1),j-1){
					if(mat[i][jd]){
						u = 2*(mat[i][j]-1)+1;
						v= 2*(mat[i][jd]-1);
						g[u].pb(v);
					}
				}
			}
		}
	}
	
	fr(u,2*l){
		if(!disc[u]) dfs(u);
	}
	
	int ok = 1;
	fr(i,l){
		if(comp[2*i]==comp[2*i+1]) ok = 0;
	}
	
	ok? cout << "YES" << endl : cout << "NO" << endl;
	
}
