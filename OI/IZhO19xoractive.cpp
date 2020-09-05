#include <iostream>
#include <bits/stdc++.h>

#include "interactive.h"
using namespace std;

///We can find the elements of a set S with 2 queries.
///We use the fact that all the elements are different - for every value we can find on which position it is found.
///Then for every bit we ask about the indexes with this bit set.

map<int, int> mp;

vector<int> guess(int n) {
    int zer = ask(1);
    vector<int> ret(n);
    for(int bit = 0; bit < 7; bit ++) {
        vector<int> curr;
        for(int i = 0; i < n; i ++) if(i & (1 << bit)) {
            curr.push_back(i + 1);
        }
        if(curr.empty()) {continue;}
        vector<int> ans1, ans2, ans3;
        ans1 = get_pairwise_xor(curr);
        curr.push_back(1);
        ans2 = get_pairwise_xor(curr);
        int cnt = 0;
        ans1.push_back(-1);
        for(int i = ans1.size() - 2; i >= 0; i --) {
            ans1[i + 1] = ans1[i];
        }
        ans1[0] = 0;
        for(auto it : ans2) {
            if(cnt >= (int)ans1.size() || ans1[cnt] != it) {
                ans3.push_back(it ^ zer);
            } else {
                cnt ++;
            }
        }
        for(auto it : ans3) {
            mp[it] |= (1 << bit);
        }
    }
    for(auto it : mp) {
        ret[it.second] = it.first;
    }
    ret[0] = zer;
    return ret;
}
