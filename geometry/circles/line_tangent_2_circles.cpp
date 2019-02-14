#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define eb emplace_back
#define fi first
#define se second
typedef pair<double,double> pdd;

const double PI = acos(-1.0);

const int N = 300; 

/*
    Solves problem G from https://codeforces.com/group/rKFicKpQAI/contest/237778/standings/groupmates/true
    IFMO Training 12 — NEERC, Moscow Subregional Contest 2009
*/

struct pt{
    double x, y;
    pt(){}
    pt(double a, double b){
        x = a, y = b;
    }
    
    double operator ^(pt p2){
        return x*p2.y-y*p2.x;
    }
    
    double operator *(pt p2){
        return x*p2.x+y*p2.y;
    }
    
    pt operator +(pt p2){
        return pt(x+p2.x,y+p2.y);
    }
    
    pt operator -(pt p2){
        return pt(x-p2.x,y-p2.y);
    }
    
    double mod(){
        return hypot(x,y);
    }
    
    bool operator <(pt p2){
        return pdd(x,y)<pdd(p2.x,p2.y);
    }
    
    bool operator >(pt p2){
        return pdd(x,y)>pdd(p2.x,p2.y);
    }
};

pt forca_mod(pt p, double r){
    double mod = p.mod();
    return pt(p.x*r/mod,p.y*r/mod);
}

// Rotaciona um ponto em relacao a origem
pt rot(pt p, double teta){
    //return pt( p.x*cos(teta) - p.y*sin(teta), p.y*cos(teta) + p.x*sin(teta) );
    double t0 = atan2(p.y,p.x);
    teta+=t0;
    
    double m = p.mod();
    
    return pt(m*cos(teta),m*sin(teta));
}

/* Retorna um vetor com 4 pares de pontos, os pontos que
definem uma reta que tangencia 2 circunferenciae
Assume circuntferencias disjutas
*/
vector<pair<pt,pt>> tg_circ(pt a, double ra, pt b, double rb){
    if(ra>rb) swap(ra,rb), swap(a,b);
    vector<pair<pt,pt>> ans;
    
    double dist = (a-b).mod();
    
    pt pra = forca_mod(b-a,ra);
    pt prb = forca_mod(a-b,rb);
    
    double tetab = acos((rb-ra)/dist);
    double tetaa = PI-tetab;
    
    ans.eb(rot(pra,2*PI-tetaa)+a,rot(prb,tetab)+b);
    ans.eb(rot(pra,tetaa)+a,rot(prb,2*PI-tetab)+b);
    
    double dra = dist*ra/(ra+rb);
    double drb = dist*rb/(ra+rb);
    
    tetaa = acos(ra/dra);
    tetab = acos(rb/drb);
    
    ans.eb(rot(pra,tetaa)+a,rot(prb,tetab)+b);
    ans.eb(rot(pra,2*PI-tetaa)+a,rot(prb,2*PI-tetab)+b);
    
    return ans;
}

int n;

double raio[N];
pt v[N];

const double eps = 5e-7;

double dist_p_line(pt p, pt p1, pt p2){
    pt vb = p2-p1;
    pt vp = p-p1;
    
    return fabs(vb^vp)/vb.mod();
}

// Projeta ponto p na linha definida por p1 e p2
pt proj(pt p, pt p1, pt p2){
    pt vb = p2-p1;
    pt vp = p-p1;
    
    pt vd(-vb.y,vb.x);
    
    if((vb^vp)>=0) vd.x*=-1, vd.y*=-1;
    
    double dist = fabs(vb^vp)/vb.mod();
    
    vd = forca_mod(vd,dist);
    
    return p+vd;
}

void process(pt p1, pt p2){
    if(dist_p_line(v[n],p1,p2)>raio[n]+eps or 
    dist_p_line(v[n+1],p1,p2)>raio[n+1]+eps) return;
    
    pt pa = proj(v[n],p1,p2);
    pt pb = proj(v[n+1],p1,p2);
    
    if(pb<pa) swap(pa,pb);
    
    fr(i,n){
        if(dist_p_line(v[i],p1,p2)<=raio[i]-eps){
            pt p = proj(v[i],p1,p2);
            if(p>pa and p<pb) return;
        }
    }
    
    puts("YES");
    exit(0);
}

int main(){
    freopen("garden.in","r",stdin);
    freopen("garden.out","w",stdout);
    
    cin >> n;
    
    fr(i,n+2){
        scanf("%lf%lf", &v[i].x, &v[i].y);
        scanf("%lf", raio+i);
    }
    
    fr(i,n+2){
        fr(j,i){
            vector<pair<pt,pt>> vt = tg_circ(v[i],raio[i],v[j],raio[j]);
            for(auto par : vt){
                process(par.fi,par.se);
            }
        }
    }
    
    puts("NO");
	
	return 0;
}

