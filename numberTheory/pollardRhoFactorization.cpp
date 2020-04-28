#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
#define fr(i,n) for(int i = 0; i<n; i++)
#define fi first
#define se second

//rand gera por garantia pelo menos de [0,2^15-1]
ll grand(){
	ll ans = 0;
	fr(i,4){
		ans <<=15;
		ans += rand()%(1<<15);
	}
	return ans;
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

//Rabin Miller
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
		d = __gcd(abs(x-xx),n);
	} while(d==1);
	return d;
}

//mapa de primo para frequencia
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

//--------------------------
//solves problem f from: https://codeforces.com/gym/102299/standings
// USP 2019 try outs

ll mypot(ll b, ll x){
	ll ans = 1;
	fr(i,x) ans*=b;
	return ans;
}

int main(){
	srand(time(0));
	ll a, b;
	cin >> a >> b;
	
	ll g = __gcd<ll>(a,b);
	
	b/=g;
	
	if(b==1){ 
		cout << 2 << endl;
		return 0;
	}
	
	factor(b);
	
	ll ans = 1;
	
	for(auto &par : F){
		ans *= par.fi;
	}
	
	cout << ans << endl;
}
