const int MAXV = 200; // maximo numero de vertices
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
    int ret = 0, got;
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
