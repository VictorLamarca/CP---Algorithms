//http://codeforces.com/problemset/problem/45/D

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
#define prin(a) (debug?cout << #a << " = " << (a) << endl:cout << "")
#define soprin(a) if(debug) cout << (a);
#define ppal(a) if(debug) cout << #a << endl;
#define prinsep if(debug) cout << "------" << endl;
#define cendl if(debug) cout << endl

const int N = 1e7+1000;
	
vector<pii> v[N];

int main(){
	ll n;
	scanf("%lld", &n);
	
	fr(i,n){
		ll x, r;
		scanf("%lld%lld", &x, &r);
		v[x].pb({r,i});
		
	}
	
	vector<int> ans(n);
	multiset<pii> st;
	fr(i,N-5){
		while(!v[i].empty()){
			st.insert(v[i].back());
			v[i].pop_back();
		}
		
		if(!st.empty()){
			ans[st.begin()->se] = i;
			st.erase(st.begin());
			
		}
	}	
	
	for(auto it : ans){
		cout << it << " ";
	}
	cout << endl;
	
	return 0;
}

