#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
typedef long long ll;

//solves https://old.yosupo.jp/problem/point_add_range_sum
//other submission: https://codeforces.com/gym/102441/submission/118017250

/*
	Seg de soma nessa implementacao, mas facil mudar em oper(a,b)
	
	Inicializaçao na main:
		pq preciso por node() no inicializador?
		Seg seg(vector<node>(n,node()));
*/

struct node{
	ll val;
	//ll id;
	//lembrar de redefinir valor default (para nulo na inicializacao)
	node(ll _val = 0) : val(_val) {}
};

node oper(node a, node b){
	return node(a.val+b.val);
}

struct Seg{
	int n;
	vector<node> s;
Seg(){}
void build(){
	for(int i = n-1;i>0;i--){ 
		s[i] = oper(s[i<<1],s[i<<1|1]);
	}
}
Seg(vector<node> v){
	n = sz(v);
	s = vector<node>(2*n);
	for(int i = n; i<2*n; i++) s[i] = v[i-n];
	build();
}
//pos 0-indexed (incrementa, nao atualiza)
void upd(int pos, node val){
	pos+=n;
	s[pos] = oper(s[pos],val);
	for(;pos>1;pos>>=1) 
		s[pos>>1] = oper(s[pos],s[pos^1]);
	//para atualizar:
	//for(s[pos+=n]=val;pos>1;pos>>=1) 
	//	s[pos>>1] = oper(s[pos],s[pos^1]);
}
//array é abstraido para 0-indexed (nas folhas da seg) e [l,r)
node qry(int l, int r){
	node ans;
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = oper(ans,s[l++]);
		if(r&1) ans = oper(ans,s[--r]);
	}
	return ans;
}
}; // end seg

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, q; cin >> n >> q;
	vector<node> v(n);
	fr(i,n) cin >> v[i].val;
	Seg seg(v);
	
	//build alternativo, precisa especificar node()
	//Seg seg(vector<node>(n,node()));
	
	fr(qq,q){
		int tipo; cin >> tipo;
		if(tipo==0){
			int p, x; cin >> p >> x;
			seg.upd(p,node(x));
		} else{
			int l, r; cin >> l >> r;
			cout << seg.qry(l,r).val << "\n";
		}
	}
}
/*
input:
5 5
1 2 3 4 5
1 0 5
1 2 4
0 3 10
1 0 5
1 0 3

output:
15
7
25
6
*/
