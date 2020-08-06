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

//solves prob F1 of https://codeforces.com/group/j1UosVRZar/contest/288543/standings

struct frac{
	ll a = 0, b = 1;
	frac(){}
	frac(ll x){
		a = x, b = 1;
	}
	frac(ll _a, ll _b){
		a = _a, b = _b;
		assert(b);
		ll g = __gcd(a,b);
		a/=g, b/=g;
		if(b<0) a*=-1, b*=-1;
	}
	frac operator +(const frac &o){
		return frac( a*o.b + o.a*b, b*o.b);
	}
	frac operator -(const frac &o){
		return frac( a*o.b - o.a*b, b*o.b);
	}
	frac operator *(const frac &o){
		return frac(a*o.a, b*o.b);
	}
	frac operator /(const frac &o){
		return frac(a*o.b, b*o.a);
	}
	void print(string s){
		cout << s << ": " << a << "/" << b << endl;
	}
};

vector<frac> interpolate(vector<frac> x, vector<frac> y) {
	int n = sz(x);
	assert(sz(y)==sz(x));
	vector<frac> res(n), temp(n);
	fr(k,n-1) for(int i = k+1; i<n; i++) 
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	frac last(0,1); temp[0] = frac(1,1);
	fr(k,n) fr(i,n){
		res[i] = res[i] + y[k] * temp[i];
		swap(last, temp[i]);
		temp[i] = temp[i] - last * x[k];
	}
	return res;
}

struct node{
	bool eh_for = 0;
	char iter, range;
	node(){}
	node(char _iter, char _range){
		iter = _iter;
		range = _range;
		eh_for = 1;
	}
};

const int N = 1e5+10;

int pai[N];
vector<int> g[N];
vector<node> nos;

void ae(int no, int it, node curno){
	g[no].push_back(it);
	pai[it] = no;
	nos.push_back(curno);
}

int val_variavel[256];

ll dfs(int no){
	if(!nos[no].eh_for) return 1;
	int range;
	if(isdigit(nos[no].range)) range = nos[no].range-'0';
	else range = val_variavel[nos[no].range];
	
	ll ans = 0;
	
	fr(i,range){
		val_variavel[nos[no].iter] = i;
		for(auto &it : g[no]) ans+=dfs(it);
	}
	
	return ans;
}

int main(){
	//freopen("fygon.in","r",stdin);
	//freopen("fygon.out","w",stdout);
	
	vector<string> vs;
	{
	string curs;
	char c;
	while(scanf("%c", &c)!=EOF){
		if(c=='\n'){
			vs.push_back(curs);
			curs.clear();
		} else{
			curs+=c;
		}
	}
	if(!curs.empty()) vs.push_back(curs);
	}
	
	int cur_pai = 0;
	int cur_no = 0;
	int lvl_pai = -1;
	nos.emplace_back(node(1,'1'));
	
	for(auto &s : vs){
		int i = 0;
		cur_no++;
		int cur_lvl = 0;
		while(s[i]==' '){
			i+=4;
			cur_lvl++;
		}
		
		while(cur_lvl<lvl_pai+1){
			cur_pai = pai[cur_pai];
			lvl_pai--;
		}
		
		node vno;
		if(s[i]!='f'){
			assert(s[i]=='l');
		} else{
			vno = node(s[i+4],s[i+15]);
			//prin(s[i+4]);
			//prin(s[i+15]);
		}
		
		//prin(vno.eh_for);
		ae(cur_pai, cur_no, vno);
		
		cur_pai = cur_no;
		lvl_pai = cur_lvl;
	}
	
	vector<frac> x, y;
	
	for(int n = 0; n<=6; n++){
		val_variavel['n'] = n;
		x.emplace_back(n);
		
		y.emplace_back(dfs(0));
	}
	
	vector<frac> ans = interpolate(x,y);
	vector<string> ss(1);
	ss.emplace_back("n");
	fr(i,5) ss.emplace_back(ss.back()+"*n");
	
	string sans;
	fr(i,7){
		if(ans[i].a){
			
			if(ans[i].a<0){
				sans+=" - ";
			} else if(!sans.empty()){
				sans+=" + ";
			}
			
			sans+=to_string(abs(ans[i].a));
			if(ans[i].b!=1) sans+="/", sans+=to_string(ans[i].b);
			
			if(!ss[i].empty()){
				sans+="*";
				sans+=ss[i];
			}
		}
	}
	
	cout << sans << "\n";
	
}
