#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define pb push_back

/*
    Resolve problema:
    https://codeforces.com/contest/877/problem/E
*/

//bom usar n global qnd for usar vector
int ng;
struct Seg{
	vector<int> v;
	int *s, *lazy;
	
void build(int no = 1, int l = 0, int r = ng){
    if(r-l==1){
        s[no] = v[l];
        return;
    }
    int mid= (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = s[2*no] + s[2*no+1];
}

Seg(vector<int> &vb, int *sb, int *lazyb){
	v = vb;
	ng = vb.size();
	s = sb;
	lazy = lazyb;
	build();
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

int query(int lq, int rq, int no = 1, int l = 0, int r = ng){
    if(rq<=l or lq>=r) return 0;
    if(l>=lq and rq>=r) return s[no];
    pass(no,l,r);
    int mid = (l+r)/2;
    return query(lq,rq,2*no,l,mid) + query(lq,rq,2*no+1,mid,r);
}

void upd(int lq, int rq, int no = 1, int l = 0, int r = ng){
    if(rq<=l or lq>=r) return;
    if(l>=lq and rq>=r){ 
        updlazy(no,l,r);
        return;
    }
    pass(no,l,r);
    int mid = (l+r)/2;
    upd(lq,rq,2*no,l,mid), upd(lq,rq,2*no+1,mid,r);
    s[no] = s[2*no] + s[2*no+1];
}
};

const int N = 2e5+10;

int s[4*N], lazy[4*N];
vector<int> v;

int n;
vector<int> g[N];
int val[N];
int no_to_inic[N], no_to_fim[N];
char str[10];

void dfs(int no){
    no_to_inic[no] = v.size();
    v.pb(val[no]);
    for(auto &it : g[no]){
        dfs(it);
    }
    no_to_fim[no] = v.size();
}

int main(){
    cin >> n;
    for(int i = 1; i<n; i++){
        int it;
        scanf("%d", &it);
        it--;
        g[it].pb(i);
    }
    fr(i,n) scanf("%d", val+i);
    dfs(0);
    Seg seg(v,s,lazy);
    
    int q;
    cin >> q;
    
    fr(qq,q){
        int no;
        scanf(" %s %d", str, &no);
        no--;
        if(str[0]=='g'){
            printf("%d\n", seg.query(no_to_inic[no],no_to_fim[no]));
        } else{
            seg.upd(no_to_inic[no],no_to_fim[no]);
        }
    }
	return 0;
}

