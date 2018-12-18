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

const int N = 1e5+10;

/*  LEMBRAR
    Por capacidade como 2*N
    Em build faco atual = filhos (ponho vetor em [n,2*n-1] e faco de n-1 até 1
    Em Update mudo folha e faco pai = atual (while pos>1, ou seja tem pai)
    Em query passo por td (l+=n, r+=n) ate l<r
*/

//funciona para toda funcao comutativa iterativa, soma, min, max, xor, etc
ll seg[2*N]; //indices de [1,2*n-1], folhas (array) de [n,2*n-1]
ll n, nq;

void build(){
	for(int i = n-1;i>0;i--){ 
	//seg[i] = min(seg[i<<1],seg[i<<1|1]);
	seg[i] = seg[i<<1]+seg[i<<1|1];
	prin(i);
	prin(seg[i]);
	cendl;
	}
}

//pos 0-indexed
void up(int pos, ll val){
	for(seg[pos+=n]=val;pos>1;pos>>=1) seg[pos>>1] = min(seg[pos],seg[pos^1]);
}

//array é abstraido para 0-indexed (nas folhas da seg) e [l,r)
ll qr(int l, int r){
	ll ans = LLONG_MAX;
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = min(ans,seg[l++]);
		if(r&1) ans = min(ans,seg[--r]);
	}
	return ans;
}


int main(){
	//FILE_IN FILE_OUT
	
	cin >> n >> nq;
	
	fr(i,n) scanf("%lld", seg+i+n);
	build();
	
	prin(seg[2]);
	return 0;
	
	fr(i,nq){
		int t;
		scanf("%d", &t);
		if(t==0){ // qr
			int l, r;
			scanf("%d%d", &l, &r);
			l--;
			cout << qr(l,r) << endl;
		} else{
			int pos;
			ll val;
			scanf("%d%lld", &pos, &val);
			pos--;
			up(pos,val);
		}
	}
	
	return 0;
}

/*
6 9
3 7 -100 1 4 20
0 1 6
0 1 2
0 4 6
1 3 100
0 1 6
1 4 5
0 3 6
1 3 -1000
0 1 6 
*/

/* resp:
-100
3
1 
1 
4 
-1000
*/



