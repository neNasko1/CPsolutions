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

set<int> diff[MAX_N], seq[MAX_N];

int searchIn(set<int> &where, int l, int r) {
    auto it = where.lower_bound(l);
    if(it == where.end() || *it > r) {
        return -1;
    } else {
        return *it;
    }
}

const int LOG = 18;
int par[MAX_N][LOG], d[MAX_N];
vector<int> g[MAX_N];

void dfs(int x, int p) {
    par[x][0] = p;
    d[x] = d[p] + 1;
    for(int i = 1; i < LOG; i ++) {
        par[x][i] = par[par[x][i - 1]][i - 1];
    }
    for(auto it : g[x]) {
        if(it == p) {continue;}
        dfs(it, x);
    }
}

int lca(int a, int b) {
    if(d[a] < d[b]) {swap(a, b);}
    for(int i = LOG - 1; i >= 0; i --) {
        if(d[par[a][i]] >= d[b]) {
            a = par[a][i];
        }
    }
    if(a == b) {return a;}
    for(int i = LOG - 1; i >= 0; i --) {
        if(par[a][i] != par[b][i]) {
            a = par[a][i];
            b = par[b][i];
        }
    }
    return par[a][0];
}

int n, m, q;
int arr[MAX_N];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> q;
    for(int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 0);
    for(int i = 1; i <= m; i ++) {
        cin >> arr[i];
        seq[arr[i]].insert(i);
    }
    for(int i = 1; i <= m - 1; i ++) {
        int curr = lca(arr[i], arr[i + 1]);
        diff[curr].insert(i);
    }
    while(q --) {
        int t;
        cin >> t;
        if(t == 1) {
            int a, v;
            cin >> a >> v;
            seq[arr[a]].erase(a);
            seq[v].insert(a);
            if(a != m) {
                int old = lca(arr[a], arr[a + 1]);
                int nw = lca(v, arr[a + 1]);
                diff[old].erase(a);
                diff[nw].insert(a);
            }
            if(a != 1) {
                int old = lca(arr[a], arr[a - 1]);
                int nw = lca(v, arr[a - 1]);
                diff[old].erase(a - 1);
                diff[nw].insert(a - 1);
            }
            arr[a] = v;
        } else {
            int l, r, v;
            cin >> l >> r >> v;
            int ans = searchIn(seq[v], l, r);
            if(ans != -1) {
                cout << ans << " " << ans << endl;
                continue;
            }
            ans = searchIn(diff[v], l, r - 1);
            if(ans != -1) {
                cout << ans << " " << ans + 1 << endl;
                continue;
            }
            cout << -1 << " " << -1 << endl;
        }
    }
    return 0;
}
