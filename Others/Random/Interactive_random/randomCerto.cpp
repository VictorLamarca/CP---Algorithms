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


//RAND_MAX eh no minimo 32 000 (que eh 2^15)
//para gerar ateh 10^9 basta concatenar dois rands()
//para gerar ateh 10^18 basta concatenar numeros 4*4 digitos + 2 digitos
ll grand(){
	return ((rand()%(1<<15))<<15) + rand()%(1<<15);
	/*
	ll cur = 0;
	fr(i,4) cur = (cur<<15)+rand()%(1<<15);
	//fr(i,4) cur = cur*10000+rand()%10000; cur = cur*100 + rand()%100;
	return cur;
	*/
}

int main(){
	//FILE_IN FILE_OUT
	
	srand(time(0));
	
	//para gerar 1e7 numeros dessa maneira demora 650ms
	fr(i,1e7){
		int x = grand()%100000;
	}
	
	return 0;
}

