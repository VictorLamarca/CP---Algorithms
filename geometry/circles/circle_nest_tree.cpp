#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//solves https://vjudge.net/contest/382848#problem/C

const int N = 2e5+10;

ll n, q;
ll xp[N][2];
long double cury[N][2];

ll sq(ll x){
	return x*x;
}

ll pai[N];
ll xc[N], yc[N], rc[N];
ll xg;
struct circev{
	ll id, up;
	circev(ll _id, ll _up){
		id = _id;
		up = _up;
	}
	
	void process() const{
		if(xp[id][up]<xg){
			ll dx = abs(xg-xc[id]);
			if(up) cury[id][up] = yc[id]+sqrt((long double)(sq(rc[id])-sq(dx)));
			else cury[id][up] = yc[id]-sqrt((long double)(sq(rc[id])-sq(dx)));
			xp[id][up] = xg;
		}
	}
	
	bool operator<(const circev &o) const{
		this->process();
		o.process();
		
		if(id==o.id) return up<o.up;
		return cury[id][up]<cury[o.id][o.up];
	}
};

ll dp[N][2];
ll ans[N];
vector<int> g[N];

void dfs(int no){
	for(auto &it : g[no]){
		dfs(it);
		if(it>=n){
			fr(cor,2) dp[no][cor]+=dp[it][cor];
		} else{
			dp[no][0] += dp[it][1];
			dp[no][1] += max(dp[it][1],dp[it][0]);
		}
	}
	
	if(no>=n){
		ans[no-n] = max(dp[no][0]+1,dp[no][1]);
	} else{
		dp[no][0]++;
	}
}

int disjoint(int i, int j){
	return sq(xc[i]-xc[j])+sq(yc[i]-yc[j]) > sq(rc[i]+rc[j]);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	cin >> n >> q;
	
	fr(i,N) fr(cor,2) xp[i][cor] = -INT_MAX;	
	vector<tuple<ll,ll,ll>> ev; //x,entra,id
	
	fr(i,n+q){
		cin >> xc[i] >> yc[i] >> rc[i];
		
		ev.emplace_back(xc[i]-rc[i],1,i);
		ev.emplace_back(xc[i]+rc[i],0,i);
	}
	
	sort(all(ev));
	
	set<circev> sup;
	
	for(auto &tup : ev){
		ll xq, entra, id; tie(xq,entra,id) = tup;
		xg = xq;
		
		if(!entra){
			sup.erase(sup.find(circev(id,1)));
			sup.erase(sup.find(circev(id,0)));
		} else{
			
			auto it = sup.upper_bound(circev(id,1));
			if(it!=sup.end()){ 
				if(!disjoint(it->id,id)){ 
					pai[id] = it->id;
				}
				else pai[id] = pai[it->id];
				
			}
			else pai[id] = n+q;
			
			sup.emplace(id,1);
			sup.emplace(id,0);
		}
	}
	
	fr(i,n+q){
		g[pai[i]].push_back(i);
	}
	
	dfs(n+q);
	
	fr(i,q){
		cout << ans[i] << endl;	
	}
}
