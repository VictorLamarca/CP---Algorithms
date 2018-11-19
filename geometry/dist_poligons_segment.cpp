#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;

class pt{
public:
	ll x, y;
	pt(){}
	pt(ll xx, ll yy){
		x = xx, y = yy;
	}
	
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
};		

ll area(pt p1, pt p2){
	return abs(p1^p2);
}

//distancia de ponto a a segmento b-c
long double dist(pt a, pt b, pt c){
	pt vbaseb = (c-b);
	pt vbasec = (b-c);
	pt vb = (a-b);
	pt vc = (a-c);
	
	if((vb*vbaseb)<0){
		return sqrt((long double)(vb.x*vb.x+vb.y*vb.y));
	}
	if((vc*vbasec)<0){
		return sqrt((long double)(vc.x*vc.x+vc.y*vc.y));
	}
	
	return area(vb,vbaseb)/(long double)vbaseb.mod();
	
}

//checa se ponto esta dentro do segmento
bool inptseg(pt a1, pt b1, pt b2){
	pt v1 = (a1-b1), v2 = (b2-b1);
	if(v1^v2) return 0;
	v1 = b1-a1, v2 = b2-a1;
	return (v1*v2)<=0;
}

//checa se segmentos intersectam (bordas inclusas)
bool seg_intersect(pt a1, pt a2, pt b1, pt b2){
	if(inptseg(a1,b1,b2) or inptseg(a2,b1,b2) or inptseg(b1,a1,a2) or inptseg(b2,a1,a2)) return 1;
	pt v1, v2, vs;
	
	//o resultado eh inteiro, entao nao preciso me preocupar com precisão, apenas overflow
	v1 = (a1-b1), v2 = (a2-b1), vs = (b2-b1);
	if( 1.0l*(v1^vs)*(v2^vs) >= -0.5 ) return 0;
	
	swap(a1,b1), swap(a2,b2);
	
	v1 = (a1-b1), v2 = (a2-b1), vs = (b2-b1);
	if( 1.0l*(v1^vs)*(v2^vs) >= -0.5 ) return 0;
	
	return 1;
}

//distancia entre segmentos
long double distseg(pt a, pt b, pt c, pt d){
	long double mindist = min({dist(a,c,d),dist(b,c,d),dist(c,a,b),dist(d,a,b)});
	
	if(seg_intersect(a,b,c,d)) return 0;
	
	return mindist;
}	

// solves: https://www.hackerrank.com/contests/booking-womenintech/challenges/distance-between-two-polygons/problem

// variacao CF : http://codeforces.com/contest/993/problem/A

const int N = 5e3+10;

pt v[2][N];
pt seg[2][N];

int tam[2];

bool inpol(pt p, int cor){
	int neg = 0, pos = 0;
	
	fr(i,tam[cor]){
		pt vet = p-v[cor][i];
		if((vet^seg[cor][i])>0) pos = 1;
		if((vet^seg[cor][i])<0) neg = 1;
	}
	
	if(neg and pos) return 0;
	return 1;
}

int main(){
	//FILE_IN FILE_OUT
	
	fr(i,2) scanf("%d", tam+i);
	
	fr(cor,2){
		fr(i,tam[cor]){
			scanf("%lld%lld", &v[cor][i].x, &v[cor][i].y);
		}
	}
	
	long double mdist = LLONG_MAX;
	
	fr(cor,2){
		fr(i,tam[cor]){
			seg[cor][i] = v[cor][(i+1)%tam[cor]]-v[cor][i];
		}
	}
	
	fr(i,tam[0]){
		fr(j,tam[1]){
			mdist = min(mdist, distseg(v[0][(i+1)%tam[0]], v[0][i], v[1][(j+1)%tam[1]], v[1][j]));
		}
	}
	
	bool zero = 0;
	fr(cor,2) if(inpol(v[!cor][0],cor)) zero = 1;
	
	if(zero) cout << 0 << endl;
	else printf("%.10lf\n", (double)mdist);
	
	return 0;
}

