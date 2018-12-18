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

vector<pt> v;

vector<pt> mch(vector<pt> v){
	// precisa definir operador < e == para unique
	sort(all(v));
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

int main(){
	//FILE_IN FILE_OUT
	int n;
	cin >> n;
	fr(i,n){
		pt p;
		scanf("%lld%lld", &p.x, &p.y);
		p.id = i+1;
		v.pb(p);
	}	
	
	vector<pt> ch = mch(v);
	
	long double per = 0;
	
	fr(i,ch.size()){
		per+= (ch[(i+1)%ch.size()]-ch[i]).mod();
	}
	
	ll area = 0;
	
	frr(i,1,ch.size()-2){
		pt v1 = ch[i+1]-ch[0];
		pt v2 = ch[i]-ch[0];
		area+= abs(v1^v2);
	}
	
	printf("%lu\n", ch.size());
	fr(i,ch.size()){
		printf("%d%c", ch[i].id, " \n"[i==ch.size()-1]);
	}
	printf("%.10lf\n",(double)(per));
	printf("%lld", area/2);
	if(area%2) printf(".5");
	printf("\n");
	
	return 0;
}

