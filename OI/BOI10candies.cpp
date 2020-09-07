#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

///Using bitsets we can optimize the DP from O(n*W) to O(n*W/32) which is enough to pass
///To find the index which we have to change we try removing every element and find out which subset of the remaining gives us the most different sums
///To find the new value we must find the smallest integer which is not a difference of two possible sums.

const int MAX_N = 210, MAX_W = 7000;
bitset<MAX_N * MAX_W> pos;

int can[MAX_N], sum;
int n;

int findCnt() {
    pos.reset();
    pos[0] = true;
    for(int i = 0; i < n; i ++) {
        if(can[i] > 0) {
            pos |= pos << can[i];
        } else {
            pos |= pos >> (-can[i]);
        }
    }
    return pos.count();
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i ++) {
        cin >> can[i];
        sum += can[i];
    }
    int best = -1;
    int ind;
    for(int i = 0; i < n; i ++) {
        int last = can[i];
        can[i] = 0;
        int curr = findCnt();
        if(chkmax(best, curr)) {
            ind = i;
        } else if(best == curr) {
            if(can[i] < can[ind]) {
                ind = i;
            }
        }
        can[i] = last;
    }
    best = -1;
    int retInd = 0, retLast = can[ind];
    can[ind] = 0;
    for(int i = 0; i < n; i ++) {
        can[i + n] = -can[i];
    }
    n = 2 * n;
    findCnt();
    while(pos[retInd]) {retInd ++;}
    cout << retLast << " " << retInd << endl;
    return 0;
}


