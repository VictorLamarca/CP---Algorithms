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

//http://codeforces.com/gym/101128/my

pii menos(pii a, pii b){
	return pii(a.fi-b.fi, a.se-b.se);
}

ll vet(pii a, pii b){
	return 1ll*a.fi*b.se-1ll*a.se*b.fi;
}

vector<pii> v[2];

int n[2];

vector<pii> lh, uh;

void mkch(){
	vector<pii> &v = ::v[0];
	
	sort(all(v));
	v.resize(unique(all(v))-v.begin());
	int n = v.size();
	
	fr(i,n){
		int iu = uh.size();
		while(iu>=2 and vet(menos(uh[iu-1],uh[iu-2]),menos(v[i],uh[iu-1]))>=0){
			iu--;
			uh.pop_back();
		}
		uh.pb(v[i]);
	}
	
	fr(i,n){
		int iu = lh.size();
		while(iu>=2 and vet(menos(lh[iu-1],lh[iu-2]),menos(v[i],lh[iu-1]))<=0){
			iu--;
			lh.pop_back();
		}
		lh.pb(v[i]);
	}
	
	return;
}

bool dentro(pii p){
	{
	auto it = upper_bound(all(uh),pii(p.fi,INT_MAX));
	if(it==uh.begin()) return 0;
	if(it==uh.end()){
		it--;
		if(it->fi<p.fi or p.se>it->se) return 0;
	} else{
		it--;
		if(vet(menos(p,*it),menos(*(it+1),*it))<0) return 0;
	}
	}
	
	{
	auto it = upper_bound(all(lh),pii(p.fi,-INT_MAX));
	if(it==lh.end()) return 0;
	if(it==lh.begin()){
		if(it->fi>p.fi or p.se<it->se) return 0;
	} else{
		it--;
		if(vet(menos(p,*it),menos(*(it+1),*it))>0) return 0;
	}
	}
	
	return 1;
	
	
}

int main(){
	//FILE_IN FILE_OUT
	int ans = 0;
	
	fr(cor,2){
		scanf("%d", n+cor);
		fr(i,n[cor]){
			int x, y;
			scanf("%d%d", &x, &y);
			if(!cor){
				v[0].pb({x,y});
			} else{
				if(dentro({x,y})) ans++;
			}
		}
		if(!cor) mkch();
		
	}
	
	cout << ans << endl;
	
	return 0;
}

