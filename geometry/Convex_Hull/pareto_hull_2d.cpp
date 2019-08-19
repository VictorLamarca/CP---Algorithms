#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
typedef long long ll;

struct pt{
	ll x, y;
	pt(ll a, ll b){
		x = a, y = b;
	}
	//tem que ser assim se nao nao compila
	bool operator <(const pt& p) const{
		if(x==p.x) return y>p.y;
		return x<p.x;
	}
};

ll vet(pt p1, pt p2){
	return p1.x*p2.y-p1.y*p2.x;
}

pt menos(pt p1, pt p2){
	return pt(p1.x-p2.x,p1.y-p2.y);
}

/*
	Mantem um hull de maximo 2d
	(semelhante a pareto, mas ligo os pontos do pareto
	por uma reta e tiro quem esta no interior(+proximo a origem)
	
	Obs: tem que ser multiset
	(set eh mais chato pq tem uns criterios de igualdade
	e se for set nao compila)
*/
struct HullD : public multiset<pt>{
	bool bad(iterator b){
		auto c = next(b);
		if(c==end()) return 0;
		if(b==begin()) return b->x < c->x and b->y < c->y;
		auto a = prev(b);
		return vet(menos(*b,*a),menos(*c,*a))>0;
	}
	void insert(ll x, ll y){
		auto b = emplace(x,y);
		if(bad(b)){
			erase(b);
			return;
		}
		while(next(b)!=end() and bad(next(b))) erase(next(b));
		while(b!=begin() and bad(prev(b))) erase(prev(b));
	}	
};

//solves https://codeforces.com/gym/102302/problem/I

int main(){
	int n;
	cin >> n;
	
	HullD hd;
	
	fr(i,n){
		ll x, y;
		scanf("%lld%lld", &x, &y);
		
		hd.insert(x,y);
		
		printf("%d\n", i+1-(int)hd.size());
	}
}
