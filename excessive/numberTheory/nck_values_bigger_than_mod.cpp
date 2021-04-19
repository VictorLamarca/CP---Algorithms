#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())

typedef long long ll;

//solves https://atcoder.jp/contests/arc117/tasks/arc117_c

const int mod = 3;

ll fp(ll base, ll exp){
	assert(base!=0);
	if(exp==0) return 1;
	ll mid = fp(base,exp/2);
	ll ans = mid*mid%mod;
	if(exp&1) ans = ans*base%mod;
	return ans;
}
//probably works for all, but for sure for mod = 3 only
struct mb{
	ll v, qnt;
	mb(ll x = 0, ll _qnt = 0){
		v= x;
		qnt = _qnt;
	}
	mb operator*(mb o){
		return mb(v*o.v%mod,qnt+o.qnt);
	}
	mb operator/(mb o){
		return mb(v*fp(o.v,mod-2)%mod,qnt-o.qnt);
	}
	ll vdd(){
		ll x = v;
		if(qnt) x = 0;
		return x;
	}
	//ao somar, perde-se informaçao de qnts fator de 3
	mb operator+(mb o){
		return mb((this->vdd()+o.vdd())%mod,0);
	}
};

const int N = 4e5+10;
mb fat[N];

mb nck(ll n, ll k){
	mb ans = fat[n]/fat[n-k]/fat[k];
	return ans;
}

mb val_to_mb(ll x){
	ll qnt = 0;
	while(x%mod==0){
		x/=mod;
		qnt++;
	}
	return mb(x%mod,qnt);
}

int char_to_int[256];
char int_to_char[3];

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	fat[0] = mb(1,0);
	for(int i = 1; i<N; i++){
		fat[i] = val_to_mb(i)*fat[i-1];
	}
	
	int n; cin >> n;
	string s; cin >> s;
	vector<int> v(n);
	char_to_int['R'] = 0;
	char_to_int['B'] = 1;
	char_to_int['W'] = 2;
	int_to_char[0] = 'R';
	int_to_char[1] = 'B';
	int_to_char[2] = 'W';
	fr(i,n) v[i] = char_to_int[(int)s[i]];
	
	mb ans(0,0);
	
	fr(i,n){
		ans = ans+mb(v[i],0)*nck(n-1,i);
	}	
	
	int id = ans.vdd();
	if(n%2==0 and id) id = mod-id;
	cout << int_to_char[id] << "\n";
}
