#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
typedef long long ll;
#define rmin(a,b) a = min<ll>(a,b)

//solves https://atcoder.jp/contests/abc193/tasks/abc193_e

ll div(ll a, ll b, bool ceil){
	ll ans = abs(a/b);
	bool pos = (a<0)==(b<0);
	if(a%b and ceil==pos) ans++;
	if(!pos) ans*=-1;
	return ans;
}

ll gcd_ext(ll a, ll b, ll &xo, ll &yo){
	if(b==0){
		xo = 1, yo = 0;
		return a;
	}
	ll x1, y1;
	ll g = gcd_ext(b,a%b,x1,y1);
	xo = y1;
	yo = x1-(a/b)*y1;
	return g;
}

/*
Retorna qual o menor x positivo que satisfaz
a*x + b*y = c (obviamente o y correspondente eh negativo)
(ou -1 se nao existe)

Util em CRT para achar menor r positivo que
	r = ra (mod a)
	r = rb (mod b)
	->
	a*x-b*y = rb-ra
	r = a*x + ra
*/
ll qual_sol(ll a, ll b, ll c){
	ll xo, yo;
	ll g = gcd_ext(a,b,xo,yo);
	if(c%g!=0) return -1;
	c/=g, a/=g,b/=g;
	xo*=c,yo*=c;
	
	ll k = div(-xo,b,b>0);
	
	return xo+k*b;
}

/*
	Return minimun r such that:
		r = ra (mod a)
		r = rb (mod b)
	Or -1 if no such r
*/
ll solve_crt(ll ra, ll a, ll rb, ll b){
	ll minx = qual_sol(a,-b,rb-ra);
	if(minx==-1) return minx;
	return a*minx+ra;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll t; cin >> t;
	fr(tt,t){
		ll X, Y, P, Q; cin >> X >> Y >> P >> Q;
		
		ll t1 = P+Q, t2 = 2*X+2*Y;
		ll ans = LLONG_MAX;
		fr(i,Q) fr(j,Y){
			ll cand = solve_crt(P+i,t1,X+j,t2);
			if(cand!=-1) rmin(ans,cand);
		}
		if(ans<LLONG_MAX){
			cout << ans << "\n";
		} else{
			cout << "infinity\n";
		}
	}
}
