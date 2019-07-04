#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

typedef long long ll;

/*
    Problema com diferentes tipos de coisa na lazy
    
    ***lazy eh setado para um nó quando ele afeta o range inteiro! (lazy nao muda soh alguns dos subfilhos do no, muda todos!)
    
    ***Tinha dado TLE inicialmente pois eu propagava lazy se fosse, num update, por algo no lazy de certo nó, eu antes propagava o que já havia naquele nó anteriormente, MAS NAO POSSO FAZER ISSO, tenho de modelar lazy de maneira que consigo adicionar varios lazy no mesmo nó! (se lazy for devo mudar filhos pra cor x, não da pra eu fazer mudar pra cor x e depois pra cor y, lazy tem de ser algo do tipo add_delta!!!)
    
    em uma query ou update, no fim, acabo achando e mudando logn intervalos inteiros que não overlapam e que juntos fazem o range atual inteiro. Não existem mais que dois intervalos de msm tamanho (em um lado da arvore esqcolhida) -> e como a diferenca de tamanho dos intervalos eh tami = 2*tami-1, há, de fato, no máximo, logn intervalos
    
    Amortização pelo número de cores -> toda vez que tenho que prosseguir com updlazy (pq cor das base sao diferentes, ou seja cor[no]==-1) eu propago e depois diminuo o número de cores existentes (pq tranformei duas cores em uma) como soh existem n cores iniciais + q cores adicionadas pelas querys, a propagação amortiza para O(n+q)
    
*/

//solves https://codeforces.com/contest/444/problem/C

const int N = 1e5+10;

ll s[4*N];
ll cor[4*N];
ll lazy_cor[4*N];
ll lazy_delta[4*N];

int n, q;

void oper(int no){
    s[no] = s[2*no]+s[2*no+1];
    if(cor[2*no]!=cor[2*no+1] or cor[2*no]==-1 or cor[2*no+1]==-1) cor[no] = -1;
    else cor[no] = cor[2*no];
}

void build(int no = 1, int l = 0, int r = n){
    if(r-l==1){
        s[no] = 0;
        cor[no] = r;
        return;
    }
    int mid = (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    oper(no);
}

void pass(int no, int l, int r);

//seto lazy no nó (marco que filhos não foram propagados)
void updlazy(int no, int l, int r, ll d, ll c){
    if(cor[no]==-1){
        pass(no,l,r);
        int mid = (l+r)/2;
        if(r-l!=1){
        updlazy(2*no,l,mid,d,c);
        updlazy(2*no+1,mid,r,d,c);
        }
        oper(no);
    } else{
        lazy_delta[no] += d;   
        lazy_cor[no] = c;
    
        s[no] += (r-l)*d;
        cor[no] = c;    
    }
}

void updlazy_cor(int no, int l, int r, ll c){
    if(cor[no]==-1){
        int mid = (l+r)/2;
        pass(no,l,r);
        if(r-l!=1){
            updlazy_cor(2*no,l,mid,c);
            updlazy_cor(2*no+1,mid,r,c);
        }
        oper(no);
    } else{
        lazy_delta[no] += abs(cor[no]-c);   
        lazy_cor[no] = c;
        
        s[no] += (r-l)*abs(cor[no]-c);
        cor[no] = c;
    }
}

//propago lazy do no
void pass(int no, int l, int r){
    int mid = (l+r)/2;
    if(!lazy_cor[no] or r-l==1) return;
    updlazy(2*no,l,mid,lazy_delta[no],lazy_cor[no]);
    updlazy(2*no+1,mid,r,lazy_delta[no],lazy_cor[no]);
    lazy_cor[no] = 0;
    lazy_delta[no] = 0;
}

void upd(ll x, int lup, int rup, int no = 1, int l = 0, int r = n){
    if(rup<=l or r<=lup) return;
    if(lup<=l and r<=rup){
        updlazy_cor(no,l,r,x);
        return;
    }   
    pass(no,l,r); //devo passar lazy do nó que estou pois analisarei filhos
    int mid = (l+r)/2;
    upd(x,lup,rup,2*no,l,mid);
    upd(x,lup,rup,2*no+1,mid,r);
    oper(no);
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

int main(){
    scanf("%d%d", &n, &q);
    
    build();
    
    fr(qq,q){
        int t;
        scanf("%d", &t);
        if(t==1){
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
	
	return 0;
}

