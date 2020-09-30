#include "stations.h"
#include <vector>

#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

const int MAX_N = 1e5 + 10;
vector<int> g[MAX_N];
int lab[MAX_N], tme = 0;
void dfs(int x, int p, int d) {
    if(d % 2 == 0) {
        lab[x] = tme ++;
    }
    for(auto it : g[x]) {
        if(it == p) {continue;}
        dfs(it, x, d + 1);
    }
    if(d % 2 == 1) {
        lab[x] = tme ++;
    }
}

vector<int> label(int n, int k, vector<int> u, vector<int> v) {
    tme = 0;
    for(int i = 0; i < n; i ++) {
        g[i].resize(0);
    }
    for(int i = 0; i < n - 1; i ++) {
        g[u[i]].push_back(v[i]);
        g[v[i]].push_back(u[i]);
    }
    dfs(0, -1, 0);
    vector<int> ret;
    for(int i = 0; i < n; i ++) {
        ret.push_back(lab[i]);
    }
    return ret;
}

int find_next_station(int s, int t, vector<int> c) {
    vector<pair<int, int> > inout;
    if(s < c[0]) {
        int last = s;
        for(int i = 0; i < c.size() - 1; i ++) {
            int it = c[i];
            if(last + 1 <= t && t <= it) {
                return it;
            }
            last = it;
        }
        return c[c.size() - 1];
    } else {
        int last = s;
        for(int i = c.size() - 1; i > 0; i --) {
            int it = c[i];
            if(last - 1 >= t && t >= it) {
                return it;
            }
            last = it;
        }
        return c[0];
    }
}
