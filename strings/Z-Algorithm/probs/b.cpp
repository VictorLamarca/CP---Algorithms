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

const int N = 1;

int main(){
	//FILE_IN FILE_OUT
	
	int n;
	cin >> n;
	
	vector<int> v(n), ans(n);
	
	fr(i,n) scanf("%d", &v[i]);
	
	int pivo = n;
	
	for(int i = n-1;i>=0;i--){
		if(v[i]){
			int prox = i-v[i]+1;
			ans[prox] = max(ans[prox],v[i]);
			
			int futpivo = pivo;
			
			int cur = v[v[i]-1];
			futpivo = min(futpivo,i-cur+1);
			
			while(cur and i-cur+1<pivo){
				ans[i-cur+1] = max(cur,ans[i-cur+1]);
				cur = v[cur-1]; 
			}
			
			pivo = futpivo;
		}
	}
	
	fr(i,n) printf ("%d%c", ans[i], " \n"[i==n-1]);
	
	return 0;
}

