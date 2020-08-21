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

namespace nck_space{

int n, k;

vector<int> v;
vector<vector<int>> vid;

int nck_too_big(){
	ll ans = 1;
	int kcur = max(k,n-k);
	
	for(ll i = kcur+1; i<=n; i++){
		if(ans>LLONG_MAX/i) return 1;
		ans*=i;
	}
	for(ll i = 2; i<=n-kcur; i++){
		ans/=i;
	}
	
	//complexidade sera da ordem de k*(n choose k)
	return ans*k > 1e7;
}

void rec(int i_val, int i_por){
	if(i_val==n){
		assert(i_por<=k);
		if(i_por!=k) return;
		vid.push_back(v);
		return;
	}
	if(i_por>k) return;
	
	int qnts_falta_por = k-i_por;
	int qnts_falta_val = n-i_val;
	if(qnts_falta_por>qnts_falta_val) return;
	
	if(i_por<k){ 
		v[i_por] = i_val;
		rec(i_val+1,i_por+1);
	}
	rec(i_val+1,i_por);
}

void generate_vid(int _n, int _k){
	n = _n, k = _k;
	assert(n>=k);
	assert(n<=1000 and !nck_too_big());
	
	vid.clear();
	v.resize(k);
	
	rec(0,0);
}

vector<ll> vmask;

void go(int i_val, int i_por){
	if(i_val==n){
		assert(i_por<=k);
		if(i_por<k) return;
		ll mask = 0;
		fr(i,i_por) mask ^= (1<<v[i]);
		vmask.push_back(mask);
		return;
	}
	if(i_por>k) return;
	
	int qnts_falta_por = k-i_por;
	int qnts_falta_val = n-i_val;
	if(qnts_falta_por>qnts_falta_val) return;
	
	if(i_por<k){ 
		v[i_por] = i_val;
		go(i_val+1,i_por+1);
	}
	go(i_val+1,i_por);
}

void generate_masks(int _n, int _k){
	n = _n, k = _k;
	assert(n>=k);
	assert(n<=1000 and !nck_too_big());
	
	vmask.clear();
	v.resize(k);
	
	go(0,0);
}

};

int main(){
	//gera vetor de vetores onde cada um tem tamanho k, e 0<=v[i]<n
	nck_space::generate_vid(7,3);
	vector<vector<int>> mat = nck_space::vid;
	
	//gera vetor de mascaras de tamanho n e k bits ativos
	nck_space::generate_masks(4,2);
	vector<int> vm(all(nck_space::vmask));
	
	for(auto &v: mat){
		prinv(v);
	}
	
	for(auto &mask : vm){
		prin(bitset<4>(mask));
	}
}
