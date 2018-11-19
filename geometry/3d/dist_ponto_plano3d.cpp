#include <bits/stdc++.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)
// for(auto it : g[i].nb)

typedef long long ll;

#define pb push_back

#define fi first
#define se second
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

const ll MOD = 1e9+7;

//LLONG_MAX
//-DBL_MAX
//__builtin_popcountll(ll x) - __builtin_popcount(int x)

bool debug = 1;
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define print(tup) if(debug) cout << #tup << " = {" << get(tup,0) << ", " << get(tup,1) << ", " << get(tup,2) << "}\n"
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

/*usar long double nos pontos pq distancia eh um numero real msm, ja usar sempre double facilita
*/

#define ld long double
#define INF 1e18
#define EPS 1e-7
const long double PI = acos(-1.0l);

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

ld dist_pt_line(pt p, array<pt,2> li){
    return ((li[1]-li[0])^(p-li[0])).mod()/(li[1]-li[0]).mod();
}

ld dist_line(array<pt,2> vp1, array<pt,2> vp2){
    pt n = (vp1[1]-vp1[0])^(vp2[1]-vp2[0]);
    if(n.nulo()) //retas paralelas - dist ponto a reta
        return dist_pt_line(vp2[0],vp1);
        
    pt o1o2 = vp2[0]-vp1[0];
    return fabs((o1o2*n)/n.mod());
}

//nao funciona se segmento contem o outro segmento (retas paralelas e intersecao nao nula)
ld dist_seg(array<pt,2> vp1, array<pt,2> vp2){
    ld ans = INF;
    fr(i,2){
        fr(j,2) ans = min(ans,(vp1[i]-vp2[j]).mod());
    }
    
    fr(teste,2){
        fr(i,2){
            int curok = 1;
            fr(cor,2){
                pt vb = vp2[!cor]-vp2[cor];
                pt vv = vp1[i]-vp2[cor];
                ld ang = acos((vb*vv)/vb.mod()/vv.mod());
                if(ang>PI/2) curok = 0;
            }
            if(curok)
                ans = min(ans,dist_pt_line(vp1[i],vp2));
        }
        swap(vp1,vp2);
    }
    
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

pt v[2][10];

int main(){
	//FILE_IN FILE_OUT
	
	/*
	codigo para parte do problema G da subreg 2010
	
	Ferramenta que calcula distancia ente linhas no 3d
	http://www.ambrsoft.com/TrigoCalc/Line3D/Distance2Lines3D_.htm
	
	Ferramenta para plotar figuras 3d e ver oq acontece
	https://www.geogebra.org/3d?lang=pt-BR
	
	Notebook que mostra formulas a respeito disso - pag 90
	https://vlecomte.github.io/cp-geo.pdf
	
	
	*/
	
	int t;
	cin >> t;
	fr(ii,t){
	    fr(cor,2){
            fr(i,4){
                int x,y,z;
                scanf("%d%d%d", &x, &y, &z);
                v[cor][i].x = x;
                v[cor][i].y = y;
                v[cor][i].z = z;
                
            }
        }
        
        ld ans = INF;
        
        fr(cor,2){
            fr(ipt,4){
                fr(j,4){
                    vector<pt> vcur;
                    fr(i,4) if(i!=j) vcur.pb(v[!cor][i]);
                    ans = min(ans,dist_pt_t(v[cor][ipt],vcur));
                }
            }
        }
        
        fr(i1,4){
            fr(j1,i1){
                fr(i2,4){
                    fr(j2,i2){
                        ans = min(ans,dist_seg({v[0][i1],v[0][j1]},{v[1][i2],v[1][j2]}));
                    }
                }
            }
        }
        
        printf("%.2lf\n", (double)(ans));
        
	}
	
	return 0;
}

