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

const int MAX_N = 2e5 + 10;
int n, m;
vector<pair<int, int> > swps;
vector<int> start;
bool used[MAX_N];
int inv[MAX_N];

int countCycles(vector<int> &a) {
    int cnt = 0;
    for(int i = 0; i < a.size(); i ++) {used[i] = false;}
    for(int i = 0; i < a.size(); i ++) {
        if(used[i]) {continue;}
        cnt ++;
        int curr = i;
        while(!used[curr]) {
            used[curr] = true;
            curr = a[curr];
        }
    }
    return cnt;
}

vector<pair<int, int> > getPairs(vector<int> &a) {
    vector<pair<int, int> > ret;
    for(int i = 0; i < a.size(); i ++) {used[i] = false;}
    for(int i = 0; i < a.size(); i ++) {
        if(used[i]) {continue;}
        int curr = i, ind = i;
        while(!used[curr]) {
            used[curr] = true;
            curr = a[curr];
            if(curr != i) {
                ret.push_back({curr, ind});
            }
            ind = curr;
        }
    }
    return ret;
}

bool eval(int x) {
    vector<int> toAsk = start;
    for(int i = 0; i < x; i ++) {
        swap(toAsk[swps[i].first], toAsk[swps[i].second]);
    }
    return n - countCycles(toAsk) <= x;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]) {
    n = N;
    m = M;
    for(int i = 0; i < n; i ++) {
        start.push_back(S[i]);
    }
    for(int i = 0; i < m; i ++) {
        swps.push_back({X[i], Y[i]});
    }
    if(countCycles(start) == n) {
        return 0;
    }
    int l = 0, r = m;
    while(l < r - 1) {
        int mid = (l + r) / 2ll;
        if(eval(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    vector<int> atEnd = start;
    for(int i = 0; i < r; i ++) {
        swap(atEnd[swps[i].first], atEnd[swps[i].second]);
    }
    for(int i = 0; i < n; i ++) {
        inv[atEnd[i]] = i;
    }
    auto toRet = getPairs(atEnd);
    vector<pair<int, int> > ret;
    for(int i = 0; i < r; i ++) {
        int ind = r - 1 - i;
        if(i >= toRet.size()) {
            ret.push_back({0, 0});
        } else {
            ret.push_back({inv[toRet[i].first], inv[toRet[i].second]});
        }
        swap(inv[atEnd[swps[ind].first]], inv[atEnd[swps[ind].second]]);
        swap(atEnd[swps[ind].first], atEnd[swps[ind].second]);
    }
    reverse(ret.begin(), ret.end());
    for(int i = 0; i < r; i ++) {
        P[i] = ret[i].first;
        Q[i] = ret[i].second;
    }
	return r;
}


