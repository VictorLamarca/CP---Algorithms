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

//solves social distancing from ieeextreme 2020

template <class T>
void rmaxid(T &ans, int &id_ans, T cur, int id_cur){
	if(cur>ans){
		ans = cur;
		id_ans = id_cur;
	}
}

const int N = 1e5+10;
vector<int> g[N];

ll subsz[N], somadist[N];

namespace calc_subsz{
void dfs(int no, int from){
	subsz[no] = 1;
	somadist[no] = 1;
	for(auto &it : g[no]){
		if(it==from) continue;
		dfs(it,no);
		subsz[no]+=subsz[it];
		somadist[no] += subsz[it]+somadist[it];
	}
}
};

int n;

ll somadistpai[N];
bool tem2cent = 0;
int cent, paicent;

namespace get_cent{
void dfs(int no, int from){
	ll tot = 0;
	int id_max = -2;
	ll max_somadist = 0;
	for(auto &it : g[no]){
		if(it==from) continue;
		tot += somadist[it];
		rmaxid(max_somadist,id_max,somadist[it],it);
	}
	if(from!=-1){
		tot+= somadistpai[from];
		rmaxid(max_somadist,id_max,somadistpai[from],from);
	}
	
	/*
	prin(no+1);
	prin(id_max+1);
	prin(tot);
	prin(max_somadist);
	cout << endl;
	*/
	
	if(2*max_somadist <= tot or id_max==from){
		cent = no;
		if(id_max==from){
			paicent = from;
			tem2cent = 1;
		}
		return;
	}
	
	assert(id_max!=-2);
	assert(id_max!=from);
	
	somadistpai[no] = somadist[no]-(somadist[id_max]+subsz[id_max]);
	if(from!=-1){
		somadistpai[no] += somadistpai[from]+(n-subsz[no]);
	}
	dfs(id_max,no);
	
}
};

double ans = 0;
namespace get_sum_sq{
void dfs(int no, int from, double dac){
	ans += dac*dac;
	for(auto &it : g[no]){
		if(it==from) continue;
		dfs(it,no,dac+1);
	}
}
};

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	fr(i,n-1){
		int pai; cin >> pai;
		pai--;
		g[pai].push_back(i+1);
		g[i+1].push_back(pai);
	}	
	
	calc_subsz::dfs(0,-1);
	
	/*
	fr(i,n){
		prin(i+1);
		prin(somadist[i]);
	}*/
	
	get_cent::dfs(0,-1);
	
	if(tem2cent){
		ll sda = somadist[cent]-subsz[cent];
		ll sza = subsz[cent];
		
		ll szb = n-subsz[cent];
		ll sdb = somadistpai[paicent]-szb;
		
		double x = (double)(sdb-sda+szb)/(sza+szb);
		if(x<0) x = 0;
		if(x>1) x = 1;
		
		get_sum_sq::dfs(cent,paicent,x);
		double ans_tot = ans;
		ans = 0;
		get_sum_sq::dfs(paicent,cent,1-x);
		ans_tot+=ans;
		
		ans_tot*=n;
		
		cout << fixed << setprecision(10) << ans_tot << "\n";
	} else{
		ans = 0;
		get_sum_sq::dfs(cent,-1,0);
		ans *= n;
		cout << fixed << setprecision(10) << ans << "\n";
	}
	
}
