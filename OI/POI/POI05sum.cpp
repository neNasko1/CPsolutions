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

///Fi = Fi-1 + Fi-2 and 2Fi = Fi+1 + Fi-2

const int MAX_N = 1e6 + 10;
int arr[MAX_N + 100];

signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    for(int i = 0; i < n; i ++) {
        cin >> arr[i];
    }
    cin >> n;
    for(int i = 0; i < n; i ++) {
        int a;
        cin >> a;
        arr[i] += a;
    }
    for(int i = MAX_N - 1; i >= 0; i --) {
        if(arr[i] == 0) {continue;}
        if(arr[i] == 1 && (i == 0 || arr[i - 1] == 0)) {continue;}
        if(arr[i] >= 1 && arr[i - 1] >= 1) {
            arr[i + 1] ++;
            arr[i] --;
            arr[i - 1] --;
            i += 10;
            continue;
        } else if(arr[i] >= 2) {
            if(i == 0) {
                arr[i + 1] ++;
                arr[i] -= 2;
                i += 10;
                continue;
            } else {
                arr[i] -= 2;
                arr[i + 1] ++;
                if(i == 1) {
                    arr[0] ++;
                } else {
                    arr[i - 2] ++;
                }
                i += 10;
                continue;
            }
        }
    }
    bool flag = 0;
    vector<int> ans;
    for(int i = MAX_N - 1; i >= 0; i --) {
        if(arr[i]) {
            flag = true;
        }
        if(flag) {
            ans.push_back(arr[i]);
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << " ";
    for(auto it : ans) {
        cout << it << " ";
    }
    return 0;
}


