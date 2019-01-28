#include <bits/stdc++.h>
using namespace std;

//mudar file.in pelo nome do input e por FILE_IN
//antes dos scanfs
#define FILE_IN freopen("file.in", "r", stdin);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;
typedef long double ld;

#define pb push_back

#define all(a) a.begin(),a.end() 

#define fi first
#define se second
typedef pair<int,int> pii;

#define PI acos(-1)
ll MOD = 1e9+7;

//LONG_LONG_MAX
//-DBL_MAX

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define prinsep if(debug) cout << "------" << endl;
#define cendl if(debug) cout << endl

int ans[2];
int n;

//por debug =1 e input como 101

string sans;
int f(string s){
	int ans = 0;
	
	fr(i,s.size()){
		if(s[i]!=sans[i]) ans++;
	}
	prin(ans);
	return ans;
}

void buscar(bool m1, int lo, int hi, int nmin,bool busc = 0){
	
	bool jan = 0;
	int nmax = n-nmin;
	string s, so;
	fr(i,n) so+='0'+!m1;
	int cur;
	while(hi>lo){
		int mid = (hi+lo)/2;
		s = so;
		frr(i,lo,mid){
			s[i] = '0'+m1;
		}
		printf("? %s\n", s.c_str());
		fflush(stdout);
		
		if(debug) cur = f(s);
		else scanf("%d", &cur);
		
		if(cur==nmin-(mid-lo+1)){ //é td 1+
			ans[m1] = lo+1;
			if(!jan and busc) buscar(!m1,mid+1,hi,n-nmin);
			return;
		} else if(cur==nmin+(mid-lo+1)){ //nao tem nenhum 1 q quero
			ans[!m1] = lo+1;
			jan = 1;
			lo = mid+1;
		} else{ // tem pelo menos 1 que quero
			if(lo==mid and !jan and busc) buscar(!m1,mid+1,hi,n-nmin);
			hi = mid;
		}
		
	}
	ans[m1] = lo+1;
	return;
}



int main(){
	
	if(debug) cin >> sans;
	
	if(debug) n = sans.size();
	else scanf("%d", &n);
	
	bool m1 = 1;
	string s;
	
	fr(i,n){
		s+='0';
	}
	
	printf("? %s\n", s.c_str());
	fflush(stdout);
	
	int nmin;
	
	if(debug) nmin = f(s);
	else scanf("%d", &nmin);
	
	if(nmin>n/2){
		nmin = n-nmin;
		m1 = 0;
	}
	
	bool jan = 0;
	
	buscar(m1,0,n-1,nmin,1);
	
	printf("! %d %d\n", ans[0], ans[1]);
	fflush(stdout);
	
	prin(sans[ans[0]-1]);
	prin(sans[ans[1]-1]);
	
	return 0;
}

