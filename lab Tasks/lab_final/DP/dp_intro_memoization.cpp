#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== Fibonacci: naive vs memo vs tabulation =====================
ll fibNaive(int n)
{
    if(n<=1) return n;
    return fibNaive(n-1)+fibNaive(n-2);
}

ll fibMemoHelper(int n, vector<ll>& memo)
{
    if(n<=1) return n;
    if(memo[n]!=-1) return memo[n];
    return memo[n]=fibMemoHelper(n-1,memo)+fibMemoHelper(n-2,memo);
}

ll fibMemo(int n)
{
    vector<ll> memo(n+1,-1);
    return fibMemoHelper(n,memo);
}

ll fibTabulation(int n)
{
    if(n<=1) return n;
    vector<ll> dp(n+1);
    dp[0]=0; dp[1]=1;
    for(int i=2;i<=n;i++) dp[i]=dp[i-1]+dp[i-2];
    return dp[n];
}

// ===================== LC 70. Climbing Stairs (counting ways) =====================
ll climbingStairs(int n)
{
    if(n<=2) return n;
    vector<ll> dp(n+1);
    dp[1]=1; dp[2]=2;
    for(int i=3;i<=n;i++) dp[i]=dp[i-1]+dp[i-2];
    return dp[n];
}

// ===================== LC 62. Unique Paths (counting-ways intro) =====================
ll uniquePaths(int m, int n)
{
    vector<vector<ll>> dp(m, vector<ll>(n,1));
    for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
    return dp[m-1][n-1];
}

void muhtasim()
{
    int n;
    cin>>n;

    cout<<"===== Fibonacci: naive vs memo vs tabulation =====\n";
    // Keep naive recursion demo bounded so it actually finishes quickly;
    // naive fib is O(2^n) so we only run it for the given n if small enough,
    // otherwise cap the naive demo at 30 to avoid a multi-minute stall.
    int naiveN = min(n,30);
    auto t1=chrono::high_resolution_clock::now();
    ll naiveVal=fibNaive(naiveN);
    auto t2=chrono::high_resolution_clock::now();
    ll memoVal=fibMemo(n);
    auto t3=chrono::high_resolution_clock::now();
    ll tabVal=fibTabulation(n);
    auto t4=chrono::high_resolution_clock::now();

    double naiveMs=chrono::duration<double,milli>(t2-t1).count();
    double memoMs=chrono::duration<double,milli>(t3-t2).count();
    double tabMs=chrono::duration<double,milli>(t4-t3).count();

    cout<<"fib("<<naiveN<<") naive recursion = "<<naiveVal<<"  time="<<naiveMs<<" ms"<<(naiveN<n?" (naive capped at n=30, exponential blowup beyond this)":"")<<"\n";
    cout<<"fib("<<n<<") memoized           = "<<memoVal<<"  time="<<memoMs<<" ms\n";
    cout<<"fib("<<n<<") tabulated          = "<<tabVal<<"  time="<<tabMs<<" ms\n";

    cout<<"===== LC 70. Climbing Stairs (bundled variant) =====\n";
    for(int test : {2,3,5})
        cout<<"climbingStairs("<<test<<") = "<<climbingStairs(test)<<"\n";

    cout<<"===== LC 62. Unique Paths (bundled variant) =====\n";
    cout<<"uniquePaths(3,7) = "<<uniquePaths(3,7)<<"\n";
    cout<<"uniquePaths(3,2) = "<<uniquePaths(3,2)<<"\n";
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
