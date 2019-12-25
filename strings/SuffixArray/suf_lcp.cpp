#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
typedef long long ll;

//solves https://www.codechef.com/problems/ANUSAR

const int N = 2e5+10;

vector<int> make_suf(string s){
	s+=(char)0;
	int n = s.size();
	vector<int> p(n), c(n), cnt(max(256,n));
	
	fr(i,n) cnt[s[i]]++;
	for(int i = 1; i<256; i++) cnt[i]+=cnt[i-1];
	fr(i,n) p[--cnt[s[i]]] = i;
	int nc = 1;
	for(int i = 1; i<n; i++){
		if(s[p[i]]!=s[p[i-1]]) nc++;
		c[p[i]] = nc-1;
	}
	
	vector<int> pn(n), cn(n);
	for(int k = 0; (1<<k)<n; k++){
		fr(i,n) pn[i] = (p[i]-(1<<k)+n)%n;
		fr(i,nc) cnt[i] = 0;
		fr(i,n) cnt[c[i]]++;
		for(int i = 1; i<nc; i++) cnt[i]+=cnt[i-1];
		for(int i = n-1; i>=0; i--) p[--cnt[c[pn[i]]]] = pn[i];
		nc = 1;
		cn[p[0]] = 0;
		for(int i = 1; i<n; i++){
			int v1 = n*c[p[i]] + c[(p[i]+(1<<k))%n];	
			int v2 = n*c[p[i-1]] + c[(p[i-1]+(1<<k))%n];
			if(v1!=v2) nc++;
			cn[p[i]] = nc-1;
		}
		c = cn;
	}
	p.erase(p.begin());
	
	return p;
}

vector<int> make_lcp(string &s, vector<int> &p){
	int n = s.size();
	vector<int> rank(n), lcp(n-1);
	
	fr(i,n) rank[p[i]] = i;
	
	int k = 0;
	fr(i,n){
		if(rank[i]==n-1){
			k = 0;
			continue;
		}
		int j = p[rank[i]+1];
		while(i+k<n and j+k<n and s[i+k]==s[j+k]) k++;
		lcp[rank[i]] = k;
		if(k) k--;
	}
	return lcp;
}

vector<int> p, lcp;

ll ans[N];
ll ac[N], l[N], r[N];
string s;

void reset(){
	int n = s.size();
	for(int i = 1; i<=n+1; i++){
		ac[i] = 0;
		ans[i] = 0;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	fr(tt,t){
		
		cin >> s;
		
		reset();
		
		p = make_suf(s);
		lcp = make_lcp(s,p);
		
		int n = s.size();
		
		stack<pair<int,int>> st;
		
		fr(i,n-1){
			int ia = i;
			while(!st.empty() and st.top().first>=lcp[i]){
				ia = st.top().second;
				st.pop();
			}
			l[i] = ia;
			st.emplace(lcp[i],ia);
		}
		
		while(!st.empty()) st.pop();
		
		for(int i = n-2;i>=0;i--){
			int ia = i;
			while(!st.empty() and st.top().first>=lcp[i]){
				ia = st.top().second;
				st.pop();
			}
			r[i] = ia;
			st.emplace(lcp[i],ia);
		}
		
		set<tuple<ll,ll,ll>> stam;
		
		fr(i,n-1) stam.emplace(l[i],r[i],lcp[i]);
		
		for(auto &tup : stam){
			ll lcpi, li, ri;
			tie(li,ri,lcpi) = tup;
			ll mult = lcpi;
			if(li){
				mult = min<ll>(mult,lcpi-lcp[li-1]);
			}
			if(ri<n-2){
				mult = min<ll>(mult,lcpi-lcp[ri+1]);
			}
			ac[ri-li+2] += mult*(ri-li+2);
		}
		
		for(int i = n; i>=2; i--){
			ans[i] = ans[i+1]+ac[i];
		}
		ans[1] = (ll)n*(n+1)/2;
		
		int q;
		cin >> q;
		fr(qq,q){
			int rep;
			cin >> rep;
			cout << ans[rep] << endl;
		}
	}
}
