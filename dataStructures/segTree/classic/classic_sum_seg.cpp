#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v).size()
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

//solves https://codeforces.com/contest/1334/problem/F

/*
    Lembrar de 4*N no tamanho da seg
    
    Lembrar de dar build
    
    Nós da seg [1,4*N-1], e nós do vetor [0,n-1] 
    (indices de ambas query e de qual range estou sao de [0,n-1] - na vdd tem n tmbm pois eh aberto
    oq vai de [1,4*N-1] eh o id do noh da arvore (variavel "no")
    
    intervalos abertos [l,r)
    
    condição base/terminal na query eh suficiente pois quando estou em folha (elemento único) com ctz cai na condição base (ou está completamente dentro ou completamente fora, pois é só um elemento!)
*/

template<int n> struct Seg{
	ll *v, *s;
	
void build(int no = 1, int l = 0, int r = n){
    if(r-l==1){ 
        s[no] = v[l];
        return;
    }
    int mid = (l+r)/2;
    build(2*no,l,mid);
    build(2*no+1,mid,r);
    s[no] = s[2*no]+s[2*no+1];
}

Seg(ll *vb, ll *sb){
	v = vb;
	s = sb;
	build();
}

//Incrementa o valor, v[i] += x
void increment(int i, ll x, int no = 1, int l = 0, int r = n){
    if(r-l==1){
        s[no] += x; // se quiser fazer upd tal que v[i] = x, basta mudar += por = aqui
        return;
    }
    int mid = (l+r)/2;
    if(i<mid) increment(i,x,2*no,l,mid);
    else increment(i,x,2*no+1,mid,r);    
    s[no] = s[2*no]+s[2*no+1]; //fazer operacao no final (apos processar filhos) - inves de fazer s[no] += x-v[l] no inicio
}

ll query(int lq, int rq, int no = 1, int l = 0, int r = n){
    if(rq<=l or r<=lq) return 0; //totalmente fora
    if(lq<=l and r<=rq) return s[no]; //range q estou totalmente dentro do range da query
    int mid = (l+r)/2;
    return query(lq,rq,2*no,l,mid) + query(lq,rq,2*no+1,mid,r);
}
	
};

const int N = 5e5+10;
ll n, m;
ll a[N], b[N], valb_to_id[N], bestsf[N], p[N];
ll val_can_delete[N];
ll id_can_delete[N];

ll s[4*N+10];
ll v[N+10];

int main(){
	scanf("%lld", &n);
	fr(i,n) scanf("%lld", a+i);
	fr(i,n) scanf("%lld", p+i);
	
	scanf("%lld", &m);
	fr(i,N) valb_to_id[i] = -1;
	fr(i,m){
		scanf("%lld", b+i);
		valb_to_id[b[i]] = i;
	}
	
	ll add_ans = 0;
	vector<int> v1, v2;
	fr(i,n){
		if(valb_to_id[a[i]]==-1 and p[i]<0){
			add_ans+=p[i];
		} else{
			v1.push_back(a[i]);
			v2.push_back(p[i]);
		}
	}
	n = sz(v1);
	fr(i,n){
		a[i] = v1[i];
		p[i] = v2[i];
	}
	
	fr(i,n){
		if(a[i]>b[m-1]) add_ans+=p[i];
	}
	
	fr(i,m) bestsf[i] = LLONG_MAX;
	Seg<N> seg(v,s);
	
	for(int i = n-1; i>=0; i--){
		int id = valb_to_id[a[i]];
		if(id!=-1){
			id_can_delete[i] = val_can_delete[a[i]];
			if(p[i]<0) val_can_delete[a[i]]+=p[i];
		}
	}
	
	fr(i,n){
		if(valb_to_id[a[i]]!=-1){
			int id = valb_to_id[a[i]];
			if(id==0 or bestsf[id-1]<LLONG_MAX){
				ll tot = 0;
				ll best_ant = 0;
				ll cost_meio = 0;
				ll ant = 0;
				if(id){ 
					ant = b[id-1];
					best_ant = bestsf[id-1];
				} 
				cost_meio = seg.query(ant+1,b[id]+1);
				tot = best_ant + cost_meio + id_can_delete[i];
				bestsf[id] = min(bestsf[id],tot);
			}
		}
		seg.increment(a[i],p[i]);
	}
	
	if(bestsf[m-1]<LLONG_MAX){
		puts("YES");
		printf("%lld\n", bestsf[m-1]+add_ans);
	} else{
		puts("NO");
	}
}
