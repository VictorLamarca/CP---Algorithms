#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

/*
	Implementação de bignum
	
	Lembrar de:
		Usar com inicialização de long long
			if(ans==bignum(0ll)) do something
		Todas as operações matematicas típicas são suportadas:
			+ - * % /
		Para printar soh usar
			x.print(); //assume base 1e9, que é a padrão
	
	Submissão exemplo minha: https://codeforces.com/gym/102785/submission/110068694
	Na mais desse código a sessão de testes
	
	Outras implementações:
		De chines no CF: https://codeforces.com/contest/98/submission/3856625
		Macacario ITA (contem erros): https://github.com/splucs/Competitive-Programming/blob/master/Macac%C3%A1rio/Math/bignum.cpp
*/

typedef long long ll;
//mudar base para 1e9 para ser mais eficiente, mas deixar como 10 para testes
const int base = round(1e9);

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
		printf("%09d", a[i]);
		//printf("%d", a[i]);
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

vector<int> multMod(const vector<int> &x, const vector<int> &y) const{
	int n = sz(x)+sz(y);
	long long carry = 0, acum;
	vector<int> z(n);
	for (int k=0; k<n || carry; k++) {
		if (k == n) z.push_back(0);
		acum = carry; carry = 0;
		for (int i=0, j=k; i <= k && i<sz(x); i++, j--) {
			if (j >= sz(y)) continue;
			acum += x[i] * 1ll * y[j];
			carry += acum / base;
			acum %= base;
		}
		z[k] = acum;
	}
	fix(z);
	return z;
}

bignum operator*(const bignum &n2) const{
	vector<int> val = multMod(a,n2.a);
	return bignum(val,sign*n2.sign);
}

vector<int> divide2teto(const vector<int> &x){
	int carry = 0;
	vector<int> ans(sz(x));
	for(int i = sz(x)-1; i>=0; i--){
		int val = x[i];
		if(carry) val+=base;
		ans[i] = val/2;
		carry = val%2;
	}
	if(carry) ans = addMod(ans,vector<int>(1,1));
	fix(ans);
	return ans;
}	

void divideModBs(const vector<int> &x, const vector<int> &y, vector<int> & q, vector<int> & r){
	if(cmp(x,y)==1){
		q = vector<int>(1,0);
		r = x;
		return;
	}
	vector<int> lo = vector<int>(1,0);
	vector<int> hi = x;
	
	while(cmp(lo,hi)==1){
		vector<int> mid = divide2teto(addMod(lo,hi));
		vector<int> val = multMod(mid,y);
		if(cmp(x,val)==1) hi = subtractMod(mid,vector<int>(1,1));
		else lo = mid;		
	}
	q = lo;
	fix(q);
	r = subtractMod(x,multMod(lo,y));
	fix(r);
}

bignum operator /(const bignum &n2){
	vector<int> q, r;
	divideModBs(a,n2.a,q,r);
	return bignum(q,sign*n2.sign);
}

bignum operator %(const bignum &n2){
	vector<int> q, r;
	divideModBs(a,n2.a,q,r);
	return bignum(r,sign);
}

}; // end bignum

ll gera(ll minx, ll maxx){
	assert(maxx>=minx);
	return minx + rand()%(maxx-minx+1);
}

clock_t ts;

void prin_time(){
	printf("Time: %2lf\n", (double)(clock()-ts)/CLOCKS_PER_SEC);
}

int main(){
	if(0){
		bignum a(171), b(39);
		ts = clock();
		bignum c = a/b;
		prin_time();
		c.print();
		return 0;
	}
	
	srand(time(0));
	ts = clock();
	fr(i,1e5){
		if(i%1000==0) prin(i);
		ll maxv = 100000;
		ll a = gera(-maxv,maxv), b = gera(-maxv,maxv);
		if(i%2) b = gera(-100,100);
		if(b==0) b++;
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
	prin_time();
}
