#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<(n);i++)
#define frr(i,a,b) for(int i=(a);i<=(b);i++)
#define frrs(i,a,b) for(int i=(a);i>=(b);i--)
#define VAR(a,b) __typeof(b) a=b
#define frit(it,c) for(VAR(it,(c).begin());it!=(c).end();it++)

typedef long long ll;
typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;

#define PI acos(-1)
#define MOD 1000000007

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define prinsep if(debug) cout << "------" << endl;
#define cendl if(debug) cout << endl

// Dinic maxflow, min(O(EV^2),O(maxflow*E)(?)) worst case
// O(E*min(V^2/3,sqrt(E))) for unit caps (O(E*sqrt(V)) if bipartite)

typedef ll FTYPE; // define as needed

const int MAXV = 200; // maximo numero de vertices
const FTYPE FINF = LLONG_MAX; // infinite flow

struct Edge {
    int to;
    FTYPE cap;
    Edge(int t, FTYPE c)
    {
        to = t;
        cap = c;
    }
};

vector<int> adj[MAXV];
vector<Edge> edge;
int ptr[MAXV], dinic_dist[MAXV];

// Inserts an edge u->v with capacity c
inline void add_edge(int u, int v, FTYPE c)
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

FTYPE dinic_dfs(int v, int _t, FTYPE flow)
{
    if (v == _t)
        return flow;
    for (int& a = ptr[v]; a < (int)adj[v].size(); ++a) {
        int ind = adj[v][a];
        int nxt = edge[ind].to;
        if (dinic_dist[nxt] == dinic_dist[v] + 1 && edge[ind].cap) {
            FTYPE got = dinic_dfs(nxt, _t, min(flow, edge[ind].cap));
            if (got) {
                edge[ind].cap -= got;
                edge[ind ^ 1].cap += got;
                return got;
            }
        }
    }
    return 0;
}

FTYPE dinic(int _s, int _t)
{
    FTYPE ret = 0, got;
    while (dinic_bfs(_s, _t)) {
        memset(ptr, 0, sizeof(ptr));
        while ((got = dinic_dfs(_s, _t, FINF)))
            ret += got;
    }
    return ret;
}

// Clears dinic structure
inline void dinic_clear()
{
    for (int a = 0; a < MAXV; ++a)
        adj[a].clear();
    edge.clear();
}

int main(){
	int t;
	scanf("%d", &t);
	int n,m;
	fr(ii,t){
		scanf("%d%d", &n, &m);
		
		fr(i,m){
			int a, b;
			scanf("%d%d", &a, &b);
			a--;
			b--;
			add_edge(a,b,1);
		}
		
		int orig, dest, k;
		
		scanf("%d%d%d", &orig, &dest, &k);
		orig--;
		dest--;
		
		(k<dinic(orig,dest))? printf("YES\n") : printf("NO\n");
		
		dinic_clear();
		
	}
	return 0;
}
