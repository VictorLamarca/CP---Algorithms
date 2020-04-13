#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v).size()
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

// solves https://codeforces.com/problemsets/acmsguru/problem/99999/106

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

ll qnt_sol(ll a, ll b, ll c, ll xl, ll xr, ll yl, ll yr){
	ll xo, yo;
	ll g = gcd_ext(a,b,xo,yo);
	if(c%g!=0) return 0;
	c/=g, a/=g,b/=g;
	xo*=c,yo*=c;
	ll kmin, kmax;
	
	if(b<0) xo*=-1, b*=-1, xl*=-1, xr*=-1, swap(xl,xr);
	a*=-1; // a assumindo o sinal do y = yo - k*a para virar y = yo + k*a
	if(a<0) yo*=-1, a*=-1, yl*=-1, yr*=-1, swap(yl,yr);
	
	kmin = div(xl-xo,b,1);
	kmax = div(xr-xo,b,0);
	
	kmin = max(kmin,div(yl-yo,a,1));
	kmax = min(kmax,div(yr-yo,a,0));
	
	if(kmin>kmax) return 0;
	return kmax-kmin+1;
}

ll seb0(ll a, ll b, ll c, ll x1, ll x2, ll y1, ll y2){
	if(c%a) return 0;
	c/=a;
	if(c<x1 or c>x2) return 0;
	return y2-y1+1;
}

int main(){
	ll a, b, c;
	ll x1,x2,y1,y2;
	scanf("%lld%lld%lld", &a, &b, &c);
	scanf("%lld%lld", &x1,&x2);
	scanf("%lld%lld", &y1,&y2);
	if(a==0 and b==0){
		ll ans;
		if(c==0) ans = (x2-x1+1)*(y2-y1+1);
		else ans = 0;
		printf("%lld\n", ans);
		return 0;
	} else if(a==0){
		printf("%lld\n", seb0(b,a,c,y1,y2,x1,x2));
	} else if(b==0){
		printf("%lld\n", seb0(a,b,c,x1,x2,y1,y2));
	}
	
	cout << qnt_sol(a,b,-c,x1,x2,y1,y2) << endl;
}
