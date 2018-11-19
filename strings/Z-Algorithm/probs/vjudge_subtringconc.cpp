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

//https://vjudge.net/contest/236668#problem/B

const int N = 1e6+10;

int Z[N];

string s;

int vago[N];

int n, m;

vector<int> pos;

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
	cin >> n >> m;
	cin >> s;
	fr(i,m){
		int x;
		scanf("%d", &x);
		x--;
		pos.pb(x);
	}
	
	makez();
	
	int tam = s.size();
	
	fr(i,m){
		if(i==0){
			int id = pos[i];
			fr(cnt,tam) vago[id++] = 1;
		} else{
			if(pos[i]>pos[i-1]+tam-1){
				int id = pos[i];
				fr(cnt,tam) vago[id++] = 1;
			} else{
				int offset = pos[i]-pos[i-1];
				if(Z[offset]<min(n-pos[i],tam-offset)){
					cout << 0 << endl;
					return 0;
				} else{
					int id = pos[i-1]+tam;
					while(id<n and id<pos[i]+tam) vago[id++] = 1;
				} 
			}
		}
	}
	
	ll ans = 1;
	fr(i,n) if(!vago[i]) ans = (ans*26)%MOD;
	
	cout << ans << endl;
	
	return 0;
}

