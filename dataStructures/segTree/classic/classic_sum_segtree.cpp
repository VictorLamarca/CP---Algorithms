#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

typedef long long ll;

/*
    Lembrar de 4*N no tamanho da seg
    
    Lembrar de dar build
    
    Nós da seg [1,4*N-1], e nós do vetor [0,n-1]
    
    intervalos abertos [l,r)
    
    condição base/terminal na query eh suficiente pois quando estou em folha (elemento único) com ctz cai na condição base (ou está completamente dentro ou completamente fora, pois é só um elemento!)
*/

const int N = 1e5+10;

ll s[4*N];
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

//mudar o valor, v[i] = x (nao aumentar em x)
void modify(int i, ll x, int no = 1, int l = 0, int r = n){
    if(r-l==1){
        s[no] = x;
        return;
    }
    int mid = (l+r)/2;
    if(i<mid) modify(i,x,2*no,l,mid);
    else modify(i,x,2*no+1,mid,r);    
    s[no] = s[2*no]+s[2*no+1]; //fazer operacao no final (apos processar filhos) - inves de fazer s[no] += x-v[l] no inicio
}

ll query(int lq, int rq, int no = 1, int l = 0, int r = n){
    if(rq<=l or r<=lq) return 0; //totalmente fora
    if(lq<=l and r<=rq) return s[no]; //range q estou totalmente dentro do range da query
    int mid = (l+r)/2;
    return query(lq,rq,2*no,l,mid) + query(lq,rq,2*no+1,mid,r);
}

int main(){

    cin >> n >> q;
    
    fr(i,n) scanf("%lld", v+i);
    
    build();
    
    fr(qq,q){
        char c;
        scanf(" %c", &c);
        if(c=='q'){
            int l, r;
            scanf("%d%d", &l, &r);
            l--;
            printf("%lld\n", query(l,r));
        } else{
            int p, x;
            scanf("%d%d", &p, &x);
            p--;
            modify(p,x);
        }
    }
	
	return 0;
}

/*
input:
7 10
1 2 3 4 5 6 7
q 1 7
q 1 6
q 2 6
u 7 1
q 1 7
q 1 6
u 4 -10
q 3 5
u 7 -100
q 4 4

answer:
28
21
20
22
21
-2
-10
*/

