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

//solves https://www.spoj.com/problems/XMAX/


//returns the maximun xor over all subsets of the values
ll gauss_xor_subset(vector<ll> v){
	int i = 0;
	for(int col = 62; col>=0 and i<sz(v); col--){
		ll val = (1ll<<col);
		int id = -1;
		for(int j = i; j<sz(v); j++){
			if(v[j]&val){
				id = j;
				break;
			}
		}
		
		if(id==-1) continue;
		
		swap(v[i],v[id]);
		
		fr(j,sz(v)){
			if(i!=j and (val&v[j])){
				v[j]^=v[i];
			}
		}
		i++;
	}
	
	ll ans = 0;
	for(auto &it : v) if( (ans^it) > ans) ans ^= it;
	
	return ans;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	
	vector<ll> v(n);
	fr(i,n) cin >> v[i];
	
	cout << gauss_xor_subset(v) << "\n";
}
