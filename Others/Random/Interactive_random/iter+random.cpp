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
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define prinsep if(debug) cout << "------" << endl;
#define cendl if(debug) cout << endl

const int N = 5e4+10;

class node{
public:
	int v, idx, next;
	node(){}
	node(int a, int b, int n){
		v = a, idx = b, next = n;
	}
};

bool operator <(const node &a, const node &b){
	if(a.v==b.v){
		return a.next<b.next;
	}
	return a.v<b.v;
}

set<node> se;

int grand(){
	return ((rand()%(1<<15))<<15) + rand()%(1<<15);
}

int main(){
	int n, s, x;
	
	scanf("%d%d%d", &n, &s, &x);
	
	srand(time(nullptr));
	
	int q = 1000;
	
	bool jas = 0;
	
	fr(i,q){
		int cur = grand()%n+1;
		
		if(!jas) cur = s, jas = 1;
		
		printf("? %d\n",cur);
		fflush(stdout);
		
		int v, next;
		scanf("%d%d",&v, &next);
		
		if(next==-1) next = INT_MAX;
		
		se.insert(node(v,cur,next));
	}
	
	
	auto cur = se.lower_bound(node(x,-1,-1));
	
	if(cur==se.begin()){
		printf("! %d\n",cur->v);
		fflush(stdout);
		return 0;
	}
	
	cur--;
	int idx = cur->next;
	if(idx==INT_MAX) idx = -1;
	int val = cur->v;
	
	while(1){
		if(idx==-1){
			printf("! %d\n",-1);
			fflush(stdout);
			return 0;
		}
		
		printf("? %d\n", idx);
		fflush(stdout);
		int v, next;
		scanf("%d%d",&v, &next);
		
		if(v>=x){
			printf("! %d\n",v);
			fflush(stdout);
			return 0;
		}
		
		if(next==-1){
			printf("! %d\n",-1);
			fflush(stdout);
			return 0;
		}
		
		idx = next;
		val = v;
		
	}
	
	
	return 0;
}
