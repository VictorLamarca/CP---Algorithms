#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;

#define fi first
#define se second

struct pt{
	ll x, y;
	pt(){}
	pt(ll xx, ll yy){
		x = xx, y = yy;
	}
	
	bool operator != (pt &p2){
	    return x!=p2.x or y!=p2.y;
	}
	
	/*
	pt operator - (pt p2){
		return pt(x-p2.x,y-p2.y);
	}
	ll operator * (pt p2){
		return x*p2.x + y*p2.y;
	}
	
	ll operator ^(pt p2){
		return x*p2.y-y*p2.x;
	}
	
	long double mod(){
		return sqrt((long double)(x*x+y*y));
	}
	
	*/
};	

/*
Function that checks for intersection between two lines p1-p2 and p3-p4 in 2d

You can alter the function to receive the paremeters of the line: a*x+b*y=c

Returns:
0: No intersection, 1: One intersecao, 2: inifinite intersections

"Pans" is the  pair of doubles that represents the intersection

Watch out for overflow, |x|,|y|<=1e9
*/
int line_intersection(pt p1, pt p2, ll a2, ll b2, ll c2, pair<long double, long double> &pans){

    assert(p1!=p2);
    
    c2 = -c2; //***

	ll a1 = p1.y-p2.y, b1 = p2.x-p1.x;
	ll c1 = p1.x*a1 + p1.y*b1; // possible overflow here, 4*|x|^2
	
	ll det = a1*b2-a2*b1;
	
	if(!det){
		if(p1.x*a2+p1.y*b2!=c2) return 0;		
		pans = {p1.x,p1.y}; 
		return 2;
	}
	
	pans = {(1.0l*c1*b2-1.0l*b1*c2)/det,(1.0l*a1*c2-1.0l*a2*c1)/det};
	
	return 1;
}

//--------------------------------------------------------------------------

// solves problem: http://codeforces.com/contest/1078/problem/A

long double dist(pair<long double,long double> a, pair<long double,long double> b){
    return hypot(fabs(a.fi-b.fi),fabs(a.se-b.se));
}

long double distman(pair<long double,long double> a, pair<long double,long double> b){
    return fabs(a.fi-b.fi)+fabs(a.se-b.se);
}

ll a, b, c;

int main(){
	//FILE_IN FILE_OUT
	ll x1, y1, x2, y2;
	
	cin >> a >> b >> c;
	cin >> x1 >> y1 >> x2 >> y2;
	
	long double ans = abs(x1-x2) + abs(y2-y1);
	
	pair<long double,long double> cur, nxt;
	
	long double anscur = 0;
	
	vector<pair<pt,pt>> va = {{pt(x1,y1),pt(x2,y1)},{pt(x1,y1),pt(x1,y2)}};
	vector<pair<pt,pt>> vb = {{pt(x2,y1),pt(x2,y2)},{pt(x1,y2),pt(x2,y2)}};
	
	if(x1!=x2 and y1!=y2) 
	fr(inic,2){
	    fr(fim,2){
	        anscur = 0;
	        cur = {x1,y1};
	        if(line_intersection(va[inic].fi,va[inic].se,a,b,c,nxt)==1){
	            anscur+=distman(cur,nxt);
	            cur = nxt;
	            if(line_intersection(vb[fim].fi,vb[fim].se,a,b,c,nxt)==1){
	                anscur+=dist(cur,nxt);
	                cur = nxt;
	                nxt = {x2,y2};
	                anscur+=distman(cur,nxt);
	                ans = min(ans,anscur);
	            }
	        }
	    }
	}
	
	printf("%.10lf\n", (double)ans);
	
	return 0;
}

