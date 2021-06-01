#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i =0 ; i<n; i++)
#define eb emplace_back
#define all(v) (v).begin(),(v).end()
#define prin(a) cout << #a << " = " << a << endl

//solves https://codeforces.com/problemset/problem/126/B

vector<int> zfunc(string &s){
	int n = s.size();
	vector<int> z(n);
	for(int i = 1, l = 0, r = 0; i<n; i++){
		if(i<=r)
			z[i] = min(z[i-l],r-i+1);
		while(i+z[i]<n and s[z[i]+i]==s[z[i]]) z[i]++;
		if(i+z[i]-1>r) l = i, r = i+z[i]-1;
	}
	return z;
}

const int N = 1e6+10;
int freq[N];

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	
	string s;
	cin >> s;
	
	vector<int> z = zfunc(s);
	
	for(int i = 1; i<s.size(); i++){
		freq[z[i]]++;
	}
	
	for(int i = (int)s.size()-1; i>0; i--){
		freq[i] += freq[i+1];
	}
	
	vector<pair<int,int>> ans;
	
	for(int i = 1; i<z.size(); i++){
		if(i+z[i]==z.size()) ans.eb(z[i],freq[z[i]]+1);
	}
	ans.eb(s.size(),1);
	
	sort(all(ans));
	
	cout << ans.size() << endl;
	
	for(auto &par : ans){
		cout << par.first << " " << par.second << endl;
	}
}
