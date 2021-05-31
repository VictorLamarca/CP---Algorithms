#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

//seed mt13997 em milissegundos
int seed_mili = chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(seed_mili);

//seed rand normal em segundos
int seed_seg = time(0);	

//funcao para forçar aumento do RAND_MAX (util para CF por exemplo)
ll grand(){
	return ((rand()%(1<<15))<<15) + rand()%(1<<15);
	/*
	ll cur = 0;
	fr(i,4) cur = (cur<<15)+rand()%(1<<15);
	return cur;
	*/
}

int gera_rand(int l, int r){
	int tam = r-l+1;
	assert(tam>0);
	return l+rand()%tam;
}

int gera_mt(int l, int r){
  return uniform_int_distribution<int>(l, r)(rng);
}

int gera_rng(int l, int r){
	int tam = r-l+1;
	assert(tam>0);
	return l+rng()%tam;
}

int main(){
	srand(seed_seg); //srand normal precisa ser na main

	cout << "Gera rand normal:" << endl;
	fr(i,5) prin(gera_rand(1,5));
	cout << endl;
	
	cout << "Gera mt13997:" << endl;
	fr(i,5) prin(gera_mt(1,5));
	cout << endl;
	
	cout << "Gera rng:" << endl;
	fr(i,5) prin(gera_rng(1,5));
	cout << endl;
	
	vector<int> v = {1,2,3,4,5};
	
	cout << "Shuffle normal: " << endl;
	random_shuffle(all(v));
	prinv(v);
	cout << endl;
	
	cout << "Shuffle mt13997: " << endl;
	shuffle(all(v),rng);
	prinv(v);
	cout << endl;
}
