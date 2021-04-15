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

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define trav(a,x) for (auto& a: x)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)

/*
	Implementacao de fft do Benq
		Codigo original em: https://github.com/bqi343/USACO/tree/0efee4d738682218c089e25f94281de5acffa98e/Implementations/content/numerical/Polynomials
	
	Tem versao usando vector<mb> e vector<comple> (double)
*/

const int root = 3, MOD = (119<<23)+1; // 998244353
const double PI = acos(-1.0l);
// For p < 2^30 there is also e.g. (5<<25, 3), (7<<26, 3) 
/// (479<<21, 3) and (483<<21, 5). Last two are > 10^9.
/*
void genRoots(vmi& roots) { // REPLACE DEF OF MOD
	int n = sz(roots); mi r = pow(mi(root),(MOD-1)/n);
	roots[0] = 1; FOR(i,1,n) roots[i] = roots[i-1]*r; }
*/
typedef complex<double> cd; 
typedef vector<cd> vcd;
void genRoots(vcd& roots) { // primitive n-th roots of unity
	int n = sz(roots); double ang = 2*PI/n;
	/// good way to compute these trig functions more quickly?
	F0R(i,n) roots[i] = cd(cos(ang*i),sin(ang*i)); }

int size(int s) { return s > 1 ? 32-__builtin_clz(s-1) : 0; }
template<class T> void fft(vector<T>& a, 
  const vector<T>& rts, bool inv = 0) {
	int n = sz(a);
	for (int i = 1, j = 0; i < n; i++) { 
		int bit = n>>1; for (; j&bit; bit /= 2) j ^= bit;
		j ^= bit; if (i < j) swap(a[i],a[j]);
	} // sort #s from 0 to n-1 by reverse binary
	for (int len = 1; len < n; len *= 2)
		for (int i = 0; i < n; i += 2*len) F0R(j,len) {
			T u = a[i+j], v = a[i+j+len]*rts[n/2/len*j];
			a[i+j] = u+v, a[i+j+len] = u-v;
		}
	if (inv) {
		reverse(1+all(a));
		T i = T(1)/T(n); trav(x,a) x *= i; 
	}
}
template<class T> vector<T> mul(vector<T> a, vector<T> b) {
	if (!min(sz(a),sz(b))) return {};
	int s = sz(a)+sz(b)-1, n = 1<<size(s);
	vector<T> roots(n); genRoots(roots);
	a.resize(n), fft(a,roots); b.resize(n), fft(b,roots);
	F0R(i,n) a[i] *= b[i];
	fft(a,roots,1); a.resize(s); return a;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	vector<double> a = {1,3,2};
	vector<double> b = {1,0,1,1};
	
	//precisa ser vector de complex
	vector<cd> ca, cb;
	fr(i,sz(a)) ca.push_back(cd(a[i],0));
	fr(i,sz(b)) cb.push_back(cd(b[i],0));
	
	vcd ans = mul(ca,cb);
	cout << "ans = ";
	fr(i,sz(ans)){
		cout << ans[i].real() << ",";
	}
	cout << endl;
}
