#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

///Dp using meet in the middle approach for optimization. Dp[x][y][c] = answer where last number has first 10 bits = x, and the bitwise and of y and last 10 bits of the number has c set bits.

const int MAX_N = 1e5 + 10, MAX_BIT = 20;
const int half = 10;
int dp[1 << half][1 << half][half + 1];
int last[1 << half][1 << half][half + 1];
int hist[MAX_N];
int arr[MAX_N], need[MAX_N];

void output(int ind) {
    if(ind == -1) {return;}
    output(hist[ind]);
    cout << ind + 1 << " ";
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        cin >> arr[i];
    }
    for(int i = 0; i < n; i ++) {
        cin >> need[i];
    }
    int ans = 0, ansind = 0;
    for(int i = 0; i < n; i ++) {
        int first = arr[i] / (1 << half), second = arr[i] % (1 << half);
        int getMax = 0, histind = -1;
        for(int j = 0; j < (1 << half); j ++) {
            for(int k = 0; k < half; k ++) {
                if(k + __builtin_popcount(j & first) == need[i]) {
                    if(chkmax(getMax, dp[j][second][k])) {
                        histind = last[j][second][k];
                    }
                }
            }
        }
        for(int j = 0; j < (1 << half); j ++) {
            int popcount = __builtin_popcount(j & second);
            if(chkmax(dp[first][j][popcount], getMax + 1)) {
                last[first][j][popcount] = i;
            }
        }
        hist[i] = histind;
        if(chkmax(ans, getMax + 1)) {
            ansind = i;
        }
    }
    cout << ans << endl;
    output(ansind);
    cout << endl;
    return 0;
}


