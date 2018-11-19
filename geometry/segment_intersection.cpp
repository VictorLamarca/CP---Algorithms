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

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LLONG_MAX
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

const int N = -1;

struct pt{
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

//checa se ponto esta dentro do segmento
bool inptseg(pt a1, pt b1, pt b2){
	pt v1 = (a1-b1), v2 = (b2-b1);
	if(v1^v2) return 0;
	v1 = b1-a1, v2 = b2-a1;
	return (v1*v2)<=0;
}

//checa se segmentos intersectam (bordas inclusas)
bool seg_intersect(pt a1, pt a2, pt b1, pt b2){
	fr(i,2){
	    fr(j,2){
	        if(inptseg(a1,b1,b2)) return 1;
	        swap(a1,a2);
	    }
	    swap(a1,b1);
	    swap(a2,b2);
	}
	
    fr(cor,2){
        //o resultado eh inteiro, entao nao preciso me preocupar com precisão, apenas overflow
        pt v1 = (a1-b1), v2 = (a2-b1), vs = (b2-b1);
        if( 1.0l*(v1^vs)*(v2^vs) >= -0.5 ) return 0;
        swap(a1,b1), swap(a2,b2);
    }
	
	return 1;
}

int main(){
	//FILE_IN FILE_OUT
	
	//segmentos a1-a2 e b1-b2;
	
	pt a1(-1,-1), a2(1,1), b1(-1,1), b2(1,-1);
	
	prin(seg_intersect(a1,a2,b1,b2));
	
	return 0;
}

