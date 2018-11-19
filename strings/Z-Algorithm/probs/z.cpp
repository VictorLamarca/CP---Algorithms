#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

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
typedef pair<ll,ll> pll;
typedef tuple<ll,ll,ll> t3ll;

#define mt make_tuple
#define get(a,id) get<id>(a)

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

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

const int N = 1;

vector<int> zf(string s){
	int l, r;
	l = r = 0;
	
	vector<int> z(s.size());
	
	prin(s);
	
	frr(i,1,s.size()-1){
		if(i>r){
			ppal(i<r);
			l = r = i;
			while(r<s.size() and s[r-l]==s[r]) r++;
			z[i] = r-l, r--;
		} else{
			ppal(i>=r);
			int k = i-l;
			prin(k);
			if(z[k]<r-i+1){ 
				z[i] = z[k]; 
				ppal(z[k]<r-i+1);
			}
			else{
				ppal(z[k]>=r-i+1);
				l = i;
				while(r<s.size() and s[r-l] == s[r]) r++;
				z[i] = r-l, r--;
			}
		}
		
		prin(i);
		prin(z[i]);
		prin(l);
		prin(r);
		cendl;
	}
	
	return z;
}

int main(){
	//FILE_IN FILE_OUT
	
	string s;
	
	cin >> s;
	
	vector<int> v = zf(s);
	
	fr(i,v.size()){
		printf("%d%c", v[i], " \n"[i==v.size()-1]);
	}
	
	return 0;
}

