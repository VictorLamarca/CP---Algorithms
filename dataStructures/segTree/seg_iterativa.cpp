#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v).size()
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()

typedef long long ll;

//solves https://codeforces.com/contest/1334/problem/F

/*
    Lembrar de 2*N no tamanho da seg
    
    Comentados estao oq tornam a em seg de minimo
    
    Em build faco atual = filhos (ponho vetor em [n,2*n-1] e faco de n-1 até 1
    Em Update mudo folha e faco pai = atual (while pos>1, ou seja tem pai)
    Em query passo por td (l+=n, r+=n) ate l<r
    
    nos na seg de [1,2*n-1], folhas (array) de [n,2*n-1]
*/

template<int N> struct Seg{
	ll *v, *s;
	
void build(){
	for(int i = N-1;i>0;i--){ 
		//s[i] = min(s[i<<1],s[i<<1|1]);
		s[i] = s[i<<1]+s[i<<1|1];
	}
}

Seg(ll *vb, ll *sb){
	v = vb;
	s = sb;
	build();
}

//pos 0-indexed (incrementa, nao atualiza)
void increment(int pos, ll val){
	for(s[pos+=N]+=val;pos>1;pos>>=1) 
		//s[pos>>1] = min(s[pos],s[pos^1]);
		s[pos>>1] = s[pos]+s[pos^1];
}

//array é abstraido para 0-indexed (nas folhas da seg) e [l,r)
ll qr(int l, int r){
	ll ans = 0;
	//ll ans = LLONG_MAX;
	for(l+=N,r+=N;l<r;l>>=1,r>>=1){
		if(l&1) ans = ans+s[l++];
		if(r&1) ans = ans+s[--r];
		//if(l&1) ans = min(ans,s[l++]);
		//if(r&1) ans = min(ans,s[--r]);
	}
	return ans;
}
	
};

const int N = 5e5+10;
ll n, m;
ll a[N], b[N], valb_to_id[N], bestsf[N], p[N];
ll val_can_delete[N];
ll id_can_delete[N];

ll s[2*N+10];
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
				cost_meio = seg.qr(ant+1,b[id]+1);
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
