#include <bits/stdc++.h>
using namespace std;
 
#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()
 
typedef long long ll;
 
#define rmin(a,b) a = min(a,b)
#define rmax(a,b) a = max(a,b)
 
#define fi first
#define se second

//solves j from: https://codeforces.com/gym/100781/standings/friends/true
 
struct comp_str{
 
vector<string> v;
 
comp_str(){}
 
comp_str(vector<string> &_v){
	v = _v;
	sort(all(v));
	v.resize(unique(all(v))-v.begin());
}
 
int str_to_int(string &s){
	return lower_bound(all(v),s)-v.begin();
}
 
string int_to_str(int i){
	return v[i];
}
 
};
 
const int N = 1e5+10;
vector<string> pergs[N];
string resps[N];
vector<int> perg[N];
int resp[N];
 
int sz = 0;
map<int,int> prox[N];
vector<int> resp_in_trie[N];
int n_tot[N], max_freq[N];
 
int n, T; 
 
vector<vector<bool>> vis;
vector<vector<long double>> dp;
 
long double rec(int i, int t){
	if(t==T) return 0;
	long double &ans = dp[i][t];
	if(vis[i][t]) return ans;
	vis[i][t] = 1;
	
	assert(fabs(ans-1e-6)<1e-5);
	
	if(n_tot[i]>1){
		int soma = 0;
		for(auto &[ii,ip] : prox[i]){
			ans += n_tot[ip]*rec(ip,t+1);
			soma+=n_tot[ip];
		}
		assert(soma==n_tot[i]);
		ans/=n_tot[i];
	}
	
	rmax(ans,(long double)max_freq[i]/n_tot[i] + rec(0,t+1));
	
	return ans;
}
 
int main(){
	
	vector<string> vsaux;
	
	scanf("%d%d", &T, &n);
	scanf(" ");
	
	fr(i,n){
		char c;
		string s;
		while(1){
			if(scanf("%c",&c)==EOF or c=='\n'){
				vsaux.emplace_back(s);
				resps[i] = s;
				s.clear();
				break;
			} else if(c==' '){
				vsaux.emplace_back(s);
				pergs[i].emplace_back(s);
				s.clear();
			} else{
				s+=c;
			}
		}
	}
	
	comp_str cs(vsaux);
	
	fr(i,n){
		for(auto &s : pergs[i]) perg[i].emplace_back(cs.str_to_int(s));
		resp[i] = cs.str_to_int(resps[i]);
		//prinv(perg[i]);
		//prin(resp[i]);
		//cout << endl;
	}
	
	fr(i,n){
		int cur = 0;
		resp_in_trie[cur].push_back(resp[i]);
		for(auto &c : perg[i]){
			if(!prox[cur].count(c)){
				prox[cur][c] = ++sz;
			}
			cur = prox[cur][c];
			resp_in_trie[cur].push_back(resp[i]);
		}
	}
	
	fr(cur,sz+1){
		sort(all(resp_in_trie[cur]));
		assert(sz(resp_in_trie[cur])>=1);
		int i = 0;
		while(i<sz(resp_in_trie[cur])){
			int freq = 1;
			while(i+1<sz(resp_in_trie[cur]) and resp_in_trie[cur][i]==resp_in_trie[cur][i+1]){
				freq++;
				i++;
			}
			rmax(max_freq[cur],freq);
			i++;
		}
		n_tot[cur] = sz(resp_in_trie[cur]);
		assert(max_freq[cur]<=n_tot[cur] and max_freq[cur]>0);
	}
	
	/*
	fr(cur,sz+1){
		prin(cur);
		prin(n_tot[cur]);
		prin(max_freq[cur]);
		for(auto &[ii,ip] : prox[cur]){
			prin(ip);
		}
		cout << endl;
	}
	*/
	
	dp.resize(sz+1,vector<long double>(T,0));
	vis.resize(sz+1,vector<bool>(T,0));
	
	printf("%.10lf\n", (double)rec(0,0));
}
