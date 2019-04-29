#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

typedef long long ll;
typedef long double ld;

#define eb emplace_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define prin(a) if(debug) cout << #a << " = " << (a) << endl

/*
rodar com crman para ver evolucao (nao requer input)

o que geralmente é necessario mudar oq esta comentado 
ao lado ou abaixo
*/

string f(int tams){
	string s;
	fr(i,tams){
		s+= 'a'+rand()%26;
	}
	
	return s;
}

const int N = 2e5+10;
ll v[N];
FILE *pfile, *pfile1, *pfile2;
//string v[1010];

ll n;

int main(){

	system("g++ -std=c++14 -Wshadow -fsanitize=address -D_GLIBCXX_DEBUG -o prog1 net.cpp"); //alterar nome
	system("g++ -std=c++14 -Wshadow -fsanitize=address -D_GLIBCXX_DEBUG -o prog2 hp.cpp");
	
	srand(time(nullptr));
	
	fr(ii,1000){
		prin(ii);
		
		n = 5 + rand()%2;
	
		pfile = fopen("input","w");
		fprintf(pfile,"%lld\n", n);
	
		fr(i,n){
			v[i] = rand()%10+1; //aumentar %10 se quiser numeros maiores
			//v[i] = f();
			
			fprintf(pfile, "%lld ", v[i]);
			//fprintf(pfile, "%s ", v[i].c_str());
		}
		fprintf(pfile,"\n");
	
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
		
		///*
		//ABRIR input !!!!!!!!!!!!!!!!!!!!!!!
		
		//CHECAR SE input ESTA CORRETO E SE É
		//O MSM DOQ PRINTADO NO TERMINAL
		if(ans1!=ans2 or 1){
			prin(ii);
			cout << n << endl;
			fr(i,n){
				cout << v[i] << " ";
			}
			cout << endl;
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

