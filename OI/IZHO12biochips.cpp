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

const int MAX_N = 2e5 + 10;
const int MAX_W = 510;
vector<int> g[MAX_N];
int in[MAX_N], out[MAX_N], arr[MAX_N];
int tme = -1;
int dp[MAX_N][MAX_W];

void dfs(int x) {
    in[x] = tme; tme ++;
    for(auto it : g[x]) {
        dfs(it);
    }
    out[x] = tme;
}

bool cmp(int a, int b) {
    return in[a] < in[b];
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, w;
    cin >> n >> w;
    vector<int> ord;
    for(int i = 1; i <= n; i ++) {
        int p;
        cin >> p >> arr[i];
        g[p].push_back(i);
        ord.push_back(i);
    }
    dfs(0);
    sort(ord.begin(), ord.end(), cmp);
    for(int i = 0; i < MAX_N; i ++) {fill_n(dp[i], MAX_W, -mod);}
    dp[0][0] = 0;
    int ret = 0;
    for(int i = 0; i < ord.size(); i ++) {
        chkmax(ret, dp[i][w]);
        for(int j = 0; j < MAX_W - 1; j ++) {
            chkmax(dp[i + 1][j], dp[i][j]);
            chkmax(dp[out[ord[i]]][j + 1], dp[i][j] + arr[ord[i]]);
        }
    }
    cout << max(ret, dp[ord.size()][w]) << endl;
    return 0;
}

