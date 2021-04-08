#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)

//solves https://acm.timus.ru/problem.aspx?space=1&num=1103

struct pt{
	double x, y;
	pt(){}
	pt(double _x, double _y){
		x = _x, y = _y;
	}
	//------------
	void read(){
		int a, b; cin >> a >> b;
		x = a, y = b;
	}
	void print(){
		cout  << (int)round(x) << " " << (int)round(y) << "\n";
	}
	pt operator-(pt &p2){
		return pt(x-p2.x,y-p2.y);
	}
	double mod2(){
		return x*x+y*y;
	}
	double mod(){
		return sqrt(this->mod2());
	}
	//-----------
};

double eps = 1e-7;
int sign(double x){
	if(x>eps) return 1;
	if(x<-eps) return -1;
	return 0;
}

bool eq(double x, double y){
	return sign(x-y)==0;
}

int line_intersection(pt p1, pt p2, pt p3, pt p4, pt &pans){
    double a1, a2, b1, b2, c1, c2;
	fr(cor,2){
        a1 = p1.y-p2.y, b1 = p2.x-p1.x;
	    c1 = p1.x*a1 + p1.y*b1;
	    swap(p1,p3);
	    swap(p2,p4);
	    swap(a1,a2);
	    swap(b1,b2);
	    swap(c1,c2);
    }
	double det = a1*b2-a2*b1;
	if(sign(det)==0){
		if(eq(p1.x*a2+p1.y*b2,c2)) return 0;		
		pans = p1;
		return 2;
	}
	pans = pt((1.0l*c1*b2-1.0l*b1*c2)/det,(1.0l*a1*c2-1.0l*a2*c1)/det);
	return 1;
}

//-----------------------------------------------

//rotaciona sentido anti horario
pt rot(pt p, double teta){
    return pt(p.x*cos(teta)-p.y*sin(teta),p.y*cos(teta)+p.x*sin(teta));
}

pt forca_mod(pt p, long double m){
    long double cm = p.mod();
    return pt(p.x*m/cm,p.y*m/cm);
}

double pi = acos(-1.0l);

pair<pt,pt> get_pts(pt p1, pt p2){
	pt vd = p2-p1;
	vd = forca_mod(vd,vd.mod()/2);
	pt pm = p2-vd;
	vd = rot(vd,pi/2);
	pt pc = pm-vd;
	return {pm,pc};
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n; cin >> n;
	vector<pt> v(n);
	fr(i,n) v[i].read();
	
	for(int i = 2; i<n; i++){
		auto [pm1,pc1] = get_pts(v[0],v[1]);
		auto [pm2,pc2] = get_pts(v[1],v[i]);
		pt centro;
		assert(line_intersection(pm1,pc1,pm2,pc2,centro));
		double r = (centro-v[0]).mod2();
		int cnt = 0;
		for(int j = 2; j<n; j++){
			if(j==i) continue;
			if((centro-v[j]).mod2()<r) cnt++;
		}
		if(cnt==(n-3)/2){
			v[0].print();
			v[1].print();
			v[i].print();
			return 0;
		}
	}
	assert(0);
}
