#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin>>n;

    if(n==0)
    {
        cout<<0;
        return 0;
    }

    vector<int>nums(n);
    for(int i=0;i<n;i++)
    {
        cin>>nums[i];
    }

    vector<int>ans;
    ans.push_back(nums[0]);

    for(int i=1;i<n;i++)
    {
        if(nums[i]>ans.back())
        {
            ans.push_back(nums[i]);
        }
        else
        {
            int idx=lower_bound(ans.begin(),ans.end(),nums[i])-ans.begin();
            ans[idx]=nums[i];
        }
    }

    cout<<ans.size();

    return 0;
}