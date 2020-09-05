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

///Dp on (banknote considered, sum gotten), lets solve each dp[i][k] using the states dp[i][k - ban[i]], dp[i][k - 2 * ban[i]]...(We see k and k - q * ban[i] are congruent mod ban[i])
///We will use a deque to find optimal value

const int MAX_N = 2e4 + 1, MAX_W = 201;
int hist[MAX_W][MAX_N];
int dp[MAX_W][MAX_N], arr[MAX_N], cnt[MAX_N], n;
deque<pair<int, int> > dq[MAX_N];

void output(int nn, int k) {
    if(nn == 0) {return;}
    output(nn - 1, k - hist[nn][k] * arr[nn - 1]);
    cout << hist[nn][k] << " ";
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i ++) {
        cin >> arr[i];
    }
    for(int i = 0; i < n; i ++) {
        cin >> cnt[i];
    }
    for(int i = 0; i < MAX_W; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            dp[i][j] = mod;
            hist[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    for(int i = 0; i < n; i ++) {
        //cout << i << endl;
        int curr = i, nxt = i + 1;
        for(int j = 0; j < MAX_N; j ++) {
            dq[j].clear();
        }
        int now = arr[i];
        for(int j = 0; j < MAX_N; j ++) {
            int ost = j % now;
            pair<int, int> dpPrv = {dp[curr][j] - j / now, j / now};
            while(!dq[ost].empty() && dq[ost].back() > dpPrv) {
                dq[ost].pop_back();
            }
            dq[ost].push_back(dpPrv);
            while(!dq[ost].empty() && j / now - dq[ost].front().second > cnt[i]) {
                dq[ost].pop_front();
            }
            if(!dq[ost].empty()) {
                dp[nxt][j] = j / now + dq[ost].front().first;
                hist[nxt][j] = j / now - dq[ost].front().second;
            }
        }
    }
    int k;
    cin >> k;
    cout << dp[n][k] << endl;
    output(n, k);
    return 0;
}


