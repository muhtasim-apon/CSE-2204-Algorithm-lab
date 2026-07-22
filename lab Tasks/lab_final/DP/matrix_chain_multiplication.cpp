p#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== Matrix Chain Multiplication (interval DP) =====================
ll matrixChainOrder(vector<ll>& p, vector<vector<int>>& split)
{
    int n=p.size()-1; // number of matrices
    vector<vector<ll>> dp(n+1, vector<ll>(n+1,0));
    split.assign(n+1, vector<int>(n+1,0));
    for(int len=2; len<=n; len++)
    {
        for(int i=1; i<=n-len+1; i++)
        {
            int j=i+len-1;
            dp[i][j]=LLONG_MAX;
            for(int k=i;k<j;k++)
            {
                ll cost = dp[i][k]+dp[k+1][j]+p[i-1]*p[k]*p[j];
                if(cost<dp[i][j]){ dp[i][j]=cost; split[i][j]=k; }
            }
        }
    }
    return dp[1][n];
}

string printOptimalParens(vector<vector<int>>& split, int i, int j)
{
    if(i==j) return "A"+to_string(i);
    int k=split[i][j];
    return "(" + printOptimalParens(split,i,k) + printOptimalParens(split,k+1,j) + ")";
}

// ===================== LC 312. Burst Balloons =====================
ll maxCoinsBurstBalloons(vector<ll> nums)
{
    vector<ll> a; a.push_back(1);
    for(ll x: nums) a.push_back(x);
    a.push_back(1);
    int n=a.size();
    vector<vector<ll>> dp(n, vector<ll>(n,0));
    for(int len=2; len<n; len++)
    {
        for(int i=0;i+len<n;i++)
        {
            int j=i+len;
            for(int k=i+1;k<j;k++)
                dp[i][j]=max(dp[i][j], dp[i][k]+dp[k][j]+a[i]*a[k]*a[j]);
        }
    }
    return dp[0][n-1];
}

// ===================== LC 1000. Minimum Cost to Merge Stones =====================
ll mergeStones(vector<ll>& stones, int K)
{
    int n=stones.size();
    if((n-1)%(K-1)!=0) return -1;
    vector<ll> prefix(n+1,0);
    for(int i=0;i<n;i++) prefix[i+1]=prefix[i]+stones[i];
    vector<vector<ll>> dp(n, vector<ll>(n,0));
    for(int len=K; len<=n; len++)
    {
        for(int i=0;i+len<=n;i++)
        {
            int j=i+len-1;
            dp[i][j]=LLONG_MAX;
            for(int k=i;k<j;k+=(K-1))
                dp[i][j]=min(dp[i][j], dp[i][k]+dp[k+1][j]);
            if((j-i)%(K-1)==0)
                dp[i][j]+= (prefix[j+1]-prefix[i]);
        }
    }
    return dp[0][n-1];
}

// ===================== LC 1130. Minimum Cost Tree From Leaf Values =====================
ll mctFromLeafValues(vector<ll>& arr)
{
    int n=arr.size();
    vector<vector<ll>> maxVal(n, vector<ll>(n,0));
    for(int i=0;i<n;i++)
    {
        maxVal[i][i]=arr[i];
        for(int j=i+1;j<n;j++) maxVal[i][j]=max(maxVal[i][j-1], arr[j]);
    }
    vector<vector<ll>> dp(n, vector<ll>(n,0));
    for(int len=2; len<=n; len++)
    {
        for(int i=0;i+len-1<n;i++)
        {
            int j=i+len-1;
            dp[i][j]=LLONG_MAX;
            for(int k=i;k<j;k++)
            {
                ll cost = dp[i][k]+dp[k+1][j]+maxVal[i][k]*maxVal[k+1][j];
                dp[i][j]=min(dp[i][j], cost);
            }
        }
    }
    return dp[0][n-1];
}

// ===================== LC 96. Unique BST count (interval-DP counting analogue) =====================
ll numTreesUniqueBST(int n)
{
    vector<ll> dp(n+1,0);
    dp[0]=1; dp[1]=1;
    for(int i=2;i<=n;i++)
        for(int j=0;j<i;j++)
            dp[i]+=dp[j]*dp[i-1-j];
    return dp[n];
}

void muhtasim()
{
    int n;
    cin>>n; // number of matrices
    vector<ll> p(n+1);
    for(auto &x: p) cin>>x; // dimensions p[0..n]

    cout<<"===== MATRIX CHAIN MULTIPLICATION (interval DP) =====\n";
    vector<vector<int>> split;
    ll minMults = matrixChainOrder(p, split);
    cout<<"Minimum scalar multiplications = "<<minMults<<"\n";
    cout<<"Optimal parenthesization = "<<printOptimalParens(split,1,n)<<"\n";

    cout<<"===== LC 312. Burst Balloons (bundled, hardcoded demo) =====\n";
    cout<<"maxCoins({3,1,5,8}) = "<<maxCoinsBurstBalloons({3,1,5,8})<<"\n";

    cout<<"===== LC 1000. Minimum Cost to Merge Stones (bundled, hardcoded demo) =====\n";
    {
        vector<ll> stones={3,2,4,1};
        cout<<"mergeStones({3,2,4,1}, K=2) = "<<mergeStones(stones,2)<<"\n";
    }

    cout<<"===== LC 1130. Minimum Cost Tree From Leaf Values (bundled, hardcoded demo) =====\n";
    {
        vector<ll> arr={6,2,4};
        cout<<"mctFromLeafValues({6,2,4}) = "<<mctFromLeafValues(arr)<<"\n";
    }

    cout<<"===== LC 96. Unique BST count (interval-DP counting analogue, bundled) =====\n";
    for(int test : {3,5})
        cout<<"numTrees("<<test<<") = "<<numTreesUniqueBST(test)<<"\n";
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
