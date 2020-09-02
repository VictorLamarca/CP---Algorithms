#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
typedef long long ll;

//solves problem E from: https://codeforces.com/gym/100625/standings/friends/true

ll MOD;

struct mynum{
	ll a = 0, b = 0;
	mynum(){};
	mynum(ll aa, ll bb){
		a = aa, b = bb;
	}
};

mynum soma(mynum a, mynum b){
	return mynum((a.a+b.a)%MOD,(a.b+b.b)%MOD);
}

mynum mult(mynum a, mynum b){
	if(b.b==0) swap(a,b);
	assert(a.b==0);
	return mynum(a.a*b.a,a.a*b.b);
}

vector<vector<mynum>> mm(vector<vector<mynum>> a, vector<vector<mynum>> b){
	int l = sz(a);
	int c = sz(b[0]);
	assert(sz(a[0])==sz(b));
	
	vector<vector<mynum>> ans(l,vector<mynum>(c));
	
	fr(i,l){
		fr(j,c){
			mynum tot(0,0);
			fr(k,a[0].size()){
				tot = soma(tot,mult(a[i][k],b[k][j]));
			}
			ans[i][j] = tot;
		}
	}
	
	return ans;
}

//Qnd elevo a zero preciso codar matriz identidade!
vector<vector<mynum>> ident(int n){
	vector<vector<mynum>> ans(n,vector<mynum>(n));
	
	fr(i,n) ans[i][i].a = 1;
	
	return ans;
}

vector<vector<mynum>> em(vector<vector<mynum>> a, ll exp){
	if(exp==0) return ident(a.size());
	if(exp==1) return a;
	vector<vector<mynum>> mid = em(a,exp/2);
	if(exp%2) return mm(mm(mid,mid),a);
	return mm(mid,mid);
}

ll fp(ll base, ll exp){
	if(exp==0) return 1;
	if(exp==1) return base;
	
	ll mid = fp(base, exp/2);
	
	if(exp%2) return mid*mid%MOD*base%MOD;
	return mid*mid%MOD;
}

int main(){
	int ttt;
	cin >> ttt;
	
	fr(tt,ttt){
		scanf("%lld", &MOD);
		
		vector<vector<mynum>> fn[2];
		
		fr(x,2){
			ll a[2], b[2], c[2], k[2], n[2];
			scanf("%lld%lld%lld%lld%lld", &a[x], &b[x], &c[x], &k[x], &n[x]);
			
			vector<vector<mynum>> f1, t;
			
			f1 = {{mynum(a[x],0),mynum(b[x],0),mynum(c[x],0),mynum(0,1)}};
			
			//Para escrever matriz T nesse formato, saber que eh igual ao que se le sim!
			t = {
					{mynum(0,0),mynum(k[x],0),mynum(1,0),mynum(0,0)},
					{mynum(1,0),mynum(0,0),mynum(k[x],0),mynum(0,0)},
					{mynum(1,0),mynum(0,0),mynum(0,0),mynum(1,0)},
					{mynum(0,0),mynum(1,0),mynum(0,0),mynum(0,0)}
				};
				
			// <fn linha> = <f1 linha>*T
			
			//vetores base e resposta sao em linhas, mas os coefs em T sao em colunas!!
			//
			// <an,bn,cn> = <a1,b1,c1>*(coefa coefb coefc)
			//                         (coefa coefb coefc)
			//						   (coefa coefb coefc)
				
			fn[x] = mm(f1,em(t,n[x]-1));
		}
		
		ll x;
		scanf("%lld", &x);
		
		if(fn[0][0][0].b==0 and fn[1][0][0].b!=0) puts("UNKNOWN");
		else if(fn[0][0][0].b==0 and fn[1][0][0].b==0){
			ll y = fn[1][0][0].a;
			printf("%lld\n", y);
		} else{
			ll h0 =  (x-fn[0][0][0].a+MOD)%MOD*fp(fn[0][0][0].b,MOD-2)%MOD;
			ll y = (fn[1][0][0].a+h0*fn[1][0][0].b)%MOD;
			printf("%lld\n", y);
		}
	}
	
}
