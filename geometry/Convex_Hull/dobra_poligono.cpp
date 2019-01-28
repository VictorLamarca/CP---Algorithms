#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0;i<n;i++)
#define all(v) (v).begin(),(v).end()
#define eb emplace_back

typedef long long ll;

typedef  pair<double,double> pll;

const double eps = 1e-5;

/*
    Dobra poligono e reflete pontos
    resolve problema f janueary 26 hard Folding:
    http://neerc.ifmo.ru/pcms2client/party
    login: brazil22
    senha: alorurohare
*/

struct pt{
	double x, y;
	pt(){}
	pt(double xx, double yy){
		x = xx, y = yy;
	}
	
	double operator ^(pt p2){
		return x*p2.y-y*p2.x;
	}
	double operator *(pt p2){
		return x*p2.x + y*p2.y;
	}
	
	pt operator -(pt p2){
		return pt(x-p2.x,y-p2.y);
	}
	
	pt operator +(pt p2){
		return pt(x+p2.x,y+p2.y);
	}
	
	bool operator < (pt p2){
		return pll(x,y)<pll(p2.x,p2.y);
	}
	
	bool operator ==(pt p2){
		return fabs(x-p2.x)<eps and fabs(y-p2.y)<eps;
	}
	
	double mod(){
	    return hypot(x,y);
	}
};

vector<vector<pt>> pol;

int f(pt p, pt a, pt b){
	pt vb = b-a;
	pt vc = p-a;
	if(fabs(vb^vc)<=eps){
		return 0;
	}
	if( (vb^vc)>0) return 1;
	return 2;
}

bool inptseg(pt a1, pt b1, pt b2){
	pt v1 = (a1-b1), v2 = (a1-b2);
	return (v1*v2)<=0;
}

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

bool inpol(pt p, vector<pt> &pp){
	int neg = 0, pos = 0;
	
	int n = pp.size();
	
	fr(i,n){
		pt vet = p-pp[i];
		pt seg = pp[(i+1)%n]-pp[i];
		if((vet^seg)>0) pos = 1;
		if((vet^seg)<0) neg = 1;
	}
	
	if(neg and pos) return 0;
	return 1;
}

/*
    se segemnto p1-p2 tem intersecao com a reta p3-p4
    por intersecao em p e retorna 1
    se tem 0 ou infinitas intersecoes retorna 0
*/
int line_intersection(pt p1, pt p2, pt p3, pt p4, pt &p){
	double a1 = p1.y-p2.y, b1 = p2.x-p1.x;
	double c1 = p1.x*a1+p1.y*b1;
	
	double a2 = p3.y-p4.y, b2 = p4.x-p3.x;
	double c2 = p3.x*a2+p3.y*b2;
	
	double det = a1*b2-a2*b1;
	
	if(fabs(det)<eps){
		return 0;
	}
	
	p = { (c1*b2-b1*c2)/det , (a1*c2-a2*c1)/det };
	
	if(!inptseg(p,p1,p2)) return 0;
	return 1;
}

/*
    reflete o ponto p em relacao a reta p1-p2
    o opnto p deve estar a esquerda de p1-p2
*/
pt reflete(pt p, pt p1, pt p2){
    pt vb = p2-p1;
    pt vc = p-p1;
    
    double mod = vb.mod();
    double dist = (vb^vc)/mod;
    
    vb = pt(vb.y/mod*2*dist,-vb.x/mod*2*dist);
    
    return (p+vb);
}

void oper(pt p1, pt p2){
	
	vector<vector<pt>> pola;
	
	for(auto &v : pol){
		vector<pt> esq, dir;
		
		fr(i,v.size()){
			if(f(v[i],p1,p2)==0){
				esq.eb(v[i]);
				dir.eb(v[i]);
			} else if(f(v[i],p1,p2)==1){
				esq.eb(v[i]);
			} else{
				dir.eb(v[i]);
			}
		}
		
		fr(i,v.size()){
			pt p;
			int tam = v.size();
			if(line_intersection(v[i],v[(i+1)%tam],p1,p2,p)==1){
				esq.eb(p);
				dir.eb(p);
			}
		}
		
		esq = mch(esq);
		dir = mch(dir);
		
		if(esq.size()>2){ 
		    vector<pt> aux;
		    for(auto p : esq){
		        aux.eb(reflete(p,p1,p2));
		    }
		    esq = aux;
		    pola.eb(esq);
		}
		if(dir.size()>2) pola.eb(dir);
	}
	
	pol = pola;
}

bool is_in(pt p) {
	for (auto &v: pol) {
		if (inpol(p, v)) return true;
	}	
	return false;
}

double area(double n){
	int K = 5e5;
	int c = 0;
	pt pmn = pol[0][0], pmx = pol[0][0];
	for (auto &v: pol) {
		for (pt p: v) {
			pmn.x = min(pmn.x, p.x);
			pmx.x = max(pmx.x, p.x);
			pmn.y = min(pmn.y, p.y);
			pmx.y = max(pmx.y, p.y);
		}
	}
	
	for (int i=0;i<K;i++) {
		pt rd;
		rd.x = pmn.x + ((double)rand()/RAND_MAX)*(pmx.x - pmn.x);
		rd.y = pmn.y + ((double)rand()/RAND_MAX)*(pmx.y - pmn.y);
		if (is_in(rd)) c++;
	}
	
	double dc = c, dk = K;
	double a = (pmx.x - pmn.x)*(pmx.y - pmn.y);
	return ((dc / dk) * a) / (n * n);
}

int main(){
	int k;
	double n;
	cin >> n >> k;
	
	srand(time(0));
	
	vector<pt> aux;
	aux.eb(pt(-n/2,-n/2));
	aux.eb(pt(-n/2,+n/2));
	aux.eb(pt(+n/2,+n/2));
	aux.eb(pt(+n/2,-n/2));
	
	pol.eb(mch(aux));
	
	fr(i,k){
		pt p1, p2;
		scanf("%lf %lf", &p1.x, &p1.y);
		scanf("%lf %lf", &p2.x, &p2.y);
		
		oper(p1,p2);
	}
	
	cout << (int)(area(n)*100.0 + 0.5) << endl;
}
