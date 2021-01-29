#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())

typedef long long ll;

/*
	Seg com lazy generica
		-Um lazy marcado (nao nulo) significa que o nó atual foi atualizado,
		mas seus filhos ainda nao
		-No geral mudar
			-Parametros do node
			-Valor default (nulo)
			-Oper
			-updlazy
*/

struct node{
	ll val = 0, lazy = 0; //valores default usados para node nulo
	int l = -1, r = -1; 
	node(){}
	node(ll valb, int lb, int rb){
		val = valb;
		l = lb, r = rb;
		lazy = 0;
	}
	
};

node oper(node n1, node n2){
	return node(n1.val+n2.val,n1.l,n2.r);
}

struct Seg{
int n;
vector<node> s;
vector<ll> v;

void updlazy(int no, ll x){
	//Lazy do pai subscreve ou incrementa o do filho 
	//a nao ser q o do pai seja nulo (ja passou)
	if(x==0) return; //boa pratica, mas soh necessario se upd for de atualizar, nao incrementar
	s[no].val += (s[no].r-s[no].l)*x;
	s[no].lazy += x;
}
//----------------MUDAR ACIMA DISSO (GERALMNT)----------------------

void build(int no, int l, int r){
    if(r-l==1){
        s[no] = node(v[l],l,r); //mudar inicializacao a partir de v tmbm
        return;
    }
    int mid = (r+l)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = oper(s[2*no],s[2*no+1]);
}

Seg(vector<ll> _v){
	v = _v;
	n = sz(v);
	s = vector<node>(4*n);
	build(1,0,n);
}

void pass(int no){
    updlazy(2*no,s[no].lazy);
    updlazy(2*no+1,s[no].lazy);
    s[no].lazy = 0;
}

void upd(int lup, int rup, ll x, int no = 1){
    if(rup<=s[no].l or s[no].r<=lup) return;
    if(lup<=s[no].l and s[no].r<=rup){
        updlazy(no,x);
        return;
    }   
    pass(no);
    upd(lup,rup,x,2*no);
    upd(lup,rup,x,2*no+1);
    s[no] = oper(s[2*no],s[2*no+1]);
}

node qry(int lq, int rq, int no = 1){
    if(rq<=s[no].l or s[no].r<=lq) return node(); //potencialmente mudar elemento nulo
    if(lq<=s[no].l and s[no].r<=rq){
        return s[no];
    } 
    pass(no);
    return oper(qry(lq,rq,2*no), qry(lq,rq,2*no+1));
}
};

//Seg soma solves: https://www.spoj.com/problems/HORRIBLE/
//Seg set range solves: https://codeforces.com/contest/1477/submission/105805925
//Seg max solves: https://codeforces.com/gym/102307/submission/105809475
//exemplo seg generica (nao testado): https://codeforces.com/gym/102307/submission/77331716
//Solves seg flip range (nao testado): https://codeforces.com/contest/877/problem/E

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	fr(tt,t){
		int n, q; cin >> n >> q;
		Seg seg((vector<ll>(n)));
		fr(qq,q){
			int tipo; cin >> tipo;
			if(tipo==0){
				int l, r, x; cin >> l >> r >> x; l--;
				seg.upd(l,r,x);
			} else {
				int l, r; cin >> l >> r; l--;
				cout << seg.qry(l,r).val << "\n";
			}	
		}
	}
}
