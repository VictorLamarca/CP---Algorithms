#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
typedef long long ll;

void printa(__int128 x){
    if(x<0){
    	cout << "-";
    	//printf("-");
    	printa(-x);
    	return;
    }
    const ll maxval = 1e18l;
    ll a = x/maxval;
    ll b = x%maxval;
    if(a){
    	ll nd = 1;
    	ll p10 = 10;
    	while(p10<=b){
    		nd++;
    		p10*=10;
    	}
    	cout << a;
    	fr(cnt,18-nd) cout << "0";
    	cout << b;
    } else{
    	cout << b;
    }
    //if(a) printf("%lld%018lld", a, b);
    //else printf("%lld", b);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	__int128 x = 1;
	fr(i,20) x*=10;
	x+=17;
	printa(x);
	cout << "\n";
}

