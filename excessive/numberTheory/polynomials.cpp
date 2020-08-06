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

//solves https://codeforces.com/group/j1UosVRZar/contest/287404/problem/B

//operations on polynomials (vector) - v[0] is the term without x (least significant first) - easier to fix (get rid of 0s at the end)
void fix(vector<ll> &v){
	while(sz(v)>1 and v.back()==0) v.pop_back();
}
 
vector<ll> soma(vector<ll> &a, vector<ll> &b){
	vector<ll> ans(max<int>(sz(a),sz(b)));
	fr(i,max<int>(sz(a),sz(b))){
		if(i<sz(a)) ans[i]+=a[i];
		if(i<sz(b)) ans[i]+=b[i];
	}
	fix(ans);
	return ans;
}
 
vector<ll> menos(vector<ll> &a, vector<ll> &b){
	vector<ll> ans(max<int>(sz(a),sz(b)));
	fr(i,max<int>(sz(a),sz(b))){
		if(i<sz(a)) ans[i]+=a[i];
		if(i<sz(b)) ans[i]-=b[i];
	}
	fix(ans);
	return ans;
}
 
vector<ll> mult(vector<ll> &a, vector<ll> &b){
	vector<ll> ans(sz(a)+sz(b)-1);
	fr(i,sz(a)){
		fr(j,sz(b)){
			ans[i+j] += a[i]*b[j];
		}
	}
	fix(ans);
	return ans;
}
 
bool check(vector<ll> &v, __int128 raiz){
	__int128 ac = 0;
	__int128 mult = 1;
	fr(i,sz(v)){
		ac += mult*v[i];
		if(i+1==sz(v)) break;
		mult*=raiz;
	}
	return ac == 0;
}
 
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	while(1){
		string s; cin >> s;		
		if(sz(s)==1) break;
		
		char maxc = '1';
		fr(i,sz(s)) if(isdigit(s[i])) maxc = max(maxc,s[i]);
		
		vector<ll> esq(1,0), dir(1,0);
		
		{
		int i = 0;
		while(s[i]!='='){
			vector<ll> ac(1,1);
			while(1){
				vector<ll> cur;
				while(s[i]!='=' and isdigit(s[i])){
					cur.push_back(s[i]-'0');
					i++;
				}
				reverse(all(cur));
				ac = mult(ac,cur);
				if(s[i]=='=' or s[i]=='+') break;
				assert(s[i]=='*');
				i++; //mult
			}	
			esq = soma(ac,esq);
			if(s[i]=='=') break;
			assert(s[i]=='+');
			i++;
		}
		
		assert(s[i]=='=');
		i++;
		
		while(i<sz(s)){
			vector<ll> ac(1,1);
			while(1){
				vector<ll> cur;
				while(i<sz(s) and isdigit(s[i])){
					cur.push_back(s[i]-'0');
					i++;
				}
				reverse(all(cur));
				ac = mult(ac,cur);
				if(i==sz(s) or s[i]=='+') break;
				assert(s[i]=='*');
				i++; //mult
			}	
			dir = soma(ac,dir);
			if(i==sz(s)) break;
			assert(s[i]=='+');
			i++;
		}
		
		
		}
		
		esq = menos(esq,dir);
		
		while(sz(esq)>1 and esq[0]==0){
			vector<ll> aux;
			for(int i = 1; i<sz(esq); i++) aux.push_back(esq[i]);
			esq = aux;
		}
		
		assert(sz(esq));
		if(sz(esq)==1 and esq[0]==0){
			cout << (int)(maxc)-'0'+1 << "+\n";
			continue;
		}
		
		set<ll> ans;
		ll val = abs(esq[0]);
		
		for(ll i = 1; i*i<=val; i++){
			if(i>maxc-'0' and check(esq,i)) ans.insert(i);
			if(val/i > maxc-'0' and check(esq,val/i)) ans.insert(val/i);
		}
		
		if(sz(ans)==0){
			cout << "*\n";
		} else{
			for(auto &it : ans){
				if(it!=*ans.begin()) cout << " ";
				cout << it;
			}
			cout << "\n";
		}
	}
}
