#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("little.in", "r", stdin);
#define FILE_OUT freopen("little.out", "w", stdout);

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

vector<ll> divisores(1,1);
vector<pll> vcur;
map<ll,int> prime_factors;
vector<pll> v_prime_factors;

#define rm (rand()%MOD)
#define rm2 (rm*rm)%(MOD+2)

ll gcd(ll a,ll b){
	if(b>a) swap(a,b);
	if(b==0) return a;
	return gcd(b,a%b);
}

ll grand(){
	ll a = rm2;
	a<<=32;
	a+=rm2;
	return a;
}

ll mulmod(ll a, ll b, ll mod){
	if(b<0) return mulmod(a,(b%mod+mod)%mod,mod);
	if(b==0) return 0LL;
	ll ans = (2LL*mulmod(a,b/2,mod))%mod;
	if(b%2==0) return ans;
	return (ans+a)%mod;
}

ll exp_mod(ll a, ll x, ll m) {
    if (x == 0) return 1;
    ll res = exp_mod(a, x/2, m);
    res = mulmod(res, res, m); //(res * res) % m;
    if(x % 2 == 1) res = mulmod(res, a, m); // (res * a) % m
    return res;
}

bool ispp(ll n){
	if(n<=1) return 0;
	if(n<=3) return 1;
	ll s = 0, d = n-1;
	while(d%2==0){
		d/=2;
		s++;
	}
	
	fr(k,64){
		ll a = (grand()%(n-3))+2;
		ll x = exp_mod(a,d,n);
		if(x!=1 and x!=n-1){
			for(int r = 1;r<s;r++){
				x = mulmod(x,x,n);
				if(x==1) return 0;
				if(x==n-1) break;
			}
			if(x!=n-1) return 0;
		}
	}
	
	return 1;
}

ll rho(ll n){
	ll d, c = grand()%n, x = grand()%n,xx=x;
	if(n%2==0){
		return 2;
	}
	do{
		x = (mulmod(x,x,n)+c)%n;
		xx = (mulmod(xx,xx,n)+c)%n;
		xx = (mulmod(xx,xx,n)+c)%n;
		d = gcd(abs(x-xx),n);
	} while(d==1);
	return d;
}



void factor(ll n){
	if(n==1) return;
	if(ispp(n)){
		prime_factors[n]++;
		return;
	}
	ll d = rho(n);
	factor(d);
	factor(n/d);
	return;
}



void go(ll cur, ll id){
	if(id==vcur.size()){
		divisores.pb(cur);
		return;
	}
	
	ll val  = vcur[id].fi;
	ll numF = vcur[id].se;
	
	ll aux = 1;
	frr(i,1,numF){
		aux*=val;
		go(cur*aux,id+1);
	}
	
	return;
	
}

void find_divisores(ll x){

	factor(x);
	
	for(auto it : prime_factors){
		v_prime_factors.pb(it);
	}
	
	int np = v_prime_factors.size();
	
	frr(mask,1,(1<<np)-1){
		vcur.clear();
		
		fr(i,np){
			if(mask&(1<<i)){
				vcur.pb(v_prime_factors[i]);
			}
		}
		
		go(1,0);
	}
	
	sort(all(divisores));
	
	divisores.resize(unique(all(divisores))-divisores.begin());
	
	return;
}

int main(){
	//FILE_IN FILE_OUT
	
	ll x;
	cin >> x;
	
	find_divisores(x);
	
	prinv(divisores);
	
	return 0;
}
