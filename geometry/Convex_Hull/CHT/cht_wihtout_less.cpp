#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min(a,b)
#define rmax(a,b) a = max(a,b)

#define fi first
#define se second

//This is a CHT - but coded wihtout the multiset<Line,less<>> that makes the code cleaner but may nto compile on older judges

//solves https://www.urionlinejudge.com.br/judge/en/problems/view/1282

bool Q;
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : k < o.k;
	}
};
 
struct Cht : multiset<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return l.k * x + l.m;
	}
};

int main(){
	//ios::sync_with_stdio(0); cin.tie(0);
	int n, k;
	while(scanf("%d%d", &n, &k)!=EOF){
		vector<vector<ll>> dp(n+1,vector<ll>(k+1));
		vector<ll> x(n+1), w(n+1);
		
		vector<ll> peso(n+1), pt(n+1);
		
		vector<Cht> vc(k+1);
		
		for(int i = 1; i<=n; i++){
			scanf("%lld", &x[i]);
			scanf("%lld", &w[i]);
		}
		
		for(int i = 1; i<=n; i++){
			peso[i] = peso[i-1]+w[i];
			pt[i] = pt[i-1] + (x[i]-x[i-1])*peso[i-1];
		}
		
		for(int i = n; i>=1; i--){
			for(int can_use = k; can_use>=1; can_use--){
				int tam_suf = n - i + 1;
				if(can_use>=tam_suf){
					dp[i][can_use] = 0;
				} else if(can_use==1){
					dp[i][can_use] = pt[n]-pt[i-1] - (x[n]-x[i-1])*peso[i-1];
				} else{
					dp[i][can_use] = -vc[can_use-1].query(peso[i-1]) + x[i-1]*peso[i-1] - pt[i-1];
				}
				vc[can_use].add(x[i-1], -pt[i-1] - dp[i][can_use]);
			}
		}
		
		printf("%lld\n", dp[1][k]);
	}
}
