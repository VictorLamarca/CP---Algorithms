#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
typedef long long ll;

/*
    Finds the biggest clique of a graph with n vertices in 
    O( (n/2)*2^(n/2) ). 
    
    the j-th bit of g[i] represents if there is an egde
    from node i to j
    
    use of meet-in-the-middle approach
    
    b_clique[half][mask] is the dynammic programming array 
    that is set to the biggest clique in a subset o nodes 
    represented by the mask. (if half==0 mask is a subset
    of the first half of the nodes, otherwise the second
    half)
*/

const int N = 44;

ll g[N];
int b_clique[2][1<<(N/2)];

int max_clique(int n){
    
    int tam[2] = {n/2,n-n/2};
    
    fr(cor,2)
    for(int mask = 1; mask<(1<<tam[cor]); mask++){
        
        fr(i,tam[cor]) 
            if( (1<<i)&mask ){
                int gg = g[i];
                if(cor) gg = g[tam[0]+i]>>tam[0];
                if( (mask&gg) != (mask^(1<<i)) ) goto jp;
            }
        
        b_clique[cor][mask] = __builtin_popcount(mask);
        
        jp:
        fr(i,tam[cor]){
            if(mask&(1<<i)){
                b_clique[cor][mask] = max(b_clique[cor][mask],b_clique[cor][mask^(1<<i)]);
            }
        }
    }
    
    int ans = 0;
    
    fr(mask,(1<<tam[0])){
        ll mask2 = (1ll<<n)-1;
        fr(i,tam[0]) if(mask&(1<<i)) mask2 &= g[i];
        mask2>>=tam[0];
        ans = max(ans,b_clique[0][mask]+b_clique[1][mask2]);
    }
    
    return ans;
}   

//---------------------------------------------------

//solves problem https://codeforces.com/contest/1105/problem/E

int n, m;
map<string,int> mp;

char str[110];

int getid(string s){
    if(mp.count(s)) return mp[s];
    int id = mp.size();
    mp[s] = id;
    return id;
}

int main(){
	cin >> n >> m;
	
	set<int> s;
	
	fr(i,n){
	    int t;
	    scanf("%d", &t);
	    if(t==1){
	        for(auto &u : s){
	            for(auto &v : s){
	                g[u] |= (1ll<<v);
	            }
	        }
	        s.clear();
	    } else{
	        scanf("%s", str);
	        s.insert(getid(string(str)));
	    }
	}
	
	for(auto &u : s){
        for(auto &v : s){
            g[u] |= (1ll<<v);
        }
    }
	
	int masktot = (1ll<<m)-1;
	fr(i,m) g[i] = masktot&(~g[i]);
	
	cout << max_clique(m) << endl;
	
	return 0;
}

