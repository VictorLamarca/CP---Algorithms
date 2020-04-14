#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define fr(i,n) for(int i = 0; i<n; i++)

/* 
	Seg lazy de soma
	para ser de minimo descomente linhas comentadas
	
    Lembrar de 4*N no tamanho da seg e lazy
    
    Nós da seg [1,4*N-1], e nós do vetor [0,n-1]
    
    intervalos abertos [l,r) para fazer query e update!
*/

//se em um vector<Seg> precisar de tamanho variavel por seg
//da pra fazer if(r==-1) r = tam[id] onde id eh um tam global
//ou fazer = um nglobal e mudar o n global td vez q for usar
//alem disso, usar vector, pois eh variavel
template<int N> struct Seg{

ll *v, *s, *lazy;

void build(int no = 1, int l = 0, int r = N){
    if(r-l==1){
        s[no] = v[l];
        return;
    }
    int mid = (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = s[2*no]+s[2*no+1];
    //s[no] = max(s[2*no],s[2*no+1]);
}

Seg(ll *vb, ll *sb, ll *lazyb){
	v = vb, s = sb, lazy = lazyb;
	//apenas o v precisa estar correto q o s sera buildado
	//ja o lazy preciso lembrar de resetar
	fr(i,4*N){
        lazy[i] = 0;
    }
	build();
}

//seto lazy no nó (marco que filhos não foram propagados)
//mas s[no] esta correto
void updlazy(int no, int l, int r, ll x){
    s[no] += (r-l)*x;
    //s[no] += x;
    lazy[no] += x;
}

//propago lazy do no
void pass(int no, int l, int r){
    int mid = (l+r)/2;
    updlazy(2*no,l,mid,lazy[no]);
    updlazy(2*no+1,mid,r,lazy[no]);
    lazy[no] = 0;
}

void upd(ll x, int lup, int rup, int no = 1, int l = 0, int r = N){
    if(rup<=l or r<=lup) return;
    if(lup<=l and r<=rup){
        updlazy(no,l,r,x);
        return;
    }   
    pass(no,l,r); //devo passar lazy do nó que estou pois analisarei filhos
    int mid = (l+r)/2;
    upd(x,lup,rup,2*no,l,mid);
    upd(x,lup,rup,2*no+1,mid,r);
    s[no] = s[2*no] + s[2*no+1];
    //s[no] = max(s[2*no],s[2*no+1]);
}

ll query(int lq, int rq, int no = 1, int l = 0, int r = N){
    if(rq<=l or r<=lq) return 0; //mudar return se for de minimo
    if(lq<=l and r<=rq){
        return s[no];
    } 
    pass(no,l,r);
    int mid = (l+r)/2;
    return query(lq,rq,2*no,l,mid) + query(lq,rq,2*no+1,mid,r);
    //return max(query(lq,rq,2*no,l,mid),query(lq,rq,2*no+1,mid,r));
}
};

const int N = 1e5+10;

//v[id] nao estara atualizado, para recuperalo preciso passar o s[no] com no referente ao id
ll v[N];
ll s[4*N];
//lazy nao precisa ter valor da soma total a ser passada, apenas o x que será multiplicado
ll lazy[4*N];

//Seg soma solves: https://www.spoj.com/problems/HORRIBLE/
//Seg max solves: https://codeforces.com/gym/102307/problem/E

int main(){
    int t;
    cin >> t;
    
    int n, q;
    fr(tt,t){
        scanf("%d%d", &n, &q);
        //nesse problema v começa com td zero, portanto nem preciso mexer nele pois nao muda entre casos msm
        Seg<N> seg(v,s,lazy);
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
                printf("%lld\n", seg.query(l,r));
            }
        }
    }
	return 0;
}

