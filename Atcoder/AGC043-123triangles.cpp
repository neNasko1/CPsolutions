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

const int MAX_N = 1e6 + 10;
int beg[MAX_N], nxt[MAX_N], cpy[MAX_N];
int cnt[3], n;

int cnt2(int x) {
    int ans = 0;
    while(x / 2 > 0) {
        ans += x / 2;
        x /= 2;
    }
    return ans;
}

bool comb(int x, int k) {
    return !(cnt2(x) - cnt2(x - k) - cnt2(k));
}

int solve() {
    if(n == 1) {
        return beg[0];
    }
    cnt[0] = cnt[1] = cnt[2] = 0;
    for(int j = 0; j < n - 1; j ++) {
        beg[j] = abs(beg[j] - beg[j + 1]);
        cnt[beg[j]] ++;
    }
    int semi;
    if(cnt[1]) {
        semi = 1;
    } else {
        semi = 2;
    }
    int ret = 0;
    for(int i = 0; i < n - 1; i ++) {
        if(beg[i] == semi) {
            ret ^= comb(n - 2, i);
        }
    }
    return ret * semi;
}

signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i ++) {
        char c;
        cin >> c;
        beg[i] = c - '0';
    }
    cout << solve();
    return 0;
    return 0;
}
