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
 
const ll MAX_N = 1e5 + 10;
pair<int, int> pict[MAX_N];
int sze[MAX_N];
int n, m;
 
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for(int i = 0; i < n; i ++) {
		cin >> pict[i];
		swap(pict[i].first, pict[i].second);
	}
	for(int i = 0; i < m; i ++) {
		cin >> sze[i];
	}
	sort(pict, pict + n);
	reverse(pict, pict + n);
	sort(sze, sze + m);
	reverse(sze, sze + m);
	int ret = 0;
	for(int i = 0; i < n && ret < m; i ++) {
		if(pict[i].second <= sze[ret]) {
			ret ++;
		}
	}
	cout << ret << endl;
	return 0;
}