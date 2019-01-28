#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

#define eb emplace_back
#define pb push_back

#define all(v) (v).begin(),(v).end()

#define fi first
#define se second
typedef pair<int,int> pii;


//Resolve problemas do tipo qnts valores tem frequencia tal em range [l,r]
//solves https://codeforces.com/gym/101879/problem/H

const int N = 3e4+10;

int rz;

int v[N];

int freq[N];
int qnts_freq[220];

int n,q ;

vector<pii> qry;

struct cmp{
    bool operator ()(int i, int j){
        pii a = qry[i], b = qry[j];
        if(a.se/rz!=b.se/rz) return a.se/rz < b.se/rz;
        return a<b;
    }

};


int ans[N];

int curans = 0;

void add(int id){
    freq[id]++;
    if(freq[id]>200) return;
    qnts_freq[freq[id]]++;
    if(qnts_freq[freq[id]] == freq[id]) curans = freq[id];
}

void tira(int id){
    if(freq[id]<=200){ 
        qnts_freq[freq[id]]--;
        if(qnts_freq[freq[id]] == freq[id]-1) curans = freq[id]-1;
    }
    freq[id]--;
}

int main(){
	
	cin >> n >> q;
	
	map<int,int> mp;
	
	fr(i,n) scanf("%d", v+i), mp[v[i]] = 0;
	
	{
	int cnt = 0;
	for(auto &it : mp){
	    it.se = cnt++;
	}
	
	fr(i,n){
	    v[i] = mp[v[i]];
	}
	
	}
	
	fr(i,q){
	    int l, r;
	    scanf("%d%d", &l, &r);
	    l--,r--;
	    qry.eb(r,l);
	}
	
	rz = max(1,(int)sqrt(n));
	
    vector<int> ito ;
    
    fr(i,q) ito.pb(i);
	sort(all(ito),cmp());
	
	int curl = 0, curr = -1;
	
	int l ,r;
	
	fr(i,q){
	    tie(r,l) = qry[ito[i]];
	    
	    //fazer adds antes dos tira para nao dar negativo no meio
	    while(curr<r){
	        curr++;
	        add(v[curr]);
	    }
	    
	    while(curl>l){
	        curl--;
	        add(v[curl]);
	    }
	    
	    while(curr>r){
	        tira(v[curr]);
	        curr--;
	    }
	    
	    while(curl<l){
	        tira(v[curl]);
	        curl++;
	    }
	    
	    ans[ito[i]] = curans;
	}
	
	fr(i,q){
	    printf("%d\n", ans[i]);
	}
	
	return 0;
}

