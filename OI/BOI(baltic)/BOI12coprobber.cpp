#include "coprobber.h"
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

bool win[MAX_N][MAX_N][2];
int hist[MAX_N][MAX_N][2];
bool used[MAX_N][MAX_N][2];
vector<int> g[MAX_N];
int n, cnt[MAX_N];
int cntChase[MAX_N][MAX_N][2];
int current;

int start(int N, bool A[MAX_N][MAX_N]) {
    n = N;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            if(A[i][j] == 1 || i == j) {
                g[i].push_back(j);
                cnt[i] ++;
            }
        }
    }
    queue<pair<pair<int, int>, int> > q;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            cntChase[i][j][0] = cnt[i] - 1;
            cntChase[i][j][1] = cnt[j] - 1;
        }
    }
    for(int i = 0; i < n; i ++) {
        win[i][i][0] = win[i][i][1] = true;
        used[i][i][0] = used[i][i][1] = true;
        q.push({{i, i}, 0});
        q.push({{i, i}, 1});
    }

    while(!q.empty()) {
        auto curr = q.front(); q.pop();
        int a, b, who;
        a = curr.first.first; b = curr.first.second; who = curr.second;
        if(who) {
            for(auto it : g[a]) {
                if(used[it][b][who ^ 1]) {continue;}
                win[it][b][who ^ 1] = true;
                hist[it][b][who ^ 1] = a;
                used[it][b][who ^ 1] = true;
                q.push({{it, b}, who ^ 1});
            }
        } else {
            for(auto it : g[b]) {
                if(used[a][it][who ^ 1] || it == b) {continue;}
                cntChase[a][it][who ^ 1] --; if(cntChase[a][it][who ^ 1] > 0) {continue;}
                win[a][it][who ^ 1] = true;
                used[a][it][who ^ 1] = true;
                q.push({{a, it}, who ^ 1});
            }
        }
    }

    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j ++) {
            if(!win[i][j][0]) {break;}
            if(j == n - 1) {
                return current = i;
            }
        }
    }
    return -1;
}

int nextMove(int R) {
    return current = hist[current][R][0];
}
