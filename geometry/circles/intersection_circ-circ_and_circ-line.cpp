#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0;i<n;i++)
#define all(v) (v).begin(),(v).end()
#define eb emplace_back
#define fi first
#define se second

//solves problem B from https://codeforces.com/gym/101666/attachments

const double PI = acos(-1.0);

const double eps = 5e-7;

int sgn (double x) { return x < -eps ? -1 : x > eps; }
int cmp(double a, double b){ return sgn(a-b);} //cmp(a,b) -1 se a<b

double sq(double x){
    return x*x;
}

struct pt{
    double x, y;
    pt(){}
    pt (double a, double b){
        x = a, y = b;
    }
    
    double operator ^(pt p2){
        return x*p2.y-y*p2.x;
    }
    double operator *(pt p2){
        return x*p2.x+y*p2.y;
    }
    
    double mod(){
        return sqrt(sq(x)+sq(y));
    }
    
    pt operator -(pt p2){
        return pt(x-p2.x,y-p2.y);
    }
    
    pt operator +(pt p2){
        return pt(x+p2.x,y+p2.y);
    }
};

bool operator <(const pt &a, const pt &b){
    if(cmp(a.x,b.x)!=0) return cmp(a.x,b.x)==-1;
    return cmp(a.y,b.y)==-1;
}

bool operator <=(const pt &a, const pt &b){
    if(cmp(a.x,b.x)!=0) return cmp(a.x,b.x)==-1;
    return cmp(a.y,b.y)<=0;
}

bool operator ==(const pt &a, const pt &b){
    return sgn(a.x-b.x)==0 and sgn(a.y-b.y)==0;
}

pt forca_mod(pt p, double m){
    double cm = p.mod();
    return pt(p.x*m/cm,p.y*m/cm);
}

pt rot(pt p, double teta){
    return pt(p.x*cos(teta)-p.y*sin(teta),p.y*cos(teta)+p.x*sin(teta));
}

/*
    Retorna vetor de ponto(s) de intersecao entre
    duas circunferencias. Vetor pode ter tamanho 0, 1 ou 2
*/
vector<pt> intersec_circ_circ(pt a, double ra, pt b, double rb){
    vector<pt> ans;
    if(a==b) return vector<pt>();
    if(ra>rb) swap(ra,rb), swap(a, b);
    double dist = (a-b).mod();
    
    if(dist>rb-ra and dist<ra+rb){
        double dx = fabs(sq(dist)+sq(ra)-sq(rb))/2/dist;
        pt va;
        if(sq(dist)+sq(ra)>sq(rb)) va = forca_mod(b-a,ra);
        else va = forca_mod(a-b,ra);
        double teta = acos(dx/ra);
        ans.eb(a+rot(va,teta));
        ans.eb(a+rot(va,2*PI-teta));
    } else if(dist==ra+rb or dist==rb-ra){
        ans.eb(b+forca_mod(a-b,rb));
    }
    
    sort(all(ans));
    return ans;
}

pt pmax(pt pa, pt pb){
    if(pa<pb) return pb;
    return pa;
}

double dist_p_line(pt p, pt p1, pt p2){
    pt vb = p2-p1;
    pt vp = p-p1;
    return fabs(vb^vp)/vb.mod();
}

bool a_esquerda(pt p, pt pa, pt pb){
    pt vb = pb-pa;
    pt vp = p-pa;
    return (vb^vp)>=0;
}

/*
    Retorn projecao do ponto p
    na reta definida por pa e pb
*/
pt proj(pt p, pt pa, pt pb){
    double dist = dist_p_line(p,pa,pb);
    pt vp = forca_mod(pb-pa,dist);
    swap(vp.x,vp.y);
    if(a_esquerda(p,pa,pb)) vp.y*=-1;
    else vp.x*=-1;
    return p+vp;
}

/*
    retorna par de intersecao entre circulo e linha
    Requer que hája duas intersecoes (ou seja, 
    distancia entre centro e reto é menor que o raio)
    se nao tiver 2 intersecoes dara erro
*/  
pair<pt,pt> intersec_circ_line(pt p, double rc, pt pa, pt pb){
    double dist = dist_p_line(p,pa,pb);
    double x = sqrt(sq(rc)-sq(dist));
    
    pair<pt,pt> ans;
    ans.fi = proj(p, pa, pb) + forca_mod(pa-pb,x);
    ans.se = proj(p, pa, pb) - forca_mod(pa-pb,x);
    if(ans.se<ans.fi) swap(ans.fi,ans.se);
    return ans;
}

//------------END OF AUX FUNCTIONS------------------

pt po, pd;
int n;

const int N = 40;

pt centro[N];
double raio[N];

vector<pt> pn;

const int NN = 1e5+10;
vector<pair<int,double>> g[NN];
int vis[NN];

bool existe(int ii, int jj){
    pt pa = pn[ii];
    pt pb = pn[jj];
    if(pb<pa) swap(pa,pb);
    
    vector<pair<pt,pt>> v;
    
    fr(i,n){
        if(dist_p_line(centro[i],pa,pb)<raio[i]) v.eb(intersec_circ_line(centro[i],raio[i],pa,pb));
    }
    
    sort(all(v));
    
    pt pc = pa;
    for(auto &par : v){
        if(par.fi<=pc) pc = pmax(pc,par.se);
    }
    
    return pb<=pc;
}

double dij(){
    set<pair<double,int>> s;
    s.emplace(0,0);
    
    while(!s.empty()){
        double curd;
        int no;
        tie(curd,no) = *s.begin();
        s.erase(s.begin());
        
        if(vis[no]) continue;
        vis[no] = 1;
        
        if(no==1) return curd;
        
        for(auto &par : g[no]){
            int it;
            double c;
            tie(it,c) = par;
            if(!vis[it]){
                s.emplace(curd+c,it);
            }
        }
    }
    
    puts("impossible");
    exit(0);
}

int main(){
    scanf("%lf%lf", &po.x, &po.y);
    scanf("%lf%lf", &pd.x, &pd.y);
    cin >> n;
    
    fr(i,n){
        scanf("%lf%lf%lf", &centro[i].x, &centro[i].y, raio+i);
    }
    
    pn.eb(po);
    pn.eb(pd);
    
    fr(i,n){
        fr(j,i){
            vector<pt> cur = intersec_circ_circ(centro[i],raio[i],centro[j],raio[j]);
            for(auto &p : cur) pn.eb(p); 
        }
    }
    
    fr(i,pn.size()) fr(j,i){
        if(existe(i,j)){
            double c = (pn[i]-pn[j]).mod();
            g[i].eb(j,c);
            g[j].eb(i,c);
        }
    }
    
    printf("%.15lf\n", dij());
}   
