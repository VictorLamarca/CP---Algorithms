#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define fr(i,n) for(int i = 0; i<n; i++)

//--------------------------------------
//No geral, mudar oq esta enter os --- (ateh upd lazy), mas sempre ha excessoes
//Ver build em inicializacao de s[] a partir de v[] tmbm
struct node{
	ll val = 0, lazy;
	int l, r; // (l,r) no node da propria seg permite que nao precise ter (l,r) nos parametros das funcoes
	node(){}
	node(ll valb, int lb, int rb){
		val = valb;
		l = lb, r = rb;
		//no.lazy esta setado quer dizer que os filhos nao tiveram a propagacao, mas o no.val esta correto!
		//lazy inicial eh sempre nulo, nunca somo dois pra dar o pai se o pai tiver com lazy, se estou somando, eh pq o lazy do pai foi propagado
		lazy = 0;
	}
	
};

node soma_update(node &n1, node &n2){
	return node(n1.val+n2.val,n1.l,n2.r);
}

ll soma_query(ll v1, ll v2){
	return v1+v2;
}

ll nulo(){ //para qnd for fora do intervalo, infinito em lazy de minimo
	return 0;
}

struct Seg{
int n;
ll *v;
node *s;

void updlazy(int no, ll x){
	s[no].val += (s[no].r-s[no].l)*x;
	s[no].lazy += x;
}
//--------------------------------------

void build(int no, int l, int r){
    if(r-l==1){
        s[no] = node(v[l],l,r); //mudar inicializacao a partir de v tmbm
        return;
    }
    int mid = (r+l)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = soma_update(s[2*no],s[2*no+1]);
}

Seg(ll *vb, node *sb, int nb){
	v = vb, s = sb;
	n = nb;
	fr(i,4*n){
        s[i].lazy = 0;
    }
	build(1,0,n);
}

void pass(int no){
    updlazy(2*no,s[no].lazy);
    updlazy(2*no+1,s[no].lazy);
    s[no].lazy = 0;
}

void upd(ll x, int lup, int rup, int no = 1){
    if(rup<=s[no].l or s[no].r<=lup) return;
    if(lup<=s[no].l and s[no].r<=rup){
        updlazy(no,x);
        return;
    }   
    pass(no);
    upd(x,lup,rup,2*no);
    upd(x,lup,rup,2*no+1);
    s[no] = soma_update(s[2*no],s[2*no+1]);
}

ll qry(int lq, int rq, int no = 1){
    if(rq<=s[no].l or s[no].r<=lq) return nulo();
    if(lq<=s[no].l and s[no].r<=rq){
        return s[no].val; //verificar aqui tmbm
    } 
    pass(no);
    return soma_query(qry(lq,rq,2*no), qry(lq,rq,2*no+1));
}
};

//exemplo seg generica: https://codeforces.com/gym/102307/submission/77331716
//Seg soma solves: https://www.spoj.com/problems/HORRIBLE/
//Seg max solves: https://codeforces.com/gym/102307/problem/E

const int N = 1e5+10;

ll v[N];
node s[4*N];

int main(){
    int t;
    cin >> t;
    
    int n, q;
    fr(tt,t){
        scanf("%d%d", &n, &q);
        Seg seg(v,s,n);
        fr(qq,q){
            int c;
            scanf("%d", &c);
            if(c==0){
                int l, r, x;
                scanf("%d%d%d", &l, &r, &x);
                l--;
                seg.upd(x,l,r);
            } else{
                int l, r;
                scanf("%d%d", &l, &r);
                l--;
                printf("%lld\n", seg.qry(l,r));
            }
        }
    }
	return 0;
}

