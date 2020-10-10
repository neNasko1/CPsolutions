#include "prize.h"
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

map<int, vector<int> > prec;

vector<int> query(int x) {
    if(prec.find(x) != prec.end()) {
        return prec[x];
    } else {
        return prec[x] = ask(x);
    }
}

bool eval(vector<int> curr, vector<int> nxt, int bigSum) {
    if(nxt[0] + nxt[1] != bigSum) {
        return true;
    } else if(nxt[0] != curr[0]) {
        return true;
    } else {
        return false;
    }
}

int find_best(int n) {
    prec.clear();
    int sqr = sqrt(n), group;
    int bigSum = 0;
    for(int i = n - 1; i > 0; i -= sqr) {
        auto now = query(i);
        chkmax(bigSum, now[0] + now[1]);
        group = i;
        //cout << i << " " << now[0] << " " << now[1] << endl;
    }
    for(int i = 0; i < n;) {
        if(i > group) {group += sqr;}
        //cout << i << endl;
        auto now = query(i), grNow = query(group);
        if(now[0] + now[1] != bigSum) {
            if(now[0] + now[1] == 0) {
                return i;
            }
            i ++;
            continue;
        }
        if(!eval(now, grNow, bigSum)) {
            i = group + 1;
            continue;
        }
        int l = i, r = group;
        while(l < r - 1) {
            int m = (l + r) / 2ll;
            if(eval(now, query(m), bigSum)) {
                r = m;
            } else {
                l = m;
            }
        }
        i = r; continue;
    }
    for(auto it : prec) {
        if(it.second[0] + it.second[1] == 0) {
            return it.first;
        }
    }
    return -1;
}
