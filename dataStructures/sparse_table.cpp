#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define all(v) (v).begin(),(v).end()
typedef long long ll;
#define rmax(a,b) a = max<ll>(a,b)

//solves https://atcoder.jp/contests/arc067/tasks/arc067_d

int log_floor(int n){
	return 31-__builtin_clz(n);
}

ll oper(ll a, ll b){
	return max(a,b);
}

/*
	Sparse table de maximo
		Ou definida de acordo com funcao oper acima
*/
struct sparse_table{
	int exp2;
	int n;
	vector<vector<ll>> mat;
sparse_table(){}
sparse_table(vector<ll> v){
	n = sz(v);
	exp2 = log_floor(n)+1;
	mat.resize(exp2);
	mat[0].resize(n);
	fr(i,n) mat[0][i] = v[i];
	for(int k = 1; k<exp2; k++){
		mat[k].resize(n);
		for(int i = 0; i+(1<<k)<=n; i++){
			mat[k][i] = oper(mat[k-1][i],mat[k-1][i+(1<<(k-1))]);
		}
	}
}
ll qry(int l, int r){
	assert(l<=r and l>=0 and r<n);
	int k = log_floor(r-l+1);
	return oper(mat[k][l],mat[k][r-(1<<k)+1]);
}
}; //end sparse_table

const int N = 5e3+10;
const int M = 210;
sparse_table st[M];
ll ans = 0;
ll pref[N];

ll n, m;

ll dist(ll l, ll r){
	assert(l<=r);
	return pref[l]-pref[r];
}

void rec(ll l, ll r, ll optl, ll optr){
	if(l>=r) return;
	ll id = (l+r)/2;
	ll idc = optl;
	ll resp = 0;
	
	for(int j = optl; j<min(id+1,optr); j++){
		ll cur = -dist(j,id);
		fr(i,m) cur+=st[i].qry(j,id);
		if(cur>resp){
			resp = cur;
			idc = j;
		}
	}
	rmax(ans,resp);
	rec(l,id,optl,idc+1);
	rec(id+1,r,idc,optr);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	fr(i,n-1) cin >> pref[i];
	for(int i = n-2; i>=0; i--) pref[i] = pref[i]+pref[i+1];
	vector<vector<ll>> mat(m,vector<ll>(n));
	fr(i,n) fr(j,m) cin >> mat[j][i];
	
	fr(i,m) st[i] = sparse_table(mat[i]);
	
	rec(0,n,0,n);
	cout << ans << "\n";
}
