#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
# include <iostream>
# include <stdio.h>
using namespace std;

unsigned char a[200000];

/*
    Problema: https://codeforces.com/contest/911/problem/G
    
    Comentario:
    the first just tells the compiler to optimize the code for speed to make is as fast as possible (and not look for space)
the second tells the compiler to unroll loops. normally if we have a loop there is a ++i instruction somewhere. We normally dont care because code inside the loop requires much more time but in this case there is only one instruction inside the loop so we want the compiler to optimize this.
and last but not least we want to tell the compiler that our cpu has simd instructions and allow him to vectorize our code
    https://codeforces.com/blog/entry/56771#comment-404681
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%hhu", &a[i]);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int l, r;
        unsigned char x, y;
        scanf("%d%d%hhu%hhu", &l, &r, &x, &y);
        for (int i = l-1; i < r; i++) {
            a[i] = a[i] == x ? y : a[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%hhu ", a[i]);
    }
}
//O(n^2) test... it seems possible for this... but it shoudnt...
