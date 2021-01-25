#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min<ll>(a,b)
#define rmax(a,b) a = max<ll>(a,b)

#define fi first
#define se second

//solves prob F - illuminatin
//http://codeforces.com/gym/101201

//Lembrar de por N*2
const int N = 2e3+10;
vector<int> g[N];

int tempo, ncomp, ss;
int disc[N], st[N], low[N], comp[N];

int dfs(int no){
	disc[no] = low[no] = ++tempo;
	st[ss++] = no;
	for(auto it : g[no]){
		if(!disc[it]) low[no] = min(low[no],dfs(it));
		else if(!comp[it]) low[no] = min(low[no],disc[it]);
		//pode ser low[it], mas melhor manter disc[it] q tmb funciona e eh indicado pelo editorial
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

/*
	Poe condição (u or v) no 2sat
	se du==1, u é 2*u+1 (impar) e significa
	que é u normal (verdadeiro), do contrario é not u
*/
void poe(int u, int v, int du, int dv){
	u = 2*u+du;
	v = 2*v+dv;
	g[u^1].push_back(v);
	g[v^1].push_back(u);
}

bool is_solvable(int n){
	assert(n<N);
	//process 2-Sat
	fr(i,2*n) if(!disc[i]) dfs(i);
	
	//Is 2-Sat solvable?
	fr(i,n){
		if(comp[2*i]==comp[2*i+1]) return 0;
	}
	return 1;
}

void reset(int n){
	n*=2;
	assert(n<N);
	fr(i,n){ 
		g[i].clear();
		disc[i] = 0;
		st[i] = 0;
		low[i] = 0;
		comp[i] = 0;
	}
	tempo = 0;
	ncomp = 0;
	ss = 0;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int ntam, r, n; cin >> ntam >> r >> n;
	vector<pair<int,int>> vp;
	fr(icur,n){
		int i, j; cin >> i >> j; i--,j--;
		int iant = -1;
		for(auto &[a,b] : vp){
			iant++;
			if(a==i and abs(b-j)<=r){
				poe(icur,iant,0,0);
			}
			if(b==j and abs(i-a)<=r){
				poe(icur,iant,1,1);
			}
		}
		vp.emplace_back(i,j);
	}
	if(is_solvable(n)) cout << "YES\n";
	else cout << "NO\n";
}
