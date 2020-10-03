#include "gondola.h"

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
const ll mod = 1e9 + 9;
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

bool different(int n, int inputSeq[]) {
    vector<int> ret;
    for(int i = 0; i < n; i ++) {
        ret.push_back(inputSeq[i]);
    }
    sort(ret.begin(), ret.end());
    for(int i = 0; i < n - 1; i ++) {
        if(ret[i] == ret[i + 1]) {
            return false;
        }
    }
    return true;
}

int valid(int n, int inputSeq[]) {
    int ind = -1;
    for(int i = 0; i < n; i ++) {
        if(inputSeq[i] <= n) {
            ind = i;
            break;
        }
    }
    if(ind != -1) {
        int rot = (-inputSeq[ind] + ind + 1 + n) % n;
        rotate(inputSeq, inputSeq + rot, inputSeq + n);
    }
    for(int i = 0; i < n; i ++) {
        if(inputSeq[i] <= n && inputSeq[i] != i + 1) {
            return 0;
        }
    }
    return different(n, inputSeq);
}

//----------------------

const int MAX_N = 3e5 + 10;
int arr[MAX_N];

int replacement(int n, int gondolaSeq[], int replacementSeq[]) {
    int ind = -1;
    vector<pair<int, int> > pos;
    for(int i = 0; i < n; i ++) {
        if(gondolaSeq[i] <= n) {
            ind = i;
            break;
        }
    }
    sort(pos.begin(), pos.end());
    if(ind != -1) {
        int rot = (-gondolaSeq[ind] + ind + 1 + n) % n;
        rotate(gondolaSeq, gondolaSeq + rot, gondolaSeq + n);
    }
    for(int i = 0; i < n; i ++) {
        arr[i] = i + 1;
        if(gondolaSeq[i] > n) {
            pos.push_back({gondolaSeq[i], i});
        }
    }
    sort(pos.begin(), pos.end());
    int l = 0, curr = n + 1;
    for(auto it : pos) {
        while(curr <= it.first) {
            replacementSeq[l ++] = arr[it.second];
            arr[it.second] = curr;
            curr ++;
        }
    }
    return l;
}

//----------------------

ll fpow(ll x, ll p) {
    if(p == 0) {
        return 1;
    }
    ll ans = fpow(x, p / 2ll); ans = (ans * ans) % mod;
    if(p & 1) {
        return (ans * x) % mod;
    } else {
        return ans;
    }
}

int countReplacement(int n, int inputSeq[]) {
    vector<pair<ll, ll> > pos;
    for(ll i = 0; i < n; i ++) {
        if(inputSeq[i] > n) {
            pos.push_back({inputSeq[i], i});
        }
    }
    sort(pos.begin(), pos.end());
    ll lft = pos.size();
    ll ret = 1, curr = n + 1;
    if(pos.size() == n) {
        ret = n;
    }
    for(ll i = 0; i < pos.size(); i ++) {
        ret = (ret * fpow(pos.size() - i, pos[i].first - curr)) % mod;
        curr = pos[i].first + 1;
    }
    return ret * valid(n, inputSeq);
}
