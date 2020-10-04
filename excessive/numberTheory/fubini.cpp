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

const int mod = round(1e9)+7;

template <class T>
T fp(T x, long long e) {
	T ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

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

int n;

mb dp[10][10];
int vis[10][10];

int tamv;
vector<int> vr[10];

int n_range;
int A[10];
int id_range[10];
int tam_range[10];
int up_to_range[10];

mb prob_in_range(int iv_range, int i_need_range){
	if(iv_range<i_need_range) return 0;
	return mb(tam_range[i_need_range])/up_to_range[iv_range];
}

mb fat[10], invfat[10], mypow[10][10], invpow[10][10];

mb prob_nck(int i_range, int k){
	if(tam_range[i_range]<k) return 0;
	
	mb ans = 1;
	fr(i,k) ans*=(tam_range[i_range]-i);
	ans *= invfat[k];
	ans *= invpow[i_range][k];
	
	return ans;
}	

mb rec(int i_pos, int i_range){
	if(i_pos==tamv) return 1;
	if(i_range==n_range) return 0;
	mb &ans = dp[i_pos][i_range];
	if(vis[i_pos][i_range]) return ans;
	
	ans = 0;
	vis[i_pos][i_range] = 1;
	
	mb prob = 1;
	for(int cip = i_pos; cip<tamv; cip++){
		for(auto &ir : vr[cip]){
			prob *= prob_in_range(ir,i_range);
		}	
		prob *= invpow[i_range][sz(vr[cip])-1];
		if(prob.val==0) break;
		ans += prob*prob_nck(i_range,cip-i_pos+1)*rec(cip+1,i_range+1);
	}
	ans += rec(i_pos,i_range+1);
	
	return ans;
}

mb calc_dp(vector<int> v, int maxv){
	memset(vis,0,sizeof(vis));
	tamv = maxv+1;
	fr(i,sz(v)){ 
		vr[v[i]].push_back(id_range[i]);
	}
	
	mb ans = rec(0,0);
	fr(i,tamv) vr[i].clear();
	
	int max_lis = 0;
	vector<int> tam_lis(n);
	fr(i,n){
		tam_lis[i] = 1;
		fr(j,i){
			if(v[i]>v[j]) rmax(tam_lis[i],1+tam_lis[j]);
		}
		rmax(max_lis,tam_lis[i]);
	}
	return ans*max_lis;
}

mb ans(0);

//generate fubini
int vf[10];
void fubini(int id, int maxv){
	if(id==n){
		vector<int> v(vf,vf+n);
		do{
			//do something with fubini instance here
			ans += calc_dp(v,maxv);
		} while(next_permutation(all(v)));
		return;
	}
	
	vf[id] = maxv;
	fubini(id+1,maxv);
	
	if(id){
		vf[id] = maxv+1;
		fubini(id+1,maxv+1);
	}
}

// solves https://atcoder.jp/contests/arc104/tasks/arc104_e

int main(){

	fat[0] = 1;
	invfat[0] = 1;
	for(int i = 1; i<10; i++){
		fat[i] = fat[i-1]*i;
		invfat[i] = mb(1)/fat[i];
	}

	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	
	{
	map<int,int> mp;
	fr(i,n) cin >> A[i], mp[A[i]];
	int cnt = 0;
	for(auto &par : mp){
		par.se = cnt++;
	}

	n_range = sz(mp);
	fr(i,n) id_range[i] = mp[A[i]];
	
	{
		int id = 0;
		for(auto &par : mp){
			up_to_range[id++] = par.fi;
		}
		
		fr(i,n_range){
			tam_range[i] = up_to_range[i];
			if(i) tam_range[i]-=up_to_range[i-1];
		}
	}
	
	fr(ir,n_range){
		mypow[ir][0] = 1;
		invpow[ir][0] = 1;
		for(int i = 1; i<=6; i++){
			mypow[ir][i] = mypow[ir][i-1]*tam_range[ir];
			invpow[ir][i] = mb(1)/mypow[ir][i];
		}
	}
	}
	
	fubini(0,0);
	
	cout << ans.val << "\n";
}
