#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

const int N = 2010;

// nao precisa ser long long pois é a soma, nao multiplicacao de numeros, portanto sem ooverflow
int binom[N][N];

int main(){

    //imaginar triangulo de pascal
    binom[0][0] = 1;
    frr(i,1,N-1){
        binom[i][0] = 1;
        //binom[i-1][j] = 0 qnd j é o ultimo da linha, e ultimo da linha é 1!
        frr(j,1,i) binom[i][j] = (binom[i-1][j-1] + binom[i-1][j]) % MOD;
    }
    
    cout << binom[4][2] << endl;  // 4 escolhe 2 = 6
	
	return 0;
}

