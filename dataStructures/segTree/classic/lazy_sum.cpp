#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define fr(i,n) for(int i = 0; i<n; i++)

/* 
    Lembrar de 4*N no tamanho da seg e lazy
    
    Lembrar de dar build
    
    Nós da seg [1,4*N-1], e nós do vetor [0,n-1]
    
    intervalos abertos [l,r)
    
    condição base/terminal na query eh suficiente pois quando estou em folha (elemento único) com ctz cai na condição base (ou está completamente dentro ou completamente fora, pois é só um elemento!)
    
    v[id] nao estara atualizado, para recuperalo preciso passar o s[no] com no referente ao id
*/

const int N = 1e5+10;

ll s[4*N];

//lazy nao precisa ter valor da soma total a ser passada, apenas o x que será multiplicado
ll lazy[4*N];

ll v[N];

int n, q;

void build(int no = 1, int l = 0, int r = n){
    if(r-l==1){
        s[no] = v[l];
        return;
    }
    int mid = (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = s[2*no]+s[2*no+1];
}

//seto lazy no nó (marco que filhos não foram propagados)
void updlazy(int no, int l, int r, ll x){
    s[no] += (r-l)*x;
    lazy[no] += x;
}

//propago lazy do no
void pass(int no, int l, int r){
    int mid = (l+r)/2;
    updlazy(2*no,l,mid,lazy[no]);
    updlazy(2*no+1,mid,r,lazy[no]);
    lazy[no] = 0;
}

void upd(ll x, int lup, int rup, int no = 1, int l = 0, int r = n){
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
}

ll query(int lq, int rq, int no = 1, int l = 0, int r = n){
    if(rq<=l or r<=lq) return 0;
    if(lq<=l and r<=rq){
        return s[no];
    } 
    pass(no,l,r);
    int mid = (l+r)/2;
    return query(lq,rq,2*no,l,mid) + query(lq,rq,2*no+1,mid,r);
}

//solves problem: https://www.spoj.com/problems/HORRIBLE/

int main(){
    int t;
    cin >> t;
    
    fr(tt,t){
        scanf("%d%d", &n, &q);
        
        //nesse problema v começa com td zero, portanto nem preciso mexer nele pois nao muda entre casos msm
        
        fr(i,4*n){
            lazy[i] = s[i] = 0;
        }
        
        fr(qq,q){
            int c;
            scanf("%d", &c);
            if(c==0){
                int l, r, x;
                scanf("%d%d%d", &l, &r, &x);
                l--;
                upd(x,l,r);
            } else{
                int l, r;
                scanf("%d%d", &l, &r);
                l--;
                printf("%lld\n", query(l,r));
            }
        }
    }
	
	return 0;
}

