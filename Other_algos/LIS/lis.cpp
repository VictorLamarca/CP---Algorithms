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

ll n;
vector<ll> v, ant;
vector<ll> tail(1,0);
ll len;

ll lis(){
	
	ant[0] = -1;
	
	frr(i,1,v.size()-1){
		if(v[i]>v[tail.back()]){
			ant[i] = tail.back();
			tail.pb(i);
		} else{
			int l = 0, r = tail.size()-1;
			while(l<r){
				int mid = (l+r)/2;
				if(v[tail[mid]]>=v[i]) r = mid;
				else l = mid+1;
			}
			if(l) ant[i] = tail[l-1];
			else ant[i] = -1;
			tail[l] = i;
		}
	}
	
	return tail.size();
}

int main(){
	//FILE_IN FILE_OUT
	
	cin >> n;
	v.resize(n);
	ant.resize(n);
		
	fr(i,n) scanf("%lld", &v[i]);
		
	cout << lis() << endl;
	
	
	vector<ll> ans;
	
	for(int i = tail.back(); i!=-1; i = ant[i]){
		ans.pb(v[i]);
	}
	
	reverse(all(ans));
	
	//fr(i,ans.size()) printf("%lld%c", ans[i], " \n"[i==ans.size()-1]);
	
	return 0;
}

