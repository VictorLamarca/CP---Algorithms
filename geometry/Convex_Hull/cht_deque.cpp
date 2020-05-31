#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

//solves https://www.spoj.com/problems/MKPAIRS/

struct Line{
	// y = m*x + k
	ll m,k;
	ll eval(ll x){
		return m*x+k;
	}
	Line(){}
	Line(ll _m, ll _k){
		m = _m, k = _k;
	}
};

//querys em ordem de x decrescente
//insercoes de linhas com m (slopes) em ordem decrescente
struct ChtDeque{
	vector<Line> dq;
	int l, r; // [l,r)
	ChtDeque(){}
	ChtDeque(int n){ //n eh o maximo de linhas a serem inseridas
		n+=5;
		dq.resize(n+5);
		l = r = n;
	}
	ll div(ll a, ll b){
		return a/b - ( (a^b)<0 and a%b);
	}
	bool tirar(Line &l1, Line &l2, Line &l3){
		if(l1.m==l2.m){
			return l1.k>=l2.k;
		}
		return div(l2.k-l3.k,l3.m-l2.m)<=div(l1.k-l2.k,l2.m-l1.m);
	}
	void add(ll m, ll k){
		Line line(m,k);
		while(r-l>=2){
			if(tirar(line,dq[l],dq[l+1])) l++;
			else break;
		}			
		if(l<r and dq[l].m==m){
			if(k>dq[l].k) dq[l] = line;
			return;
		}
		dq[--l] = line;
	}
	ll query(ll x){
		assert(r>l);
		while(r-l>=2){
			if(dq[r-2].eval(x)>=dq[r-1].eval(x)) r--;
			else break;			
		}
		return dq[r-1].eval(x);
	}
};

const int N = 1e3+10;
ll a[N], b[N];
ll n; 

ll dp[N][N], aca[N], acb[N];
ChtDeque chta[N], chtb[N];

ll sq(ll x){
	return x*x;
}

ll somaa(int i, int j){
	if(i>j) return 0;
	ll ans = aca[j+1];
	ans-=aca[i];
	return ans;
}

ll somab(int i, int j){
	if(i>j) return 0;
	ll ans = acb[j+1];
	ans-=acb[i];
	return ans;
}

int main(){
	cin >> n;
	
	fr(i,n) scanf("%lld", a+i);
	fr(i,n) scanf("%lld", b+i);
	
	fr(i,n+1) chta[i] = ChtDeque(n);
	fr(i,n+1) chtb[i] = ChtDeque(n);
	
	fr(i,n+1) fr(j,n+1) dp[i][j] = -LLONG_MAX/2;
	
	fr(i,n){
		aca[i+1] = a[i];
		aca[i+1]+=aca[i];
	}
	fr(i,n){
		acb[i+1] = b[i];
		acb[i+1]+=acb[i];
	}
	
	
	for(int j = n; j>=0; j--){
		int i = n;
		dp[i][j] = -sq(somab(j,n-1));
	}
	
	for(int i = n; i>=0; i--){
		int j = n;
		dp[i][j] = -sq(somaa(i,n-1));
	}
	
	for(int pivo = n-1; pivo>=0; pivo--){
		for(int j = n-1; j>=pivo; j--){
			int i = pivo;
			
			chta[i].add(2*acb[j],a[i]*b[j]-sq(acb[j])+dp[i+1][j+1]);
			if(i!=j) chtb[j].add(2*aca[i],a[i]*b[j]-sq(aca[i])+dp[i+1][j+1]);
			
			dp[i][j] = max(dp[i][j],chta[i].query(acb[j])-sq(acb[j]));
			if(i!=j) dp[i][j] = max(dp[i][j],chtb[j].query(aca[i])-sq(aca[i]));
		}
		for(int i = n-1; i>=pivo; i--){
			int j = pivo;
			
			if(i!=j) chta[i].add(2*acb[j],a[i]*b[j]-sq(acb[j])+dp[i+1][j+1]);
			chtb[j].add(2*aca[i],a[i]*b[j]-sq(aca[i])+dp[i+1][j+1]);
			
			dp[i][j] = max(dp[i][j],chta[i].query(acb[j])-sq(acb[j]));
			dp[i][j] = max(dp[i][j],chtb[j].query(aca[i])-sq(aca[i]));
		}
	}
	
	cout << dp[0][0] << endl;	
}
