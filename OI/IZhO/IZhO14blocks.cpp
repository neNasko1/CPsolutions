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

const int MAX_N = 1e5 + 10, MAX_K = 110;
int arr[MAX_N], n, k;
int dpFinished[MAX_N][MAX_K];
int dpOpen[MAX_N][MAX_K];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> k;
    for(int i = 1; i <= n; i ++) {
        cin >> arr[i];
    }
    for(int i = 0; i <= n; i ++) {
        for(int j = 0; j <= k; j ++) {
            dpFinished[i][j] = dpOpen[i][j] = mod;
        }
    }
    stack<pair<int, int> > st;
    for(int i = 1; i <= n; i ++) {
        while(!st.empty() && st.top().first <= arr[i]) {
            for(int j = 1; j <= k; j ++) {
                chkmin(dpFinished[i][j], min(dpFinished[st.top().second][j - 1], dpOpen[st.top().second][j - 1]) + arr[i]);
                chkmin(dpOpen[i][j], min(dpOpen[st.top().second][j], dpFinished[st.top().second][j]));
            }
            st.pop();
        }
        if(st.empty()) {
            chkmin(dpFinished[i][1], arr[i]);
        } else {
            for(int j = 1; j <= k; j ++) {
                chkmin(dpFinished[i][j], min(dpFinished[st.top().second][j], dpFinished[st.top().second][j - 1] + arr[i]));
            }
        }
        st.push({arr[i], i});
    }
    cout << dpFinished[n][k] << endl;
    return 0;
}


