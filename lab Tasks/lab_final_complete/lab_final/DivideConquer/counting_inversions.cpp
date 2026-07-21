#include<bits/stdc++.h>
#define ll long long
using namespace std;

// =====================================================================
// Core: count inversions in an array via merge sort, O(n log n).
// An inversion is a pair (i<j) with a[i] > a[j].
// =====================================================================
static ll mergeCount(vector<ll>& a, vector<ll>& tmp, int l, int r)
{
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    ll inv = mergeCount(a, tmp, l, m) + mergeCount(a, tmp, m, r);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[k++] = a[i++];
        else { tmp[k++] = a[j++]; inv += (m - i); } // a[i..m-1] all > a[j]
    }
    while (i < m) tmp[k++] = a[i++];
    while (j < r) tmp[k++] = a[j++];
    for (int x = l; x < r; x++) a[x] = tmp[x];
    return inv;
}

static ll countInversions(vector<ll> a)
{
    vector<ll> tmp(a.size());
    return mergeCount(a, tmp, 0, (int)a.size());
}

// =====================================================================
// LC 493: Reverse Pairs — count pairs i<j with nums[i] > 2*nums[j] (long long to avoid overflow)
// =====================================================================
static ll reversePairsCount(vector<ll>& a, vector<ll>& tmp, int l, int r)
{
    if (r - l <= 1) return 0;
    int m = (l + r) / 2;
    ll cnt = reversePairsCount(a, tmp, l, m) + reversePairsCount(a, tmp, m, r);
    int j = m;
    for (int i = l; i < m; i++) {
        while (j < r && a[i] > 2 * a[j]) j++;
        cnt += (j - m);
    }
    int i = l, k = l, jj = m;
    while (i < m && jj < r) {
        if (a[i] <= a[jj]) tmp[k++] = a[i++];
        else tmp[k++] = a[jj++];
    }
    while (i < m) tmp[k++] = a[i++];
    while (jj < r) tmp[k++] = a[jj++];
    for (int x = l; x < r; x++) a[x] = tmp[x];
    return cnt;
}

// =====================================================================
// LC 315: Count of Smaller Numbers After Self — merge sort over (value, origIndex) pairs
// =====================================================================
static void countSmaller(vector<pair<ll,int>>& a, vector<pair<ll,int>>& tmp, int l, int r, vector<int>& res)
{
    if (r - l <= 1) return;
    int m = (l + r) / 2;
    countSmaller(a, tmp, l, m, res);
    countSmaller(a, tmp, m, r, res);
    int i = l, j = m, k = l;
    int rightCountSoFar = 0;
    while (i < m && j < r) {
        if (a[j].first < a[i].first) { rightCountSoFar++; tmp[k++] = a[j++]; }
        else { res[a[i].second] += rightCountSoFar; tmp[k++] = a[i++]; }
    }
    while (i < m) { res[a[i].second] += rightCountSoFar; tmp[k++] = a[i++]; }
    while (j < r) tmp[k++] = a[j++];
    for (int x = l; x < r; x++) a[x] = tmp[x];
}

void muhtasim()
{
    // ---------------- Core: counting inversions (primary job) ----------------
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    cout << countInversions(a) << "\n";

    // ---------------- Bundled LeetCode demo sections (run once) ----------------
    static bool demosShown = false;
    if (!demosShown) {
        demosShown = true;

        cout << "\n===== LC 493: Reverse Pairs (demo [1,3,2,3,1]) =====\n";
        {
            vector<ll> nums = {1, 3, 2, 3, 1};
            vector<ll> tmp(nums.size());
            cout << reversePairsCount(nums, tmp, 0, (int)nums.size()) << "\n"; // expected 2
        }

        cout << "\n===== LC 315: Count of Smaller Numbers After Self (demo [5,2,6,1]) =====\n";
        {
            vector<int> nums = {5, 2, 6, 1};
            vector<pair<ll,int>> a;
            for (int i = 0; i < (int)nums.size(); i++) a.push_back({nums[i], i});
            vector<pair<ll,int>> tmp(a.size());
            vector<int> res(a.size(), 0);
            countSmaller(a, tmp, 0, (int)a.size(), res);
            for (size_t i = 0; i < res.size(); i++) cout << res[i] << (i + 1 < res.size() ? ' ' : '\n'); // expected 2 1 1 0
        }
    }
}
int main()
{
ios::sync_with_stdio(false);
cin.tie(nullptr);
ll tests;
cin>>tests;
while(tests--)
{
muhtasim();
}
}
