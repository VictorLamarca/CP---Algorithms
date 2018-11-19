#include <bits/stdc++.h>
using namespace std;

//mudar file.in pelo nome do input e por FILE_IN
//antes dos scanfs
#define FILE_IN freopen("file.in", "r", stdin);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;

#define PI acos(-1)

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 0;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl

const int N = 1e5+10;
const int MN = (1<<21) + 10;

int freqmais[MN], freqmenos[MN];

vector<int> v;
int n, m;
int m1, m2;

int prim(int x){
	return x>>m2;
}

int seg(int x){
	return x%(1<<m2);
}

int conc(int a, int b){
	return a*(1<<m2)+b;
}

bool ehsub(int a, int b){
	return b==(a|b);
}

int main(){
	scanf("%d%d", &n, &m);
	
	v.resize(n);
	
	fr(i,n) scanf("%d", &v[i]);
	
	vector<int> eq;
	
	sort(all(v));
	
	int ant = -1;
	int cur = 0;
	fr(i,n){
		if(v[i]==ant){
			cur++;
		} else{
			if(cur>1){
				eq.pb(cur);
			}
			cur = 1;
			ant = v[i];
		}
	}
	
	if(cur>1){
		eq.pb(cur);
	}
	
	m1 = (m+1)/2, m2 = m/2;
	long long ans = 1ll*n*(n-1)/2;
	
	fr(i,n){
		int pcur = prim(v[i]);
		int scur = seg(v[i]);
		int mm = (1ll<<m1)-1;
		frr(j,pcur,mm){
			if(ehsub(pcur,j)){
				freqmais[conc(j,scur)]++;
			}
		}
		
		fr(j,scur+1){
			if(ehsub(j,scur)){
				freqmenos[conc(pcur,j)]++;
			}
		}
	}
	
	long long sub = 0;
	
	fr(i,MN){
		sub+=1ll*freqmais[i]*freqmenos[i];
	}
	
	sub-=n;
	
	for(auto it : eq){
		sub -= 1ll*it*(it-1)/2;
	}
	
	//cout << ans - sub << endl;
	printf("%lld\n",ans-sub);
	
	return 0;
}
