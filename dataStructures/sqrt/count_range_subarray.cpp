#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)

/*
    Given array a of size n and -1e5<=ai<=1e5
    answer querys of how many numbers from the subarray [lid,rid]
    belong to the interval [lval,rval]
    and updates, change element ai to val
    
    Works in O(n*sqrt(nlogn)) online
    (Acctually a little less than this, check which k minimizes
    O(q*(n/k*logk + k + k)) )
    
    Solution: Divide in buckets of size K where it bucket is assigned to 
    a certain interval from the array, but the bucket is sorted
    Query: if bucket is completely inside query [lid,rid] use upper_bound in 
    bucket to count, if just part of bucket, do bruteforce
    Update: change main array and change corrresponding bucket and resort it
    BUT when sorting, do swaps to left or right to sort in O(n)!
    
    original problem: https://codeforces.com/contest/1093/problem/E
*/

const int N = 2e5+10;

//main array
int st[N];

int tam[150];
int st_buck[150][1500]; //st in buckets, constraits: (n/k,k) = (number of buckets, size of bucket)

//n size of st, k = size of bucket
void build(int n, int k){
    int i = 0, ist = 0;
    while(1){
        fr(cnt,k){
            st_buck[i/k][i%k] = st[i];
            i++;
            tam[ist]++;
            if(i==n) break;
        }
        sort(st_buck[ist],st_buck[ist]+tam[ist]);
        ist++;
        if(i==n) break;
    } //need how many buckets? (ist)
}

int qry_buck(int id, int l, int r){
    int ans = upper_bound(st_buck[id],st_buck[id]+tam[id],r)-upper_bound(st_buck[id],st_buck[id]+tam[id],l-1);
    return ans;
}

/* count how many numbers in the subarray [lid,rid] from st 
   belong to [lval,rval]
   Works in O(n/k*log(k) + k)   */
int qry(int lid, int rid, int lval, int rval, int k){
    int ans = 0;
    int i = lid;
    while(i<=rid){
        if(i%k==0  and i+tam[i/k]-1<=rid){
            ans+=qry_buck(i/k,lval,rval);
            i+=tam[i/k];
        } else{
            if(lval<=st[i] and st[i]<=rval){
                ans++;
            }
            i++;
        }
    }
    
    return ans;
}

//change st[ichange] to val, and st_buck accordingly
// Works in O(k)
void up(int ichange, int val, int k){ 
    int id = ichange/k;
    int tira = st[ichange];
    int poe = st[ichange] = val;
    int i;
    fr(ii,tam[id]) if(st_buck[id][ii]==tira) i = ii;
    
    st_buck[id][i] = poe;
    
    while(i and st_buck[id][i-1]>st_buck[id][i]){
        swap(st_buck[id][i],st_buck[id][i-1]);
        i--;
    }
    
    while(i<tam[id]-1 and st_buck[id][i+1]<st_buck[id][i]){
        swap(st_buck[id][i],st_buck[id][i+1]);
        i++;
    }
}

//--------------------------------

int n, k;
int q;

int a[N], b[N];
int vala_to_id[N];

int main(){
    scanf("%d%d", &n, &q);
    
    fr(i,n) scanf("%d", a+i), vala_to_id[a[i]] = i;
    fr(i,n) scanf("%d", b+i);
    
    //define k - around sqrt(nlogn)
    k = min(1484,n);
    //k = min(2,n);
    
    //read st and build
    fr(i,n) st[i] = vala_to_id[b[i]];
    build(n,k);
    
    fr(qq,q){
        char t;
        scanf(" %c", &t);
        if(t=='1'){
            int la, ra, lb, rb;
            scanf("%d%d%d%d", &la, &ra, &lb, &rb);
            la--,ra--,lb--,rb--;
            
            printf("%d\n", qry(lb,rb,la,ra,k));
        
        } else{
            int x, y;
            scanf("%d%d", &x, &y);
            x--,y--;
            
            int valx = st[y];
            int valy = st[x];
            
            up(x,valx,k);
            up(y,valy,k);
        }
    }
	
	return 0;
}

