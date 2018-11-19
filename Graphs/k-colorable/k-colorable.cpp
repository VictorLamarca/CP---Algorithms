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

const long double PI = acos(-1.0l);
const ll MOD = 1e9+7;

//LLONG_MAX
//-DBL_MAX
//__builtin_popcountll(ll x) - __builtin_popcount(int x)

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl
#define soprin(a) if(debug) cout << (a)
#define ppal(a)  if(debug) cout << #a << endl
#define prinsep if(debug) cout << "------" << endl
#define cendl if(debug) cout << endl
#define prinpar(p) if(debug) cout << #p << ".fi=" << (p).fi << " " << #p << ".se=" << (p).se << endl
#define print(tup) if(debug) cout << #tup << " = {" << get(tup,0) << ", " << get(tup,1) << ", " << get(tup,2) << "}\n"
#define prinv(v) if(debug){ cout << #v << ":" << endl; for(auto it = (v).begin(); it!=(v).end();it++){ cout << *it << " ";} cout << endl;}

const int N = 16;

//problema original: https://vjudge.net/contest/244493#problem/D

//grafo eh matriz de adjacencia (soh qq bitwise, o iesimo bit eh se vai para o iesimo no)
int g[N];

int n, m;

void inic(){
	fr(i,N) g[i] = 0;
}

int ind[N];

/*
codeforces link do tutorial:
http://codeforces.com/blog/entry/57496

P(k) eh o numero de maneiras de colorir grafo com K cores

P(K) eh o somatorio de:
	Pra todo U subconjunto de V (set de vertices):
		P(K) += (-1)^(|V|-|U|)*(ind(U))^K

ind(U) eh o numero de subconjuntos de U que sao independentes (que sao 1 colorivel - sem edge entre 2 deles)

pag 13 desse paper tem explicacao do ind(u)=g+1 na tabela
https://compscicenter.ru/media/course_class_attachments/Thore_Husfeldt_Graph_colouring_algorithms.pdf

input do grafo do paper:
1
4 4
0 2
1 2
1 3
2 3

x=0 v=1 u=2 w=3

no pape
*/


int solve(){

    vector<int> ind(1<<n), s(1<<n);
    
    fr(i,1<<n){
    	//s[i] indica se eh positivo ou negativo
    	if((n-__builtin_popcount(i))%2) s[i] = -1;
    	else s[i]  = 1;
    }
    
    ind[0] = 1;
    
    frr(i,1,(1<<n)-1){
        int ctz = __builtin_ctz(i);//indice do primeiro bit setado de i
        
        /*i representa a mascara correspondente ao subconjunto U dos vertices
        dado um subconjunto U' = U\{v} (U sem um vertice v)
        ind(U) = ind(U') + ind(U' tirando os vertices vizinhos a v)
        	(o segundo termo eh somado de novo pq corresponde a tds os subconjuntos
        	contados de novo mas agora considerando que v esteja la, por isso sao novos subconjuntos)
        */
        ind[i] = ind[i-(1 << ctz)] + ind[(i-(1<<ctz))&~g[ctz]];
    }
    
    ///*
    //imprimindo ind(i)
    
    fr(i,(1<<n)){
    	vector<bool> v;
    	int aux = i;
    	fr(j,n) v.pb(i&(1<<j));
    	fr(i,v.size()){
    		printf("%d", (int)(v[i]));
    		if(i!=v.size()-1) printf(" ");
    		else printf(": ");
    	}
    	printf("%d\n", ind[i]);
    	
    }
    //*/
    
    frr(k,1,min(4,n)){
        ll tot = 0;
        fr(i,1<<n){
                ll cur = (s[i]*ind[i]);
                s[i] = cur; //isso serve para simular o elevar a k
                tot += cur;
        }
        if(tot) return k;
        // tot eh P(k)
    }
    
    
    
    return 5;
}

int main(){
	//FILE_IN FILE_OUT
	
	int t;
	cin >> t;
	
	fr(ii,t){
		inic();
		
		scanf("%d%d", &n, &m);
		
		fr(i,m){
			int l, r;
			scanf("%d%d", &l, &r);
			g[l] |= (1<<r);
			g[r] |= (1<<l);
		}
		
		int ans = solve();
		assert(ans);
		
		if(ans==5) puts("many");
		else printf("%d\n", ans);
	}
	
	return 0;
}

