#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;
typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define PI acos(-1)
ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << p.fi << " " << #p << ".se=" << p.se << endl
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

#define mt make_tuple
#define get(a,id) get<id>(a)
#define t3ll tuple<ll,ll,ll>

const int N = 1e5+10;

class node{
public:
	list<int> nb;
};

vector<node> g;

bool vis[N];

void dfs(int no){
	if(vis[no]) return;
	vis[no] = 1;
	for(auto it : g[no].nb){
		dfs(it);
	}
	
	return;
}

int main(){
	bool ans = 0;
	int n, m;
	cin >> n >> m;
	g.resize(n);
	
	fr(i,m){
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].nb.pb(v);
		g[v].nb.pb(u);
	}
	
	dfs(0);
	
	int visitados = 0;
	fr(i,n){ 
		if(vis[i]) visitados++;
		else{
			prin(i+1);
		}
	}
	
	prin(n);
	prin(visitados);
	
	return 0;
}

