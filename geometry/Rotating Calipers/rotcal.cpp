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

class pt{
public:
	ll x, y;
	int id;
	pt(){}
	pt(ll a, ll b){
		x = a, y = b;
	}
	
	pt operator -(pt p2){
		return pt(x-p2.x,y-p2.y);
	}
	
	ll operator ^(pt p2){
		return x*p2.y-y*p2.x;
	}
	
	long double mod(){
		return sqrt((long double)(x*x+y*y));
	}
	
	bool operator <(pt p2){
		return pll(x,y)<pll(p2.x,p2.y);
	}
	
	bool operator ==(pt p2){
		return x==p2.x and y==p2.y;
	}
};

vector<pt> mch(vector<pt> v){
	// precisa definir operador < para sort e == para unique
	sort(v.begin(),v.end());
	v.resize(unique(all(v))-v.begin());
	
	vector<pt> uh, lh;
	
	for(int i = v.size()-1;i>=0;i--){
		while(uh.size()>=2 and ((uh.back()-uh[uh.size()-2])^(v[i]-uh.back()))<=0){
			uh.pop_back();
		}
		uh.pb(v[i]);
	}
	
	fr(i,v.size()){
		while(lh.size()>=2 and ((lh.back()-lh[lh.size()-2])^(v[i]-lh.back()))<=0){
			lh.pop_back();
		}
		lh.pb(v[i]);
	}
	
	vector<pt> ch;
	fr(i,uh.size()-1) ch.pb(uh[i]);
	fr(i,lh.size()-1) ch.pb(lh[i]);
	
	return ch;
}

vector<pt> v, ch;
int n, r;

double dist(pt p, pt a, pt b){
	pt vb = (b-a);
	pt vd = (p-a);
	double area = abs(vb^vd);
	area/=vb.mod();
	return area;
}

int main(){
	//FILE_IN FILE_OUT
	cin >> n >> r;
	fr(i,n){
		pt pp;
		scanf("%lld%lld", &pp.x, &pp.y);
		v.pb(pp);
	}
	
	ch = mch(v);
	
	n = ch.size();
	
	double ans = INT_MAX;
	
	int curp = 1;
	
	fr(i,n){
		int pid = (i+1)%n;
		//pt v = ch[pid]-ch[i];
		int nid = (curp+1)%n;
		while(dist(ch[curp],ch[i],ch[(i+1)%n])<dist(ch[(curp+1)%n],ch[i],ch[(i+1)%n])){
			curp = (curp+1)%n;
		}
		ans = min(ans,dist(ch[curp],ch[i],ch[(i+1)%n]));
	}
	
	printf("%.10lf\n", ans);
	
	return 0;
}

