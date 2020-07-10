#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

//solves https://www.spoj.com/problems/LCMSUM/

template <int N> struct List{
	int sz = 0;
	int edge[N], prox[N], fi[N];

	List(){
		memset(fi,-1,sizeof(fi));
	}

	void ae(int u, int v){
		edge[sz] = v;
		prox[sz] = fi[u];
		fi[u] = sz++;
	}
};

const int N = 1e6;
const int N10 = N+10;
const int M = 5e7+10;
List<M> primos, divisor;

int v_phi[N10];

int phi(int n){
	int ans = n;
	for(int id = primos.fi[n]; id!=-1; id = primos.prox[id]) ans -= ans/primos.edge[id];
	return ans;
}

int main(){
	int t; cin >> t;
	
	for(int i = 1; i<=N; i++){
		for(int j = 2*i; j<=N; j+=i){
			divisor.ae(j,i);
		}
	}
	for(int i = 2; i<=N; i++){
		if(primos.fi[i]==-1) for(int j = i; j<=N; j+=i){
			primos.ae(j,i);
		}
	}
	
	for(int i = 1; i<=N; i++) v_phi[i] = phi(i);
	
	fr(tt,t){
		int n;
		scanf("%d", &n);
		ll ans = 0;
		for(int id = divisor.fi[n]; id!=-1; id = divisor.prox[id]){
			ll g = divisor.edge[id];
			ll add = (ll)n*n/g*v_phi[n/g]/2ll;
			ans += add;
			
		} 
		ans+=n;
		printf("%lld\n", ans);
	}		
}
