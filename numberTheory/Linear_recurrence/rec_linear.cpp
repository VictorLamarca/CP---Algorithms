#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
typedef long long ll;
#define eb emplace_back

const ll MOD = 1e9+7;

//solves https://codeforces.com/contest/1117/problem/D

//multipllica matriz - VALORES EM MÓDULO
vector<vector<ll>> mm(vector<vector<ll>> a, vector<vector<ll>> b){
	vector<vector<ll>> ans(a.size(),vector<ll>(b[0].size()));
	
	int l = a.size();
	int c = b[0].size();
	int tam = a[0].size();
	
	fr(i,l){
		fr(j,c){
			ll tot = 0;
			fr(k,a[0].size()){
				tot = (tot+a[i][k]*b[k][j])%MOD;
			}
			ans[i][j] = tot;
		}
	}
	
	return ans;
}

//matriz identidade N x N
vector<vector<ll>> ident(int n){
	vector<vector<ll>> ans(n,vector<ll>(n,0));
	
	fr(i,n) ans[i][i] = 1;
	
	return ans;
}

//Eleva matriz a um expoente
vector<vector<ll>> em(vector<vector<ll>> a, ll exp){
	if(exp==0) return ident(a.size());
	if(exp==1) return a;
	vector<vector<ll>> mid = em(a,exp/2);
	if(exp%2) return mm(mm(mid,mid),a);
	return mm(mid,mid);
}

int main(){
    ll n, k;
    cin >> n >> k;
    
    /*
        n-- pois embora no problema, 
        nao haja dp[0] (1<=i<=n apenas),
        a construcao que uso comeca de 0, portanto 
        fazer n--
    */
    n--;
    
    /*
        Ao fazer matrizes, cuidado com coisas como
        valores maiores que MOD (pegar o modulo dele)
        se valor negativo, -1 = MOD-1
        CUIDADO com eo = eo%MOD, if(eo==0) cout << 0
        POR if ANTES DO MOD!
    */
    
    vector<vector<ll>> f0, t(k,vector<ll>(k));
    
    //fazendo f0
    vector<ll> aux;
    aux.eb(2);
    fr(i,k-1) aux.eb(1);
    f0.eb(aux);
    
    //fazendo matriz t
    fr(i,k-1) t[i][i+1] = 1;
    t[0][0] = 1;
    t[k-1][0] = 1;
    
    if(n<k){
        printf("%lld\n", f0[0][k-1-n]);
    } else{
        vector<vector<ll>> ans = mm(f0,em(t,n-k+1));
        cout << ans[0][0] << endl;
    }   
    
	
	return 0;
}

