#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void printa(__int128 x){
    assert(x>0);
    const ll maxval = 1e18l;
    ll a = x/maxval;
    ll b = x%maxval;
    if(a) printf("%lld%018lld\n", a, b);
    else printf("%lld\n", b);
}

int main(){
	__int128 x = 1e15l;
	
	x = x*x;
	x+= 19;
	 
	printa(x);
	
	return 0;
}

