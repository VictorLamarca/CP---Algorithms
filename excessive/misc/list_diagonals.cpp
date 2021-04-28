#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v).size()
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;
#define fi first
#define se second

//solves problem C from: https://arena.topcoder.com/#/u/contests/18645/

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

void build_pref(vector<vector<mb>> &dp, vector<vector<pair<int,int>>> &list_positions, vector<vector<mb>> &list_dp){
 	fr(cor,sz(list_positions)){
 		fr(id,sz(list_positions[cor])){
 			int i, j; tie(i,j) = list_positions[cor][id];
 			list_dp[cor][id] = dp[i][j];
 			if(id) list_dp[cor][id]+=list_dp[cor][id-1];
 		}
 	}
}

class Antiqueen
{
public:
 int countPaths(int R, int C, int N_ITER) {
 	//generate prefix lists from matrix RxC in horizontal, vertical, diagonal principal e secundaria
 	//-------------
 	vector<vector<pair<int,int>>> h_list(R), v_list(C), dsec_list(C+R-1), dprin_list(C+R-1);
 	vector<vector<mb>> h_dp(R), v_dp(C), dsec_dp(C+R-1), dprin_dp(C+R-1); //dp prefix sum
 	vector<vector<int>> cell_to_h(R,vector<int>(C)), cell_to_v(R,vector<int>(C)), cell_to_dprin(R,vector<int>(C)), cell_to_dsec(R,vector<int>(C));
 	//h
 	fr(i,R){
 		fr(j,C){
 			cell_to_h[i][j] = i;
 			h_list[i].emplace_back(i,j);
 			h_dp[i].emplace_back(0);
 		}
 	}
 	//v
 	fr(j,C){
 		fr(i,R){
 			cell_to_v[i][j] = j;
 			v_list[j].emplace_back(i,j);
 			v_dp[j].emplace_back(0);
 		}
 	}
 	//dsec - vai subindo - sentido: //////
 	fr(id,R+C-1){
 		int i = id, j = 0;
 		if(id>=R){
 			j = id-(R-1);
 			i = R-1;
 		}
 		while(1){
 			dsec_list[id].emplace_back(i,j);
 			dsec_dp[id].emplace_back(0);
 			cell_to_dsec[i][j] = id;
 			i--,j++;
 			if(i<0 or j==C) break;
 		}
 	}
 	//dprin - vai descendo - sentido: \\\\\ .
 	fr(id,R+C-1){
 		//enumera diagonais de baixo pra cima
 		int i = (R-1)-id, j = 0;
 		if(id>=R){
 			j = id-(R-1);
 			i = 0;
 		}
 		while(1){
 			dprin_list[id].emplace_back(i,j);
 			dprin_dp[id].emplace_back(0);
 			cell_to_dprin[i][j] = id;
 			i++,j++;
 			if(i==R or j==C) break;
 		}
 	}
 	//----------------
 	
 	vector<vector<mb>> ant_dp(R,vector<mb>(C)), cur_dp(R,vector<mb>(C));
 	
 	mb soma = 0;
 	mb soma_ant = 0;
 	fr(i,R) fr(j,C) ant_dp[i][j] = 1;
 	
 	//build dps
 	soma_ant = 0;
 	fr(i,R) fr(j,C) soma_ant+=ant_dp[i][j];
 	
 	build_pref(ant_dp,h_list,h_dp);
 	build_pref(ant_dp,v_list,v_dp);
 	build_pref(ant_dp,dprin_list,dprin_dp);
 	build_pref(ant_dp,dsec_list,dsec_dp);
 	
 	fr(cnt,N_ITER){
 		fr(i,R) fr(j,C){
 			cur_dp[i][j] = soma_ant+ant_dp[i][j]*3;
 			int id;
 			//h
 			id = cell_to_h[i][j];
 			cur_dp[i][j]-=h_dp[id].back();
 			//v
 			id = cell_to_v[i][j];
 			cur_dp[i][j]-=v_dp[id].back();
 			//dprin
 			id = cell_to_dprin[i][j];
 			cur_dp[i][j]-=dprin_dp[id].back();
 			//dsec
 			id = cell_to_dsec[i][j];
 			cur_dp[i][j]-=dsec_dp[id].back();
 		}
 		swap(cur_dp,ant_dp);
 		
 		//build dps,...
 		soma_ant = 0;
	 	fr(i,R) fr(j,C) soma_ant+=ant_dp[i][j];
	 	build_pref(ant_dp,h_list,h_dp);
	 	build_pref(ant_dp,v_list,v_dp);
	 	build_pref(ant_dp,dprin_list,dprin_dp);
	 	build_pref(ant_dp,dsec_list,dsec_dp);
 		
 		if(cnt==N_ITER-1) soma = soma_ant;
 		
 	}
 	return soma.val;
}
};

//comment main afterwards
int main(){
	int ans = Antiqueen().countPaths(3,3,1);
	prin(ans);
}
