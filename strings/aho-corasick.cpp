#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min<ll>(a,b)
#define rmax(a,b) a = max<ll>(a,b)

#define fi first
#define se second

//solves: https://codeforces.com/contest/963/problem/D

struct no{
	int prox[26]; //qual o proximo vertice na trie se por caracter
	int go[26]; //qual proximo vertice no automato (suffix link + pc se nao tiver)
	int p = -1; //vertice do pai
	char pc; //caracter do qual pai atinge vertice atual
	int link = -1; //suffix link
	
	bool is_leaf = 0;
	int id_leaf = -1; //indice da string que eh leaf nesse vertice (nao pode repetir)
	int p_leaf = -2; //vertice na trie que é sufixo da string atual e eh leaf
	
	no(int _p = -1, char _pc = '$'){
		p = _p, pc = _pc;
		fr(i,26) prox[i] = -1, go[i] = -1;
	}
};

vector<no> trie(1);

void add_string(string &s, int ids){
	int v = 0;	
	fr(i,sz(s)){
		int ic = s[i]-'a';
		if(trie[v].prox[ic]==-1){
			trie[v].prox[ic] = sz(trie);
			trie.emplace_back(v,s[i]);
		}
		v = trie[v].prox[ic];
	}
	trie[v].is_leaf = 1;
	trie[v].id_leaf = ids;
}

int go(int v, char c);

int get_link(int v){
	if(trie[v].link==-1){
		if(v==0 or trie[v].p==0) trie[v].link = 0;
		else trie[v].link = go(get_link(trie[v].p),trie[v].pc);
	}
	return trie[v].link;
}

int go(int v, char c){
	int ic = c-'a';
	if(trie[v].go[ic]==-1){
		if(trie[v].prox[ic]!=-1) trie[v].go[ic] = trie[v].prox[ic];
		else if(v==0) trie[v].go[ic] = 0;
		else trie[v].go[ic] = go(get_link(v),c);
	}
	return trie[v].go[ic];
}

const int N = 1e5+10;
int tam[N], k[N];
vector<int> oc[N];

int get_previous_leaf(int v){
	if(trie[v].p_leaf!=-2) return trie[v].p_leaf;
	if(trie[v].is_leaf) return trie[v].p_leaf = v;
	if(v==0) return trie[v].p_leaf = -1;
	return trie[v].p_leaf = get_previous_leaf(get_link(v));
}

void process_all_leaves(int v, int i){
	while(1){
		v = get_previous_leaf(v);
		if(v==-1) return;
		oc[trie[v].id_leaf].emplace_back(i);
		v = get_link(v);
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	string t; cin >> t;
	int q; cin >> q;
	
	fr(qq,q){
		string s; cin >> k[qq] >> s;
		add_string(s,qq);
		tam[qq] = sz(s);
	}
	
	int v = 0;
	fr(i,sz(t)){
		v = go(v,t[i]);
		process_all_leaves(v,i);
	}
	
	fr(qq,q){
		if(sz(oc[qq])<k[qq]){
			cout << -1 << "\n";
		} else{
			int ans = INT_MAX;
			fr(i,sz(oc[qq])-k[qq]+1){
				rmin(ans,
					oc[qq][i+k[qq]-1]-oc[qq][i]);
			}
			ans+=tam[qq];
			cout << ans << "\n";
		}	
	}
}
