#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

/*
Qnd o programa parar eh pq o caso q da diferente esta no arquivo input
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
ll n;

ll gera(ll minx, ll maxx){
	assert(maxx>=minx);
	return minx + rand()%(maxx-minx+1);
}

int main(){

	//talvez tirar flags se eu quiser q rode chegando RTE vs. + rapido
	system("g++ -std=c++14 -O2 -o prog1 A.cpp"); //alterar nome
	system("g++ -std=c++14 -O2 -o prog2 net.cpp");
	
	srand(time(nullptr));
	
	fr(ii,1000){
		prin(ii);
		
		n = gera(1,10);
	
		pfile = fopen("input","w");
		fprintf(pfile,"%lld\n", n);
	
		fr(i,n){
			v[i] = gera(-10,10);
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
		if(ans1!=ans2){
			prin(ii);
			//Se parou eh pq input esta com o arquivo que quebra
			goto end;
		}
		//*/
		
		
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
		//*/
	
	}
	
	end:
	return 0;
}
