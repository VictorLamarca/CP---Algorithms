#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define rmin(a,b) a = min<ll>(a,b)
#define rmax(a,b) a = max<ll>(a,b)

#define fi first
#define se second

template <class T>
T fp(T x, long long e) {
	T ans(1);
	for(; e > 0; e /= 2) {
		if(e & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

const ll mod = round(1e9)+7;
struct mb {
	mb(int v = 0) : val(v < 0 ? v + mod : v) {}
	mb(ll v){ val = (v%mod+mod)%mod; }
	int val;
 
	void operator += (mb o) { *this = *this + o; }
	void operator -= (mb o) { *this = *this - o; }
	void operator *= (mb o) { *this = *this * o; }
	mb operator * (mb o) { return (int)((long long) val * o.val % mod); }
	mb operator / (mb o) { return *this * fp(o, mod - 2); }
	//bool operator == (mb o) { return val==o.val; } //usar soh para hashes
	mb operator + (mb o) { return val + o.val >= mod ? val + o.val - mod : val + o.val; }
	mb operator - (mb o) { return val - o.val < 0 ? val - o.val + mod : val - o.val; }
};

/*
	retorno:
		0 - sem solução
		1 - uma solução
		2 - infinitas soluções
		
	rsolve sistma - acha X para
		a*X = b
	nos parametros, b é a ultima coluna da matriz a
*/
int gauss (vector < vector<mb> > a, vector<mb> & ans) {
    int n = sz(a), m = sz(a[0])-1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (a[i][col].val > a[sel][col].val)
                sel = i;
        if (a[sel][col].val==0)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                mb c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        mb sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if( sum.val != a[i][m].val)
        	return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	vector<vector<mb>> mat = {{1,2,8},
						  {2,4,16}};
						  
	vector<mb> ans;
	prin(gauss(mat,ans));
	fr(i,sz(ans)) prin(ans[i].val);
	
	
}
