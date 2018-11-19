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
#define prin(a) cout << #a << " = " << (a) << endl
#define cendl if(debug) cout << endl

class no{
public:
	int v;
	int l, r;
};

vector<no> s;
vector<int> v;

#define lid 2*id+1
#define rid 2*id+2

void bseg(int id = 0,int l = 0, int r = v.size()){
	s[id].l = l;
	s[id].r = r;
	
	if(r-l==1){ s[id].v=v[l]; return ;}
	
	int mid = (l+r)/2;
	bseg(lid,l,mid);
	bseg(rid,mid,r);
	
	s[id].v = min(s[lid].v,s[rid].v);
	
	return;
}

int q(int id, int l, int r){
	if(s[id].l>=l and s[id].r<=r) return s[id].v;
	
	if(s[id].l>=r or s[id].r<=l) return INT_MAX;
	
	return min(q(lid,l,r),q(rid,l,r));
}

int main(){
	int n;
	
	cin >> n;
	
	v.resize(n);
	s.resize(4*n);
	
	fr(i,n){
		scanf("%d", &v[i]);
	}
	
	bseg();
	
	int l, r;
	
	while(scanf("%d %d", &l, &r)!=EOF){
		cout << q(0,l,r) << endl << endl;		
	}
	
	s.clear();
	
	return 0;
}

