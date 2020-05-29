#include <bits/stdc++.h>
using namespace std;
 
#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()
typedef long long ll;
 
//Convex hull trick de maximo
// solves https://codeforces.com/contest/1083/problem/E
 
struct Line{
	//reta da forma y=x*m+k
	// p eh onde a reta para, onde deixa de ser a maxima
	mutable ll m,k,p;
	// lembrar de fazer funcao const
	bool operator <(const Line &o) const { return m<o.m;}
	bool operator <(ll x) const { return p<x;}
};
 
//less<> eh pra deixar container trasnparente e ter 2 tipos de comparador pro multiset
struct Cht : multiset<Line,less<>> {
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b){
		return a/b - ( (a^b)<0 and a%b);
	}
	//retas x e y tem inclinacoes vizinhas no container, mx <= my. Seta-se o valor de p de x, ou seja, onde intersecta com y, e retorna true se a reta x esta acima de y inteiramente no intervalo em q y era a maxima, ou seja, y deve ser apagada
	bool bad2(iterator x, iterator y){
		if(y==end()){
			x->p = inf;
			return 0;
		}
		//se tem inclinacao igual e o x eh pior, marco ele como -inf, assim, msm q x continue no set, ele nao funciona pra ngm cujo x>=-inf, ou seja, nenhum x msm!
		if(x->m==y->m) x->p = (x->k>y->k)? inf : -inf;
		else x->p = div(x->k-y->k, y->m-x->m);
		return x->p>=y->p;
	}	
	//tenta adicionar a reta y=m*x+k ao CHTmaximo e o ajusto caso necessario
	void add(ll m, ll k){
		//nao da pra usar emplace(m,k,0) pois nao define construtor para Line
		auto z = insert({m,k,0}), y = z++, x = y;
		while(bad2(y,z)) z = erase(z);
		if(x!=begin() and bad2(--x,y)) bad2(x,erase(y));  //no original se usa y=erase(y), mas nao precisa pois y sera redefinido na proxima linha msm
		while((y=x)!=begin() and (--x)->p >= y->p) bad2(x,erase(y));
	}
	//retorna o valor do qual do convex hull de maximo na coordenada x
	ll query(ll x){
		assert(!empty());
	    auto l = *lower_bound(x);
		return x*l.m + l.k;
	}
};
 
int main(){
	ll n;
	cin >> n;
	
	vector<tuple<ll,ll,ll>> v;
	fr(i,n){
		ll x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		v.emplace_back(x,y,z);
	}
	
	sort(all(v));
	
	Cht cht;
	
	ll ans = 0;
	
	cht.add(0,0);
	for(auto &tup : v){
		ll x, y, a;
		tie(x,y,a) = tup;
		ll dp = cht.query(y) + x*y - a;
		ans = max(ans,dp);
		cht.add(-x,dp);
	}
	
	cout << ans << endl;
}
