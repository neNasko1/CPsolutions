#include "werewolf.h"

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
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

const int MAX_N = 2e5 + 10;
struct DSU {
    int par[MAX_N], sz[MAX_N], big[MAX_N];
    int find(int x) {
        if(x == par[x]) {
            return x;
        } else {
            return par[x] = find(par[x]);
        }
    }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if(x == y) {return false;}
        if(sz[x] < sz[y]) {swap(x, y);}
        par[y] = x;
        sz[x] += sz[y];
        return true;
    }
    void reset() {
        for(int i = 0; i < MAX_N; i ++) {
            par[i] = big[i] = i;
            sz[i] = 1;
        }
    }
};

struct Tree {
    vector<int> g[MAX_N];
    int in[MAX_N], out[MAX_N], tme;
    void addEdge(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void dfs(int x, int p) {
        in[x] = ++ tme;
        for(auto it : g[x]) {
            if(it == p) {continue;}
            dfs(it, x);
        }
        out[x] = tme;
    }
    void calculate(int x) {
        tme = -1;
        dfs(x, -1);
    }
};

struct Query {
    int v, ind;
};

Tree tPref, tSuf;
DSU dsuPref, dsuSuf;
vector<Query> query[MAX_N];

set<int> pos[MAX_N];
int ans[MAX_N];
vector<pair<pair<int, int>, int> > compPref[MAX_N], compSuf[MAX_N];

void dfs(int x, int p) {
    pos[x].insert(tSuf.in[x]);
    for(auto it : tPref.g[x]) {
        if(it == p) {continue;}
        dfs(it, x);
        if(pos[it] < pos[x]) {swap(pos[x], pos[it]);}
        for(auto itt : pos[it]) {
            pos[x].insert(itt);
        }
    }
    for(auto it : query[x]) {
        auto found = pos[x].lower_bound(tSuf.in[it.v]);
        if(found == pos[x].end() || (*found) > tSuf.out[it.v]) {
            ans[it.ind] = 0;
        } else {
            ans[it.ind] = 1;
        }
    }
}

vector<int> g[MAX_N];
int werewolf[MAX_N];

std::vector<int> check_validity(int N, std::vector<int> X, std::vector<int> Y,
                                std::vector<int> S, std::vector<int> E,
                                std::vector<int> L, std::vector<int> R) {
    vector<int> ret;
    int n = N, m = X.size(), q = S.size();
    for(int i = 0; i < m; i ++) {
        int a = X[i], b = Y[i];
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 0; i < q; i ++) {
        int s = S[i], e = E[i], l = L[i], r = R[i];
        compPref[r].push_back({{s, e}, i});
        compSuf[l].push_back({{s, e}, i});
    }
    dsuPref.reset();
    dsuSuf.reset();
    for(int i = n - 1; i >= 0; i --) {
        for(auto it : g[i]) {
            if(it > i) {
                int prv = dsuSuf.big[dsuSuf.find(it)];
                if(dsuSuf.merge(it, i)) {
                    tSuf.addEdge(i, prv);
                    dsuSuf.big[dsuSuf.find(i)] = i;
                }
            }
        }
        for(auto it : compSuf[i]) {
            werewolf[it.second] = dsuSuf.big[dsuSuf.find(it.first.first)];
        }
    }
    for(int i = 0; i < n; i ++) {
        for(auto it : g[i]) {
            if(it < i) {
                int prv = dsuPref.big[dsuPref.find(it)];
                if(dsuPref.merge(it, i)) {
                    tPref.addEdge(i, prv);
                    dsuPref.big[dsuPref.find(i)] = i;
                }
            }
        }
        for(auto it : compPref[i]) {
            query[dsuPref.big[dsuPref.find(it.first.second)]].push_back({werewolf[it.second], it.second});
        }
    }
    tPref.calculate(dsuPref.big[dsuPref.find(1)]);
    tSuf.calculate(dsuSuf.big[dsuSuf.find(1)]);
    dfs(dsuPref.big[dsuPref.find(1)], -1);
    for(int i = 0; i < q; i ++) {
        ret.push_back(ans[i]);
    }
    return ret;
}
