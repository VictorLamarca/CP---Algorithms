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

//solves https://acm.timus.ru/problem.aspx?space=1&num=1989

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
	int val;
 
	void operator += (mb<mod> o) { *this = *this + o; }
	void operator -= (mb<mod> o) { *this = *this - o; }
	void operator *= (mb<mod> o) { *this = *this * o; }
	bool operator == (mb<mod> o) { return val==o.val; }
	mb<mod> operator * (mb<mod> o) { return (int)((long long) val * o.val % mod); }
	mb<mod> operator / (mb<mod> o) { return *this * fp(o, mod - 2); }
	mb<mod> operator + (mb<mod> o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	mb<mod> operator - (mb<mod> o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }
};

template<class T> struct Seg{
	int n;
	vector<T> s;
	
void build(){
	for(int i = n-1;i>0;i--){ 
		//s[i] = min(s[i<<1],s[i<<1|1]);
		s[i] = s[i<<1]+s[i<<1|1];
	}
}

Seg(vector<T> v){
	n = sz(v);
	s = vector<T>(2*n);
	for(int i = n; i<2*n; i++) s[i] = v[i-n];
	build();
}

//pos 0-indexed (atualiza, nao incrementa)
void upd(int pos, T val){
	for(s[pos+=n]=val;pos>1;pos>>=1) 
		//s[pos>>1] = min(s[pos],s[pos^1]);
		s[pos>>1] = s[pos]+s[pos^1];
}

//array é abstraido para 0-indexed (nas folhas da seg) e [l,r)
T qry(int l, int r){
	T ans = T(0);
	//T ans = T(LLONG_MAX);
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = ans+s[l++];
		if(r&1) ans = ans+s[--r];
		//if(l&1) ans = min(ans,s[l++]);
		//if(r&1) ans = min(ans,s[--r]);
	}
	return ans;
}
	
};

mb<> val[256];
const int N = 1e5+10;
mb<> p27[N];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	srand(time(0));
	for(int i = 'a'; i<='z'; i++) val[i] = mb<>(i-'a'+1);
	random_shuffle(val+'a',val+'z'+1);
	
	p27[0] = 1;
	
	for(int i = 1; i<N; i++) p27[i] = mb<>(27)*p27[i-1];
		
	string s;
	cin >> s;
	
	vector<mb<>> vl(sz(s)), vr(sz(s));
	
	fr(i,sz(s)){
		vl[i] = val[s[i]]*p27[i];
	}
	
	for(int i = sz(s)-1; i>=0; i--){
		vr[i] = val[s[i]]*p27[sz(s)-1-i];
	}
	
	Seg<mb<>> segl(vl), segr(vr);
	
	int q; cin >> q;
	fr(qq,q){
		string tipo; cin >> tipo;
		if(tipo[0]=='p'){ //qry
			int l, r; cin >> l >> r; l--;
			int tam = r-l;
			if(tam==1 or segl.qry(l,l+tam/2)/p27[l]==segr.qry(r-tam/2,r)/p27[sz(s)-r]) cout << "Yes\n";
			else cout << "No\n";
		} else{
			int i; char c; cin >> i >> c; i--;
			s[i] = c;
			segl.upd(i,val[c]*p27[i]);
			segr.upd(i,val[c]*p27[sz(s)-1-i]);
		}
	}
}
