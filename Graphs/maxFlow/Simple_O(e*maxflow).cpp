//O(maxflow*E)

//O QUE PRECISA LER/mudar:

//---------------------------------
// maximo numero de vertices
const int N = 160;
//E = N^2 - > ok

int g[N][N];
//---------------------------------
 
// flow network
int flow[N][N];
// visited array
bool vis[N];

int dfs(int cur, int sink, int minc){
	vis[cur] = 1;
	
	if(cur==sink) return minc;
	
	fr(i,N){
		int curflow = g[cur][i]-flow[cur][i];
		if(!vis[i] and curflow>0){
			if(int sent = dfs(i,sink,min(minc,curflow))){
				flow[cur][i]+=sent;
				flow[i][cur]-=sent;
				return sent;
			}
		}
	}
	
	//nao achou sink
	return 0;
}

int maxflow(int src, int sink){
	int ans = 0;
	
	memset(flow,0,sizeof(flow));
	
	while(int sent = dfs(src,sink,INT_MAX)){
		ans+=sent;
		memset(vis,0,sizeof(vis));
	}
	
	return ans;
}

int main(){
	//memset(g,0,sizeof(g));
	//g[a][b] = 1
	//cout << maxFlow(s,t) << endl;
	
	return 0;
}

