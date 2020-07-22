#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//solves https://acm.timus.ru/problem.aspx?space=1&num=1774

const int MAXV = 3e3+10; // maximo numero de vertices
const int FINF = INT_MAX; // infinite flow

struct Edge {
    int to;
    int cap;
    Edge(int t, int c)
    {
        to = t;
        cap = c;
    }
};

vector<int> adj[MAXV];
vector<Edge> edge;
vector<Edge> eo;
int ptr[MAXV], dinic_dist[MAXV];

// Inserts an edge u->v with capacity c
inline void add_edge(int u, int v, int c)
{
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v, c));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u, 0)); // modify to Edge(u,c) if graph is non-directed
}

bool dinic_bfs(int _s, int _t)
{
    memset(dinic_dist, -1, sizeof(dinic_dist));
    dinic_dist[_s] = 0;
    queue<int> q;
    q.push(_s);
    while (!q.empty() && dinic_dist[_t] == -1) {
        int v = q.front();
        q.pop();
        for (size_t a = 0; a < adj[v].size(); ++a) {
            int ind = adj[v][a];
            int nxt = edge[ind].to;
            if (dinic_dist[nxt] == -1 && edge[ind].cap) {
                dinic_dist[nxt] = dinic_dist[v] + 1;
                q.push(nxt);
            }
        }
    }
    return dinic_dist[_t] != -1;
}

int dinic_dfs(int v, int _t, int flow)
{
    if (v == _t)
        return flow;
    for (int& a = ptr[v]; a < (int)adj[v].size(); ++a) {
        int ind = adj[v][a];
        int nxt = edge[ind].to;
        if (dinic_dist[nxt] == dinic_dist[v] + 1 && edge[ind].cap) {
            int got = dinic_dfs(nxt, _t, min(flow, edge[ind].cap));
            if (got) {
                edge[ind].cap -= got;
                edge[ind ^ 1].cap += got;
                return got;
            }
        }
    }
    return 0;
}

int dinic(int _s, int _t)
{
	eo = edge; // qnd for fazer o fluxo, guardar como eram as capacidades originais (na vdd isto eh o grafo residual - quanto tem disponivel pra ir de fluxo) para poder recuperar a resposta
    int ret = 0, got;
    while (dinic_bfs(_s, _t)) {
        memset(ptr, 0, sizeof(ptr));
        while ((got = dinic_dfs(_s, _t, FINF)))
            ret += got;
    }
    return ret;
}

// Clears dinic structure
inline void dinic_clear(int n_vertices)
{
    for (int a = 0; a < n_vertices; ++a)
        adj[a].clear();
    edge.clear();
}

typedef tuple<int,int,int> tii;

/* rec_ans recupera resposta do fluxo do dinic
   returna tupla (u,v,c) quanto de fluxo (c) passa de u pra v (direcionado)
   (nao adiciona aresta se nao passa nd de fluxo nela)
   
   Lembrar de por em resposta apenas os vertices necessarios
   (geralmente tenho o source e sink a mais por exemplo)
*/
vector<tii> rec_ans(int n_vertices){
	vector<tii> ans;
	fr(i,n_vertices){
		for(auto &ide : adj[i]){
			if(eo[ide].cap>edge[ide].cap){
				ans.emplace_back(i,edge[ide].to,eo[ide].cap-edge[ide].cap);
			}
		}
	}
	return ans;
}

int T = round(2e3);

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, k; cin >> n >> k;
	fr(i,n){
		int ti, duracao; cin >> ti >> duracao;
		for(int t = ti; t<ti+duracao; t++){
			add_edge(i,n+t,1);
		}
	}
	fr(i,n) add_edge(n+T,i,2);
	for(int t = n;t<n+T;t++) add_edge(t,n+T+1,k);
	
	if(dinic(n+T,n+T+1)==2*n){
		vector<tii> ans = rec_ans(n+T+2);
		cout << "Yes\n";
		vector<vector<int>> temp(n);
		for(auto &tup : ans){
			int u, v, c; tie(u,v,c) = tup;
			
			if(u<n){
				temp[u].push_back(v-n);
			}
		}
		fr(i,n){
			assert(sz(temp[i])==2);
			fr(j,2){
				if(j) cout << " ";
				cout << temp[i][j];
			}
			cout << "\n";
		}
	} else{
		cout << "No\n";
	}
}
