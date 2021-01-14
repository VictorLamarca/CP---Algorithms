#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;
typedef unsigned long long ull;

#define rmin(a,b) a = min<ll>(a,b)
#define rmax(a,b) a = max<ll>(a,b)

#define fi first
#define se second

//solves https://codeforces.com/contest/1466/problem/G

const int N = 2e6+10;

template <class T>
T fp(T x, long long e) {
	T ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

template <class T>
T fp2(T base, T exp){
	if(exp==0) return T(1);
	T mid = fp(base,exp/2);
	if(exp%2) return mid*mid*base;
	return mid*mid;
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
	//mb operator / (mb o) { return *this * fp(o, mod - 2); }
	//bool operator == (mb o) { return val==o.val; } //usar soh para hashes
	mb operator + (mb o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	mb operator - (mb o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }
};

ll n, q;
string s0, t;

vector<ull> perm;
ull p27[N];
ull inv27[N];

struct meuhash{
	vector<ull> pref;
	meuhash(string &s){
		assert(sz(s)<N);
		assert(p27[1]*inv27[1]==1);
		ull cur = 0;
		fr(i,sz(s)){
			cur = cur + p27[i]*perm[s[i]-'a'];
			pref.push_back(cur);
		}
	}
	
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
};

vector<int> matid[30];
vector<mb> matpref[30];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> q; 
	cin >> s0 >> t;
	
	srand(time(0));
	
	//init hash
	fr(i,26) perm.push_back(i+1);
	random_shuffle(all(perm));
	p27[0] = inv27[0] = 1;
	for(int i = 1; i<N; i++){
		p27[i] = 27*p27[i-1];
		inv27[i] = fp2(p27[i],((ull)0)-1);
	}
	
	
	//calcular mats
	fr(i,sz(t)){
		int ic = t[i]-'a';
		mb cnt;
		if(!matpref[ic].empty()){
			cnt = matpref[ic].back();
			ll dif = i+1-matid[ic].back();
			cnt *= fp(mb(2),dif);
			cnt += 1;
		} else{
			cnt = 1;
		}
		matid[ic].push_back(i+1);
		matpref[ic].push_back(cnt);
	}
	
	fr(qq,q){
		ll id_f; string w; cin >> id_f >> w;
		string s = s0;
		ll id_i = 0;
		while(sz(s)<sz(w) and id_i<id_f){
			s = s + t[id_i] + s;
			id_i++;
		}
		if(sz(s)<sz(w)){
			cout << 0 << "\n";
			continue;
		}
		meuhash hs(s), hw(w);
		mb ans_cont = 0;
		
		fr(i,sz(s)-sz(w)+1){
			if(hs.gethash(i,i+sz(w)-1)==hw.gethash(0,sz(w)-1)) ans_cont+=1;
		}
		ll dif = id_f-id_i;
		ans_cont *= fp(mb(2),dif);
		
		mb ans_add = 0;		
		vector<mb> addc(26);
		fr(i,sz(w)){
			if(i){
				if(hw.gethash(0,i-1)!=hs.gethash(sz(s)-i,sz(s)-1)) continue;
			}
			if(i<sz(w)-1){
				if(hw.gethash(i+1,sz(w)-1)!=hs.gethash(0,sz(w)-i-2)) continue;
			}
			int ic = w[i]-'a';
			addc[ic] += 1;
		}
		fr(ic,26){
			if(matid[ic].empty()) continue;
			mb addcur = 0, subcur = 0;
			int iif = upper_bound(all(matid[ic]),id_f) - matid[ic].begin();
			if(iif==0) continue;
			iif--;
			ll diff = id_f-matid[ic][iif];
			addcur = matpref[ic][iif]*fp(mb(2),diff);
			
			int iii = upper_bound(all(matid[ic]),id_i) - matid[ic].begin();
			if(iii>0){ 
				iii--;
				ll difi = id_f-matid[ic][iii];
				subcur = matpref[ic][iii]*fp(mb(2),difi);
			}
			
			addcur -= subcur;
			ans_add += addcur*addc[ic];
		}
		
		mb ans = ans_cont + ans_add;
		cout << ans.val << "\n";
	}
}
