#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

/*
    Non comutative operation Segment tree
    https://codeforces.com/contest/380/problem/C  
*/

const int N = 1e6+10;

array<int,3> s[2*N];

int n;

char str[N];

array<int,3> comb(array<int,3> &a, array<int,3> &b){
    array<int,3> ans;
    int mn = min(a[1],b[2]);
    fr(i,3) ans[i] = a[i]+b[i];
    ans[0]+=2*mn;
    frr(i,1,2) ans[i]-=mn;
    return ans;
}

void build(){
    fr(i,n){
        if(str[i]=='('){
            s[i+n] = {0,1,0};
        } else s[i+n] = {0,0,1};
    }
    for(int i = n-1;i>=1;i--){
        s[i] = comb(s[i<<1],s[i<<1|1]);
    }
}

int query(int l, int r){
    array<int,3> resl = {0,0,0}, resr = {0,0,0};
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
        if(l&1) resl = comb(resl,s[l++]);
        if(r&1) resr = comb(s[--r],resr);
    }
    return comb(resl,resr)[0];
}

int main(){ 
    int id = 0;
    char c;
    while(scanf("%c", &c)!=EOF and c!='\n') str[id++] = c;
    
    n = id;
    build();
    
    int q;
    cin >> q;
    
    fr(i,q){
        int l, r;
        scanf("%d %d", &l, &r);
        l--;
        printf("%d\n", query(l,r));
    }
	
	return 0;
}

