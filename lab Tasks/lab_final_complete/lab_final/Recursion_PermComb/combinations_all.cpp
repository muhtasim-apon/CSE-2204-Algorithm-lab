#include<bits/stdc++.h>
#define ll long long
using namespace std;

// =====================================================================
// Core (primary job, no instructor exact-spec given for this file):
// LC 77 Combinations — given n and k, generate all k-combinations of 1..n
// in lexicographic order.
// =====================================================================
static void lc77(int n, int k, int start, vector<int>& cur, vector<vector<int>>& res)
{
    if ((int)cur.size() == k) { res.push_back(cur); return; }
    for (int v = start; v <= n; v++) {
        cur.push_back(v);
        lc77(n, k, v + 1, cur, res);
        cur.pop_back();
    }
}

// =====================================================================
// LC 39: Combination Sum (unlimited reuse, no duplicates in output set)
// =====================================================================
static void lc39(vector<int>& cand, int target, int start, vector<int>& cur, vector<vector<int>>& res)
{
    if (target == 0) { res.push_back(cur); return; }
    for (int i = start; i < (int)cand.size(); i++) {
        if (cand[i] > target) continue;
        cur.push_back(cand[i]);
        lc39(cand, target - cand[i], i, cur, res); // i, not i+1: reuse allowed
        cur.pop_back();
    }
}

// =====================================================================
// LC 40: Combination Sum II (each number used once, candidates may repeat)
// =====================================================================
static void lc40(vector<int>& cand, int target, int start, vector<int>& cur, vector<vector<int>>& res)
{
    if (target == 0) { res.push_back(cur); return; }
    for (int i = start; i < (int)cand.size(); i++) {
        if (i > start && cand[i] == cand[i-1]) continue; // dedup
        if (cand[i] > target) break;
        cur.push_back(cand[i]);
        lc40(cand, target - cand[i], i + 1, cur, res);
        cur.pop_back();
    }
}

// =====================================================================
// LC 216: Combination Sum III (exactly k numbers from 1..9 summing to target)
// =====================================================================
static void lc216(int k, int target, int start, vector<int>& cur, vector<vector<int>>& res)
{
    if ((int)cur.size() == k) { if (target == 0) res.push_back(cur); return; }
    for (int v = start; v <= 9; v++) {
        if (v > target) break;
        cur.push_back(v);
        lc216(k, target - v, v + 1, cur, res);
        cur.pop_back();
    }
}

// =====================================================================
// LC 78: Subsets (all subsets, distinct nums)
// =====================================================================
static void lc78(vector<int>& nums, int start, vector<int>& cur, vector<vector<int>>& res)
{
    res.push_back(cur);
    for (int i = start; i < (int)nums.size(); i++) {
        cur.push_back(nums[i]);
        lc78(nums, i + 1, cur, res);
        cur.pop_back();
    }
}

// =====================================================================
// LC 90: Subsets II (nums may contain duplicates)
// =====================================================================
static void lc90(vector<int>& nums, int start, vector<int>& cur, vector<vector<int>>& res)
{
    res.push_back(cur);
    for (int i = start; i < (int)nums.size(); i++) {
        if (i > start && nums[i] == nums[i-1]) continue;
        cur.push_back(nums[i]);
        lc90(nums, i + 1, cur, res);
        cur.pop_back();
    }
}

// =====================================================================
// LC 17: Letter Combinations of a Phone Number
// =====================================================================
static void lc17(const string& digits, int idx, string& cur, vector<string>& res, vector<string>& mapping)
{
    if (idx == (int)digits.size()) { if (!cur.empty()) res.push_back(cur); return; }
    for (char c : mapping[digits[idx] - '0']) {
        cur.push_back(c);
        lc17(digits, idx + 1, cur, res, mapping);
        cur.pop_back();
    }
}

// =====================================================================
// LC 22: Generate Parentheses
// =====================================================================
static void lc22(int open, int close, string& cur, vector<string>& res)
{
    if (open == 0 && close == 0) { res.push_back(cur); return; }
    if (open > 0) { cur.push_back('('); lc22(open - 1, close, cur, res); cur.pop_back(); }
    if (close > open) { cur.push_back(')'); lc22(open, close - 1, cur, res); cur.pop_back(); }
}

void muhtasim()
{
    // ---------------- Core: LC 77 Combinations (primary job) ----------------
    // Input: n k  -> all k-combinations of 1..n
    ll n, k;
    cin >> n >> k;
    vector<int> cur;
    vector<vector<int>> res;
    lc77((int)n, (int)k, 1, cur, res);
    for (auto& c : res) {
        for (size_t i = 0; i < c.size(); i++) cout << c[i] << (i + 1 < c.size() ? ' ' : '\n');
    }

    // ---------------- Bundled LeetCode demo sections (run once) ----------------
    static bool demosShown = false;
    if (!demosShown) {
        demosShown = true;

        cout << "\n===== LC 39: Combination Sum (demo cand={2,3,6,7}, target=7) =====\n";
        {
            vector<int> cand = {2, 3, 6, 7};
            vector<int> tmp; vector<vector<int>> r;
            lc39(cand, 7, 0, tmp, r);
            for (auto& c : r) { for (size_t i = 0; i < c.size(); i++) cout << c[i] << (i+1<c.size()?' ':'\n'); }
        }

        cout << "\n===== LC 40: Combination Sum II (demo cand={10,1,2,7,6,1,5}, target=8) =====\n";
        {
            vector<int> cand = {10, 1, 2, 7, 6, 1, 5};
            sort(cand.begin(), cand.end());
            vector<int> tmp; vector<vector<int>> r;
            lc40(cand, 8, 0, tmp, r);
            for (auto& c : r) { for (size_t i = 0; i < c.size(); i++) cout << c[i] << (i+1<c.size()?' ':'\n'); }
        }

        cout << "\n===== LC 216: Combination Sum III (demo k=3, target=7) =====\n";
        {
            vector<int> tmp; vector<vector<int>> r;
            lc216(3, 7, 1, tmp, r);
            for (auto& c : r) { for (size_t i = 0; i < c.size(); i++) cout << c[i] << (i+1<c.size()?' ':'\n'); }
        }

        cout << "\n===== LC 78: Subsets (demo nums={1,2,3}) =====\n";
        {
            vector<int> nums = {1, 2, 3};
            vector<int> tmp; vector<vector<int>> r;
            lc78(nums, 0, tmp, r);
            for (auto& c : r) {
                cout << "{ "; for (int x : c) cout << x << ' '; cout << "}\n";
            }
        }

        cout << "\n===== LC 90: Subsets II (demo nums={1,2,2}) =====\n";
        {
            vector<int> nums = {1, 2, 2};
            sort(nums.begin(), nums.end());
            vector<int> tmp; vector<vector<int>> r;
            lc90(nums, 0, tmp, r);
            for (auto& c : r) {
                cout << "{ "; for (int x : c) cout << x << ' '; cout << "}\n";
            }
        }

        cout << "\n===== LC 17: Letter Combinations of a Phone Number (demo digits=\"23\") =====\n";
        {
            vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
            string digits = "23";
            string tmp; vector<string> r;
            lc17(digits, 0, tmp, r, mapping);
            for (auto& s : r) cout << s << ' ';
            cout << "\n";
        }

        cout << "\n===== LC 22: Generate Parentheses (demo n=3) =====\n";
        {
            string tmp; vector<string> r;
            lc22(3, 3, tmp, r);
            for (auto& s : r) cout << s << ' ';
            cout << "\n";
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
