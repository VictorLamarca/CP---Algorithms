#include <bits/stdc++.h>
using namespace std;
 
#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;
 
#define fi first
#define se second

//solves https://codeforces.com/contest/1383/problem/A
 
const int N = 256;
int pai[N];

int rep(int u){
	return pai[u]<0? u : pai[u] = rep(pai[u]);
}
 
void merge(int u, int v){
	u = rep(u), v = rep(v);
	if(u!=v){
		if(pai[u]>pai[v]) swap(u,v);
		pai[u]+=pai[v];
		pai[v] = u;
	}
}

int freq[N];
 
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	
	fr(tt,t){
		int n; cin >> n;
		string a, b; cin >> a >> b;
		
		for(char c = 'a'; c<='z'; c++){
			freq[c] = 0;
			pai[c] = -1;
		}
		
		int ok = 1;
		fr(i,n){
			if(a[i]>b[i]) ok = 0;
			else if(a[i]<b[i]){
				freq[a[i]]++;
				freq[b[i]]++;
				merge(a[i],b[i]);
			}
		}
		if(!ok){
			cout << -1 << "\n";
			continue;
		}
		
		int ans = 0;
		for(char c = 'a'; c<='z'; c++){
			if(freq[c] and rep(c)==c) ans+=-pai[c]-1;
		}
		cout << ans << "\n";
	}	
}
