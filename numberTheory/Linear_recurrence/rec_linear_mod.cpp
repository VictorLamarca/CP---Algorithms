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

//solves https://codeforces.com/gym/102644/problem/G

const ll MOD = round(1e9)+7;

template <class T>
T fp(T x, long long e) {
	T ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

template <int mod = MOD>
struct mb {
	mb(int v = 0) : val(v < 0 ? v + mod : v) {}
	mb(ll v){ val = (v%mod+mod)%mod; }
	int val;
 
	void operator += (mb<mod> o) { *this = *this + o; }
	void operator -= (mb<mod> o) { *this = *this - o; }
	void operator *= (mb<mod> o) { *this = *this * o; }
	mb<mod> operator * (mb<mod> o) { return (int)((long long) val * o.val % mod); }
	//mb<mod> operator / (mb<mod> o) { return *this * fp(o, mod - 2); }
	//bool operator == (mb<mod> o) { return val==o.val; } //usar soh para hashes
	mb<mod> operator + (mb<mod> o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	mb<mod> operator - (mb<mod> o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }
};

vector<vector<mb<>>> mm(vector<vector<mb<>>> a, vector<vector<mb<>>> b){
    int l = sz(a);
	int c = sz(b[0]);
	assert(sz(a[0])==sz(b));
	
	vector<vector<mb<>>> ans(l,vector<mb<>>(c));
	fr(i,l){
		fr(j,c){
			fr(k,a[0].size()){
				ans[i][j] += a[i][k]*b[k][j];
			}
		}
	}
	
	return ans;
}

/*
    Eleva matriz a um expoente que deve ser >=1
    se for zero deveria retornar matriz identidade
*/
vector<vector<mb<>>> em(vector<vector<mb<>>> a, ll exp){
	if(exp==1) return a;
	vector<vector<mb<>>> mid = em(a,exp/2);
	if(exp%2) return mm(mm(mid,mid),a);
	return mm(mid,mid);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	ll n, k; cin >> n >> k;
	
	vector<mb<>> a(n), coef(n);
	fr(i,n) cin >> a[i].val;
	reverse(all(a));
	fr(i,n) cin >> coef[i].val;
	//reverse(all(coef));
	
	mb<> p,q,r; cin >> r.val >> q.val >> p.val;
	
	if(k<=n-1){
		cout << a[n-1-k].val << "\n";
	} else{
		k-=n-1;
		
		vector<vector<mb<>>> mat(n+3,vector<mb<>>(n+3));
		for(int i = 0; i<n; i++) mat[i][0] = coef[i];
		mat[n][0] = p;
		mat[n+1][0] = q+p*2;
		mat[n+2][0] = r+p+q;
		
		fr(i,n-1) mat[i][i+1] = 1;
		
		mat[n][n] = 1;
		mat[n+1][n] = 2;
		mat[n+2][n] = 1;
		
		mat[n+1][n+1] = 1;
		mat[n+2][n+1] = 1;
		
		mat[n+2][n+2] = 1;
		
		vector<mb<>> a_aux = a;
		a_aux.push_back((n-1)*(n-1));
		a_aux.push_back(n-1);
		a_aux.push_back(1);
		
		vector<vector<mb<>>> a_mat(1,a_aux);
		a_mat = mm(a_mat,em(mat,k));
		
		cout << a_mat[0][0].val << "\n";
	}
}
