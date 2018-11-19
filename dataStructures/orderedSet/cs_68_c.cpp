#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> //required
#include <ext/pb_ds/tree_policy.hpp> //required
using namespace __gnu_pbds; //required 
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

const int N = 1e5;

template <class T> class cmp{
public:
  bool operator() (const T& a, const T& b) const {return a.se*b.fi<a.fi*b.se;}
};

template <typename T> using ordered_set =  tree<T, null_type, cmp<T>, rb_tree_tag, tree_order_statistics_node_update>; 

ordered_set <pll> s; 

vector<pll> vp;
vector<int> ord;
int ans[N];

class cmp2{
public:
	bool operator ()(int a, int b){
		return vp[a]<vp[b];
	}
};

int main(){
	//FILE_IN FILE_OUT
	int n;
	cin >> n;
	
	fr(i,n){
		int x, y;
		scanf("%d%d", &x, &y);
		vp.pb(pll(x,y));
		ord.pb(i);
	}
	
	sort(all(ord), cmp2());
	
	fr(i,n){
		s.insert(vp[ord[i]]);
		ans[ord[i]] = s.order_of_key(vp[ord[i]]);
	}	
	
	fr(i,n) printf("%d%c", ans[i], " \n"[i==n-1]);
	
	return 0;
}

