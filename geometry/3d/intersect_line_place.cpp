#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

#define eb emplace_back

#define prin(a) cout << #a << " = " << (a) << endl
#define prinp(p) cout << #p << " = " << p.x << ", " << p.y << ", " << p.z << endl

/*
    usar long double nos pontos pq distancia eh um numero real msm, ja usar sempre double facilita
*/

typedef long double ld;
const ld INF = 1e19;
const ld EPS = 1e-7;
const ld PI = acos(-1.0l);

int sgn(ld x){
    if(x>EPS) return 1;
    if(x<-EPS) return -1;
    return 0;
}

struct pt{
    ld x, y, z;
    pt(){}
    pt(ld a, ld b, ld c) : x(a), y(b), z(c) {}
    pt operator - (pt p2){
        return pt(x-p2.x,y-p2.y,z-p2.z);
    }
    pt operator + (pt p2){
        return pt(x+p2.x,y+p2.y,z+p2.z);
    }
    ld operator * (pt p2){
        return x*p2.x+y*p2.y+z*p2.z;
    }
    pt operator ^(pt p2){
        pt ans;
        ans.x = y*p2.z - z*p2.y;
        ans.y = z*p2.x - x*p2.z;
        ans.z = x*p2.y - y*p2.x;
        return ans;
    }
    ld mod(){
        return sqrt(x*x+y*y+z*z);
    }
    int nulo(){
        return fabs(x)<EPS and fabs(y)<EPS and fabs(z)<EPS;
    }
};


ld misto(pt p1, pt p2, pt p3){
    return (p1^p2)*p3;
}   


//retorna infinito se distancia do ponto ao triangulo eh maior q a distancia do ponto a algum dos segmentos
//ou seja, retorna infinito se ponto nao pertence ao prisma do triangulo
ld dist_pt_t(pt p, vector<pt> v){
    ld ans = 1e18;
    assert(v.size()==3);
    pt v1 = v[1]-v[0];
    pt v2 = v[2]-v[0];
    
    pt n = (v1^v2);
    
    fr(i,3){
        pt vb = v[(i+1)%3]-v[i];
        pt eq = vb^n;
        ld d = eq*v[i];
        pt vp = p-v[i];
        //se ponto coplanar com um dos lados do prisma (vp^vb eh nulo), ele esta dentro do prisma (poderia desconsiderar pois distancia vai ser a msm da distancia do ponto ao segmento)
        if(!(vp^vb).nulo() and (v[(i+2)%3]*eq>d) ^ (p*eq>d)) return INF;
    }
    
    //se ponto for coplanar ao triangulo (e dentro do triangulo) vai retornar zero corretamente
    return fabs(misto(p-v[0],v1,v2)/n.mod());
}

ld dist_pt_line(pt p, vector<pt> li){
    return ((li[1]-li[0])^(p-li[0])).mod()/(li[1]-li[0]).mod();
}

ld dist_line(vector<pt> vp1, vector<pt> vp2){
    pt n = (vp1[1]-vp1[0])^(vp2[1]-vp2[0]);
    if(n.nulo()) //retas paralelas - dist ponto a reta
        return dist_pt_line(vp2[0],vp1);
        
    pt o1o2 = vp2[0]-vp1[0];
    return fabs((o1o2*n)/n.mod());
}

//nao funciona se segmento contem o outro segmento (retas paralelas e intersecao nao nula)
ld dist_seg(vector<pt> vp1, vector<pt> vp2){

    assert(vp2.size()==2);
    assert(vp1.size()==2);
    
    //pontos extremos do segmento
    ld ans = INF;
    fr(i,2){
        fr(j,2) ans = min(ans,(vp1[i]-vp2[j]).mod());
    }
    
    //verificando distancia de ponto extremo com ponto interno dos segs
    fr(teste,2){
        fr(i,2){
            int curok = 1;
            fr(cor,2){
                pt vb = vp2[!cor]-vp2[cor];
                pt vv = vp1[i]-vp2[cor];
                ld ang = atan2((vb^vv).mod(),vb*vv);
                if(ang>PI/2) curok = 0;
            }
            if(curok)
                ans = min(ans,dist_pt_line(vp1[i],vp2));
        }
        swap(vp1,vp2);
    }
    
    //ponto interno com ponto interno dos segmentos
    pt v1 = vp1[1]-vp1[0], v2 = vp2[1]-vp2[0];
    pt n = v1^v2;
    if(!n.nulo()){
        int ok = 1;
        fr(teste,2){
            pt n2 = v2^n;
            pt o1o2 = vp2[0]-vp1[0];
            ld escalar = (o1o2*n2)/(v1*n2);
            if(escalar<0 or escalar>1) ok = 0;
            swap(vp1,vp2);
            swap(v1,v2);
        }
        if(ok) ans = min(ans,dist_line(vp1,vp2));
    }
    
    return ans;
}

pt esc(pt p, ld k){
    p.x*=k;
    p.y*=k;
    p.z*=k;
    return p;
}

//retorna 0 se forem paralelos (0 msm q se intersecao infinita ou nula)
//p assume o valor da intersecao entre o plano e a reta
bool intersect_plane_line(vector<pt> t, vector<pt> l, pt &p){
    assert(t.size()==3);
    assert(l.size()==2);
    pt n = (t[1]-t[0])^(t[2]-t[0]);
    ld d = n*t[0];
    pt dl = l[1]-l[0];
    pt ol = l[0];
    
    if(sgn(n*dl)==0) return 0;
    
    ld k = (d-n*ol)/(n*dl);
    
    p = ol+esc(dl,k);
    return 1;
}

bool cruza(vector<pt> t, vector<pt> l){
    pt p;
    
    assert(t.size()==3);
    assert(l.size()==2);
    
    if(intersect_plane_line(t,l,p)==0) return 0;
    
    return dist_pt_t(p,t)<EPS and (p-l[0])*(p-l[1])<0;
}

//solves problem I from: https://codeforces.com/gym/102040/standings/friends/true

int main(){
	
	int test;
	cin >> test;
	
	fr(cnt_test,test){
	    vector<pt> t[2];
	    
	    ld dist = INF;
	    
	    fr(cor,2){
	        fr(ip,3){
	            ld x, y, z;
	            scanf("%Lf%Lf%Lf", &x, &y, &z);
	            t[cor].eb(x,y,z);
	        }
	    }
	    
	    fr(i_sem,3){
	        fr(j_sem,3){
	        
	            vector<pt> v1, v2;
	            fr(i,3) if(i!=i_sem) v1.eb(t[0][i]);
	            fr(j,3) if(j!=j_sem) v2.eb(t[1][j]);
	            
	            dist = min(dist,dist_seg({v1[0],v1[1]},{v2[0],v2[1]}));
	        }
	    }
	    
	    fr(cor,2){
	        fr(i,3){
	            dist = min(dist,dist_pt_t(t[!cor][i],t[cor]));
	        }
	    }
	    
	    fr(cor,2){
	        fr(i_sem,3){
	            vector<pt> l;
	            fr(i,3) if(i!=i_sem) l.eb(t[!cor][i]);
	            if(cruza(t[cor],l)){
	                dist = 0;
	            }
	        }
	    }  
	    
	    printf("%.10Lf\n", dist);
	}
	
	return 0;
}

