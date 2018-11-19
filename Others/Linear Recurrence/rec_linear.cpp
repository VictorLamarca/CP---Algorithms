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

//multipllica matriz - VALORES EM MÓDULO
vector<vector<ll>> mm(vector<vector<ll>> a, vector<vector<ll>> b){
	vector<vector<ll>> ans(a.size(),vector<ll>(b[0].size()));
	
	int l = a.size();
	int c = b[0].size();
	int tam = a[0].size();
	
	fr(i,l){
		fr(j,c){
			ll tot = 0;
			fr(k,a[0].size()){
				tot = (tot+a[i][k]*b[k][j])%MOD;
			}
			ans[i][j] = tot;
		}
	}
	
	return ans;
}

//matriz identidade N x N
vector<vector<ll>> ident(int n){
	vector<vector<ll>> ans(n,vector<ll>(n,0));
	
	fr(i,n) ans[i][i] = 1;
	
	return ans;
}

//Eleva matriz a um expoente
vector<vector<ll>> em(vector<vector<ll>> a, ll exp){
	if(exp==0) return ident(a.size());
	if(exp==1) return a;
	vector<vector<ll>> mid = em(a,exp/2);
	if(exp%2) return mm(mm(mid,mid),a);
	return mm(mid,mid);
}

int main(){
	//FILE_IN FILE_OUT
	ll e0, k;
	cin >> e0 >> k;
	
	if(e0==0){
		cout << 0 << endl;
		return 0;
	}
	
	//e0 = e0%MOD DEPOISSSS de checar se é zero
	e0 = e0%MOD;
	
	//MOD-1 = -1
	vector<vector<ll>> f0 = {{2ll*e0,MOD-1}}, t = {{2,0},{1,1}};
	
	vector<vector<ll>> ans = mm(f0,em(t,k));
	
	cout << ans[0][0] << endl;
	
	return 0;
}

