#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

/*
    Lembrar de 4*N no tamanho da seg
    
    Altura = logn
    Em query, td vez que se divide, um dos intervalos para na hora, portanto é 2*logn max
    
    Nós da seg [1,4*N-1], e nós do vetor [0,n-1]
*/

const int N = 2e5+10;

//pode ser uma seg de node (com varios parametros), e a operação pode ser correspondente
ll seg[4*N];
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

//mudar o valor, v[i] = x (nao aumentar em x)
void modify(int i, ll x, int no = 1, int l = 0, int r = n){
    s[no] += x - v[i];
    if(r-l==1){
        v[p] = x;
        return;
    }
    int mid = (l+r)/2;
    if(l<mid) modify(i,x,2*no,l,mid);
    modify(i,x,2*no+1,mid,r);    
}

ll query(int liq, int riq, int no = 1, int l = 0, int r = n){
    if(riq<=l or liq>=r) return 0;
    if(liq>=l and riq<=r) return s[no];
    int mid = (l+r)/2;
    return query(liq,riq,2*no,l,mid) + query(liq,riq,2*no+1,mid,r);
}

int main(){
	
	return 0;
}

