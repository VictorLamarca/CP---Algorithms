#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> //required
#include <ext/pb_ds/tree_policy.hpp> //required
using namespace __gnu_pbds; //required 
using namespace std;

//----------------------------------------------------------

bool debug = 1;
#define printa(a) cout << #a << " = " << (a) << endl
#define prin(a) if(debug) cout << #a << " = " << (a) << endl

//SEM TEMPLATE PRA SER MAIS RÁPIDO

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; 

ordered_set s;

//FUNÇÃO COMPARADORA CUSTOMIZADA - SEM TEMPLATE E ORDENANDO ÍNDICE (NÃO ELEMENTO EM SI -> MAIS RÁPIDO)
/*
vector<pll> v;

class cmp{
public:
  bool operator() (int a, int b) const {
  		if(v[a].fi*v[b].se==v[a].se*v[b].fi) return a<b;
  		return v[a].fi*v[b].se<v[a].se*v[b].fi;
  }
};

typedef tree<int, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update> ordered_set; 

ordered_set s;
*/

int main(){
	for(auto it : {1,2,4,5})
		s.insert(it);
	
	prin(s.order_of_key(1));  // 0 (key/elemento 1 ta na posicao 0th) (0-indexed)
	
	prin(s.order_of_key(3));  // 2 (index)
	// 3 seria o terceiro elemnto (2 em 0-indexed) == numero de elemntos estritamente menores que x
	
	//find retorna iterador!!
	prin(*s.find_by_order(0)); // elemento 1 (printa o 0th elemnto)
	
	//--------------------------------------------------------------------------------------------
	
	//*
	cout << endl;
	prin(s.size());
	cout << "pus elemento repetido" << endl;
	s.insert(4); //funciona como set -> nao repete elemnto
	prin(s.size());
	cout << endl;
	
	//tem lower e upper bound tmbm - retorna iterador
	prin(*s.lower_bound(3));
	cout << endl;
	
	//erase - funciona tanto para elemneto qnt pra iterador
	s.erase(4); 
	cout << "apaguei elemento" << endl;
	prin(s.size());
	s.erase(s.find(2));
	cout << endl;
	
	//tem clear e empty tmbm
	s.clear();
	prin(s.empty());
	
	//*/
}

/*
usado no problema do csacademy - cs_68_c.cpp:

template <class T> struct cmp{
  bool operator() (const T& x, const T& y) const {return x.fi*y.se<x.se*y.fi;}
};

template <typename T> using ordered_set =  tree<T, null_type, cmp<T>, rb_tree_tag, tree_order_statistics_node_update>; 

ordered_set <pll> s; 
*/


/*
template <typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; 

ordered_set<int> s;

 or:
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
ordered_set s;
//This works in C++98 but the above version wiht template only works in C++11
//*/

