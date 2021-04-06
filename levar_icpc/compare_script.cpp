#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

/*
Qnd o programa parar eh pq o caso q da diferente esta no arquivo input
*/

string gera_string(int tams){
	string s;
	fr(i,tams){
		s+= 'a'+rand()%26;
	}
	
	return s;
}

ll gera(ll minx, ll maxx){
	assert(maxx>=minx);
	return minx + rand()%(maxx-minx+1);
}

/*
	Gera vetor de pares de tamanho n-1 com valores de [1,n]
	que representam uma arvore (conexa e sem ciclos)
*/	
vector<pair<int,int>> gera_arvore(int n){
	vector<pair<int,int>> edges;
	for(int i = 2; i<=n; i++){
		edges.emplace_back(gera(1,i-1),i);
	}
	return edges;
}

int main(){

	//talvez tirar flags se eu quiser q rode chegando RTE vs. + rapido
	system("g++ -std=c++17 -O2 -o prog1 A.cpp"); //alterar nome
	system("g++ -std=c++17 -O2 -o prog2 brut.cpp");
	
	srand(time(nullptr));
	
	FILE *pfile, *pfile1, *pfile2;
	
	for(ll n = 2; n<=20; n++){
		prin(n);
		fr(ii,100+20*n){
			//prin(ii);
			
			//se quiser gerar n randomico, tirar for n de fora e gera-lo aqui
			//ll n = gera(2,10);
		
			pfile = fopen("input","w");
			fprintf(pfile,"%lld\n", n);
			//fprintf(pfile,"%lld %lld\n", n, m);
			
			fr(i,n){
				if(i) fprintf(pfile, " ");
				ll x = gera(-10,100);
				fprintf(pfile, "%lld", x);
				
				//fprintf(pfile, "%s ", gera_string(10).c_str());
			}
			fprintf(pfile,"\n");
			fclose(pfile);
		
			system("./prog1 < input > a1");
			system("./prog2 < input > a2");
		
			pfile1 = fopen("a1","r");
			pfile2 = fopen("a2","r");
		
			///*
			ll ans1, ans2;
			fscanf(pfile1,"%lld", &ans1);
			fscanf(pfile2,"%lld", &ans2);
			//*/
			
			//Le e comparar vetor inves de ll
			/*
			vector<ll> ans1(n), ans2(n);
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
			
			if(ans1!=ans2){
				prin(ii);
				//Se parou eh pq input esta com o arquivo que quebra
				goto end;
			}
		
		}
	}
	
	end:
	return 0;
}
