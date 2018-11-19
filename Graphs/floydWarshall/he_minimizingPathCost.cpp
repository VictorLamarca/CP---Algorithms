#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<(n);i++)
#define frr(i,a,b) for(int i=(a);i<=(b);i++)
#define frrs(i,a,b) for(int i=(a);i>=(b);i--)
#define VAR(a,b) __typeof(b) a=b
#define frit(it,c) for(VAR(it,(c).begin());it!=(c).end();it++)

typedef long long ll;
typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;

#define PI acos(-1)
#define MOD 1000000007

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define prinsep if(debug) cout << "------" << endl;
#define cendl if(debug) cout << endl

const int N = 1e2+10;
ll g[N][N];

map<string,int> ma;

int main(){
	int n, m;
	
	scanf("%d%d", &n, &m);
	
	fr(i,n){
		fr(j,n){
			g[i][j] = LLONG_MAX/3;
		}
	}
	
	fr(i,n){
		string s;
		cin >> s;
		ma[s] = i;
	}
	
	fr(i,m){
		string a, b;
		int d;
		cin >> a >> b >> d;
		//prin(d);
		if(a!=b){
			g[ma[a]][ma[b]] = d;
			g[ma[b]][ma[a]] = d;
		}
		
	}
	
	fr(i,n) g[i][i] = 0;
	
	int q;
	scanf("%d", &q);
	
	fr(k,n){
		fr(i,n){
			fr(j,n){
				g[i][j] = min(g[i][j], g[i][k]+g[k][j]);
			}
		}
	}	
	
	fr(i,q){
		string a, b;
		
		cin >> a >> b;
		
		printf("%lld\n", g[ma[a]][ma[b]]);
	}
	
	return 0;
}

