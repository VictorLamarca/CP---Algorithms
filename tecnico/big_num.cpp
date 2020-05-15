#include <bits/stdc++.h>
using namespace std;

//submissao modelo sugerida no codeforces: https://codeforces.com/contest/98/submission/3856625
// macacario ITA: https://github.com/splucs/Competitive-Programming/blob/master/Macac%C3%A1rio/Math/bignum.cpp (contem erros)

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

//mudar base para 1e9 para ser mais eficiente, mas deixar como 10 para testes
const int base = 10;

//Remover Leading zeros
void fix(vector<int> &a) {
	while (sz(a) > 1 && a.back() == 0) {
		a.pop_back();
	}
}

struct bignum{

int sign = 1;
vector<int> a;

void print() {
	if(sign<0) printf("-");
	printf("%d", a.empty() ? 0 : a.back());
	for (int i=(int)sz(a)-2; i>=0; --i) {
		//printf("%09d", a[i]);
		printf("%d", a[i]);
	}
	puts("");
}

//1-> x<y,  0->x>y;  2->x==y
//true if x<=y
int cmp(const vector<int> &x,const vector<int> &y) const{
	if (sz(x) != sz(y)) return sz(x) < sz(y);
	for(int i=(int)sz(x)-1; i>=0; i--) {
		if (x[i] != y[i]) return x[i] < y[i];
	}
	return 2;
}

bool operator <(const bignum &n2) const{
	if(sign!=n2.sign){
		return sign<n2.sign;
	}
	if(sign==-1) return cmp(a,n2.a)==0;
	return cmp(a,n2.a)==1;
}

bool operator ==(const bignum &n2) const{
	return sign==n2.sign and cmp(a,n2.a)==2;
}

bignum(){}

bignum(char* s) {
	a.clear();
	int inic = 0;
	if(s[0]=='-') sign = -1, inic = 1;
	for (int i=(int)strlen(s); i>inic; i-=9) {
		s[i] = 0;
		a.push_back (atoi (i>=9 ? s+i-9 : s));
	}
	fix(a);
}

bignum(ll n) {
	a.clear();
	if(n<0){
		sign = -1;
		n = -n;
	}
	if (n == 0) a.push_back(0);
	while(n > 0) {
		a.push_back(n%base);
		n /= base;
	}
}

bignum(vector<int> &_a, int _sign) {
	a = _a, sign = _sign;
	fix(a);
	if(a==vector<int>(1,0)) sign = 1;
}

vector<int> addMod(const vector<int> &x, const vector<int> &y){
	int carry = 0, n = max(sz(x), sz(y));
	vector<int> z(n);
	for (int i=0, xi, yi; i<n; i++) {
		xi = i < (int)sz(x) ? x[i] : 0;
		yi = i < (int)sz(y) ? y[i] : 0;
		z[i] = carry + xi + yi;
		carry = z[i] / base;
		z[i] %= base;
	}
	if (carry > 0) z.push_back(carry);
	fix(z);
	return z;
}

vector<int> subtractMod(const vector<int> &x, const vector<int> &y) {
	int carry = 0, n = max(sz(x), sz(y));
	vector<int> z(n);
	for (int i=0, xi, yi; i<n; i++) {
		xi = i < (int)sz(x) ? x[i] : 0;
		yi = i < (int)sz(y) ? y[i] : 0;
		z[i] = carry + xi - yi;
		carry = z[i] < 0 ? -1 : 0;
		if (z[i] < 0) z[i] += base;
	}
	fix(z);
	return z;
}

bignum operator +(const bignum &n2){
	vector<int> v;
	int signf = 1;
	if(sign==n2.sign){
		v = addMod(a,n2.a);
		signf = sign;
	} else{
		vector<int> x = a, y = n2.a;
		signf = sign;
		if(cmp(x,y)==1){
			signf*=-1;
			swap(x,y);
		}
		v = subtractMod(x,y);
	}
	return bignum(v,signf);
}

bignum operator -(bignum n2){
	n2.sign*=-1;
	return (*this)+n2;
}

vector<int> shiftL(const vector<int> &x, int b) {
	vector<int> c(sz(x)+b);
	for(int i=sz(c)-1; i>=0; i--) {
		if(i>=b) c[i] = x[i-b];
		else c[i] = 0;
	}
	fix(c);
	return c;
}

vector<int> shiftR(const vector<int>& x, int b) {
	vector<int> c;
	if (sz(x) <= b) {
		c.push_back(0);
		return c;
	}
	c.resize(sz(x) - b);
	for(int i=0; i<sz(c); i++) {
		c[i] = x[i+b];
	}
	fix(c);
	return c;
}

bignum operator*(const bignum &n2) const{
	vector<int> b = n2.a;
	int n = sz(a)+sz(b);
	long long carry = 0, acum;
	vector<int> c(n);
	for (int k=0; k<n || carry; k++) {
		if (k == n) c.push_back(0);
		acum = carry; carry = 0;
		for (int i=0, j=k; i <= k && i<sz(a); i++, j--) {
			if (j >= sz(b)) continue;
			acum += a[i] * 1ll * b[j];
			carry += acum / base;
			acum %= base;
		}
		c[k] = acum;
	}
	fix(c);
	return bignum(c,sign*n2.sign);
}

void divideMod(vector<int> x, vector<int> y, vector<int> & q, vector<int> & r) {
	vector<int> z(1,0), p(1,1);
	q = vector<int>(1,0);
	while(cmp(y, x)==1) {
		p = shiftL(p, max(1, sz(x)-sz(y) ) );
		y = shiftL(y, max(1, sz(x)-sz(y) ) );
	}
	while(true) {
		while (cmp(x, y)==1 && cmp(z, p)==1) {
			p = shiftR(p, 1); 
			y = shiftR(y, 1);
		}
		if (cmp(p,z)) break;
		x = subtractMod(x, y);
		q = addMod(q,p);
	}
	fix(q), fix(r);
	swap(x, r);
}

bignum operator /(const bignum &n2){
	vector<int> q, r;
	divideMod(a,n2.a,q,r);
	return bignum(q,sign*n2.sign);
}

bignum operator %(const bignum &n2){
	vector<int> q, r;
	divideMod(a,n2.a,q,r);
	return bignum(r,sign);
}

}; // end bignum

ll gera(ll minx, ll maxx){
	assert(maxx>=minx);
	return minx + rand()%(maxx-minx+1);
}

int main(){
	
	if(0){
		bignum a(2), b(10);
		bignum c = a*b;
		bool menor = (a<b);
		c.print();
		return 0;
	}
	
	srand(time(0));
	fr(i,1e5){
		if(i%1000==0) prin(i);
		ll maxv = 100000;
		ll a = gera(-maxv,maxv), b = gera(-maxv,maxv);
		bignum big_a(a), big_b(b);
		
		//menor
		{
			bool menor = a<b;
			bool big_menor = big_a<big_b;
			if(menor!=big_menor){
				puts("menor");
				prin(big_menor);
				prin(menor);
				prin(a);
				prin(b);
				return 0;
			}
		}
		
		//igual
		{
			bool igual = (a==b);
			bool big_igual = big_a==big_b;
			if(igual!=igual){
				puts("igual");
				prin(a);
				prin(b);
				return 0;
			}
		}
		
		//+
		{
			ll c = a+b;
			bignum big_c = big_a+big_b;
			if(!(bignum(c)==big_c)){
				puts("+");
				prin(a);
				prin(b);
				prin(c);
				big_c.print();
				return 0;
			}
		}		
		
		//-
		{
			ll c = a-b;
			bignum big_c = big_a-big_b;
			if(!(bignum(c)==big_c)){
				puts("-");
				prin(a);
				prin(b);
				return 0;
			}
		}	
		
		//*
		{
			ll c = a*b;
			bignum big_c = big_a*big_b;
			if(!(bignum(c)==big_c)){
				puts("*");
				prin(a);
				prin(b);
				return 0;
			}
		}	
		
		if(b==0) continue;
		
		// /
		{
			ll c = a/b;
			bignum big_c = big_a/big_b;
			if(!(bignum(c)==big_c)){
				puts("div");
				prin(a);
				prin(b);
				return 0;
			}
		}
		
		// %
		{
			ll c = a%b;
			bignum big_c = big_a%big_b;
			if(!(bignum(c)==big_c)){
				puts("%");
				prin(a);
				prin(b);
				return 0;
			}
		}
	}
}
