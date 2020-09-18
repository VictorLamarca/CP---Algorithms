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

const int N = 1e3+10;
mb<> nck[N][N];

int main(){
	nck[0][0] = mb<>(1);
	for(int i = 1; i<N; i++){
		fr(j,i+1){
			nck[i][j] = nck[i-1][j];
			if(j) nck[i][j]+=nck[i-1][j-1];
		}
	}
	
	prin(nck[5][2].val);
}
