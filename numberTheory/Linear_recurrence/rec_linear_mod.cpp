#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

//solves https://www.urionlinejudge.com.br/judge/en/problems/view/2970

//similar submission: https://codeforces.com/gym/102644/submission/94732323

template <class T>
T fp(T x, long long e) {
	T ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

const ll mod = round(1e9)+7;
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

vector<vector<mb>> mm(vector<vector<mb>> a, vector<vector<mb>> b){
    int l = sz(a);
	int c = sz(b[0]);
	assert(sz(a[0])==sz(b));
	vector<vector<mb>> ans(l,vector<mb>(c));
	fr(i,l){
		fr(j,c){
			fr(k,sz(a[0])){
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
vector<vector<mb>> em(vector<vector<mb>> a, ll exp){
	if(exp==1) return a;
	vector<vector<mb>> mid = em(a,exp/2);
	if(exp%2) return mm(mm(mid,mid),a);
	return mm(mid,mid);
}

int main(){
	//Coeficientes da recorrencia linear decrescente (em mod)
	//f[n] = coef[0]*f[n-1] + coef[1]*f[n-2] + ...
	vector<ll> coef = {6, 999999999, 999999999, 16, 0};
	
	//Valores iniciais originais de forma crescente
	// f[0], f[1], f[2], ...
	vector<ll> vo_int = {2, 24, 96, 416, 1536};
	reverse(all(vo_int));
	
	assert(sz(coef)==sz(vo_int));
	
	vector<mb> vo;
	for(auto &x : vo_int) vo.emplace_back(x);
	
	vector<vector<mb>> mat(sz(vo),vector<mb>(sz(vo)));
	fr(i,sz(vo)){
		mat[i][0] = coef[i];
	}
	fr(i,sz(vo)-1) mat[i][i+1] = 1;
	
	/*
	//Printar matriz
	fr(i,sz(vo)){
		fr(j,sz(vo)) cout << mat[i][j].val << " ";
		cout << endl;
	}
	*/
	
	ll n;
	cin >> n;
	n--; //subtrair se 1-indexado em relacao ao vo
	if(n<sz(vo)){
		n = sz(vo)-1-n;
		cout << vo[n].val << "\n";
		return 0;
	}
	n-=sz(vo)-1;
	vector<vector<mb>> mo;
	mo.emplace_back(vo);
	mo = mm(mo,em(mat,n));
	cout << mo[0][0].val << "\n";
}
