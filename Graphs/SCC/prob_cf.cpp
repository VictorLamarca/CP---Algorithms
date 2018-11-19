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
Problema original
https://codeforces.com/contest/894/problem/E
*/

const int N = 1e6+10;

ll soma_comp[N];
vector<int> vcomp[N];

vector<pii> g[N];

int disc[N], low[N], tempo;

int st[N], ss;

int comp[N], ncomp;

int dfs(int no){
    disc[no] = low[no] = ++tempo;
    st[ss++] = no;
    for(auto par : g[no]){
        int it = par.fi;
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

int n, m;

vector<ll> pivo;
vector<ll> pref;

ll val(ll x){
    if(pivo.empty()){
        int x = 0;
        ll soma = 0;
        while(soma<1e8+10){
            soma+=x;
            pivo.pb(soma);
            x++;
        }
        pref.pb(0);
        frr(i,1,pivo.size()-1){
            pref.pb(pref.back()+pivo[i]);
        }
    }
    
    //fr(i,5) prin(pivo[i]);
    auto it = --upper_bound(all(pivo),x);
    //prin(*it);
    int qnt = it-pivo.begin();
    
    return x*(qnt+1)-pref[qnt];
}

ll dp[N];

ll rec(int compi){
    ll &ans = dp[compi];
    if(~ans) return ans;
    ans = 0;
    
    for(auto no : vcomp[compi]){
        for(auto it : g[no]){
            if(comp[it.fi]!=compi) ans = max(ans,it.se+rec(comp[it.fi]));
        }
    }
    
    ans+= soma_comp[compi];
    
    return ans;
}

int main(){
	//FILE_IN FILE_OUT
	
	cin >> n >> m;
	
	fr(i,m){
	    int u, v, c;
	    scanf("%d%d%d", &u, &v, &c);
	    u--,v--;
	    g[u].pb({v,c});
	}
	
	fr(i,n) if(!disc[i]) dfs(i);
	
	fr(i,n) comp[i]--;
	
	fr(i,n){
	    vcomp[comp[i]].pb(i);
	}
	
	fr(no,n){
	    for(auto it : g[no]){
	        if(comp[no]==comp[it.fi]){ soma_comp[comp[no]] += val(it.se);
	        }
	    }
	}
	
	memset(dp,-1,sizeof(dp));
	
	int s;
	cin >> s;
	s--;
	cout << rec(comp[s]) << endl;
	
	return 0;
}

