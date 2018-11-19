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
	pt(){}
	pt(ll xx, ll yy){
		x = xx, y = yy;
	}
	
	pt operator - (pt p2){
		return pt(x-p2.x,y-p2.y);
	}
	ll operator * (pt p2){
		return x*p2.x + y*p2.y;
	}
	
	ll operator ^(pt p2){
		return x*p2.y-y*p2.x;
	}
	
	long double mod(){
		return sqrt((long double)(x*x+y*y));
	}
};	

ll area(pt p1, pt p2){
	return abs(p1^p2);
}

long double dist(pt a, pt b, pt c, bool ray1, bool ray2){
	pt vbaseb = (c-b);
	pt vbasec = (b-c);
	pt vb = (a-b);
	pt vc = (a-c);
	
	if(!ray1 and (vb*vbaseb)<0){
		return sqrt((long double)(vb.x*vb.x+vb.y*vb.y));
	}
	if(!ray2 and (vc*vbasec)<0){
		return sqrt((long double)(vc.x*vc.x+vc.y*vc.y));
	}
	
	return area(vb,vbaseb)/(long double)vbaseb.mod();
	
}

bool in(long double x, long double y, pt a, pt b, bool raya, bool rayb){
	ll x1 = min(a.x,b.x);
	ll x2 = max(a.x,b.x);
	
	ll y1 = min(a.y,b.y);
	ll y2 = max(a.y,b.y);
	
	if(x>=x1 and x<=x2 and y>=y1 and y<=y2) return 1;
	
	long double dista = (x-a.x)*(x-a.x) + (y-a.y)*(y-a.y);
	long double distb = (x-b.x)*(x-b.x) + (y-b.y)*(y-b.y);
	
	if(dista<distb) return raya;
	return rayb;
}

long double distline(pt a, pt b, bool raya, bool rayb, pt c, pt d, bool rayc, bool rayd){
	long double mindist = min({dist(a,c,d,rayc,rayd),dist(b,c,d,rayc,rayd),dist(c,a,b,raya,rayb),dist(d,a,b,raya,rayb)});
	
	ll a1 = b.y-a.y;
	ll b1 = a.x-b.x;
	ll c1 = a1*a.x+b1*a.y;
	
	ll a2 = d.y-c.y;
	ll b2 = c.x-d.x;
	ll c2 = a2*c.x+b2*c.y;
	
	long double delta = a1*b2-b1*a2;
	
	if(delta){
		long double x = (c1*b2-c2*b1)/delta;
		long double y = (a1*c2-a2*c1)/delta;
		
		if(in(x,y,a,b,raya,rayb) and in(x,y,c,d,rayc,rayd)) return 0;
	} 
	
	return mindist;
}	

int main(){
	//FILE_IN FILE_OUT
	pt a, b, c, d;
	
	cin >> a.x >> a.y;	
	cin >> b.x >> b.y;
	cin >> c.x >> c.y;
	cin >> d.x >> d.y;
	
	//The distance from the point A to the point C.
	printf("%.10lf\n", (double)(a-c).mod());
	
	//The distance from the point A to the segment CD.
	printf("%.10lf\n", (double)dist(a,c,d,0,0));
	
	//The distance from the point A to the half-infinite ray CD.
	printf("%.10lf\n", (double)dist(a,c,d,0,1));
	
	//The distance from the point A to the line CD.
	printf("%.10lf\n", (double)dist(a,c,d,1,1));
	
	//The distance from the segment AB to the point C.
	printf("%.10lf\n", (double)dist(c,a,b,0,0));
	
	//The distance from the segment AB to the segment CD.
	printf("%.10lf\n", (double)distline(a,b,0,0,c,d,0,0));
	
	//The distance from the segment AB to the half-infinite ray CD.
	printf("%.10lf\n", (double)distline(a,b,0,0,c,d,0,1));
	
	//The distance from the segment AB to the line CD.
	printf("%.10lf\n", (double)distline(a,b,0,0,c,d,1,1));
	
	//The distance from the half-infinite ray AB to the point C.
	printf("%.10lf\n", (double)dist(c,a,b,0,1));
	
	//The distance from the half-infinite ray AB to the segment CD.
	printf("%.10lf\n", (double)distline(a,b,0,1,c,d,0,0));
	
	//The distance from the half-infinite ray AB to the half-infinite ray CD.
	printf("%.10lf\n", (double)distline(a,b,0,1,c,d,0,1));
	
	//The distance from the half-infinite ray AB to the line CD.
	printf("%.10lf\n", (double)distline(a,b,0,1,c,d,1,1));
	
	//The distance from the line AB to the point C.
	printf("%.10lf\n", (double)dist(c,a,b,1,1));
	
	//The distance from the line AB to the segment CD.
	printf("%.10lf\n", (double)distline(a,b,1,1,c,d,0,0));
	
	//The distance from the line AB to the half-infinite ray CD.
	printf("%.10lf\n", (double)distline(a,b,1,1,c,d,0,1));
	
	//The distance from the line AB to the line CD.
	printf("%.10lf\n", (double)distline(a,b,1,1,c,d,1,1));
	
	return 0;
}
