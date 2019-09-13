#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
typedef pair<int,int> pii;
#define fi first
#define se second

const int N = 1e6+10;
int v[N], z[N];

/*
	z[i] eh a maior substring de s comecando em i
	que coincide com o prefixo de msm tamaho de s
	
	[l,r] eh o range/bloco que conheco da string
	tal que ateh entao era o range de maior r que continha
	i e dava match (era igual ao prefixo da string)
	l<=i sempre com ctz
	r pode ser maior ou menor, caso em que devo atualizar r
	
	se i<=r, caso em que i esta dentro do bloco, ja sei
	um candidato minimo para z[i], que eh min(r-i+1,z[i-l]);
	(pego o minimo para nao passar do proprio bloco [l,r],
	pois valor ja calculado do prefixo z[i-l] pode passar, mas nao
	da pra dar match depois de r, sei que, na vdd, para de dar
	match em depois r)
	
	Em seguida atualizo z[i] brutamente (ateh parar de dar match)
	E atualizo o bloco l,r
	
*/

void makez(int n){
	int l = 0, r = 0;
	for(int i = 1; i<n; i++){
		if(i<=r) z[i] = min(r-i+1,z[i-l]);
		while(i+z[i]<n and v[z[i]]==v[i+z[i]]) z[i]++;
		if(i+z[i]-1>r){
			l=i;
			r=i+z[i]-1;
		}
	}
}

//solves problem I from https://codeforces.com/gym/101667/standings/friends/true

pii best(pii a, pii b){
	if(a.fi+a.se==b.fi+b.se){
		if(b.se<a.se) swap(a,b);
	} else if(b.fi+b.se<a.fi+a.se) swap(a,b);
	return a;
}

int main(){
	int n;
	cin >> n;
	
	fr(i,n) scanf("%d", v+i);
	
	reverse(v,v+n);
	
	makez(n);
	
	pii ans(0,n);
	
	for(int p = 1; p<=n; p++){
		int d = p;
		while(d<n and z[d]>=p) d+=p;
		if(d<n) d+=z[d];
		int k = n-d;	
		ans = best(ans,pii(k,p));		
	}
	
	printf("%d %d\n", ans.fi, ans.se);
}
