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

const ll MAX_N = 3e3 + 10;
string arr[MAX_N];
ll n, m;
bool down[MAX_N][MAX_N], rght[MAX_N][MAX_N];

vector<ll> diag[MAX_N * 2];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for(ll i = 0; i < n; i ++) {
        cin >> arr[i];
    }
    for(ll i = 0; i < n; i ++) {
        for(ll j = 1; j < m - 1; j ++) {
            rght[i][j] = arr[i][j - 1] == 'R' && arr[i][j] == 'G' && arr[i][j + 1] == 'W';
        }
    }
    for(ll j = 0; j < m; j ++) {
        for(ll i = 1; i < n - 1; i ++) {
            down[i][j] = arr[i - 1][j] == 'R' && arr[i][j] == 'G' && arr[i + 1][j] == 'W';
        }
    }
    for(ll i = 0; i < n; i ++) {
        for(ll j = 0; j < m; j ++) {
            diag[i + j].push_back(((ll)down[i][j] << 1) + (ll)rght[i][j]);
        }
    }
    ll cnt = 0;
    for(ll i = 0; i < n + m; i ++) {
        ll dp[3] = {0, 0, 0};
        ll curr[3] = {0, 0, 0};
        for(auto it : diag[i]) {
            if(it & (1 << 1)) {
                curr[1] = max(dp[1], dp[0]) + 1;
            }
            if(it & 1) {
                curr[2] = max(dp[2], dp[0]) + 1;
            }
            curr[0] = max({dp[0], dp[1], dp[2]});
            for(ll i = 0; i < 3; i ++) {dp[i] = curr[i]; curr[i] = 0;}
        }
        cnt += max({dp[0], dp[1], dp[2]});
    }
    cout << cnt << endl;
    return 0;
}

