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

///Dp on tree - state (x, k) - which subtree are we using and how many rooms have we been to.
///Optimization using barricade - from O(n^3) to O(n^2)

const int MAX_N = 1e4 + 10;
unsigned int dp1[MAX_N][MAX_N];
unsigned int dp2[MAX_N][MAX_N];
int sz[MAX_N];
vector<pair<int, unsigned int> > g[MAX_N];

void dfs(int x, int p) {
    sz[x] = 1;
    for(auto it : g[x]) {
        if(it.first == p) {continue;}
        dfs(it.first, x);
    }
    dp1[x][1] = 0;
    dp2[x][1] = 0;
    for(auto it : g[x]) {
        if(it.first == p) {continue;}
        for(int i = sz[x]; i >= 0; i --) {///Barricade dp
            for(int j = min(MAX_N, sz[it.first]); j >= 0; j --) {
                chkmin(dp1[x][i + j], dp1[x][i] + dp1[it.first][j] + 2ll * it.second);
                chkmin(dp2[x][i + j], dp2[x][i] + dp1[it.first][j] + 2ll * it.second);
                chkmin(dp2[x][i + j], dp1[x][i] + dp2[it.first][j] + it.second);
                chkmin(dp2[x][i + j], dp1[x][i] + dp1[it.first][j] + it.second);
            }
        }
        sz[x] += sz[it.first];
    }
    return;
    cout << "Dfs " << x << endl;
    for(int i = 0; i <= sz[x]; i ++) {
        cout << dp1[x][i] << " ";
    }
    cout << endl;
    for(int i = 0; i <= sz[x]; i ++) {
        cout << dp2[x][i] << " ";
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, k, x;
    cin >> n >> k >> x;
    for(int i = 0; i < n - 1; i ++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    for(int i = 0; i <= n; i ++) {
        for(int j = 0; j <= n; j ++) {
            dp1[i][j] = 2 * mod;
            dp2[i][j] = 2 * mod;
        }
    }
    dfs(x, 0);
    cout << dp2[x][k] << endl;
    return 0;
}
