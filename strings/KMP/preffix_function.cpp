#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())

//solves https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2447

vector<int> fpref(string &s){
	vector<int> pref(s.size());
	
	for(int i = 1; i<sz(s); i++){
		int t = pref[i-1];
		while(t and s[i]!=s[t]) t = pref[t-1];
		if(s[i]==s[t]) t++;
		pref[i] = t;
	}
	return pref;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	
	fr(tt,t){
		string s;
		cin >> s;
		
		vector<int> pref = fpref(s);
		
		int atm = s.size()-pref[s.size()-1];
		int d = s.size()%atm;
		
		fr(i,8) cout << s[(d+i)%atm];
		cout << "..." << endl;
	}
}
