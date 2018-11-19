#include <bits/stdc++.h>

using namespace std;

#define ll long long

//DESCONSIDERAR
//variveis especificas desse problema
ll x[3030], y[3030];
set < ll > nums;
map < ll, int > comp;

//prob original:
//http://codeforces.com/gym/101485/standings/friends/true

//--------------------------------------------------------------------------

//complexidade O(E*V) -> supoe fluxo unitario!!!

//M é o numero de candidatos e N o numero de vagas
int n, m; // em problemas de grafo quadrado lembrar de fazer m = n
#define N 3030
#define M 11100

//g[i] = j (indice no : i (0 a M-1) "source" e it : j "dest" (0 a N-1)
vector < int > g[M]; //pra onde aplicam cada um dos M cand
bool vis[N];
int match[N]; // vaga i (das N) vai para candidato match[i] (de 0 a M-1)


bool match_vertex(int u) {
    for (int v : g[u])
        if (!vis[v]) {
            vis[v] = true;
            if (match[v] < 0 || match_vertex(match[v])) {
                match[v] = u;
                return true;
            }
        }
    return false;
}

int max_match() {
    memset(match, -1, sizeof match);
    int result = 0;
    for (int u = 0; u < m; u++) {
        memset(vis, 0, sizeof vis);
        if (match_vertex(u)) result++;
    }
    return result;
}

//--------------------------------------------------------------------------

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &x[i], &y[i]);
        nums.insert(x[i] + y[i]);
        nums.insert(x[i] - y[i]);
        nums.insert(x[i] * y[i]);
    }

    int ind = 3030;
    for (auto v : nums)
        comp[v] = ind++;
    m = ind;

    for (int i = 0; i < n; i++) {
        g[comp[x[i] + y[i]]].push_back(i);
        g[comp[x[i] - y[i]]].push_back(i);
        g[comp[x[i] * y[i]]].push_back(i);
    }

    int ans = max_match();
    if (ans != n) printf("impossible\n");
    else {
        for (int i = 0; i < n; i++) {
            if (match[i] == comp[x[i] + y[i]]) printf("%lld + %lld = %lld\n", x[i], y[i], x[i] + y[i]);
            else if (match[i] == comp[x[i] - y[i]]) printf("%lld - %lld = %lld\n", x[i], y[i], x[i] - y[i]);
            else printf("%lld * %lld = %lld\n", x[i], y[i], x[i] * y[i]);
        }
    }

    return 0;
}
