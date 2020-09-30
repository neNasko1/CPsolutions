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

const int MAX_N = 1e5 + 10;
vector<int> g[MAX_N];
vector<pair<int, pair<int, int> > > inter;
vector<pair<int, int> > grid;
int n, ret = 0;

int dfs(int x, int p) {
    //cout << inter[x].first << " " << inter[x].second.first << " " << inter[x].second.second << endl;
    int sz = inter[x].second.second - inter[x].second.first + 1;
    for(auto it : g[x]) {
        if(it == p) {continue;}
        sz += dfs(it, x);
    }
    ret += ((ll)sz * (ll)(n - sz) % 1000000000ll);
    ret %= 1000000000ll;
    return sz;
}

void generateTree() {
    inter.resize(0);
    sort(grid.begin(), grid.end());
    for(int i = 0; i < n; i ++) {
        int j = i;
        while(j + 1 < n && grid[j + 1].first == grid[i].first && grid[j + 1].second == grid[j].second + 1) {j ++;}
        inter.push_back({grid[i].first, {grid[i].second, grid[j].second}});
        i = j;
    }
    for(int i = 0; i < inter.size(); i ++) {
        g[i].resize(0);
    }
    int r = 0;
    for(int l = 0; l < inter.size(); l ++) {
        while(r < inter.size() && inter[r].first < inter[l].first + 1) {r ++;}
        if(r == inter.size()) {
            break;
        }
        while(r < n - 1 && inter[r].second.second < inter[l].second.first && inter[r].first == inter[l].first + 1) {r ++;}
        while(r <= n - 1 && inter[r].second.second <= inter[l].second.second && inter[r].first == inter[l].first + 1) {
            g[l].push_back(r);
            g[r].push_back(l);
            r ++;
        }
        if(r != n && inter[r].second.first <= inter[l].second.second && inter[r].first == inter[l].first + 1) {
            g[l].push_back(r);
            g[r].push_back(l);
        }
    }
    dfs(0, -1);
}


int DistanceSum(int N, int *X, int *Y) {
    n = N;;
    grid.resize(n);
    for(ll i = 0; i < n; i ++) {
        grid[i] = {X[i], Y[i]};
    }
    generateTree();
    for(ll i = 0; i < n; i ++) {
        swap(grid[i].first, grid[i].second);
    }
    generateTree();
    return ret;
}
