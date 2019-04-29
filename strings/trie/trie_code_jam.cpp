#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

#define eb emplace_back
#define all(v) (v).begin(),(v).end()

const int N = 50*1000+10;

int sz = 1;

/*estado [c][id]:
    id implica em um certo prefixo da palavra e c significa a ultima letra da palavra
    c = SizeAlphabet
    id = n*size_of_word = total_number_of_letters
*/
int prox[26][N];
list<int> lt[26][N];

int usado[1010];

int ans;

void reset(){
    fr(c,26) fr(i,N){
        prox[c][i] = -1;
        lt[c][i].clear();
    }
    
    memset(usado,0,sizeof(usado));
    
    ans = 0;
    sz = 1;
}

int main(){
    int t;
    cin >> t;
    
    fr(tt,t){
        
        int n;
        cin >> n;
        
        reset();
        
        fr(nn,n){
            string str;
            cin >> str;
            
            reverse(all(str));
            
            int id = 0;
            fr(i,str.size()){
                int c = str[i]-'A';
                lt[c][id].eb(nn);
                if(prox[c][id]==-1) prox[c][id] = sz++;
                id = prox[c][id];
            }
        }
        
        for(int id = sz;id>=0;id--) fr(c,26){
            int n_nu = 0;
            for(auto it : lt[c][id]){
                if(!usado[it]) n_nu++;
                if(n_nu==2) break;
            }
            
            if(n_nu==2){
                n_nu = 0;
                for(auto it : lt[c][id]){
                    if(!usado[it]){
                        usado[it] = 1;
                        n_nu++;
                        ans++;
                    }
                    if(n_nu==2) break;
                }
            }
        }
        
        printf("Case #%d: %d\n", tt+1, ans);
    }
    
	
	return 0;
}

