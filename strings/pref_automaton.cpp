#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//solves https://arena.topcoder.com/#/u/practiceCode/18687/189587/16991/1/335949 - problem: MostSubstrings

const int N = 1e2+10;
/*
	Constroi automato de sufixo da string (usa kmp)
		Para string de tamanho n, ha n+1 estados (de [0,n])
		estado 0 é nada da string e n é tudo da string (estou na ultima letra)
		
	prox[c][i] = proximo estado dado que estou no estado i apos adicionar letra c
	
		note que para string "aaaa"
		prox['a'][4] = 4 (continuo na string completa)
*/
int prox[26][N];

vector<int> fpref(string &s){
	vector<int> pref(s.size());
	
	for(int i = 1; i<sz(s); i++){
		int t = pref[i-1];
		while(t and s[i]!=s[t]) t = pref[t-1];
		if(s[i]==s[t]) t++;
		pref[i] = t;
	}
	return pref;
}

void build_aut(string &s){
	vector<int> pref = fpref(s);
	int n = sz(s);
	vector<int> v(n);
	fr(i,n) v[i] = s[i]-'a';
	fr(c,26) prox[c][0] = 0;
	prox[v[0]][0] = 1;
	for(int i = 1; i<=n; i++){
		fr(c,26){
			prox[c][i] = prox[c][pref[i-1]];
		}
		if(i<n) prox[v[i]][i] = i+1;
	}
}

// end automaton

const ll mod = round(1e9)+7;
struct mb {
	mb(int v = 0) : val(v < 0 ? v + mod : v) {}
	mb(ll v){ val = (v%mod+mod)%mod; }
	int val;
 
	void operator += (mb o) { *this = *this + o; }
	void operator -= (mb o) { *this = *this - o; }
	void operator *= (mb o) { *this = *this * o; }
	mb operator * (mb o) { return (int)((long long) val * o.val % mod); }
	//mb operator / (mb o) { return *this * fp(o, mod - 2); }
	//bool operator == (mb o) { return val==o.val; } //usar soh para hashes
	mb operator + (mb o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	mb operator - (mb o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }
};

const int M = 1e3+10;
mb dp[M][3][N];
int vis[M][3][N];

class MostSubstrings
{
public:
int count(string s, int l) {
	fr(it,l+1) fr(noc,3) fr(is,sz(s)+1) dp[it][noc][is] = 0, vis[it][noc][is] = 0;
	dp[0][0][0] = 1;
	vis[0][0][0] = 1;
	build_aut(s);
	int i0 = 0, i1 = 1;
	fr(it,l){
		bool aumentou = 0;
		for(int noc : {i0,i1}){
			fr(is,sz(s)+1){
				if(!vis[it][noc][is]) continue;
				fr(c,26){
					int js = prox[c][is];
					int poc = noc;
					if(js==sz(s)) poc = (poc+1)%3;
					if(poc!=i0 and poc!=i1) aumentou = 1;
					vis[it+1][poc][js] = 1;
					dp[it+1][poc][js] += dp[it][noc][is];
				}
			}
		}
		if(aumentou){ 
			i0 = (i0+1)%3;
			i1 = (i0+1)%3;
		}
	}
	for(int noc : {i1,i0}){
		mb ans = 0;
		int ok = 0;
		fr(is,sz(s)+1){
			if(vis[l][noc][is]){
				ok = 1;
				ans+=dp[l][noc][is];
			}
		}
		if(ok) return ans.val;
	}
	//assert(0);
	return 0;
}
};

//comment main afterwards
int main(){
	int ans = MostSubstrings().count("aaaa",13);
	prin(ans); //ans = 1

	ans = MostSubstrings().count("helloworld",7);
	prin(ans); //ans = 31810120
	
	ans = MostSubstrings().count("decode",11);
	prin(ans); //ans = 52
}
