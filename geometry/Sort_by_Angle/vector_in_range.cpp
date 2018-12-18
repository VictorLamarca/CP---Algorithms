#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

typedef long long ll;
#define pb push_back
#define fi first
#define se second

//Sort by angle - solve in range querys
//solves problem: https://codeforces.com/gym/101879/problem/A

struct pt{
    ll x, y;
    pt(){}
    pt(ll xx, ll yy){
        x = xx, y = yy;
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

//equal operator is differrent - (1,0) is equal to (2,0) - modulo is not important
bool operator ==(const pt &a, const pt &b){
    return quad(a)==quad(b) and (a^b)==0;
}

//Set of pair of vectors that represents multiple disjoint angle ranges
set<pair<pt,pt>> s;

//Biggest and smallest vectors by angle
pt maior_pt(2e9+100,-1), menor_pt(1,0);

bool intersec(pair<pt,pt> a, pair<pt,pt> b){
    pt inic = a.fi;
    if(inic<b.fi) inic = b.fi;
    pt fim = a.se;
    if(b.se<fim) fim = b.se;
    if(inic<fim or inic==fim) return 1;
    return 0;
}

pair<pt,pt> merge(pair<pt,pt> a, pair<pt,pt> b){
    pt inic = a.fi;
    if(b.fi<inic) inic = b.fi;
    pt fim = a.se;
    if(fim<b.se) fim = b.se;
    return {inic,fim};
}

//Necessary flag - becuase first vector is corner case when treating in range
int zero_dentro = 0;

//Insert range - cur.fi start and cur.se end
void poe(pair<pt,pt> cur){
    if(cur.se<cur.fi){
        poe({cur.fi,maior_pt});
        poe({menor_pt,cur.se});
        zero_dentro = 1;
        return;
    }
    auto it = s.upper_bound(pair<pt,pt>(cur.fi,maior_pt));
    if(it!=s.begin()) it--;
    for(;(it!=s.end()) and ((it->fi<cur.se) or (it->fi==cur.se));){
        if(intersec(cur,*it)){
            cur = merge(cur,*it);
            it = s.erase(it);
        } else it++;
            
    }
    s.insert(cur);
}   

//Is vector p in any range - (open extremes)
bool dentro(pt p){
    if(p==menor_pt and zero_dentro) return 1; //corner case
    auto it = s.upper_bound(pair<pt,pt>(p,maior_pt));
    if(it!=s.begin()){
        it--;
        if((it->fi<p) and (p<it->se)) return 1;
    }
    return 0;
}

//-------------------------------------------

int n, q;

vector<pt> hull;

int main(){
    cin >> n >> q;

    fr(i,n){
        int x, y;
        scanf("%d%d", &x, &y);
        hull.pb(pt(x,y));
    }
    
    fr(i,n){
        pt v1 = hull[(i-1+n)%n]-hull[i];
        pt v2 = hull[(i+1)%n]-hull[i];
        if((v1^v2)>0){
            pt v1_op = v1;
            v1_op.x*=-1, v1_op.y*=-1;
            pt v2_op = v2;
            v2_op.x*=-1, v2_op.y*=-1;
            poe({v2,v1_op});
            poe({v2_op,v1});
        }
    }
    
    fr(i,q){
        pt p;
        scanf("%lld%lld", &p.y, &p.x);
        p.x*=-1;
        if(dentro(p)){
            puts("N");
        } else puts("Y");
    }
	
	return 0;
}

