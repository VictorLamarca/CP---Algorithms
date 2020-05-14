#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(a) (int)(a.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

//solves https://codeforces.com/contest/982/problem/E

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

ll n, m, x, y, vx, vy;
void no(){
	puts("-1");
	exit(0);
}

int main(){
	cin >> n >> m >> x >> y >> vx >> vy;
	
	if(vx==0){
		if(x!=0 and x!=n) no();
		if(vy<0) y = 0;
		else y = m;
		cout << x << " " << y << endl;
		return 0;
	} 
	if(vy==0){
		if(y!=0 and y!=m) no();
		if(vx<0) x = 0;
		else x = n;
		cout << x << " " << y << endl;
		return 0;
	} 
	
	ll rn = x;
	if(vx>0) rn = n-x;
	ll rm = y;
	if(vy>0) rm = m-y;
	
	ll xo = qual_sol(n,-m,rm-rn);
	if(xo==-1) no();
	
	ll k = xo*n+rn;
	ll xf = x+vx*k;
	ll yf = y+vy*k;
	
	ll divx = xf/n;
	ll divy = yf/m;
	if(divx%2==0) n = 0;
	if(divy%2==0) m = 0;
	
	cout << n << " " << m << endl;
}
