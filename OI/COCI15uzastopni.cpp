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

///First consider the bool dp[x][l][r]: True means we can make interval l, r in the subtree of x using x. Then we can decompose the problem into left part and right part - construct graph for possible intervals of x-ses children.

const int MAX_N = 1e4 + 10, MAX_VAL = 1e2 + 10;
vector<int> g[MAX_N];
int arr[MAX_N];
bool used[MAX_VAL];

vector<pair<short, short> > dfs(int x, int p) {
    vector<short> fake[MAX_VAL];
    for(int i = 0; i < MAX_VAL; i ++) {
        fake[i].resize(0);
    }
    for(auto it : g[x]) {
        if(it == p) {continue;}
        auto dp = dfs(it, x);
        for(auto &inter : dp) {
            int i = inter.first;
            int j = inter.second;
            if(i <= arr[x] && j >= arr[x]) {continue;}
            if(i == arr[x] || j == arr[x]) {continue;}
            if(i < arr[x]) {
                fake[j].push_back(i - 1);
            } else {
                fake[i].push_back(j + 1);
            }
        }
    }

    for(int i = 0; i < MAX_VAL; i ++) {
        used[i] = false;
    }
    vector<int> foundl, foundr;
    vector<pair<short, short> > ret;
    ret.resize(0);
    queue<short> q;
    q.push(arr[x] - 1);
    q.push(arr[x] + 1);
    used[arr[x] + 1] = true;
    used[arr[x] - 1] = true;
    foundl.push_back(arr[x] - 1);
    foundr.push_back(arr[x] + 1);
    while(!q.empty()) {
        auto curr = q.front(); q.pop();
        for(auto it : fake[curr]) {
            if(!used[it]) {
                used[it] = true;
                if(it < arr[x]) {
                    foundl.push_back(it);
                } else {
                    foundr.push_back(it);
                }
                q.push(it);
            }
        }
    }

    for(auto l : foundl) {
        for(auto r : foundr) {
            ret.push_back({l + 1, r - 1});
        }
    }
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++) {
        cin >> arr[i];
    }
    for(int i = 0; i < n - 1; i ++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    cout << dfs(1, 0).size() << endl;
    return 0;
}


