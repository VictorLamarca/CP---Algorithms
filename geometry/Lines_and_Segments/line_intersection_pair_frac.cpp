#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
typedef long long ll;

#define fi first
#define se second
typedef pair<ll,ll> pll;

struct pt{
	ll x, y;
	pt(){}
	pt(ll xx, ll yy){
		x = xx, y = yy;
	}
	
	bool operator == (pt p2){
	    return x==p2.x and y==p2.y;
	}
};	

/*
Function that checks for intersection between two lines p1-p2 and p3-p4 in 2d

You can alter the function to receive the paremeters of the line: a*x+b*y=c

Returns:
0: No intersection, 1: One intersecao, 2: inifinite intersections

"Pintersection" is the pair of pairs "returned" by reference that represents the irrecductible fraction
of a intersection (if any), that is for examle x=3/4 and y=-1/1

Watch out for overflow, |x|,|y|<=5e5
*/
int line_intersection(pt p1, pt p2, pt p3, pt p4, pair<pll,pll> &pintersection){
    if(p1==p2 or p3==p4) return 0; //assert(0); //?
    ll a1, a2, b1, b2, c1, c2;
    fr(cor,2){
        a1 = p1.y-p2.y, b1 = p2.x-p1.x;
	    c1 = p1.x*a1 + p1.y*b1;
	    swap(p1,p3);
	    swap(p2,p4);
	    swap(a1,a2);
	    swap(b1,b2);
	    swap(c1,c2);
    }
	ll det = a1*b2-a2*b1;
	
	if(!det){
		if(p1.x*a2+p1.y*b2!=c2) return 0;
		pintersection = {{p1.x,1},{p1.y,1}}; //pintersection = {p1.x,p1.y};
		return 2;
	}
	//For pair double:
	//pintersection = {(1.0l*c1*b2-1.0l*b1*c2)/det,(1.0l*a1*c2-1.0l*a2*c1)/det};
	//return 1;
	
	pll x, y;
	ll num, div, g;
	fr(cor,2){
	    if(cor) num = a1*c2-a2*c1; //possible overflow here (8*|x|^3)
	    else num = c1*b2-b1*c2;
	    div = det;
	    g = __gcd(abs(num),abs(div));
	    num/=g, div/=g;
	    if(div<0) div*=-1, num*=-1;
	    x = {num,div};
	    swap(x,y);
	}
	pintersection = {x,y};
	return 1;
}


//solves problem: https://www.spoj.com/problems/TAP2013A/

// variacao CF: http://codeforces.com/contest/993/problem/C

map<pair<pair<pll,pll>,pair<pll,pll>>,int> mp;
map<pair<pll,pll>,int> mp2;

const int N = 1e3+10;
pt v[N];
ll n;

ll f(ll x){
	ll lo = 2, hi = n;
	while(lo<hi){
		ll mid=  (lo+hi)/2;
		if(mid*(mid-1)/2>=x){
			hi = mid;
		} else{
			lo = mid+1;
		}
	}
	if(lo*(lo-1)/2!=x){
		exit(0);
	}
	return lo-1;
}

int main(){
	cin >> n;
	fr(i,n){
		ll x, y;
		scanf("%lld%lld", &x, &y);
		v[i] = {x,y};
		
	}
	pair<pll,pll> p1, p2;
	fr(i,n){
		fr(j,i){
			if(line_intersection(pt(0,0),pt(1,0),v[i],v[j],p1)){
				line_intersection(pt(0,1),pt(1,1),v[i],v[j],p2);
				mp[{p1,p2}]++;
			}
		}
	}
	set<ll> s;
	s.insert(n);
	for(auto &it : mp){
		mp2[it.fi.fi] += f(it.se);
	}
	for(auto it : mp2){
		s.insert(n-it.se);
	}
	cout << s.size() << endl;
	return 0;
}

//SIMPLE CHECK

/*
int main(){
	//FILE_IN FILE_OUT
	
	pair<pll,pll> p;
	if(line_intersection(pt(0,0),pt(1,1),pt(0,1),pt(1,0),p)){
		puts("Retas tem intersecao:");
		cout << "X = " << p.fi.fi << "/" << p.fi.se << ", Y = " << p.se.fi << "/" << p.se.se << endl;
	} else{
		puts("Retas paralelas");
	}
	
	return 0;
}
*/
