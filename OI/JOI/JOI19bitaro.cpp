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
 
const ll MAX_N = 3e3 + 10;
ll cnto[MAX_N][MAX_N], cnti[MAX_N][MAX_N];
string in[MAX_N];
ll n, m;
 
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for(ll i = 0; i < n; i ++) {
		cin >> in[i];
	}	
	ll ans = 0;
	for(ll i = n - 1; i >= 0; i --) {
		for(ll j = m - 1; j >= 0; j --) {
			cnto[i][j] = cnto[i][j + 1];
			cnti[i][j] = cnti[i + 1][j];
			if(in[i][j] == 'O') {
				cnto[i][j] ++;
			} else if(in[i][j] == 'I') {
				cnti[i][j] ++;
			} else {
				ans += cnto[i][j] * cnti[i][j];
			}
		}
	}
	cout << ans << endl;
	return 0;
}