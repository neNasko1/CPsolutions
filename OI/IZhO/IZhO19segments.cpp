#include <bits/stdc++.h>
using namespace std;
#define endl "\n" // BRAT NASKO KUF E TOQ TRASH KOD
template<class T, class T2> bool chkmax(T &a, const T2 &b) {return (a < b) ? a = b, 1 : 0;}
typedef long long ll;

const ll MAX_N = 5e5 + 10;
ll arr[MAX_N];

ll tree[4 * MAX_N];

void upd(ll curr, ll l, ll r, ll ind, ll val) {
	if(l == r && l == ind) {
		chkmax(tree[curr], val);
		return;
	} else if(r < ind || l > ind) {return;}
	ll m = (l + r) / 2ll;
	upd(curr * 2, l, m, ind, val);
	upd(curr * 2 + 1, m + 1, r, ind, val);
	tree[curr] = max(tree[curr * 2], tree[curr * 2 + 1]);
}

ll ans(ll curr, ll l, ll r, ll ql, ll qr) {
	if(ql <= l && r <= qr) {
		return tree[curr];
	} else if(l > qr || r < ql) {
		return 0;
	}
	ll m = (l + r) / 2ll;
	return max(ans(curr * 2, l, m, ql, qr), ans(curr * 2 + 1, m + 1, r, ql, qr));
}

ll dp[MAX_N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	ll n;
	cin >> n;
	for(ll i = 1; i <= n; i ++) {
		cin >> arr[i];
		arr[i] += arr[i - 1];
	}
	for(ll i = 1; i <= n; i ++) {
		ll curr = ans(1, 0, n, 0, i);
		dp[i] = dp[curr] + 1;
		ll nowWeight = arr[i] * 2 - arr[curr];
		ll ind = lower_bound(arr + 1, arr + n + 1, nowWeight) - arr;
		upd(1, 0, n, ind, i);
	}
	cout << dp[n] << endl;
}
