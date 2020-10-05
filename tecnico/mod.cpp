#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

#define fi first
#define se second

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
	//mb operator / (mb o) { return *this * fp(o, mod - 2); }
	//bool operator == (mb o) { return val==o.val; } //usar soh para hashes
	mb operator + (mb o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	mb operator - (mb o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }
};

/*
//mod com double - usar para debugar para ver se valor faz sentido

struct mb {
	mb(double v = 0) : val(v) {}
	double val;
 
	void operator += (mb o) { *this = *this + o; }
	void operator -= (mb o) { *this = *this - o; }
	void operator *= (mb o) { *this = *this * o; }
	mb operator * (mb o) { return val * o.val; }
	//mb operator / (mb o) { return val/o.val; }
	//bool operator == (mb o) { return val==o.val; }
	mb operator + (mb o) { return val + o.val; }
	mb operator - (mb o) { return val - o.val; }
};
//*/

//solves https://acm.timus.ru/problem.aspx?space=1&num=2030

const int N = 1e5+10;
vector<int> g[N];
vector<int> viz_big[N];
int is_big[N];

mb val[N];
mb inc[N];

int n;
int r;

mb get_val(int no){
	mb ans = val[no];
	if(!is_big[no]){
		for(auto &it : viz_big[no]) ans+=inc[it];
	}
	return ans;
}

int main(){
	//ios::sync_with_stdio(0); cin.tie(0);	
	scanf("%d", &n);
	r = sqrt(n)+0.5;
	
	fr(i,n) scanf("%d", &val[i].val);
	
	fr(i,n-1){
		int a, b; scanf("%d%d", &a, &b); a--,b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	
	fr(i,n){
		if(sz(g[i])>r){ 
			is_big[i] = 1;
			for(auto &it : g[i]){
				viz_big[it].push_back(i);
			}
		}
	}	
	
	int q; scanf("%d", &q);
	
	fr(qq,q){
		int tipo, no; scanf("%d%d", &tipo, &no); no--;
		
		if(tipo==1){
			if(!is_big[no]){
				mb cur_val = get_val(no);
				for(auto &it : g[no]){
					val[it] += cur_val;
				}
			} else{
				for(auto &it : viz_big[no]){
					val[it] += val[no];
				}
				inc[no] += val[no];
			}
		} else{
			printf("%d\n", get_val(no).val);
		}
	}	
}
