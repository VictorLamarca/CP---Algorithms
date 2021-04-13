#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min<ll>(a,b)
#define rmax(a,b) a = max<ll>(a,b)

#define fi first
#define se second

//solves problem L from: https://codeforces.com/gym/101612/standings/friends/true

typedef pair<ll,ll> pll;

const int N = 1e5+10;

vector<ll> divisores(1,1);
vector<pll> vcur;
map<ll,int> prime_factors;
vector<pll> v_prime_factors;

void reset_find_divisores(){
	divisores = vector<ll>(1,1);
	vcur.clear();
	prime_factors.clear();
	v_prime_factors.clear();
}

//rand gera por garantia pelo menos de [0,2^15-1]
ll grand(){
	ll ans = 0;
	fr(i,4){
		ans <<=15;
		ans += rand()%(1<<15);
	}
	ans<<=3;
	ans+=rand()%(1<<3);
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
	if(id==sz(vcur)){
		divisores.push_back(cur);
		return;
	}
	ll val  = vcur[id].fi;
	ll numF = vcur[id].se;
	ll aux = 1;
	for(int i = 1; i<=numF; i++){
		aux*=val;
		go(cur*aux,id+1);
	}
}

void find_divisores(ll x){
	factor(x);
	for(auto it : prime_factors){
		v_prime_factors.push_back(it);
	}
	int np = v_prime_factors.size();
	for(int mask = 1; mask<(1<<np); mask++){
		vcur.clear();
		fr(i,np){
			if(mask&(1<<i)){
				vcur.push_back(v_prime_factors[i]);
			}
		}	
		go(1,0);
	}
	sort(all(divisores));
	divisores.resize(unique(all(divisores))-divisores.begin());
}

int main(){
	#ifdef ONLINE_JUDGE
	freopen("little.in", "r", stdin);
	freopen("little.out", "w", stdout);
	#endif // ONLINE_JUDGE

	ios::sync_with_stdio(0); cin.tie(0);	
	ll n;
	cin >> n;
	
	find_divisores(n);
	
	//prinv(divisores);
	
	//The code below is specific to the problem
	//-------------------------------------------
	
	if(n==1 or (sz(prime_factors)==1 and prime_factors.begin()->fi==2)){
		cout << -1 << "\n";
		return 0;
	}
	vector<vector<ll>> ans(1,vector<ll>(1,n));
	fr(i,sz(divisores)-1){
		if(divisores[i]==1) continue;
		{
			ll cur = 1;
			int f1 = 0;
			while(divisores[i]<LLONG_MAX/cur and n%(cur*divisores[i])==0){
				f1++;
				cur*=divisores[i];
			}
			if(cur==n){
				ans.emplace_back();
				fr(cnt,f1) ans.back().emplace_back(divisores[i]);
			}
		}
		if(divisores[i]+1==divisores[i+1]){
			ll cur = 1;
			int f1 = 0, f2 = 0;
			while(divisores[i]<LLONG_MAX/cur and n%(cur*divisores[i])==0){
				f1++;
				cur*=divisores[i];
			}
			while(divisores[i+1]<LLONG_MAX/cur and n%(cur*divisores[i+1])==0){
				f2++;
				cur*=divisores[i+1];
			}
			if(cur==n){
				ans.emplace_back();
				fr(cnt,f1) ans.back().emplace_back(divisores[i]);
				fr(cnt,f2) ans.back().emplace_back(divisores[i+1]);
			}
		}
	}
	
	cout << sz(ans) << "\n";
	for(auto &v : ans){
		cout << sz(v) << " ";
		fr(i,sz(v)){
			if(i) cout << " ";
			cout << v[i];
		}
		cout << "\n";
	}
}
