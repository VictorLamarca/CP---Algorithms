#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;
typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LLONG_MAX
//-DBL_MAX
//__builtin_popcountll(ll x) - __builtin_popcount(int x)

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define print(tup) if(debug) cout << #tup << " = {" << get(tup,0) << ", " << get(tup,1) << ", " << get(tup,2) << "}\n"
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

const int N = -1;

int main(){
	//FILE_IN FILE_OUT
	vector<string> mat;
	vector<string> v;
	
	bool comAspas = 1;
	
	char c;
	string linha;
	
	while(scanf("%c", &c)!=EOF){
		if(c=='\n'){
			if(linha.size()) mat.pb(linha);
			linha = "";
		} else{
			linha+=c;
		}
	}
	if(linha.size()) mat.pb(linha);
	
	string pal;
	int lastif = 0;
	
	for(auto &l : mat){
		int i = 0;
		
		while(i<l.size()){
			//if(!lastif) pal = "";
			//else lastif = 0;
			pal = "";
			
			while(i<l.size() and isspace(l[i])) i++;
			//while(i<l.size() and (isspace(l[i]) or isdigit(l[i]))) i++;
			while(i<l.size() and !isspace(l[i])) pal+=l[i++];
			
			v.pb(pal);
			//if(pal.size() and pal.back()!='-') v.pb(pal);
			//else if(pal.back()=='-') lastif = 1;
		}
	}
	cout << "vector<string> v = {";
	fr(i,v.size()){
		if(comAspas) printf("\"%s\"%c ", v[i].c_str(), ",}"[i==v.size()-1]);
		else printf("%s%c ", v[i].c_str(), ",}"[i==v.size()-1]);
	}
	printf(";\n");
	
	return 0;
}

