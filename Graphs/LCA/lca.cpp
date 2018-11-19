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
typedef tuple<ll,ll,ll> t3ll;

#define mt make_tuple
#define get(a,id) get<id>(a)

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

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

//<O(nlgn), O(lgn)>


//LEMBRAR DE POR O MAKE DEPOIS DE MONTAR A ARVORE
const int N = 1e5+10;
const int MLOG = 20;
vector<int> g[N];
int L[N]; //L[i] = level do nó i (raiz = 0)
int P[N]; //pai do nó i (raiz = -1)
int A[N][MLOG+1]; //A[i][j] = pai 2^j niveis acima do nó i - A de ancestral

void dfsd(int no, int from, int d){
	L[no] = d;
	
	for(auto it : g[no]){
		if(it==from) continue;
		P[it] = no;
		dfsd(it,no,d+1);
	}
	
	return;
}

void make(int n){
	P[0] = -1;
	dfsd(0,-1,0);
	
	fr(i,n){
		fr(j,MLOG){
			A[i][j] = -1;
		}
	}
	
	fr(i,n) A[i][0] = P[i];
	
	for(int j = 1; 1<<j<n;j++){
		fr(i,n){
			if(~A[i][j-1]){
				A[i][j] = A[A[i][j-1]][j-1];
			}
		}
	}
	return;
}

int lca(int p, int q){
	if(L[p]<L[q]) swap(p,q);
	
	for(int i = MLOG; i>=0;i--){
		if(L[p]-L[q]>=1<<i){
			p = A[p][i];	
		}
	}
	
	if(p==q) return p;
	
	for(int i = MLOG;i>=0;i--){
		if(A[p][i]!=A[q][i]){
			q = A[q][i];
			p = A[p][i];
		}
	}
	
	return P[q];
}	

int dist(int p, int q){
	prin(lca(p,q));	
	return L[p]+L[q]-2*L[lca(p,q)];
}

int main(){
	//FILE_IN FILE_OUT
	
	int n;
	
	int m, a, b;
	
	cin >> n >> m;
	
	fr(i,m){
		cin >> a >> b;
		a--,b--;
		g[a].pb(b);
		g[b].pb(a);
	}
	
	make(n);
	
	//prin(lca(7,4)+1);
	prin(lca(4-1,5-1)+1);
	
	return 0;
}

/*
8
7
1 2
2 3
3 4
4 5
5 6
6 7
7 8

grafo vetor
lca(7,4)+1 = 5

--------------------
ATUAL
5
4
1 3
1 2
2 4
2 5

lca(4-1,5-1)+1 = 2
*/

