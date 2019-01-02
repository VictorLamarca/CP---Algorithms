#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

#define pb push_back

/*
    Resolve problema:
    https://codeforces.com/contest/877/problem/E
*/

const int N = 2e5+10;

int s[4*N], lazy[4*N];
vector<int> v;

int n;

void build(int no = 1, int l = 0, int r = n){
    if(r-l==1){
        s[no] = v[l];
        return;
    }
    int mid= (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = s[2*no] + s[2*no+1];
}

void updlazy(int no, int l, int r){
    lazy[no] = !lazy[no];
    s[no] = r-l-s[no];
}

void pass(int no, int l, int r){
    if(!lazy[no]) return;
    int mid = (l+r)/2;
    updlazy(2*no,l,mid);
    updlazy(2*no+1,mid,r);
    lazy[no] = 0;
}

int query(int lq, int rq, int no = 1, int l = 0, int r = n){
    if(rq<=l or lq>=r) return 0;
    if(l>=lq and rq>=r) return s[no];
    pass(no,l,r);
    int mid = (l+r)/2;
    return query(lq,rq,2*no,l,mid) + query(lq,rq,2*no+1,mid,r);
}

void upd(int lq, int rq, int no = 1, int l = 0, int r = n){
    if(rq<=l or lq>=r) return;
    if(l>=lq and rq>=r){ 
        updlazy(no,l,r);
        return;
    }
    pass(no,l,r);
    int mid = (l+r)/2;
    upd(lq,rq,2*no,l,mid), upd(lq,rq,2*no+1,mid,r);
    s[no] = s[2*no] + s[2*no+1]; //tinha errado aqui!
}

vector<int> g[N];

int val[N];
int no_to_inic[N], no_to_fim[N];

void dfs(int no){
    no_to_inic[no] = v.size();
    v.pb(val[no]);
    for(auto &it : g[no]){
        dfs(it);
    }
    no_to_fim[no] = v.size();
}

char str[10];

int main(){
    cin >> n;
    frr(i,1,n-1){
        int it;
        scanf("%d", &it);
        it--;
        g[it].pb(i);
    }
    fr(i,n) scanf("%d", val+i);
    
    dfs(0);
    
    build();
    
    int q;
    cin >> q;
    
    fr(qq,q){
        int no;
        scanf(" %s %d", str, &no);
        no--;
        if(str[0]=='g'){
            printf("%d\n", query(no_to_inic[no],no_to_fim[no]));
        } else{
            upd(no_to_inic[no],no_to_fim[no]);
        }
    }
	
	return 0;
}

