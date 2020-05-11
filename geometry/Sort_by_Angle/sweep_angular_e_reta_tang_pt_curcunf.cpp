#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define fi first
#define se second

//solves h from: https://codeforces.com/gym/101557

template<class T>
T sq(T x){
	return x*x;
}

struct pt{
	double x, y;
	pt(){}
	pt(double _x, double _y){
		x = _x, y = _y;
	}
	double mod(){
        return sqrt(sq(x)+sq(y));
    }
	pt operator -(pt b){
		return pt(x-b.x,y-b.y);
	}
	pt operator +(pt b){
		return pt(x+b.x,y+b.y);
	}
	double operator ^(pt b) const{
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

pt rot(pt p, double teta){
    return pt(p.x*cos(teta)-p.y*sin(teta),p.y*cos(teta)+p.x*sin(teta));
}

pt forca_mod(pt p, double m){
    double cm = p.mod();
    return pt(p.x*m/cm,p.y*m/cm);
}

const int N = 1e3+10;
ll x_centro[N], y_centro[N], raio[N], x_pt[N], y_pt[N];
pair<pt,pt> p_tang[N];
vector<pt> ponto, pcirc;
ll dist_tg_quad[N];
ll n, m;

int vis[N];
vector<int> g[N];

void dfs(int no){
	vis[no] = 1;
	for(auto &it : g[no]){
		if(!vis[it]) dfs(it);	
	}
}

ll quad_dist(ll i_ponto, ll i_circunf){
	return sq(x_centro[i_circunf]-x_pt[i_ponto])+sq(y_centro[i_circunf]-y_pt[i_ponto]);
}

int main(){
	cin >> n >> m;
	fr(i,n){
		scanf("%lld%lld", x_pt+i, y_pt+i);
		ponto.emplace_back(x_pt[i],y_pt[i]);
	}
	fr(i,m){
		scanf("%lld%lld%lld", x_centro+i, y_centro+i, raio+i);
		pcirc.emplace_back(x_centro[i],y_centro[i]);
	}
	
	fr(i_pivo,n){
		set<pair<ll,int>> circ_ativ;
		vector<tuple<pt,int,int,int>> ev;
		fr(j,n){
			if(i_pivo==j) continue;
			ev.emplace_back(ponto[j]-ponto[i_pivo],0,0,j);
		}
		fr(i,m){
			double teta = asin(raio[i]/sqrt((double)quad_dist(i_pivo,i)));
			pt vet_dist = pcirc[i]-ponto[i_pivo];
			double dist_pt = sqrt(quad_dist(i_pivo,i)-sq(raio[i]));
			dist_tg_quad[i] = quad_dist(i_pivo,i)-sq(raio[i]);
			pt vet_reta_tg_l = forca_mod(rot(vet_dist,-teta),dist_pt);
			pt vet_reta_tg_r = forca_mod(rot(vet_dist,teta),dist_pt);
			p_tang[i] = {ponto[i_pivo]+vet_reta_tg_l,ponto[i_pivo]+vet_reta_tg_r};
			
			ev.emplace_back(vet_reta_tg_l,1,1,i);
			ev.emplace_back(vet_reta_tg_r,1,0,i);
			if(vet_reta_tg_r<vet_reta_tg_l){ 
				circ_ativ.emplace(dist_tg_quad[i],i);
			}
		}
		sort(all(ev));
	
		for(auto &tup : ev){
			pt v; int tipo, ativ, id; tie(v,tipo,ativ,id) = tup;
			if(tipo==0){ //ponto
				if(!circ_ativ.empty()){
					ll dist, i_circ; tie(dist,i_circ) = *circ_ativ.begin();
					pt vb = p_tang[i_circ].fi-p_tang[i_circ].se;
					pt v_pivo = ponto[i_pivo]-p_tang[i_circ].se;
					pt v_obj = ponto[id]-p_tang[i_circ].se;
					if( ((vb^v_pivo)>0)!=((vb^v_obj)>0)) continue;
				}
				g[i_pivo].push_back(id);
			} else{
				if(ativ){
					circ_ativ.emplace(dist_tg_quad[id],id);					
				} else{
					circ_ativ.erase(pair<ll,int>(dist_tg_quad[id],id));		
				}
			}
		}
	}
	
	int ans = 0;
	fr(i,n){
		if(!vis[i]){
			ans++;
			dfs(i);
		}
	}
	
	cout << ans-1 << endl;
}
