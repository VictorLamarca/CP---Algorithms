#include <bits/stdc++.h> 
using namespace std;

#define all(v) (v).begin(),(v).end()

#define fr(i,MAXN) for(int i = 0;i<MAXN;i++)

#define frr(i,a,b) for(int i =a;i<=b;i++)

#define eb emplace_back

#define pii pair<int,int>
#define debug printf
#define pb push_back
#define prin(a) cout << #a << " = " << a << endl

#define maxn MAXN
const int MAXN = 4e5+10;

vector<int> g[MAXN];

int n, m, k;
int N;

int disc[MAXN], low[MAXN], tempo;

int st[MAXN], ss;

int comp[MAXN], ncomp;

int dfs(int no){
	disc[no] = low[no] = ++tempo;
	st[ss++] = no;
	
	for(auto it : g[no]){
		if(!disc[it]) low[no] = min(low[no],dfs(it));
		else if(!comp[it]) low[no] = min(low[no],disc[it]);
	}
	
	if(low[no]==disc[no]){
		comp[no] = ++ncomp;
		while(st[ss-1]!=no) comp[st[--ss]] = comp[no];
		ss--;
	}
	return low[no];
}

void no(){
	cout << "-1" << endl;
	exit(0);
}

int marcado[MAXN];
vector<int> nos_na_comp[MAXN];
vector<int> gcomp[MAXN];
int compvis[MAXN];

int nf = 0;

/*
	Construindo resposta
	Basta fazer de greedy de marcar o primeiro que vir
	x ou !x
	Percorrer na ordem de baixo pra cima, ou seja,
	top sort invertida
	
	Pois se pai x implica em filho !x, basta
	fazer com que !x seja verdadeiro e x falso
	x sendo falso, nao importa noq ele implica
*/
void dfsl(int compcur){
	if(compvis[compcur]) return;
	compvis[compcur] = 1;
	
	for(auto itcomp : gcomp[compcur]){
		dfsl(itcomp);
	}
	for(auto no : nos_na_comp[compcur]){
		if(!marcado[no^1]) marcado[no] = 1;
	}
}

//solves problem from camp unicamp jan19
//contest 22 de jan, dia2, prob B

vector<pii> v[maxn];

int vx[maxn];

int main(){
	cin >> n >> m >> k;
	
	//ler input e construiir grafo robado
	for(int i=0;i<k;i++){
		
		int a,b;
		scanf("%d%d",&a,&b), a--;
		
		int ty;
		if(b < 0) ty = -1;
		else ty = 1;
		
		b = abs(b)-1;
		
		v[a].pb(pii(b,ty));
	
	}
	
	N = 2*m;
	
	for(int i=0;i<n;i++){
		
		int sz = v[i].size();
		if(sz == 0) continue;
		
		for(int j=0;j<sz;j++){
			vx[j] = 2*v[i][j].first;
			if(v[i][j].second == 1) vx[j]++;
		}
		
		int begR = N;
		int begL = N + sz;
		N += 2*sz;
		
		for(int j=begR;j<begL-1;j++)
			g[j].pb(j+1), g[j].pb(vx[j-begR]);
		g[begL-1].pb(vx[begL-1-begR]);
		
		for(int j=begL+1;j<N;j++)
			g[j].pb(j-1), g[j].pb(vx[j-begL]);
		g[begL].pb(vx[begL-begL]);
		
		for(int j=0;j<sz;j++){
			
			int u = vx[j]^1;
			
			if(j) g[u].pb(begL + j - 1);
			if(j != sz-1) g[u].pb(begR + j + 1);
		}
	}
	
	//agora vou ver se tem reposta e contruir	
	fr(i,N) if(!disc[i]) dfs(i);
	
	vector<int> ans;
	
	//vendo se tem negacao na msm componente da afirmacao
	fr(i,m){
		if(comp[2*i]==comp[2*i+1]) no();
	}
	
	fr(i,2*m){
		nos_na_comp[comp[i]].eb(i);
	}
	
	frr(i,2*m,N-1) nos_na_comp[comp[i]].eb(i);
	
	int cnt = 0;
	//fazendo grafo comprimido
	fr(no,N){
		for(auto it : g[no]){
			if(comp[no]!=comp[it]){
				gcomp[comp[no]].eb(comp[it]);
				//assert(comp[no]>comp[it]);
			} else cnt++;
		}
	}
	
	assert(nos_na_comp[0].size()==0);
	
	//vendo oq eh verdade do grafo original
	frr(no,1,ncomp){
		dfsl(no);
	}
	
	//vendo quais cidades sao visitadas
	fr(i,m){
		if(marcado[2*i+1]){
			ans.eb(i);
		} else assert(marcado[2*i]);
	}
	
	cout << ans.size() << endl;
	fr(i,ans.size()) printf("%d%c", ans[i]+1, " \n"[i==ans.size()-1]);
	
}
