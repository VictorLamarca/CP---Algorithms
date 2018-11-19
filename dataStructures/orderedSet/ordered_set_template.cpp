#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

#define fi first
#define se second
typedef pair<int,int> pii;

bool debug = 1;
#define prin(a) if(debug) cout << #a << " = " << (a) << endl

//-------------------------------------------------------------------
#include <ext/pb_ds/assoc_container.hpp> //required
#include <ext/pb_ds/tree_policy.hpp> //required
using namespace __gnu_pbds; //required 

template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 

ordered_set <pii> s; 
//-------------------------------------------------------------------

int main(){
    
    frr(i,1,5) s.insert({i,i});
	
	prin(s.order_of_key({1,1}));  // 0 (key/elemento 1 ta na posicao 0th) (0-indexed)
	
	prin(s.order_of_key({2,3})); // 2 (seria posto no 2o elemento, 0-indexado)
	
	//find retorna iterador!!
	prin(s.find_by_order(3)->fi); // {4,4} (4 é o 3o elemento, 0-indexado)
	
	prin(s.size());
	
	s.erase({2,2});
	
	prin(s.size());
	
	return 0;
}

/*
Com comparador feito

template <class T> struct cmp{
  bool operator() (const T& x, const T& y) const {return x.fi*y.se<x.se*y.fi;}
};

template <typename T> using ordered_set =  tree<T, null_type, cmp<T>, rb_tree_tag, tree_order_statistics_node_update>; 

ordered_set <pll> s; 
*/

