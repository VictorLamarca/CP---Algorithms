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

const int N = 7e4*50;
int prox[10][N];
int fim[N];

int main(){
	int n;
	scanf("%d", &n);
	vector<string> v(n);
	
	memset(fim,-1,sizeof(fim));
	
	int sz = 1;
	bool notprin = 0;
	fr(ii,n){
		cin >> v[ii];
		string s = v[ii];
		
		fr(i,s.size()){
			int cur = 0;
			frr(j,i,s.size()-1){
				int c = s[j]-'0';
				if(!prox[c][cur]){
					prox[c][cur] = sz++;
				}
				cur = prox[c][cur];
				fim[cur] = (fim[cur]==-1 or fim[cur]==ii)? ii:INT_MAX;
			}
			
		}
		
	}
	
	fr(ii,n){
		int len = 10;
		string s = v[ii];
		string sans;
		
		fr(i,s.size()){
			int cur = 0;
			frr(j,i,s.size()-1){
				int c = s[j]-'0';
				cur = prox[c][cur];
				if(fim[cur]!=INT_MAX){
					if(j-i+1<len){
						len = j-i+1;
						sans = s.substr(i,len);
					}
				}
			}
		}
		
		printf("%s\n",sans.c_str());
	}
	
	return 0;
}
