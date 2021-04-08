#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define prinv(v) cout << #v << " = "; for(auto it : v) cout << it << ", "; cout << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

template<class T>
T sq(T x){
	return x*x;
}

const long double pi = acos(-1.0l);

struct pt{
	long double x, y;
	pt(){}
	pt(long double _x, long double _y){
		x = _x, y = _y;
	}
	long double mod(){
        return sqrt(sq(x)+sq(y));
    }
	pt operator -(pt b){
		return pt(x-b.x,y-b.y);
	}
	pt operator +(pt b){
		return pt(x+b.x,y+b.y);
	}
	long double operator ^(pt b) const{
		return x*b.y-y*b.x;
	}
	int quad() const{
		int ans = 0;
		if(x<0) ans++;
		if(y<0) ans^=1, ans+=2;
		return ans;
	}
	bool operator <(pt b) const{
		if(this->quad()==b.quad()){
		    return ((*this)^b)>0;
		}
		return this->quad()<b.quad();
	}
};

//rotaciona sentido anti horario
pt rot(pt p, double teta){
    return pt(p.x*cos(teta)-p.y*sin(teta),p.y*cos(teta)+p.x*sin(teta));
}

pt forca_mod(pt p, long double m){
    long double cm = p.mod();
    return pt(p.x*m/cm,p.y*m/cm);
}

int main(){
	pt a(2,0);
	
	a = rot(a,pi/4);
	
	prin(a.x);
	prin(a.y);
}
