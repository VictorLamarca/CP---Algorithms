#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min(a,b)
#define rmax(a,b) a = max(a,b)

#define fi first
#define se second

const int N = 1e5+10;
ll no_to_pos[N], no_to_val[N];
vector<int> g[N];

ll prox[N];

//solves https://codeforces.com/gym/102441/problem/D

/*
	Cuidado com inicializacao da Seg na main
	
	//???????? - pq preciso por node() no inicializador?
	Seg seg(vector<node>(n,node()));
*/

struct node{
	ll val, no;
	//lembrar de redefinir valor default (para nulo na inicializacao)
	node(ll _val = 0, ll _no = 0) : val(_val), no(_no) {}
};

node oper(node a, node b){
	if(a.val>b.val) return a;
	return b;
}

struct Seg{
	int n;
	vector<node> s;
	
void build(){
	for(int i = n-1;i>0;i--){ 
		s[i] = oper(s[i<<1],s[i<<1|1]);
	}
}

Seg(vector<node> v){
	n = sz(v);
	s = vector<node>(2*n);
	for(int i = n; i<2*n; i++) s[i] = v[i-n];
	build();
}

//pos 0-indexed (atualiza, nao incrementa)
void upd(int pos, node val){
	for(s[pos+=n]=val;pos>1;pos>>=1) 
		s[pos>>1] = oper(s[pos],s[pos^1]);
}

//array é abstraido para 0-indexed (nas folhas da seg) e [l,r)
node qry(int l, int r){
	node ans;
	for(l+=n,r+=n;l<r;l>>=1,r>>=1){
		if(l&1) ans = oper(ans,s[l++]);
		if(r&1) ans = oper(ans,s[--r]);
	}
	return ans;
}
	
};

map<ll,vector<ll>> mp;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, k; cin >> n >> k;
	
	ll vno = 0;
	fr(i,n){
		ll tam; cin >> tam;
		fr(j,tam){
			ll x; cin >> x;
			mp[-x].push_back(vno);
			no_to_pos[vno] = i;
			no_to_val[vno] = x;
			vno++;
		}
	}
	
	//???????? - pq preciso por node() no inicializador?
	Seg seg(vector<node>(n,node()));
	
	ll maxd = 0, sno;
	
	for(auto &par_mp : mp){
		vector<pair<ll,ll>> vupd;
		for(auto &no : par_mp.se){
			int id = no_to_pos[no];
			ll l = id+1, r = id+k+1;
			node cur_node;
			
			if(r>=n){
				r-=n;
				cur_node = oper(seg.qry(l,n),seg.qry(0,r+1));
			} else{
				cur_node = seg.qry(l,r+1);
			}
			if(cur_node.val){
				vupd.emplace_back(cur_node.val+1,no);
				prox[no] = cur_node.no;
			} else{
				vupd.emplace_back(1,no);
				prox[no] = -1;
			}
		}
		
		for(auto &par : vupd){
			ll val, no; tie(val, no) = par;
			int id = no_to_pos[no];
			if(val>maxd and id<=k){
				sno = no;
				maxd = val;
			}
			seg.upd(id,node(val,no));
		}
	}
	
	cout << maxd << "\n";
	while(maxd){
		cout << no_to_pos[sno]+1 << " " << no_to_val[sno] << "\n";
		if(prox[sno]==-1) break;
		sno = prox[sno];
	}
}
