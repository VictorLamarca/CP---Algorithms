#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
#define eb emplace_back
#define all(v) (v).begin(),(v).end()

//LEMBRAR DE POR O MAKE DEPOIS DE MONTAR A ARVORE
const int N = 1e5+10;
const int MLOG = 17;
vector<int> g[N];
int L[N]; //L[i] = level do nó i (raiz = 0)
int P[N]; //pai do nó i (raiz = -1)
int A[N][MLOG+1]; //A[i][j] = pai 2^j niveis acima do nó i - A de ancestral

void dfsd(int no, int from, int d){
	L[no] = d;
	
	for(auto it : g[no]){
		if(it==from) continue;
		P[it] = no;
		dfsd(it,no,d+1);
	}
	
	return;
}

void make(int n){
	P[0] = -1;
	dfsd(0,-1,0);
	
	fr(i,n){
		fr(j,MLOG){
			A[i][j] = -1;
		}
	}
	
	fr(i,n) A[i][0] = P[i];
	
	for(int j = 1; (1<<j) < n;j++){
		fr(i,n){
		    int mp = A[i][j-1];
			if(~mp){
				A[i][j] = A[mp][j-1];
			}
		}
	}
	return;
}

int lca(int p, int q){
	if(L[p]<L[q]) swap(p,q);
	
	for(int i = MLOG; i>=0;i--){
		if(L[p]-L[q] >= (1<<i) ){
			p = A[p][i];	
		}
	}
	
	if(p==q) return p;
	
	for(int i = MLOG;i>=0;i--){
		if(A[p][i]!=A[q][i]){
			q = A[q][i];
			p = A[p][i];
		}
	}
	
	return P[q];
}	

/*
    Solves problem:
    https://www.urionlinejudge.com.br/judge/pt/problems/view/2887
*/

int no_to_id[N];
int vlca[4][4];

int flca(int u, int v){
    u = no_to_id[u];
    v = no_to_id[v];
    return vlca[u][v];
}

int is(int u1, int u2, int v1, int v2){
    if(L[flca(u1,u2)]<L[flca(v1,v2)]) swap(u1,v1), swap(u2,v2);
    
    int ans = 0;
    
    fr(cor,2){
        int lca_outro = flca(u1,v1);
        if(L[flca(u1,v2)]>L[flca(u1,v1)]) lca_outro = flca(u1,v2);
        ans+= max(0, L[lca_outro]-L[flca(u1,u2)]+1);
        swap(u1,u2);
    }   
    
    if(ans) ans--;
    return ans;
}

int main(){
    int n, q;
    cin >> n >> q;
    
    fr(i,n-1){
        int u, v;
        scanf("%d%d", &u, &v);;
        u--,v--;
        g[u].eb(v);
        g[v].eb(u);
    }
    
    make(n);
    
    fr(qq,q){
        vector<int> v(4);
        fr(i,4) scanf("%d", &v[i]), v[i]--;
        fr(i,4) no_to_id[v[i]] = i;
        fr(i,4) fr(j,i){
            vlca[i][j] = vlca[j][i] = lca(v[i],v[j]);
        }
        fr(i,4) vlca[i][i] = v[i];
        printf("%d\n", is(v[0],v[1],v[2],v[3]));
    }
}
