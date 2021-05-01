#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
typedef long long ll;

//solves https://acm.timus.ru/problem.aspx?space=1&num=1710

template<class T>
T sq(T x){
	return x*x;
}

const long double PI = acosl(-1.0l);

template<class T>
struct pt{
	T x, y;
	pt(){}
	pt(T _x, T _y){
		x = _x, y = _y;
	}
	void read(){
		cin >> x >> y;
	}
	void print(){
		if(is_same<T,int>::value) cout << x << " " << y << "\n";
		else if(is_same<T,ll>::value) cout << x << " " << y << "\n";
		else cout << fixed << setprecision(10) << x << " " << y << "\n";
	}
	long double mod(){
        return sqrtl(sq(x)+sq(y));
    }
	template <class R>
	pt<T> operator -(pt<R> b){
		return pt<T>(x-b.x,y-b.y);
	}
	template <class R>
	pt<T> operator +(pt<R> b){
		return pt<T>(x+b.x,y+b.y);
	}
	//produto vetorial
	T operator ^(pt<T> b) const{
		return x*b.y-y*b.x;
	}
	//produto escalar
	T operator *(pt<T> b) const{
		return x*b.x+y*b.y;
	}
	int quad() const{
		int ans = 0;
		if(x<0) ans++;
		if(y<0) ans^=1, ans+=2;
		return ans;
	}
	bool operator <(pt<T> b) const{
		if(this->quad()==b.quad()){
		    return ((*this)^b)>0;
		}
		return this->quad()<b.quad();
	}
};

pt<double> add_mod(pt<ll> p, double add){
    double cm = p.mod();
    double m = cm+add;
    return pt(p.x*m/cm,p.y*m/cm);
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	pt<ll> a, b, c;
	a.read();
	b.read();
	c.read();
	pt<ll> vab = b-a, vac = c-a, vcb = b-c, vca = a-c;
	if(vac*vab<=0 or vca*vcb==0){
		cout << "YES\n";
		return 0;
	}
	
	double add;
	if(vca*vcb>0){ 
		double cos_alfa = (vca*vcb)/(vca.mod()*vcb.mod());
		double d = cos_alfa*vcb.mod();
		add = -2*d;
		if(2*d>=vac.mod()){
			cout << "YES\n";
			return 0;
		}
	} else{
		double cos_alfa = (vac*vcb)/(vac.mod()*vcb.mod());
		double d = cos_alfa*vcb.mod();
		add = 2*d;
	}
	
	pt<double> vac_double = add_mod(vac,add);
	pt<double> ans = vac_double+a;
	
	cout << "NO\n";
	a.print();
	b.print();
	ans.print();
}
