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
 
const ll MAX_N = 1e6 + 10;
ll n;
ll arr[MAX_N][2];	
 
ll dpLow[MAX_N][2], dpHigh[MAX_N][2];
 
bool output(ll x, ll y, ll got = mod) {
	if(x == -1) {return true;}
 
	if(dpLow[x][0] <= y && y <= dpHigh[x][0] && arr[x][0] <= got) {
		output(x - 1, y, arr[x][0]);
		cout << "A";
		return true;
	} else if(dpLow[x][1] <= y && y <= dpHigh[x][1] && arr[x][1] <= got) {	
		output(x - 1, y - 1, arr[x][1]);
		cout << "B";
		return true;
	}
	return false;
}
 
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	n *= 2;
	for(ll j = 0; j < 2; j ++) {
		for(ll i = 0; i < n; i ++ ){
			cin >> arr[i][j];
		}
	}
	
	for(ll i = 0; i < n; i ++) {
		dpLow[i][0] = dpLow[i][1] = mod;
		dpHigh[i][0] = dpHigh[i][1] = -mod;
	}
	
	dpLow[0][0] = 0; dpHigh[0][0] = 0;
	dpLow[0][1] = 1; dpHigh[0][1] = 1;
	
	for(ll i = 0; i < n; i ++) {
		for(ll j = 0; j < 2; j ++) {
			ll now = arr[i][j];
			if(now <= arr[i + 1][0]) {
				chkmin(dpLow[i + 1][0], dpLow[i][j]);
				chkmax(dpHigh[i + 1][0], dpHigh[i][j]);
			}
			if(now <= arr[i + 1][1]) {
				chkmin(dpLow[i + 1][1], dpLow[i][j] + 1);
				chkmax(dpHigh[i + 1][1], dpHigh[i][j] + 1);
			}
		}
	}
	if(!output(n - 1, n / 2)) {
		cout << -1 << endl;
	} 
	return 0;
}