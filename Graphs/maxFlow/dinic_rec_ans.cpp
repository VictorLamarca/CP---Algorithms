#include <bits/stdc++.h>

using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()
#define eb emplace_back
#define prin(a) cout << #a << " = " << a << endl;
typedef long long ll;

const int MAXV = 1002; // maximo numero de vertices
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
	eo = edge;
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

//recupera resposta do fluxo do dinic
//returna u,v,c quanto de fluxo passa de u pra v
vector<tii> rec_ans(int n_vertices){
	vector<tii> ans;
	fr(i,n_vertices){
		for(auto &ide : adj[i]){
			if(eo[ide].cap>edge[ide].cap){
				ans.eb(i,edge[ide].to,eo[ide].cap-edge[ide].cap);
			}
		}
	}
	return ans;
}

//solves from http://opentrains.snarknews.info
//contest 10411 problem c

int n, m;

#define fi first
#define se second
typedef pair<int,int> pii;

vector<int> g[MAXV];
vector<pii> e;
int main(){	
	
	cin >> n >> m;
	
	fr(i,m){
		int u, v;
		scanf("%d%d", &u, &v);
		u--,v--;
		e.eb(u,v);
		g[u].eb(v);
		g[v].eb(u);
	}
	
	fr(cand_tl,n){
		vector<int> nb(n,0);
		int n_nb = 0;
		for(auto &it : g[cand_tl]){ 
			nb[it] = 1;
			n_nb++;
			add_edge(it,cand_tl,1);
		}
		for(auto &par : e){
			int u, v;
			tie(u,v) = par;
			if(u==cand_tl or v==cand_tl) continue;
			if(nb[u]>nb[v]) swap(u,v);
			if(nb[u] or !nb[v]) continue;
			add_edge(u,v,1);
		}
		fr(i,n){
			if(!nb[i] and i!=cand_tl) add_edge(n,i,1);
		}
		int n_not_nb = n-1-n_nb;
		if(dinic(n,cand_tl)==n_not_nb){
			puts("Yes");
			
			vector<tii> ans = rec_ans(n);
			vector<int> mark(n);
			mark[cand_tl] = 1;
			vector<pii> vans;
			for(auto &tup : ans){
				int u, v, c;
				tie(u,v,c) = tup;
				if(u!=n and v!=cand_tl and c){
					vans.eb(u+1,v+1);
					mark[u] = 1;
					mark[v] = 1;
				}
			}
			fr(i,n) if(!mark[i]){
				assert(nb[i] ==1);
				vans.eb(i+1,-1);
			}
			printf("%d %d\n", cand_tl+1, (int)vans.size());
			for(auto &par : vans){
				int u, v;
				tie(u,v) = par;
				printf("%d %d\n", u,v);
			}
			return 0;
		}
		dinic_clear(n+1);
	}
	puts("No");
}
