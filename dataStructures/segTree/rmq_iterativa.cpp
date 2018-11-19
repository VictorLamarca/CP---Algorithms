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

vector<int> v, sl, sr;

//PRECISA DEFINIR v, sl e sr e dar update em tds os indices
//E TALVEZ MUDAR OPERACAO DE MAXIMO	

//PRECISA POR O TAMANHO DE V, SL E SR

//É zero-indexed e a query é fechada [l,r]

void updt(int id, int val, vector<int> &v = v, vector<int> &sl = sl, vector<int> &sr = sr){
	v[id] = max(v[id],val);
	int x = id;
	while(x<sl.size()){
		sl[x] = max(sl[x],val);
		x |= (x+1);
	}
	x = id;
	while(x>=0){
		sr[x] = max(sr[x],val);
		x = (x & (x+1))-1;
	}
	
	return;
}

int qry(int l, int r, vector<int> &v = v, vector<int> &sl=  sl, vector<int> &sr = sr){
	int ans = -INT_MAX;
	int x = l;
	while((x| (x+1)) <= r){
		ans = max(ans,sr[x]);
		x |= (x+1);
	}
	ans = max(ans,v[x]);
	x = r;
	while((x& (x+1))-1>=l){
		ans = max(ans,sl[x]);
		x = (x&(x+1))-1;
	}
	
	return ans;
}	

vector<pii> dogs;

struct cmp{
	bool operator ()(int a, int b){
		pii pa(dogs[a].fi,dogs[a].se);
		pii pb(dogs[b].fi,dogs[b].se);
		
		if(pa==pb) return 0;
		
		if(max(pa.fi,pb.fi)>min(pa.se,pb.se)){
			return qry(pa.fi,pa.se,v)<qry(pb.fi,pb.se,v);
		}
		
		if(pb.fi>=pa.fi and pb.se<=pa.se) return 0;
		if(pa.fi>=pb.fi and pa.se<=pb.se) return 1;
		
		if(pa.fi<pb.fi){
			return qry(pa.fi,pb.fi-1,v)<qry(pa.se+1,pb.se,v);
		} else{
			return qry(pb.fi,pa.fi-1,v)>qry(pb.se+1,pa.se,v);
		}
		
	}
};

int main(){
	int n;
	
	cin >> n;
	
	v.assign(n,0);
	sl.assign(n,0);
	sr.assign(n,0);
	
	fr(i,n){
		int x;
		scanf("%d", &x);
		updt(i,x,v,sl,sr);
	}
	
	int m;
	cin >> m;
	
	frr(i,1,m){
		int l, r;
		scanf("%d%d", &l, &r);
		l--, r--;
		dogs.pb({l,r});
	}
	
	vector<int> ord(m);
	fr(i,m) ord[i] = i;
	
	sort(all(ord),cmp());
	
	fr(i,m){
		printf("%d%c", ord[i]+1," \n"[i==m-1]);
	}
	
	return 0;
}

/*
vector<ll> v, sl, sr;

void updt(int id, ll val, vector<ll> &v = v, vector<ll> &sl = sl, vector<ll> &sr = sr){
	v[id] = max(v[id],val);
	int x = id;
	while(x<sl.size()){
		sl[x] = max(sl[x],val);
		x |= (x+1);
	}
	x = id;
	while(x>=0){
		sr[x] = max(sr[x],val);
		x = (x & (x+1))-1;
	}
	
	return;
}

ll qry(int l, int r, vector<ll> &v = v, vector<ll> &sl=  sl, vector<ll> &sr = sr){
	ll ans = -LLONG_MAX;
	ll x = l;
	while((x| (x+1)) <= r){
		ans = max(ans,sr[x]);
		x |= (x+1);
	}
	ans = max(ans,v[x]);
	x = r;
	while((x& (x+1))-1>=l){
		ans = max(ans,sl[x]);
		x = (x&(x+1))-1;
	}
	
	return ans;
}	
*/

