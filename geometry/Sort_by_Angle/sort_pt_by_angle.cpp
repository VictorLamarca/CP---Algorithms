#include <bits/stdc++.h>
using namespace std;
 
#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()
 
typedef long long ll;

//solves https://codeforces.com/gym/102966/problem/B
 
struct pt{
    ll x, y;
    pt(){}
    pt(ll xx, ll yy){
        x = xx, y = yy;
    }
    void read(){
    	cin >> x >> y;
    }	
};
 
ll operator ^(const pt &a, const pt &b){
    return a.x*b.y-a.y*b.x;
}
 
int quad(const pt& p){
    int ans = 0;
    if(p.x<0) ans++;
    if(p.y<0) ans^=1, ans+=2;
    return ans;
}
 
bool operator ==(const pt &a, const pt &b){
	return quad(a)==quad(b) and (a^b)==0;
}
 
// Vector by angle comparator - return 0 if they are equal
bool operator <(const pt &a, const pt &b){
    if(quad(a)==quad(b)){
        return (a^b)>0;
    }
    return quad(a)<quad(b);
}
 
pt operator -(const pt &a, const pt &b){
    return pt(a.x-b.x, a.y-b.y);
}

//-----------------
 
int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<pt> v(n);
	fr(i,n) v[i].read();
	
	int maxf = 0;
	fr(no,n){
		vector<pt> vo;
		fr(i,n){
			if(i==no) continue;
			vo.emplace_back(v[i]-v[no]);
		}
		sort(all(vo));
		int i = 0;
		while(i<sz(vo)){
			int tam = 1;
			while(i+1<sz(vo) and vo[i+1]==vo[i]){
				i++;
				tam++;
			}
			i++;
			maxf = max(maxf,tam+1);
		}
	}
	
	int ans = min(n/3, (n-maxf));
	cout << ans << "\n";
}
