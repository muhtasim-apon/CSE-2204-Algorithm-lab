#include<bits/stdc++.h>
#define ll long long
using namespace std;

// =====================================================================
// Instructor "Problem A: Permutation" — helper machinery
// Given N, print all permutations of 1..N such that:
//   1. No two even numbers are adjacent.
//   2. No two odd numbers are adjacent.
//   3. |adjacent difference| < 5.
// Output must be in increasing (lexicographic) order of the sequences.
//
// Approach: backtracking that fills the permutation left to right,
// trying the still-unused values in ASCENDING order at every position.
// Because candidates are always tried smallest-first, the sequences are
// produced in exact lexicographic order (no separate sort needed).
// At each step we prune immediately if placing the candidate would
// violate parity-alternation (rules 1+2 combined, since there are only
// two parity classes, "different parity" <=> "not two evens / not two
// odds adjacent") or the diff<5 rule (rule 3).
// =====================================================================
static void solvePermA(int n, vector<int>& cur, vector<bool>& used, vector<string>& out)
{
    if ((int)cur.size() == n) {
        string line;
        for (int i = 0; i < n; i++) {
            if (i) line += ' ';
            line += to_string(cur[i]);
        }
        out.push_back(line);
        return;
    }
    for (int v = 1; v <= n; v++) {
        if (used[v]) continue;
        if (!cur.empty()) {
            int last = cur.back();
            if ((last % 2) == (v % 2)) continue;       // rules 1 & 2
            if (abs(last - v) >= 5) continue;           // rule 3
        }
        used[v] = true;
        cur.push_back(v);
        solvePermA(n, cur, used, out);
        cur.pop_back();
        used[v] = false;
    }
}

// =====================================================================
// LC 46: Permutations (distinct integers) — plain backtracking
// =====================================================================
static void lc46(vector<int>& nums, vector<int>& cur, vector<bool>& used, vector<vector<int>>& res)
{
    if (cur.size() == nums.size()) { res.push_back(cur); return; }
    for (size_t i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        used[i] = true;
        cur.push_back(nums[i]);
        lc46(nums, cur, used, res);
        cur.pop_back();
        used[i] = false;
    }
}

// =====================================================================
// LC 47: Permutations II (with duplicates) — sort + skip-duplicate rule
// =====================================================================
static void lc47(vector<int>& nums, vector<int>& cur, vector<bool>& used, vector<vector<int>>& res)
{
    if (cur.size() == nums.size()) { res.push_back(cur); return; }
    for (size_t i = 0; i < nums.size(); i++) {
        if (used[i]) continue;
        if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue; // dedup
        used[i] = true;
        cur.push_back(nums[i]);
        lc47(nums, cur, used, res);
        cur.pop_back();
        used[i] = false;
    }
}

// =====================================================================
// LC 60: Permutation Sequence — k-th permutation via factorial number system
// =====================================================================
static string lc60(int n, int k)
{
    vector<int> fact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i;
    vector<int> nums;
    for (int i = 1; i <= n; i++) nums.push_back(i);
    k--; // 0-indexed
    string res;
    for (int i = n; i >= 1; i--) {
        int idx = k / fact[i-1];
        k %= fact[i-1];
        res += to_string(nums[idx]);
        nums.erase(nums.begin() + idx);
    }
    return res;
}

// =====================================================================
// LC 526: Beautiful Arrangement — count perms where perm[i]%i==0 or i%perm[i]==0
// =====================================================================
static int beautifulCount = 0;
static void lc526(int n, int pos, vector<bool>& used)
{
    if (pos > n) { beautifulCount++; return; }
    for (int v = 1; v <= n; v++) {
        if (used[v]) continue;
        if (v % pos == 0 || pos % v == 0) {
            used[v] = true;
            lc526(n, pos + 1, used);
            used[v] = false;
        }
    }
}

void muhtasim()
{
    // ---------------- Instructor Problem A (primary job) ----------------
    ll n;
    cin >> n;
    vector<int> cur;
    vector<bool> used(n + 1, false);
    vector<string> results;
    solvePermA((int)n, cur, used, results);
    for (auto& line : results) cout << line << "\n";

    // ---------------- Bundled LeetCode demo sections (run once) ----------------
    static bool demosShown = false;
    if (!demosShown) {
        demosShown = true;

        cout << "\n===== LC 46: Permutations (demo nums = {1,2,3}) =====\n";
        {
            vector<int> nums = {1, 2, 3};
            vector<int> tmp; vector<bool> usedFlag(nums.size(), false);
            vector<vector<int>> res;
            lc46(nums, tmp, usedFlag, res);
            for (auto& p : res) {
                for (size_t i = 0; i < p.size(); i++) cout << p[i] << (i + 1 < p.size() ? ' ' : '\n');
            }
        }

        cout << "\n===== LC 47: Permutations II (demo nums = {1,1,2}) =====\n";
        {
            vector<int> nums = {1, 1, 2};
            sort(nums.begin(), nums.end());
            vector<int> tmp; vector<bool> usedFlag(nums.size(), false);
            vector<vector<int>> res;
            lc47(nums, tmp, usedFlag, res);
            for (auto& p : res) {
                for (size_t i = 0; i < p.size(); i++) cout << p[i] << (i + 1 < p.size() ? ' ' : '\n');
            }
        }

        cout << "\n===== LC 31: Next Permutation (demo nums = {1,2,3}) =====\n";
        {
            vector<int> nums = {1, 2, 3};
            cout << "before: ";
            for (int x : nums) cout << x << ' ';
            cout << "\n";
            next_permutation(nums.begin(), nums.end());
            cout << "after:  ";
            for (int x : nums) cout << x << ' ';
            cout << "\n";
        }

        cout << "\n===== LC 60: Permutation Sequence (demo n=4, k=9) =====\n";
        cout << lc60(4, 9) << "\n"; // expected "2314"

        cout << "\n===== LC 526: Beautiful Arrangement (demo n=2 and n=4) =====\n";
        {
            beautifulCount = 0;
            vector<bool> u2(3, false);
            lc526(2, 1, u2);
            cout << "n=2 -> " << beautifulCount << "\n"; // expected 2

            beautifulCount = 0;
            vector<bool> u4(5, false);
            lc526(4, 1, u4);
            cout << "n=4 -> " << beautifulCount << "\n"; // expected 8
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
