#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef tuple<ll,ll,ll> t3ll;

#define mt make_tuple
#define get(a,id) get<id>(a)

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define print(tup) if(debug) cout << #tup << " = {" << get(tup,0) << ", " << get(tup,1) << ", " << get(tup,2) << "}\n"
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

const int N = 1e5+10;

int pre[N];

vector<int> tot;

/*
Problema de achar Longest nondecreasing subsequence
Q é usado para achar maior subsequencia unimodal
(só sobe uma vez e depois desce (pode repetir numeros)

CF 468 - Prob C div 1
http://codeforces.com/contest/930/problem/C
*/

int li[N], ld[N];

int main(){
	//FILE_IN FILE_OUT
	int n, m;
	cin >> n >> m;
	
	fr(i,n){
		int l, r;
		scanf("%d%d", &l, &r);
		pre[l]++;
		pre[r+1]--;
	}
	
	
	int cur = 0;
	frr(i,1,m){
		cur+=pre[i];
		tot.pb(cur);
	}
	
	map<int,int> mp;
	
	//--------------------------------------------
	//ESSA é a parte que pega o LIS (na vdd longest nondecreasing subsequence
	
	fr(i,m){
		int cur = 0;
		if(mp.count(tot[i])){
			cur = mp[tot[i]]+1;
			mp[tot[i]]++;
		}
		else{
			auto it = mp.upper_bound(tot[i]);
			if(it!=mp.begin()){
				it--;
				cur = it->se;
			}
			cur++;
			mp[tot[i]] = cur;
		}
		for(auto it = ++mp.find(tot[i]);it!=mp.end();){
			if(it->se>cur) break;
			it = mp.erase(it);
		}
		li[i] = (--mp.end())->se;
	}
	
	//---------------------------------------------------------
	
	reverse(all(tot));
	mp.clear();
	
	fr(i,m){
		int cur = 0;
		if(mp.count(tot[i])){
			cur = mp[tot[i]]+1;
			mp[tot[i]]++;
		}
		else{
			auto it = mp.upper_bound(tot[i]);
			if(it!=mp.begin()){
				it--;
				cur = it->se;
			}
			cur++;
			mp[tot[i]] = cur;
		}
		for(auto it = ++mp.find(tot[i]);it!=mp.end();){
			if(it->se>cur) break;
			it = mp.erase(it);
		}
		ld[m-1-i] = (--mp.end())->se;
	}
	
	int ans = 0;
	
	fr(i,m){
		ans = max(ans,li[i]+ld[i+1]);
	}
	
	cout << ans << endl;
	
	return 0;
}

