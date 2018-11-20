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

const int N = 1e5+10;

int seg[4*N];
int lazy[4*N];
int v[N];

int n;

//ii eh o id do no que diz respeito ao intervalo [il,ir) de v, 0-indexed, seg de soma
void build(int il = 0, int ir = n, int ii = 0){
	if(il+1==ir){
		seg[ii] = v[il];
		return;
	}
	
	int mid = (il+ir)/2;
	build(il,mid,2*ii+1);
	build(mid,ir,2*ii+2);
	
	seg[ii] = seg[2*ii+1] + seg[2*ii+2];
}

void upr(int ii, int il, int ir, int ul, int ur, int x){
	seg[ii] += (ir-il)*lazy[ii];
	if(il+1!=ir){
		lazy[2*ii+1]+=lazy[ii];
		lazy[2*ii+2]+=lazy[ii];
		lazy[ii] = 0;
	}
	
	if(il>=ur or ul>=ir) return;
	
	if(il>=ul and ir<=ur){
		seg[ii]+=x*(ir-il);
		if(il+1!=ir){
			lazy[2*ii+1]+=x;
			lazy[2*ii+2]+=x;
		}
		return;
	}
	int mid = (ir+il)/2;
	upr(2*ii+1,il,mid,ul,ur,x);
	upr(2*ii+2,mid,ir,ul,ur,x);
	
	seg[ii] = seg[2*ii+1]+seg[2*ii+2];
	return;
}

//
int getsum(int ii, int il, int ir, int ql, int qr){
	seg[ii] += (ir-il)*lazy[ii];
	if(il+1!=ir){
		lazy[2*ii+1]+=lazy[ii];
		lazy[2*ii+2]+=lazy[ii];
		lazy[ii] = 0;
	}
	
	if(il>=qr or ql>=ir) return 0;
	
	if(il>=ql and ir<=qr) return seg[ii];
	
	int mid = (ir+il)/2;
	
	return getsum(2*ii+1,il,mid,ql,qr) + getsum(2*ii+2,mid,ir,ql,qr);
}	

/*
input exemplo - adaptacao da seg desenhada no ggeks:
https://www.geeksforgeeks.org/lazy-propagation-in-segment-tree/
6
1 3 5 7 9 11
9
q 1 6
q 1 3
q 4 6
u 1 6 1
q 1 6
u 1 3 -2
q 1 6
q 1 3
q 4 6
*/

int main(){
	//FILE_IN FILE_OUT
	cin >> n;
	fr(i,n) scanf("%d",v+i);
	
	build();
	
	int q;
	cin >> q;
	fr(i,q){
		char c;
		scanf(" %c", &c);
		if(c=='q'){
			int l, r;
			scanf("%d%d", &l, &r);
			cout << "opt, l, r = " << c << " " << l << " " << r << endl;
			l--,r--;
			prin(getsum(0,0,n,l,r+1));
		} else{
			int x, l, r;
			scanf("%d%d%d", &l, &r, &x);
			cout << "opt, l, r, x = " << c << " " << l << " " << r << " " << x << endl;
			l--,r--;
			upr(0,0,n,l,r+1,x);
		}
		cendl;
	}
	
	return 0;
}

