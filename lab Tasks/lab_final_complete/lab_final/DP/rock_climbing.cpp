#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== LC 746. Min Cost Climbing Stairs =====================
ll minCostClimbingStairs(vector<ll>& cost)
{
    int n=cost.size();
    vector<ll> dp(n+1,0);
    for(int i=2;i<=n;i++)
        dp[i]=min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]);
    return dp[n];
}

// ===================== LC 70. Climbing Stairs (counting ways) =====================
ll climbingStairsWays(int n)
{
    if(n<=2) return n;
    vector<ll> dp(n+1);
    dp[1]=1; dp[2]=2;
    for(int i=3;i<=n;i++) dp[i]=dp[i-1]+dp[i-2];
    return dp[n];
}

// ===================== LC 55. Jump Game (reachability) =====================
bool canJump(vector<ll>& nums)
{
    int n=nums.size();
    ll reach=0;
    for(int i=0;i<n;i++)
    {
        if(i>reach) return false;
        reach=max(reach, (ll)i+nums[i]);
    }
    return true;
}

// ===================== LC 45. Jump Game II (min jumps) =====================
int jumpGameII(vector<ll>& nums)
{
    int n=nums.size();
    int jumps=0, curEnd=0, farthest=0;
    for(int i=0;i<n-1;i++)
    {
        farthest=max(farthest, (int)(i+nums[i]));
        if(i==curEnd)
        {
            jumps++;
            curEnd=farthest;
        }
    }
    return jumps;
}

// ===================== LC 403. Frog Jump =====================
bool canCrossFrogJump(vector<ll>& stones)
{
    int n=stones.size();
    unordered_map<ll,int> idx;
    for(int i=0;i<n;i++) idx[stones[i]]=i;
    // dp[i] = set of jump sizes k that can land on stone i
    vector<set<ll>> dp(n);
    dp[0].insert(0);
    for(int i=0;i<n;i++)
    {
        for(ll k: dp[i])
        {
            for(ll step : {k-1,k,k+1})
            {
                if(step<=0) continue;
                ll nextPos = stones[i]+step;
                auto it=idx.find(nextPos);
                if(it!=idx.end()) dp[it->second].insert(step);
            }
        }
    }
    return !dp[n-1].empty();
}

// ===================== Generalized k-step climbing stairs =====================
ll climbStairsKSteps(int n, int k)
{
    vector<ll> dp(n+1,0);
    dp[0]=1;
    for(int i=1;i<=n;i++)
        for(int s=1;s<=k && s<=i;s++)
            dp[i]+=dp[i-s];
    return dp[n];
}

void muhtasim()
{
    int n;
    cin>>n;
    vector<ll> cost(n);
    for(auto &x: cost) cin>>x;

    cout<<"===== LC 746. Min Cost Climbing Stairs =====\n";
    cout<<"Min cost = "<<minCostClimbingStairs(cost)<<"\n";

    cout<<"===== LC 70. Climbing Stairs (counting ways, bundled) =====\n";
    for(int test : {2,3,5})
        cout<<"climbingStairsWays("<<test<<") = "<<climbingStairsWays(test)<<"\n";

    cout<<"===== LC 55. Jump Game (bundled) =====\n";
    {
        vector<ll> a={2,3,1,1,4};
        vector<ll> b={3,2,1,0,4};
        cout<<"canJump({2,3,1,1,4}) = "<<(canJump(a)?"true":"false")<<"\n";
        cout<<"canJump({3,2,1,0,4}) = "<<(canJump(b)?"true":"false")<<"\n";
    }

    cout<<"===== LC 45. Jump Game II (min jumps, bundled) =====\n";
    {
        vector<ll> a={2,3,1,1,4};
        cout<<"jumpGameII({2,3,1,1,4}) = "<<jumpGameII(a)<<"\n";
    }

    cout<<"===== LC 403. Frog Jump (bundled) =====\n";
    {
        vector<ll> stones1={0,1,3,5,6,8,12,17};
        vector<ll> stones2={0,1,2,3,4,8,9,11};
        cout<<"canCross({0,1,3,5,6,8,12,17}) = "<<(canCrossFrogJump(stones1)?"true":"false")<<"\n";
        cout<<"canCross({0,1,2,3,4,8,9,11}) = "<<(canCrossFrogJump(stones2)?"true":"false")<<"\n";
    }

    cout<<"===== Generalized k-step climbing stairs (bundled) =====\n";
    for(int k : {1,2,3})
        cout<<"climbStairsKSteps(n=6, k="<<k<<") = "<<climbStairsKSteps(6,k)<<"\n";
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
