#include "xylophone.h"
 
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
 
const int MAX_N = 5e3 + 10;
int two[MAX_N], three[MAX_N];
 
void solve(int n) {
	for(int i = 1; i <= n - 1; i ++) {
		two[i] = query(i, i + 1);
	}
	for(int i = 1; i <= n - 2; i ++) {
		three[i] = query(i, i + 2);
	}
	int curr = 0;
	pair<int, int> mn = {0, 1}, mx = {0, 1};
	int last = 1;
	for(int i = 1; i < n; i ++) {
		if(i == 1 || two[i - 1] + two[i] == three[i - 1]) {
			curr += two[i] * last;
		} else {
			last *= -1;
			curr += two[i] * last;
		}
		chkmin(mn, make_pair(curr, i));
		chkmax(mx, make_pair(curr, i));
	}
	if(mn.second > mx.second) {
		last = -1;
		mx.first *= -1;
		mn = mx;
	} else {
		last = 1;
	}
	curr = -mn.first + 1;
	answer(1, curr);
	for(int i = 1; i <= n - 1; i ++) {
		if(i == 1 || two[i - 1] + two[i] == three[i - 1]) {
			curr += two[i] * last;
		} else {
			last *= -1;
			curr += two[i] * last;
		}
		answer(i + 1, curr);
	}
}