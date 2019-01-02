#include <bits/stdc++.h>
using namespace std;

/* 
    nao esquecer de 4*N no tamanho da seg e do lazy
    e de dar build 
    
    build e pass tem 3 paramtros
    updlazy tem 4
    e operacoes normais (usadas de fora) tem 5 parametros 
    upd e query
    
    Em upd e query, td vez que passo dos caso base, preciso passar o pass do no (talvez nao tenha, mas precisaria checar), pois se a operacao atual vai lidar com nos mais debaixo preciso telos atualizados
    
    Nós da seg q são de um único elemento nunca passam dos casos base, pois ou está inteiramente dentro ou fora do intervalo. E esses nós (q são folhas) podem até estar com lazy ativo, mas nao significa nada porque elas nao tem filhos mesmo
    
    v[id] nao estara atualizado, para recuperalo preciso passar o s[no] que é de id na vdd.
*/

ll seg[4*N];

//lazy nao precisa ter valor da soma total a ser passada, apenas o x que será multiplicado
ll lazy[4*N];

ll v[N];

int n;

void build(int no = 1, int l = 0, int r = n){
    if(r-l==1){
        seg[no] = v[l];
        return;
    }
    int mid = (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = s[2*no]+s[2*no+1];
}

void updlazy(int no, int l, int r, ll x){
    s[no] += (r-l)*x;
    lazy[no] += x;
}

void pass(int no, int l, int r){
    int mid = (l+r)/2;
    updlazy(2*no,l,mid,lazy[no]);
    updlazy(2*no+1,mid,r,lazy[no]);
    lazy[no] = 0;
}

void upd(ll x, int lup, int rup, int no = 1, int l = 0, int r = n){
    if(rup<=l or lup>=r) return;
    if(lup<=l and rup>=r){ //intervalo q o NÓ representa completamente inteiro
        updlazy(no,l,r,x);
        return;
    }   
    pass(no,l,r);
    int mid = (l+r)/2;
    upd(x,lup,rup,2*no,l,mid);
    upd(x,lup,rup,2*no+1,mid,r);
    s[id] = s[2*id] + s[2*id+1]; //cuidado com essa operacao, pois os filhos podem nao ter mudado por completo, as vezes é diferente da operação do updlazy
}

ll query(int lq, int rq, int no = 1, int l = 0, int r = n){
    if(rq<=l or lq>=r) return;
    if(lq<=l and rq>=r){
        return s[no];
    } 
    pass(no,l,r);
    int mid = (l+r)/2;
    return query(lq,rq,2*no,l,mid) + query(lq,rq,2*no+1,mid,r);
}

int main(){
	
	return 0;
}

