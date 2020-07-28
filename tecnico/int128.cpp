#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void printa(__int128 x){
    if(x<0){
    	printf("-");
    	printa(-x);
    	return;
    }
    const ll maxval = 1e18l;
    ll a = x/maxval;
    ll b = x%maxval;
    if(a) printf("%lld%018lld", a, b);
    else printf("%lld", b);
}

int main(){
	__int128 x = 1e15l;
	x = x*x;
	x+= 19;
	printa(x);
}

