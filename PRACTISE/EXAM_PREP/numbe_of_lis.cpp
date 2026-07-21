#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;

    vector<int>nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>nums[i];
    }

    vector<int>dp(n,1);
    vector<int>cnt(n,1);

    int maxima=1;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(nums[j]<nums[i] && dp[j]+1>dp[i])
            {
                dp[i]=dp[j]+1;
                cnt[i]=cnt[j];
            }
            else if(nums[j]<nums[i] && dp[j]+1==dp[i])
            {
                cnt[i]+=cnt[j];
            }
        }

        maxima=max(maxima,dp[i]);
    }

    int ans=0;

    for(int i=0;i<n;i++)
    {
        if(dp[i]==maxima)
        {
            ans+=cnt[i];
        }
    }

    cout<<ans;

    return 0;
}