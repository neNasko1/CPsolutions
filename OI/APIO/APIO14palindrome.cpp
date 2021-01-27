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

const int MAX_N = 1e5 + 10, MAX_K = 210;
int hist[MAX_K][MAX_N];
ll dp[MAX_N][2];
ll pref[MAX_N], arr[MAX_N];
int cnt, curr;

void output(int n, int k) {
    if(k == 0) {
        return;
    }
    output(hist[k][n], k - 1);
    cout << hist[k][n] << " ";
}

void div(int l, int r, int optl, int optr) {
    if(l > r) {return;}
    int m = (l + r) / 2ll;
    int best = optl;
    for(int tr = optl; tr <= min(m - 1, optr); tr ++) {
        ll now = dp[tr][curr ^ 1] + pref[tr] * (pref[m] - pref[tr]);
        if(chkmax(dp[m][curr], now)) {
            dp[m][curr] = now;
            best = tr;
        }
    }
    hist[cnt][m] = best;
    div(l, m - 1, optl, best);
    div(m + 1, r, best, optr);
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i ++) {
        cin >> arr[i];
        pref[i] = pref[i - 1] + arr[i];
    }

    for(int i = 1; i <= k; i ++) {
        curr = i & 1;
        cnt = i;
        for(int j = 0; j <= n; j ++) {
            dp[j][curr] = -mod;
        }
        div(1, n, 1, n);
    }

    cout << dp[n][k & 1] << endl;
    output(n, k);
    return 0;
}
