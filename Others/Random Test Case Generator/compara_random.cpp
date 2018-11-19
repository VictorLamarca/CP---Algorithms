#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<(n);i++)
#define frr(i,a,b) for(int i=(a);i<=(b);i++)
#define frrs(i,a,b) for(int i=(a);i>=(b);i--)
#define VAR(a,b) __typeof(b) a=b
#define frit(it,c) for(VAR(it,(c).begin());it!=(c).end();it++)

typedef long long ll;
typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;

#define PI acos(-1)
#define MOD 1000000007

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define prinsep if(debug) cout << "------" << endl;
#define cendl if(debug) cout << endl

/*
para usar esse programa faca uma copia para
manter o original intocado

rodar com crman para ver evolucao (nao requer input)

o que geralente é necessario mudar esta comentado 
ao lado ou abaixo
*/

int main(){

	system("g++ -std=c++11 -o prog1 net.cpp"); //alterar nome
	system("g++ -std=c++11 -o prog2 _d.cpp");
	
	srand(time(nullptr));
	
	int n = 5; //alterar valor de n
	int v[200100];
	
	fr(ii,1000){
		prin(ii);
	
		FILE *pfile = fopen("input","w");
		fprintf(pfile,"%d\n", n);
	
		fr(i,n){
			v[i] = rand()%10+1; //aumentar %10 se quiser numeros maiores
			fprintf(pfile, "%d ", v[i]);
		}
		fprintf(pfile,"\n");
	
		fclose(pfile);
	
		system("./prog1 < input > a1");
		system("./prog2 < input > a2");
	
		FILE *pfile1 = fopen("a1","r");
		FILE *pfile2 = fopen("a2","r");
	
		int ans1, ans2;
		//vector<int> ans1(n), ans2(n);
	
		fscanf(pfile1,"%d", &ans1);
		fscanf(pfile2,"%d", &ans2);
		
		/*
		fscanf(pfile1,"%*d");
		fscanf(pfile2,"%*d");
		
		fr(i,n){
			fscanf(pfile1,"%d", &ans1[i]);
		}
		
		fr(i,n){
			fscanf(pfile2,"%d", &ans2[i]);
		}
		*/
	
		fclose(pfile1);
		fclose(pfile2);
	
		if(ans1!=ans2){
			prin(ii);
			cout << n << endl;
			fr(i,n){
				cout << v[i] << " ";
			}
			cout << endl;
			goto end;
		}
		
		/*
		bool dif = 0;
		fr(i,n){
			if(ans1[i]!=ans2[i]) dif = 1;
		}
	
		if(dif){
			cout << n << endl;
			fr(i,n){
				cout << v[i] << " ";
			}
			cout << endl;
			goto end;
		}
		*/
	
	}
	
	end:
	return 0;
}

