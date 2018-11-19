#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;

#define pb push_back

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LLONG_MAX
//-DBL_MAX
//__builtin_popcountll(ll x) - __builtin_popcount(int x)

bool debug = 1;
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

#define all(v) (v).begin(),(v).end()

/*
Enunciado poroblema
https://vjudge.net/contest/255455#problem/C
*/

const int N = 1e5+10;

int n, m;

vector<int> g[N];
int disc[N], low[N], tempo; 
//primeiro tempo em que nó foi descoberto, minimo entre disc[no] e low[v] dos vizinhos

int st[N], ss; 
//stack e size of stack

int comp[N], ncomp;
//componente do noh i (0 se ainda nao pertence a componente)

int dfs(int no){
	disc[no] = low[no] = ++tempo;
	st[ss++] = no;
	for(auto it : g[no]){
		if(!disc[it]) low[no] = min(low[no],dfs(it));
		else if(!comp[it]) low[no] = min(low[no],disc[it]);
	}
	if(low[no]==disc[no]){
		comp[no] = ++ncomp;
		while(st[ss-1]!=no){
			comp[st[--ss]] = comp[no];
		}
		ss--;
	}
	return low[no];
}

int no_to_idcomp[N];

vector<int> comp_to_nos[N];

//id eh comp
vector<vector<int>> matgcomp[N];
vector<vector<int>> maxdist[N];

int dpgeral[N], dpsai[N];

int recsai(int no);
int recgeral(int no);

int recgeral(int no){
    if(~dpgeral[no]) return dpgeral[no];
    int &ans = dpgeral[no] = 0;
    
    int id = no_to_idcomp[no];
    /*prin(no);
    prin(maxdist[comp[no]][id].size());
    cendl;*/
    fr(i,maxdist[comp[no]][id].size()){
        ans = max(ans,maxdist[comp[no]][id][i]+recsai(comp_to_nos[comp[no]][i]));
    }
    
    return ans;
}

int recsai(int no){
    int &ans = dpsai[no];
    if(~ans) return ans;
    ans = 0;
    
    for(auto it : g[no]){
        if(comp[it]!=comp[no]) ans = max(ans,1+recgeral(it));
    }
    
    return ans;
}


int main(){
	//FILE_IN FILE_OUT
	
	cin >> n >> m;
	
	fr(i,m){
	    int u, v;
	    scanf("%d%d", &u, &v);
	    u--,v--;
	    g[u].pb(v);
	}
	
	fr(i,n) if(!disc[i]) dfs(i);
	
	fr(i,n){
	    if(comp[i]==0) break;
	    else comp[i]--;
	}
	
	fr(i,n){
	    comp_to_nos[comp[i]].pb(i);
	}
	
	/*
	fr(i,ncomp){
	    prinv(comp_to_nos[i]);
	}*/
	
	fr(i,ncomp){
	    int tam = comp_to_nos[i].size();
	    maxdist[i] = vector<vector<int>>(tam,vector<int>(tam,0));
	    matgcomp[i] = vector<vector<int>>(tam,vector<int>(tam,0));
	    fr(j,tam){
	        no_to_idcomp[comp_to_nos[i][j]] = j;
	    }
	}
	
	fr(i,n){
	    int cc = comp[i];
	    for(auto it : g[i]){
	        if(cc==comp[it]){
	            matgcomp[cc][no_to_idcomp[i]][no_to_idcomp[it]] = 1;
	        }
	    }
	}
	
	fr(compi,ncomp){
	    do{
	        int curno = comp_to_nos[compi][0];
	        int ant = curno;
	        frr(i,1,comp_to_nos[compi].size()-1){
	            int it = comp_to_nos[compi][i];
	            if(!matgcomp[compi][no_to_idcomp[ant]][no_to_idcomp[it]]) break;
	            maxdist[compi][no_to_idcomp[curno]][no_to_idcomp[it]] = max(maxdist[compi][no_to_idcomp[curno]][no_to_idcomp[it]],i);
	            ant = it;
	        }
	        //break;
	    } while(next_permutation(all(comp_to_nos[compi])));
	    sort(all(comp_to_nos[compi]));
	}
	
	memset(dpgeral,-1,sizeof(dpgeral));
	memset(dpsai,-1,sizeof(dpsai));
	
	int ans = 0;
	fr(i,n){
	    if(dpgeral[i]==-1){ ans = max(ans,recgeral(i));}// prin(i);}
	}
	
	cout << ans+1 << endl;
	
	return 0;
}

