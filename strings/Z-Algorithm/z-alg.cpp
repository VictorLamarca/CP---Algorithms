#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;

#define pb push_back

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LLONG_MAX
//-DBL_MAX
//__builtin_popcountll(ll x) - __builtin_popcount(int x)

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define print(tup) if(debug) cout << #tup << " = {" << get(tup,0) << ", " << get(tup,1) << ", " << get(tup,2) << "}\n"
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

const int N = 1e6+10;

int Z[N];
string s;

void makez(){
	int l, r;
	l = r = 0;
	
	int n = s.size();
	
	fr(i,n){
		if(!i) continue;
		if(i>r){
			l = r = i;
			while(r<n and s[r]==s[r-l]) r++;
			Z[i] = r-l;
			r--;
		} else{
			int k = i-l;
			if(Z[k]+i-1<=r) Z[i] = Z[k];
			else{
				l = i;
				while(r<n and s[r]==s[r-l]) r++;
				Z[i] = r-l;
				r--;
			}
		}
	}
	
	return;
}

int main(){
	//FILE_IN FILE_OUT
	cin >> s;
	
	makez();
	
	fr(i,s.size()){
		cout << Z[i] << " ";
	}	
	cout << endl;
	
	return 0;
}

