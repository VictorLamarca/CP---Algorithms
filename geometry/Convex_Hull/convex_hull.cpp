#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(),(v).end()
#define eb emplace_back
#define fr(i,n) for(int i = 0;i<n;i++)
#define frr(i,a,b) for(int i = a;i<=b;i++)

typedef long long ll;
typedef pair<ll,ll> pll;

/*
    finds convex hull of set of pointes
    area and perimeter
    solves this problem:
    https://codeforces.com/group/3qadGzUdR4/contest/101706/problem/G
*/

struct pt{
    ll x, y;
    int id;
    pt(){}
    pt(ll xx, ll yy){
        x = xx, y = yy;
    }
    
    pt operator -(pt p2){
        return pt(x-p2.x,y-p2.y);
    }
    
    ll operator ^(pt p2){
        return x*p2.y-y*p2.x;   
    }
    
    double mod(){
        return hypot(x,y);
    }
};

bool operator <(const pt &p1, const pt &p2){
    return pll(p1.x,p1.y)<pll(p2.x,p2.y);
}

bool operator ==(const pt &p1, const pt &p2){
    return pll(p1.x,p1.y)==pll(p2.x,p2.y);
}

/*
    gera convex hull em ordem ccw
    pontos colineares são retirados
    no fr(cor,2) porimeiro se faz o lower hull
    depois o upper
    
    unico corner eh se pontos forem tds colineares,
    ai o ch eh degenerado
*/
vector<pt> mch(vector<pt> v){
    sort(all(v));
    v.resize(unique(all(v))-v.begin());
    
    vector<pt> ans;
    
    fr(cor,2){
        vector<pt> h;
        fr(i,v.size()){
            while(h.size()>=2){
                pt v1 = h.back()-h[h.size()-2];
                pt v2 = v[i]-h.back();
                if( (v1^v2) > 0 ) break;
                h.pop_back();
            }
            h.eb(v[i]);
        }
        fr(i,(int)h.size()-1){
            ans.eb(h[i]);
        }
        reverse(all(v));
    }
    
    return ans;
}

int main(){
    ll n;
    cin >> n;
    vector<pt> v;
    fr(i,n){
        pt p;
        p.id = i+1;
        scanf("%lld%lld", &p.x, &p.y);
        v.eb(p);
    }   
    
    v = mch(v);
    n = v.size();
    
    double per = 0;
    fr(i,n) per += (v[(i+1)%n]-v[i]).mod();
    ll area = 0;
    frr(i,1,n-1){
        pt v1 = v[i]-v[0];
        pt v2 = v[(i+1)%n]-v[0];
        area += abs(v1^v2);
    }
    
    cout << v.size() << endl;
    fr(i,n) printf("%d%c", v[i].id, " \n"[i==n-1]);
    printf("%.15lf\n", per);
    printf("%lld", area/2);
    if(area%2) puts(".5");
    else puts("");
    
}
