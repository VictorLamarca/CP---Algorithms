#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//solves https://codeforces.com/contest/1535/submission/118546615

const int N = 2e5+10;

typedef unsigned long long ull;

ull fpull(ull x, ull e) {
	ull ans = 1;
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

mt19937 rng(time(0));

vector<int> perm;
ull p27[N];
ull inv27[N];

void init_hash(int n){
	fr(i,26) perm.push_back(i+1);
	shuffle(all(perm),rng);
	p27[0] = inv27[0] = 1;
	for(int i = 1; i<n; i++){
		p27[i] = 27*p27[i-1];
		inv27[i] = fpull(p27[i],-1);
	}
}

/*
	Calcula hash de intervalos da string 
		primeira letra é digito menos significativo
		string de lowercase english letters
		Base 27 é usada, cada letra é mapeada para [1,26], nao tem 0
		Modulo é (1<<64) - unsigned long long
*/
struct meuhash{
	vector<ull> pref;
	meuhash(){}
	meuhash(string &s){
		assert(sz(s)<N);
		assert(p27[1]*inv27[1]==1);
		pref.resize(sz(s));
		ull cur = 0;
		fr(i,sz(s)){
			cur += p27[i]*perm[s[i]-'a'];
			pref[i] = cur;
		}
	}
	//intervalo fechado [l,r]
	ull gethash(int l, int r){
		assert(l<=r and l>=0 and l<sz(pref) and r>=0 and r<sz(pref));
		l--;
		ull ans = pref[r];
		if(l>=0){ 
			ans -= pref[l];
			ans *= inv27[l+1];
		}
		return ans;
	}
}; //end hash

vector<ull> mat[610][610];

int fcnt(ull cur, int l, int r){
	return upper_bound(all(mat[l][r]),cur)-lower_bound(all(mat[l][r]),cur);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	init_hash(N);
	
	ll n; cin >> n;
	map<string,vector<string>> mp;
	fr(i,n){
		string s; cin >> s;
		string aux = s;
		sort(all(aux));
		mp[aux].push_back(s);
	}
	
	ll ans = n*(n-1)/2*1337;
	
	for(auto &[s_sort,v] : mp){
		ans -= (ll)sz(v)*(sz(v)-1)/2*1335;
		int tam = sz(v[0]);
		if(sz(v)<=600){
			fr(i,sz(v)) fr(j,i){
				if(i==j) continue;
				int l = 0, r = tam-1;
				while(l<tam and v[i][l]==v[j][l]) l++;
				while(r>=0 and v[i][r]==v[j][r]) r--;
				int ok = 0;
				for(int k = l+1; k<=r; k++){
					if(v[i][k]<v[i][k-1]) break;
					if(k==r) ok = 1;
				}
				if(!ok) for(int k = l+1; k<=r; k++){
					if(v[j][k]<v[j][k-1]) break;
					if(k==r) ok = 1;
				}
				if(ok) ans--;
			}
		} else{
			vector<meuhash> hashes(sz(v));
			fr(i,sz(v)) hashes[i] = meuhash(v[i]);
			fr(r,tam) fr(l,r+1) mat[l][r].clear();
			fr(i,sz(v)){
				fr(r,tam) fr(l,r+1){
					ull cur = 0;
					if(l) cur = hashes[i].gethash(0,l-1);
					if(r<tam-1) cur += p27[l]*hashes[i].gethash(r+1,tam-1);
					mat[l][r].push_back(cur);
				}
			}
			fr(r,tam) fr(l,r+1) sort(all(mat[l][r]));
			fr(i,sz(v)){
				int l = 0;
				while(l<tam){
					int r = l;
					while(r+1<tam and v[i][r+1]>=v[i][r]) r++;
					ull cur = 0;
					if(l) cur = hashes[i].gethash(0,l-1);
					if(r<tam-1) cur += p27[l]*hashes[i].gethash(r+1,tam-1);
					ans-=fcnt(cur,l,r)-1;
					l = r+1;
				}	
			}
		}
	}
	cout << ans << "\n";
}
