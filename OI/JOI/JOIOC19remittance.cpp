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
ll arr[MAX_N], target[MAX_N],	n;

bool cycle() {
	bool change = false;
	for(ll i = 0; i < n; i ++) {
		if(arr[i] <= target[i]) {continue;}
		ll need;
		if(arr[i] % 2 != target[i] % 2) {
			need = arr[i] - target[i] - 1;
		} else {
			need = arr[i] - target[i];			
		}
		chkmax(need, 2);
		if(arr[i] < need || need == 0) {continue;}
		change = true;
		arr[i] -= need;
		arr[(i + 1) % n] += need / 2;
	}
	return change;
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	for(ll i = 0; i < n; i ++) {
		cin >> arr[i] >> target[i];
	}
	while(cycle()) {}

	for(ll i = 0; i < n; i ++) {
		if(arr[i] != target[i]) {
			cout << "No" << endl;
			return 0;
		} 
	}
	cout << "Yes" << endl;
	return 0;
}

