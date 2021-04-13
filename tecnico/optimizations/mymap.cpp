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

//solves https://atcoder.jp/contests/abc191/tasks/abc191_f

template <class key_type,class value_type> 
struct mymap{
	vector<key_type> keys;
	vector<value_type> values;
 
mymap(vector<key_type> _keys){
	keys = _keys;
	sort(all(keys));
	keys.resize(unique(all(keys))-keys.begin());
	values = vector<value_type>(sz(keys)); //valores iniciados como default (nulo)
}
 
value_type &operator[](key_type key){
	//assert(binary_search(all(keys),key));
	int id = lower_bound(all(keys),key)-keys.begin();
	return values[id];
}
}; //end mymap

/*
//mymap without template, ll to ll

struct mymap{
vector<ll> keys, values;

mymap(vector<ll> _keys){
	keys = _keys;
	sort(all(keys));
	keys.resize(unique(all(keys))-keys.begin());
	values = vector<ll>(sz(keys),0); //valores iniciados zerados
}

ll &operator[](ll key){
	//assert(binary_search(all(keys),key));
	int id = lower_bound(all(keys),key)-keys.begin();
	return values[id];
}
}; //end mymap
*/

const int N = 2e3+10;
vector<ll> divisores[N];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n; cin >> n;
	vector<ll> v(n); fr(i,n) cin >> v[i];
	sort(all(v));
	v.resize(unique(all(v))-v.begin());
	
	fr(i,n){
		for(ll d = 1; d*d<=v[i]; d++){
			if(v[i]%d==0){
				divisores[i].push_back(d);
				if(d!=v[i]/d) divisores[i].push_back(v[i]/d);
			}
		}
	}
	vector<ll> chaves;
	fr(i,n) for(auto &d : divisores[i]) chaves.push_back(d);
	
	mymap<ll,ll> mp(chaves);
	
	fr(i,n) for(auto &d : divisores[i]) mp[d] = gcd(mp[d],v[i]);
	
	int ans = 0;
	for(auto &d : mp.keys) if(mp[d]==d and d<=v[0]) ans++;
	cout << ans << "\n";
}
