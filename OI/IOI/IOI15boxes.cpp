#include "boxes.h"

#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
template<class T, class T2> inline ostream &operator <<(ostream &out, const pair<T, T2> &x) { out << x.first << " " << x.second; return out;}
template<class T, class T2> inline istream &operator >>(istream &in, pair<T, T2> &x) { in >> x.first >> x.second; return in;}
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "

const int MAX_N = 1e7 + 10;
ll dpLeft[MAX_N], dpRight[MAX_N];

long long delivery(int N, int K, int L, int p[]) {
    int n = N, k = K;
    for(int i = 0; i < n; i ++) {
        if(i >= k) {
            dpLeft[i] = dpLeft[i - k] + min(L, 2 * p[i]);
        } else {
            dpLeft[i] = min(L, 2 * p[i]);
        }
    }
    for(int i = n - 1; i >= 0; i --) {
        if(i + k < n) {
            dpRight[i] = dpRight[i + k] + min(L, 2 * L - 2 * p[i]);
        } else {
            dpRight[i] = min(L, 2 * L - 2 * p[i]);
        }
    }
    ll ret = min(dpRight[0], dpLeft[n - 1]);
    for(int i = 0; i < n - 1; i ++) {
        chkmin(ret, dpLeft[i] + dpRight[i + 1]);
    }
    return ret;
}
