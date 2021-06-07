#include <bits/stdc++.h>
using namespace std;

//solves https://codeforces.com/contest/1523/problem/D

template<const char ch, class T>
vector<T> FWHT(vector<T> a, const bool inv = false) {
	int n = (int) a.size();
	for(int len = 1; len < n; len += len) {
		for(int i = 0; i < n; i += 2 * len) {
			for(int j = 0; j < len; j++) {
				auto u = a[i + j], v = a[i + j + len];
				if(ch == '^') {
					a[i + j] = u + v;
					a[i + j + len] = u - v;
				}
				if(ch == '|') {
					if(!inv) {
						a[i + j + len] += a[i + j];
					} else {
						a[i + j + len] -= a[i + j];
					}
				}
				if(ch == '&') {
					if(!inv) {
						a[i + j] += a[i + j + len];
					} else {
						a[i + j] -= a[i + j + len];
					}
				}
			}
		}
	}
	if(ch == '^' && inv) {
		for(int i = 0; i < n; i++) {
			a[i] = a[i] / n;
		}
	}
	return a;
}

mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n, m, p;
	cin >> n >> m >> p;
	vector<string> a(n);
	for(int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int ans = 0;
	string wtf(m, '0');
	for(int rep = 0; rep < 20; rep++) {
		vector<int> f(1 << p, 0);
		int id = rng() % n;
		vector<int> pos;
		for(int i = 0; i < m; i++) {
			if(a[id][i] == '1') {
				pos.push_back(i);
			}
		}
 
		for(int i = 0; i < n; i++) {
			int mask = 0;
			for(int j = 0; j < (int) pos.size(); j++) {
				if(a[i][pos[j]] == '1') {
					mask |= 1 << j;
				}
			}
			f[mask]++;
		}
		f = FWHT<'&'>(f);
		for(int i = 0; i < (1 << p); i++) {
			if(2 * f[i] >= n) {
				int bits = 0;
				for(int j = 0; j < p; j++) {
					if(i & (1 << j)) {
						bits++;
					}
				}
				if(ans < bits) {
					ans = bits;
					wtf = string(m, '0');
					for(int j = 0; j < p; j++) {
						if(i & (1 << j)) {
							wtf[pos[j]] = '1';
						}
					}
				}
			}
		}
	}
	cout << wtf << '\n';
}
