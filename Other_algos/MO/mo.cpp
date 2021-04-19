#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define all(v) (v).begin(),(v).end()

typedef long long ll;

#define fi first
#define se second

//solves https://codeforces.com/contest/1514/problem/D

//other Mo problem: https://codeforces.com/gym/101879/problem/H

const int N = 3e5+10;

int rz; //raiz de n - usado para ordenar querys
int freq[N];
int qnts_freq[N];

vector<pair<int,int>> qry;

//comparador dos indices das querys do mo
struct cmp{
    bool operator ()(int i, int j){
        auto &a = qry[i], &b = qry[j];
        if(a.fi/rz!=b.fi/rz) return a.fi/rz < b.fi/rz;
        if(a.se!=b.se) return a.se<b.se;
        return a<b; //bom para deixar querys iguais juntas, fica mais rapido
    }
};

int max_freq = 0;

void poe(int id){
	qnts_freq[freq[id]]--;
    freq[id]++;
    qnts_freq[freq[id]]++;
    if(freq[id]>max_freq) max_freq = freq[id];
}

void tira(int id){
    qnts_freq[freq[id]]--;
    freq[id]--;
    qnts_freq[freq[id]]++;
    if(qnts_freq[max_freq]==0) max_freq--;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	
	int n, q;
	cin >> n >> q;
	
	vector<int> ans(q);
	vector<int> v(n);
	fr(i,n) cin >> v[i];
	
	fr(i,q){
	    int l, r; cin >> l >> r;
	    l--,r--;
	    //[l,r] é o intervalo incluso da query
	    qry.emplace_back(l,r);
	}
	rz = max(1,(int)sqrt(n));
	
    vector<int> ito;
    fr(i,q) ito.push_back(i);
	sort(all(ito),cmp());
	
	//nao necessario, mas bom para coordenar q tem n elementos com frequencia 0
	qnts_freq[0] = n; 
	
	//curr começa negativo para o indice 0 ser ativado
	int curl = 0, curr = -1; 
	fr(i,q){
		int l ,r;
	    tie(l,r) = qry[ito[i]];
	    //fazer poes antes dos tira para nao dar negativo no meio
	    while(curr<r) poe(v[++curr]);
	    while(curl>l) poe(v[--curl]);
	    while(curr>r) tira(v[curr--]);
	    while(curl<l) tira(v[curl++]);
	    //max_freq é a frequencia do elemento mais frequente no intervalo
	    //curl==l and curr==r
	    int tot = r-l+1;
	    int rest = tot-max_freq;
	    int resp = 1;
	    if(rest+1<max_freq) resp+=max_freq-(rest+1);
	    ans[ito[i]] = resp;
	}
	
	fr(i,q) cout << ans[i] << "\n";
}
