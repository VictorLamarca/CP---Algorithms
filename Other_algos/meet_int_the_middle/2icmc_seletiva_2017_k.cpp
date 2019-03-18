#include <bits/stdc++.h>
using namespace std;

//mudar file.in pelo nome do input e por FILE_IN
//antes dos scanfs
#define FILE_IN freopen("file.in", "r", stdin);

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

const ll MN = (1<<21), N = 1e5+10;

ll dp[MN], cnt[MN];

int main(){
	ll n, m;
	
	scanf("%lld%lld",&n, &m);
	
	fr(i,n){
		ll x;
		scanf("%lld",&x);
		cnt[x]++, dp[x]++;
	}
	
	fr(j,21){
		fr(i,MN){
			if(i&(1<<j)) dp[i]+=dp[i^(1<<j)];
		}	
	}
	ll ans = n*(n-1)/2;
	fr(i,MN){
		if(cnt[i]){
			ans-= cnt[i]*dp[i] - cnt[i] - cnt[i]*(cnt[i]-1)/2;// cnt[i]*(cnt[i]-1)/2 - cnt[i]*cnt[i];
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
