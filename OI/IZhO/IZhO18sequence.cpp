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
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

const int MAX_N = 4e5 + 10;
vector<int> g[MAX_N];
int used[MAX_N];
int n, m;
int arr[MAX_N], pref[MAX_N];

vector<int> top;

bool eval(int x) {
    top.resize(0);
    for(int i = 0; i <= x; i ++) {
        g[i].resize(0);
        used[i] = 0;
    }
    for(int i = 0; i <= x; i ++) {
        if(i + n <= x) {
            g[i + n].push_back(i);
            used[i] ++;
        }
        if(i - m >= 0) {
            g[i - m].push_back(i);
            used[i] ++;
        }
    }
    for(int i = 0; i <= x; i ++) {
        if(used[i] == 0) {
            top.push_back(i);
        }
    }
    int ind = 0;
    while(ind < top.size()) {
        auto curr = top[ind]; ind ++;
        for(auto it : g[curr]) {
            used[it] --;
            if(used[it] == 0) {
                top.push_back(it);
            }
        }
    }
    return top.size() == x + 1;
}

void build(int x) {
    for(int i = 0; i <= x; i ++) {
        pref[top[i]] = i;
    }
    for(int i = 0; i < x; i ++) {
        arr[i] = pref[i + 1] - pref[i];
    }
}

void solve() {
    cin >> n >> m;
    int l = n + m - __gcd(n, m) - 1;
    cout << l << endl;
    eval(l);
    build(l);
    for(int i = 0; i < l; i ++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int t;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}

