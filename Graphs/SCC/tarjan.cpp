#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;

#define pb push_back

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LLONG_MAX
//-DBL_MAX
//__builtin_popcountll(ll x) - __builtin_popcount(int x)

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define print(tup) if(debug) cout << #tup << " = {" << get(tup,0) << ", " << get(tup,1) << ", " << get(tup,2) << "}\n"
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

const int N = 1e5+10;

vector<int> g[N];
int disc[N], low[N], tempo; 
//primeiro tempo em que nó foi descoberto, minimo entre disc[no] e low[v] dos vizinhos

int st[N], ss; 
//stack e size of stack

int comp[N], ncomp;
//componente do noh i (0 se ainda nao pertence a componente)
//compi[i] : [1,ncomp]

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

int main(){
	//FILE_IN FILE_OUT
	int n, m;
	cin >> n >> m;
	
	fr(i,m){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].pb(v);
	}
	
	fr(i,n) if(!disc[i]) dfs(i);
	
	fr(i,n) cout << "comp[" << i << "] = " << comp[i] << endl;
	
	return 0;
}
/*
7 9
0 1
1 3
1 2
3 2
2 4
4 1
3 5
5 6
6 5
*/

