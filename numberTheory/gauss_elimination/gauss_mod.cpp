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

//solves: https://codeforces.com/gym/102861/problem/K
 
template <class T>
T fp(T x, long long e) {
	T ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}
 
const ll mod = 2;
struct mb {
	mb(int v = 0) : val(v < 0 ? v + mod : v) {}
	mb(ll v){ val = (v%mod+mod)%mod; }
	int val;
 
	void operator += (mb o) { *this = *this + o; }
	void operator -= (mb o) { *this = *this - o; }
	void operator *= (mb o) { *this = *this * o; }
	mb operator * (mb o) { return (int)((long long) val * o.val % mod); }
	mb operator / (mb o) { return *this * fp(o, mod - 2); }
	//bool operator == (mb o) { return val==o.val; } //usar soh para hashes
	mb operator + (mb o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	mb operator - (mb o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }
};
 
/*
	retorno:
		0 - sem solução
		1 - uma solução
		2 - infinitas soluções
		
	resolve sistma - acha X para
		a*X = b
	nos parametros da funcao, b é a ultima coluna da matriz a
*/
int gauss (vector < vector<mb> > a, vector<mb> & ans) {
    int n = sz(a), m = sz(a[0])-1;
 
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (a[i][col].val > a[sel][col].val)
                sel = i;
        if (a[sel][col].val==0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;
 
        for (int i=0; i<n; ++i)
            if (i != row) {
                mb c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }
 
    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        mb sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if( sum.val != a[i][m].val)
        	return 0;
    }
 
    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}
 
const int N = 210;
vector<int> g[N];
 
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m; cin >> n >> m;
	
	fr(i,m){
		int u, v; cin >> u >> v; u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	vector<vector<mb>> mat(n,vector<mb>(n+1));
	
	fr(i,n){
		vector<mb> &v = mat[i];
		if(sz(g[i])%2==1){
			v[i] = 1;
			for(auto &it : g[i]){
				v[it] = 1;
			}
		} else{
			for(auto &it : g[i]){
				v[it] = 1;
			}
			v[n] = 1;
		}
	}
	
	vector<mb> ans;
	if(gauss(mat,ans)>=1) cout << "Y" << "\n";
	else cout << "N\n";
}
