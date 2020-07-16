#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
typedef long long ll;

//solves https://judge.yosupo.jp/problem/point_add_range_sum

template<class T> struct Seg{
	int n;
	vector<T> s;
	
void build(){
	for(int i = n-1;i>0;i--){ 
		//s[i] = min(s[i<<1],s[i<<1|1]);
		s[i] = s[i<<1]+s[i<<1|1];
	}
}

Seg(vector<T> v){
	n = sz(v);
	s = vector<T>(2*n);
	for(int i = n; i<2*n; i++) s[i] = v[i-n];
	build();
}

//pos 0-indexed (incrementa, nao atualiza)
void upd(int pos, ll val){
	for(s[pos+=n]+=val;pos>1;pos>>=1) 
		//s[pos>>1] = min(s[pos],s[pos^1]);
		s[pos>>1] = s[pos]+s[pos^1];
}

//array é abstraido para 0-indexed (nas folhas da seg) e [l,r)
T qry(int l, int r){
	T ans = T(0);
	//T ans = T(LLONG_MAX);
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = ans+s[l++];
		if(r&1) ans = ans+s[--r];
		//if(l&1) ans = min(ans,s[l++]);
		//if(r&1) ans = min(ans,s[--r]);
	}
	return ans;
}
	
};

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, q; cin >> n >> q;
	vector<ll> v(n);
	fr(i,n) cin >> v[i];
	
	Seg<ll> seg(v);
	
	fr(qq,q){
		int tipo; cin >> tipo;
		if(tipo==0){
			ll i, x; cin >> i >> x;
			seg.upd(i,x);
		} else{
			int l, r; cin >> l >> r;
			cout << seg.qry(l,r) << "\n";
		}
	}
}
