#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;
#define rmax(a,b) a = max<ll>(a,b)
#define fi first
#define se second

/*
	Recebe vector de pares de intervalos [l,r], os ordena
	e retira todos os intervalos que estao contidos na intersecao de
	outros intervalos (ou seja, sao desnecessarios para cobrir o range todo)
*/
vector<pair<int,int>> tirar_contidos(vector<pair<int,int>> vp){
	sort(all(vp));
	vector<pair<int,int>> ans;
	int r_reached = -INT_MAX;
	for(auto &[l,r] : vp){
		if(r<=r_reached) continue;
		while((sz(ans) and l==ans.back().fi) or (sz(ans)>=2 and l-1<=ans[sz(ans)-2].se)) ans.pop_back();
		assert(r>=r_reached);
		rmax(r_reached,r);
		ans.emplace_back(l,r);
	}
	return ans;
}	

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	vector<pair<int,int>> vp;
	vp.emplace_back(1,3);
	vp.emplace_back(3,5);
	vp.emplace_back(4,6);
	vp = tirar_contidos(vp);
	for(auto &[l,r] : vp){
		prin(l);
		prin(r);
		cout << endl;
	}
}
