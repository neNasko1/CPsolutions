#include "paint.h"

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

const int MAX_N = 2e5 + 10, MAX_K = 110;

bool dpPref[MAX_N][MAX_K], dpSuf[MAX_N][MAX_K];
int delta[MAX_N], pref[MAX_N];
bool black[MAX_N];
bool canBlack[MAX_N], canWhite[MAX_N];

void calculate(string s) {
    int n = s.size();
    for(int i = 0; i < n; i ++) {
        black[i + 1] = s[i] == 'X';
        if(s[i] == '_') {
            pref[i + 1] = 1;
        } else {
            pref[i + 1] = 0;
        }
        if(i != 0) {
            pref[i + 1] += pref[i];
        }
    }
}

int sum(int l, int r) {
    return pref[r] - pref[l - 1];
}

void upd(int l, int r) {
    delta[l] ++;
    delta[r + 1] --;
}

std::string solve_puzzle(std::string s, std::vector<int> c) {
    int n = s.size(), k = c.size();
    calculate(s);

    dpSuf[n + 1][k + 1] = true;
    for(int i = n; i > 0; i --) {
        char curr = s[i - 1];
        if(curr != 'X') {
            dpSuf[i][k + 1] = dpSuf[i + 1][k + 1];
        }
        for(int j = 1; j <= k; j ++) {
            int nowClue = c[j - 1];
            bool canContin = (i + nowClue + 1 <= n + 1 && dpSuf[i + nowClue + 1][j + 1] && !black[i + nowClue]) || (j == k  && i + nowClue + 1 == n + 2);
            if(curr == '.') {
                if(i + nowClue - 1 <= n && sum(i, i + nowClue - 1) == 0 && canContin) {
                    dpSuf[i][j] = true;
                } else {
                    dpSuf[i][j] = dpSuf[i + 1][j];
                }
            } else if(curr == '_') {
                dpSuf[i][j] = dpSuf[i + 1][j];
            } else if(curr == 'X') {
                if(i + nowClue - 1 <= n && sum(i, i + nowClue - 1) == 0 && canContin) {
                    dpSuf[i][j] = true;
                }
            }
        }
    }

    dpPref[0][0] = true;
    for(int i = 1; i <= n; i ++) {
        char curr = s[i - 1];
        if(curr != 'X') {
            dpPref[i][0] = dpPref[i - 1][0];
        }
        for(int j = 1; j <= k; j ++) {
            int nowClue = c[j - 1];
            bool canContin = (i - nowClue - 1 >= 0 && dpPref[i - nowClue - 1][j - 1] && !black[i - nowClue]) || (j == 1 && i - nowClue - 1 == -1);
            bool got = false;
            if(curr == '.') {
                if(i >= nowClue && sum(i - nowClue + 1, i) == 0 && canContin) {
                    dpPref[i][j] = true;
                    got = true;
                } else {
                    dpPref[i][j] = dpPref[i - 1][j];
                }
            } else if(curr == '_') {
                dpPref[i][j] = dpPref[i - 1][j];
            } else if(curr == 'X') {
                if(i - nowClue + 1 >= 1 && sum(i - nowClue + 1, i) == 0 && canContin) {
                    dpPref[i][j] = true;
                    got = true;
                }
            }
            if(got && ((i == n && j == k) || (dpSuf[i + 2][j + 1] && s[i] != 'X'))) {
                upd(i - nowClue + 1, i);
            }

        }
    }

    for(int i = 1; i <= n; i ++) {
        if(s[i - 1] != '.') {canWhite[i] = s[i - 1] == '.'; continue;}
        for(int j = 0; j <= k; j ++) {
            if(dpPref[i - 1][j] && dpSuf[i + 1][j + 1]) {
                canWhite[i] = true;
            }
        }
    }
    int nowSum = 0;
    for(int i = 1; i <= n; i ++) {
        nowSum += delta[i];
        if(nowSum > 0) {
            canBlack[i] = true;
        }
    }
    string ret = "";
    for(int i = 1; i <= n; i ++) {
        if(s[i - 1] != '.') {
            ret += s[i - 1];
        } else {
            if(!canBlack[i]) {
                ret += '_';
            } else if(!canWhite[i]) {
                ret += 'X';
            } else {
                ret += '?';
            }
        }
    }
    return ret;
    return "";
}
