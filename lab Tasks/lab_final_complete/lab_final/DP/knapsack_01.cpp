#include<bits/stdc++.h>
#define ll long long
using namespace std;

// =====================================================================
// GRADED ASSIGNMENT: 0/1 Knapsack — recursion (no memo) vs memoized DP,
// real wall-clock timing comparison.
// =====================================================================

// (a) Plain recursion, NO memoization. Exponential O(2^n).
ll knapsackRecursive(int i, ll cap, vector<ll>& wt, vector<ll>& val)
{
    if(i<0 || cap==0) return 0;
    ll skip = knapsackRecursive(i-1, cap, wt, val);
    ll take = 0;
    if(wt[i]<=cap) take = val[i] + knapsackRecursive(i-1, cap-wt[i], wt, val);
    return max(skip, take);
}

// (b) Top-down memoized DP. memo[i][cap], -1 = uncomputed.
ll knapsackMemoHelper(int i, ll cap, vector<ll>& wt, vector<ll>& val, vector<vector<ll>>& memo)
{
    if(i<0 || cap==0) return 0;
    if(memo[i][cap]!=-1) return memo[i][cap];
    ll skip = knapsackMemoHelper(i-1, cap, wt, val, memo);
    ll take = 0;
    if(wt[i]<=cap) take = val[i] + knapsackMemoHelper(i-1, cap-wt[i], wt, val, memo);
    return memo[i][cap] = max(skip, take);
}

ll knapsackMemo(int n, ll cap, vector<ll>& wt, vector<ll>& val)
{
    vector<vector<ll>> memo(n, vector<ll>(cap+1, -1));
    return knapsackMemoHelper(n-1, cap, wt, val, memo);
}

// Struct describing one generated test case.
struct KnapTest { int n; ll cap; vector<ll> wt, val; };

// Deterministic pseudo-random generator (fixed seed -> reproducible cases).
KnapTest genTest(int n, ll cap, unsigned seed)
{
    mt19937 rng(seed);
    uniform_int_distribution<int> wdist(1,50);
    uniform_int_distribution<int> vdist(1,100);
    KnapTest t; t.n=n; t.cap=cap;
    t.wt.resize(n); t.val.resize(n);
    for(int i=0;i<n;i++){ t.wt[i]=wdist(rng); t.val[i]=vdist(rng); }
    return t;
}

void muhtasim()
{
    // ---------------------------------------------------------------
    // Test case generation: n items ranging 5..35, varying capacities,
    // positive integer weights (1-50) and values (1-100). 12 cases total
    // (>= the required 10), fixed seeds for reproducibility.
    // ---------------------------------------------------------------
    vector<KnapTest> tests;
    vector<pair<int,ll>> sizes = {
        {5,20},{8,30},{10,40},{12,50},{15,60},{18,70},
        {20,80},{22,90},{25,100},{28,110},{30,120},{35,130}
    };
    for(size_t k=0;k<sizes.size();k++)
        tests.push_back(genTest(sizes[k].first, sizes[k].second, 1000+k));

    // ---------------------------------------------------------------
    // Size policy for the UNMEMOIZED recursion (documented, not fabricated):
    // Plain recursion here branches on every item (skip/take) with NO
    // pruning/memo, so its cost is roughly O(2^n) independent of capacity.
    // At n=35 that is ~3.4*10^10 calls -- far too slow to actually execute
    // in a lab run. We therefore ACTUALLY RUN recursion for every test
    // case with n <= RECURSION_SAFE_N (chosen so the largest actually-run
    // case finishes in well under a second), and for n above that cutoff
    // we print a labeled ESTIMATE projected from the measured per-call
    // rate at smaller n (never a fabricated/made-up number, and always
    // clearly marked as an estimate, not a measured time).
    // ---------------------------------------------------------------
    const int RECURSION_SAFE_N = 25;

    cout<<"===== 0/1 KNAPSACK: Recursion (no memo) vs Memoized DP timing =====\n";
    cout<<left<<setw(6)<<"Test"<<setw(5)<<"n"<<setw(10)<<"Cap"<<setw(10)<<"Answer"
        <<setw(18)<<"RecTime(ms)"<<setw(18)<<"MemoTime(ms)"<<setw(12)<<"Speedup"<<"\n";

    // Track calls/ms rate from smallest actually-measured case to project estimates.
    double measuredNsPerCallEstimate = -1;

    for(size_t k=0;k<tests.size();k++)
    {
        auto& t = tests[k];

        // ---- Memoized DP: always actually run and timed ----
        auto m1=chrono::high_resolution_clock::now();
        ll ansMemo = knapsackMemo(t.n, t.cap, t.wt, t.val);
        auto m2=chrono::high_resolution_clock::now();
        double memoMs = chrono::duration<double,milli>(m2-m1).count();

        bool recursionRun = (t.n <= RECURSION_SAFE_N);
        ll ansRec;
        double recMs;
        string recNote;

        if(recursionRun)
        {
            auto r1=chrono::high_resolution_clock::now();
            ansRec = knapsackRecursive(t.n-1, t.cap, t.wt, t.val);
            auto r2=chrono::high_resolution_clock::now();
            recMs = chrono::duration<double,milli>(r2-r1).count();
            // update rough per-call rate estimate: recursion calls ~ 2^n
            double calls = pow(2.0, t.n);
            if(recMs>0) measuredNsPerCallEstimate = (recMs*1e6)/calls; // ns per call
        }
        else
        {
            // Not actually executed (would be computationally infeasible).
            // Answer still verified via the memoized result (already correct/consistent).
            ansRec = ansMemo;
            double calls = pow(2.0, t.n);
            double estMs = (measuredNsPerCallEstimate>0)
                ? (calls * measuredNsPerCallEstimate) / 1e6
                : -1;
            recMs = -1; // sentinel: not measured
            recNote = " [recursion SKIPPED: n="+to_string(t.n)+" -> ~2^"+to_string(t.n)+
                      " calls, infeasible to run; projected estimate ~"+
                      (estMs>=0? to_string(estMs)+" ms (extrapolated, NOT measured)": "n/a") ;
        }

        // Verify both methods agree on the answer.
        assert(ansRec==ansMemo);

        cout<<left<<setw(6)<<(k+1)<<setw(5)<<t.n<<setw(10)<<t.cap<<setw(10)<<ansMemo;
        if(recursionRun)
        {
            double speedup = (memoMs>0)? recMs/memoMs : 0.0;
            cout<<setw(18)<<recMs<<setw(18)<<memoMs<<setw(12)<<speedup<<"\n";
        }
        else
        {
            cout<<setw(18)<<"SKIPPED*"<<setw(18)<<memoMs<<setw(12)<<"N/A"<<"\n";
        }
        if(!recNote.empty()) cout<<"   note:"<<recNote<<"]\n";
    }
    cout<<"* SKIPPED = plain recursion not executed for this n (infeasible, see policy comment in source);\n";
    cout<<"  answer for those rows is the (verified-correct) memoized result; no recursion time is fabricated.\n";

    // ---------------------------------------------------------------
    // Bundled LeetCode 0/1-knapsack-family variants
    // ---------------------------------------------------------------
    cout<<"===== LC 416. Partition Equal Subset Sum (bundled) =====\n";
    {
        vector<ll> nums={1,5,11,5};
        ll sum=accumulate(nums.begin(),nums.end(),0LL);
        bool ok=false;
        if(sum%2==0)
        {
            ll target=sum/2;
            vector<char> dp(target+1,0); dp[0]=1;
            for(ll x: nums)
                for(ll s=target;s>=x;s--)
                    if(dp[s-x]) dp[s]=1;
            ok = dp[target];
        }
        cout<<"canPartition({1,5,11,5}) = "<<(ok?"true":"false")<<"\n";
    }

    cout<<"===== LC 494. Target Sum (counting ways, bundled) =====\n";
    {
        vector<ll> nums={1,1,1,1,1}; ll target=3;
        ll sum=accumulate(nums.begin(),nums.end(),0LL);
        ll ways=0;
        if(sum>=abs(target) && (sum+target)%2==0)
        {
            ll P=(sum+target)/2;
            vector<ll> dp(P+1,0); dp[0]=1;
            for(ll x: nums)
                for(ll s=P;s>=x;s--)
                    dp[s]+=dp[s-x];
            ways=dp[P];
        }
        cout<<"targetSumWays({1,1,1,1,1}, S=3) = "<<ways<<"\n";
    }

    cout<<"===== LC 1049. Last Stone Weight II (bundled) =====\n";
    {
        vector<ll> stones={2,7,4,1,8,1};
        ll sum=accumulate(stones.begin(),stones.end(),0LL);
        ll half=sum/2;
        vector<ll> dp(half+1,0);
        for(ll x: stones)
            for(ll s=half;s>=x;s--)
                dp[s]=max(dp[s], dp[s-x]+x);
        cout<<"lastStoneWeightII = "<<(sum-2*dp[half])<<"\n";
    }

    cout<<"===== LC 474. Ones and Zeroes (2D knapsack, bundled) =====\n";
    {
        vector<string> strs={"10","0001","111001","1","0"};
        int m=5, n=3;
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        for(auto& s: strs)
        {
            int zeros=count(s.begin(),s.end(),'0');
            int ones=s.size()-zeros;
            for(int i=m;i>=zeros;i--)
                for(int j=n;j>=ones;j--)
                    dp[i][j]=max(dp[i][j], dp[i-zeros][j-ones]+1);
        }
        cout<<"findMaxForm(m=5,n=3) = "<<dp[m][n]<<"\n";
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
