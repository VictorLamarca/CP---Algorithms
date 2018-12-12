#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
typedef long long ll;
#define pb push_back
#define all(v) (v).begin(),(v).end()

/*
original problem: https://www.urionlinejudge.com.br/judge/pt/problems/view/2907

solved using sort by angle technique
*/

class pt{
public:
    ll x, y;
    pt(){}
    pt( ll xx, ll yy){
        x = xx, y = yy;
    }
    pt operator -(pt &p2){
        return pt(x-p2.x,y-p2.y);
    }
};

int quad(const pt &p){
    int ans = 0;
    if(p.x<0) ans++;
    if(p.y<0) ans+=2, ans^=1;
    return ans;
}

ll operator ^(const pt &p1, const pt &p2){
    return p1.x*p2.y-p1.y*p2.x;
}

bool operator <(const pt &a, const pt &b){
    if(quad(a)==quad(b)){
        return (a^b)>0;
    }
    return quad(a)<quad(b);     
}

vector<pt> pol;

//structure of vectors sorted by angle
vector<pt> v;

int n;

/*How many vectors are between the oposities of pi (initial) and pj (end)
(exclude extremes)*/
ll entre(pt pi, pt pj){
    pi.x*=-1,pi.y*=-1;
    pj.x*=-1,pj.y*=-1;
    ll ans = (lower_bound(all(v),pj)-upper_bound(all(v),pi));
    if(ans<0) ans+=n;
    return ans;
}

//the same as last but include pj(end) extreme
ll entre2(pt pi, pt pj){
    pi.x*=-1,pi.y*=-1;
    pj.x*=-1,pj.y*=-1;
    ll ans = (upper_bound(all(v),pj)-upper_bound(all(v),pi));
    if(ans<0) ans+=n;
    return ans;
}

int main(){
	//FILE_IN FILE_OUT
	cin >> n;
	
	fr(i,n){
	    ll x, y;
	    scanf("%lld%lld", &x, &y);
	    pol.pb(pt(x,y));
	}   
	
	fr(i,n){
	    v.pb(pol[(i+1)%n]-pol[i]);
	}
	
	sort(all(v));
	
	int i = -1, j = 0;
	
	ll cur = 0, ans = 0, nativo = 0;
	
	while(1){
	    if(i==n-1) break;
	    if(i!=-1){ 
	        nativo--;
	        cur-= nativo*entre2(v[i],v[i+1])+entre(v[i],v[i+1]);
	    }
        i++;
        while((v[i]^v[(j+1)%n])>0){ 
            j = (j+1)%n;
            cur+=entre(v[i],v[j]);
            nativo++;
        }
        ans+=cur;
	}
	
	ans/=3;
	cout << ans << endl;
	
	return 0;
}

