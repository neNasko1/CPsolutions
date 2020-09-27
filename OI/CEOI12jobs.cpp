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

const int MAX_N = 1e6 + 10;
pair<int, int> arr[MAX_N];
vector<int> p;
int n, d, m;

bool eval(int x) {
    priority_queue<int> pq;
    int ind = 0;
    for(int i = 1; i <= m; i ++) {
        while(ind < n && arr[ind].first == i) {
            pq.push(-arr[ind].first - d);
            ind ++;
        }
        for(int j = 0; j < x; j ++) {
            if(pq.empty()) {break;}
            pq.pop();
        }
        if(!pq.empty() && -pq.top() <= i) {
            return false;
        }
    }
    return true;
}

void print(int x) {
    priority_queue<pair<int, int> > pq;
    int ind = 0;
    for(int i = 1; i <= m; i ++) {
        while(ind < n && arr[ind].first == i) {
            pq.push({-arr[ind].first - d, arr[ind].second + 1});
            ind ++;
        }
        for(int j = 0; j < x; j ++) {
            if(pq.empty()) {break;}
            cout << pq.top().second << " ";
            pq.pop();
        }
        cout << 0 << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> m >> d >> n;
    for(int i = 0; i < n; i ++) {
        cin >> arr[i].first;
        arr[i].second = i;
        p.push_back(arr[i].first);
        p.push_back(arr[i].first + d);
    }
    sort(arr, arr + n);
    int l = 0, r = n + 1;
    while(l < r - 1) {
        int m = (l + r) / 2ll;
        if(eval(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r << endl;
    print(r);
    return 0;

}

/*
8 2 12
1 2 4 2 1 3 5 6 2 3 6 4
*/
