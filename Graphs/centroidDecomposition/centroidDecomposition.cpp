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

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LLONG_MAX
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

const int N = 1e5+10;

vector<int> g[N], ct[N];
int rootct;
int subsize[N];
int jact[N];

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
		ct[from].pb(cur);
		ct[cur].pb(from);
	}
	jact[cur] = 1;
	
	for(auto &it : g[cur]){
		if(it==from or jact[it]) continue;
		mkct(it,cur);
	}
	return;
}

//--------TESTE-----------------------------
// a partir do grafo ct, faz a matriz mat para visualizar levels da centroid tree
vector<vector<int>> mat;

void fazmat(int no, int from, int d){
	if(d==mat.size()) mat.pb(vector<int>(1,no));
	else mat[d].pb(no);
	for(auto &it : ct[no]){
		if(it==from) continue;
		fazmat(it,no,d+1);
	}
}
//-----------------------------------------

int main(){
	//FILE_IN FILE_OUT
	int n;
	cin >> n;
	
	fr(i,n-1){
		int u,v;
		scanf("%d%d", &u, &v);
		g[u].pb(v);
		g[v].pb(u);
	}
	
	mkct(1,-1);
	
	//----PRINTANDO CENTROID TREE----------
	fazmat(rootct,-1,0);
	
	for(auto &v : mat){
		for(auto it : v) cout << it << " ";
		cout << endl;
	}
	//----------------------------------
	
	return 0;
}


/*tutorial com imagem do teste a seguir:
https://www.geeksforgeeks.org/centroid-decomposition-of-tree/

16
1 4
2 4
3 4
4 5
5 6
6 7
8 7
9 7
6 10
10 11
11 12
11 13
12 14
15 13
13 16
*/

