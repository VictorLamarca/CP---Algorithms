#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<(n);i++)
#define frit(it,c) for(auto it = (c).begin();it!=(c).end();it++)
// for(auto it : g[i].nb)

typedef long long ll;
typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;

#define PI acos(-1)
ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define prinsep if(debug) cout << "------" << endl;
#define cendl if(debug) cout << endl

/*
	Complexidade:
	100*O(raiz quarta de n)
	que é raiz do menor primo que divide n
	
	100 pq tem na vdd um big constant factor,
	da pra fatorar qlqr numero ateh 10^18 em 356 seg
	que é 100*sqrt(1e9)
	
*/

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

map<ll,int> F;

void factor(ll n){
	if(n==1) return;
	if(ispp(n)){
		F[n]++;
		return;
	}
	ll d = rho(n);
	factor(d);
	factor(n/d);
	return;
}

int main(){
	ll n;
	
	cin >> n;
	
	factor(n);
	
	prin(n);
	for(auto i : F){
		prin(i.fi);
	}
	
	return 0;
}

