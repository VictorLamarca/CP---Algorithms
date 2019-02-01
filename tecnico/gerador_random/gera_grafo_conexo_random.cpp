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
typedef tuple<ll,ll,ll> t3ll;

#define mt make_tuple
#define get(a,id) get<id>(a)

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

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

/*
rodar com crman para ver evolucao (nao requer input)

o que geralmente é necessario mudar oq esta comentado 
ao lado ou abaixo
*/

#define rm (rand()%MOD)
#define rm2 (rm*rm)%(MOD+2)

#define eb emplace_back

string f(int tams){
	string s;
	fr(i,tams){
		s+= 'a'+rand()%26;
	}
	
	return s;
}

const int N = 2e5+10;

FILE *pfile, *pfile1, *pfile2;
//string v[1010];

int n;

int main(){

	system("g++ -std=c++14 -Wshadow -fsanitize=address -D_GLIBCXX_DEBUG -o prog1 i.cpp"); //alterar nome
	system("g++ -std=c++14 -Wshadow -fsanitize=address -D_GLIBCXX_DEBUG -o prog2 tfg.cpp");
	
	srand(time(nullptr));
	
	fr(ii,10000){
		prin(ii);
		
		vector<tuple<int,int,int>> v;
		
		n = 1 + rand()%2000;
		int k = 1 + rand()%min((n-1),(n-1));
		int m = n-1 + rand()%( min(n*(n-1)/2,2000) - (n-1) + 1);
		const int MAXV = 1e8;
		
		assert(m>=n-1);
		
		//assert(m<=40);
		
		pfile = fopen("input","w");
		fprintf(pfile,"%d %d %d\n", n, m, k);
		
		/*
		vector<int> v0;
		frr(i,2,n) v0.eb(i);
		random_shuffle(all(v0));
		
		fr(cnt,k){
		    assert(cnt<v0.size());
		    int a = 1, b = v0[cnt];
		    int c = 1 + rand()%1000;
		    fprintf(pfile,"%d %d %d\n", a, b, c);
		    v.eb(a,b,c);
		}
		*/
		
		vector<pii> vr;
	    
	    frr(i,1,n){
	        frr(j,i+1,n){
	            vr.eb(i,j);
	        }
	    }
	    
	    random_shuffle(all(vr));
	    
	    set<pii> s;
	    frr(i,2,n){
	        int a = 1 + rand()%(i-1), b = i;
	        pii par(a,b);
	        s.insert(par);
	        int c = 1 + rand()%MAXV;
		    fprintf(pfile,"%d %d %d\n", a, b, c);
		    v.eb(a,b,c);
	    }
	    
	    int idr = 0;
	    fr(cnt,m - (n-1) ){
	        int a, b;
	        while(s.count(vr[idr])) idr++;
	        assert(idr<vr.size());
	        tie(a,b) = vr[idr++];
		    int c = 1 + rand()%MAXV;
		    fprintf(pfile,"%d %d %d\n", a, b, c);
		    v.eb(a,b,c);
	    }
	
		fclose(pfile);
	
		system("./prog1 < input > a1");
		system("./prog2 < input > a2");
	
		pfile1 = fopen("a1","r");
		pfile2 = fopen("a2","r");
	
		ll ans1, ans2;
		//vector<ll> ans1(n), ans2(n);
		
		///*
		fscanf(pfile1,"%lld", &ans1);
		fscanf(pfile2,"%lld", &ans2);
		//*/
		
		
		/*
		//fscanf(pfile1,"%*d"); //caso no output seja printado n
		//fscanf(pfile2,"%*d");
		
		fr(i,n){
			fscanf(pfile1,"%lld", &ans1[i]);
		}
		
		fr(i,n){
			fscanf(pfile2,"%lld", &ans2[i]);
		}
		//*/
	
		fclose(pfile1);
		fclose(pfile2);
		
		/*prin(n);
		prin(m);
		prin(k);
		prin(ans2);*/
		
		///*
		//ABRIR input !!!!!!!!!!!!!!!!!!!!!!!
		
		//CHECAR SE input ESTA CORRETO E SE É
		//O MSM DOQ PRINTADO NO TERMINAL
		if(ans1!=ans2 or 1){
			prin(ii);
			cout << n << " " << m << " " << k << endl;
			fr(i,m){
			    int a, b, c;
			    tie(a,b,c) = v[i];
				cout << a << " " << b << " " << c << endl;
			}
			goto end;
		}
		//*/
		
		/*
		bool dif = 0;
		fr(i,n){
			if(ans1[i]!=ans2[i]) dif = 1;
		}
	
		if(dif or 1){
			cout << n << endl;
			fr(i,n){
				cout << v[i] << " ";
			}
			cout << endl;
			goto end;
		}
		//*/
	
	}
	
	end:
	return 0;
}

