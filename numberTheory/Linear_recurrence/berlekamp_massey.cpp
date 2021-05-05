#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl

typedef long long ll;

const int mod = 1e9+7;

ll mul(ll x, ll y, ll modc){ return (__int128) x * y % modc; }
ll ipow(ll x, ll y, ll p = mod){
 ll ret = 1, piv = x % p;
 while(y){
  if(y&1) ret = mul(ret, piv, p);
  piv = mul(piv, piv, p);
  y >>= 1;
 }
 return ret;
}

//https://github.com/koosaga/DeobureoMinkyuParty/blob/master/teamnote.tex
vector<int> berlekamp_massey(vector<int> x){
 vector<int> ls, cur;
 int lf, ld;
 fr(i,sz(x)){
  ll t = 0;
  fr(j,sz(cur)){
   t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
  }
  if((t - x[i]) % mod == 0) continue;
  if(cur.empty()){
   cur.resize(i+1);
   lf = i;
   ld = (t - x[i]) % mod;
   continue;
  }
  ll k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
  vector<int> c(i-lf-1);
  c.push_back(k);
  for(auto &j : ls) c.push_back(-j * k % mod);
  if(sz(c) < sz(cur)) c.resize(sz(cur));
  fr(j,sz(cur)){
   c[j] = (c[j] + cur[j]) % mod;
  }
  if(i-lf+sz(ls)>=sz(cur)){
   tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
  }
  cur = c;
 }
 for(auto &i : cur) i = (i % mod + mod) % mod;
 return cur;
}

int get_nth(vector<int> rec, vector<int> dp, ll n){
 int m = sz(rec);
 vector<int> s(m), t(m);
 s[0] = 1;
 if(m != 1) t[1] = 1;
 else t[0] = rec[0];
 auto mul = [&rec](vector<int> v, vector<int> w){
  vector<int> ans(2 * sz(v));
  fr(j,sz(v)){
   fr(k,sz(v)){
    ans[j+k] += 1ll * v[j] * w[k] % mod;
    if(ans[j+k] >= mod) ans[j+k] -= mod;
   }
  }
  for(int j=2*sz(v)-1; j>=sz(v); j--){
   for(int k=1; k<=sz(v); k++){
    ans[j-k] += 1ll * ans[j] * rec[k-1] % mod;
    if(ans[j-k] >= mod) ans[j-k] -= mod;
   }
  }
  ans.resize(sz(v));
  return ans;
 };
 while(n){
  if(n & 1) s = mul(s, t);
  t = mul(t, t);
  n >>= 1;
 }
 ll ret = 0;
 fr(i,m) ret += 1ll * s[i] * dp[i] % mod;
 return ret % mod;
}

vector<int> coef; //imprimir vetor coef na main
int guess_nth_term(vector<int> x, ll n){
 if(n < sz(x)) return x[n];
 coef = berlekamp_massey(x);
 if(coef.empty()) return 0;
 return get_nth(coef, x, n);
}

/*
struct elem{int x, y, v;}; // A_(x, y) <- v, 0-based. no duplicate please..
vector<int> get_min_poly(int n, vector<elem> M){ 
 // smallest poly P such that A^i = sum_{j < i} {A^j \times P_j} 
 vector<int> rnd1, rnd2;
 mt19937 rng(0x14004);
 auto randint = [&rng](int lb, int ub){
  return uniform_int_distribution<int>(lb, ub)(rng);
 };
 for(int i=0; i<n; i++){
  rnd1.push_back(randint(1, mod - 1));
  rnd2.push_back(randint(1, mod - 1));
 }
 vector<int> gobs;
 for(int i=0; i<2*n+2; i++){
  int tmp = 0;
  fr(j,n){
   tmp += 1ll * rnd2[j] * rnd1[j] % mod;
   if(tmp >= mod) tmp -= mod;
  }
  gobs.push_back(tmp);
  vector<int> nxt(n);
  for(auto &id : M){
   nxt[id.x] += 1ll * id.v * rnd1[id.y] % mod;
   if(nxt[id.x] >= mod) nxt[id.x] -= mod;
  }
  rnd1 = nxt;
 }
 auto sol = berlekamp_massey(gobs);
 reverse(sol.begin(), sol.end());
 return sol;
}

ll det(int n, vector<elem> M){ 
 vector<int> rnd;
 mt19937 rng(0x14004);
 auto randint = [&rng](int lb, int ub){
  return uniform_int_distribution<int>(lb, ub)(rng);
 };
 fr(i,n) rnd.push_back(randint(1, mod - 1));
 for(auto &i : M){
  i.v = 1ll * i.v * rnd[i.y] % mod;
 }
 auto sol = get_min_poly(n, M)[0];
 if(n % 2 == 0) sol = mod - sol;
 for(auto &i : rnd) sol = 1ll * sol * ipow(i, mod - 2) % mod;
 return sol;
}
*/

int main() {
	//f(n) = coef[0]*f(n-1) + coef[1]*f(n-2) + ...
    
    vector<int> va = {1,1,2,3,5,8};
    //fibonacci - n é 0-indexado
    for(int n = sz(va)-2; n<=sz(va)+5; n++){
    	assert(n>=0);
    	ll fib = guess_nth_term(va, n);
    	cout << "fib[" << n << "] = " << fib << endl;
    }
    prinv(coef);
    
    //used to solve https://codeforces.com/gym/102966/problem/F
    //cout << guess_nth_term({16, 600, 4680, 19904, 61000, 152136, 329280, 642560, 1158624, 1963000, 3162456, 4887360}, 12) << endl;
    
    //to solve subreg https://www.urionlinejudge.com.br/judge/en/problems/view/2970
   // for(int n = 2; n<=15; n++)
    	//cout << guess_nth_term({2, 24, 96, 416, 1536, 5504, 18944, 64000, 212992, 702464, 2301952, 7512064, 24444928}, n) << endl;
}
