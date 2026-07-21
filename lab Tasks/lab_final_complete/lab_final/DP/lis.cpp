#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== LC 300. LIS: O(n^2) =====================
int lisON2(vector<ll>& a, vector<int>& parent, int& bestEnd)
{
    int n=a.size();
    vector<int> dp(n,1);
    parent.assign(n,-1);
    int best=0; bestEnd=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(a[j]<a[i] && dp[j]+1>dp[i])
            {
                dp[i]=dp[j]+1;
                parent[i]=j;
            }
        }
        if(dp[i]>best){ best=dp[i]; bestEnd=i; }
    }
    return best;
}

vector<ll> reconstructLIS(vector<ll>& a, vector<int>& parent, int bestEnd)
{
    vector<ll> seq;
    for(int cur=bestEnd; cur!=-1; cur=parent[cur]) seq.push_back(a[cur]);
    reverse(seq.begin(), seq.end());
    return seq;
}

// ===================== LC 300. LIS: O(n log n) patience sorting =====================
int lisNLogN(vector<ll>& a)
{
    vector<ll> tails;
    for(ll x: a)
    {
        auto it=lower_bound(tails.begin(), tails.end(), x);
        if(it==tails.end()) tails.push_back(x);
        else *it=x;
    }
    return tails.size();
}

// ===================== LC 673. Number of Longest Increasing Subsequences =====================
int numberOfLIS(vector<ll>& a)
{
    int n=a.size();
    vector<int> len(n,1), cnt(n,1);
    int best=1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(a[j]<a[i])
            {
                if(len[j]+1>len[i]){ len[i]=len[j]+1; cnt[i]=cnt[j]; }
                else if(len[j]+1==len[i]) cnt[i]+=cnt[j];
            }
        }
        best=max(best,len[i]);
    }
    int total=0;
    for(int i=0;i<n;i++) if(len[i]==best) total+=cnt[i];
    return total;
}

// ===================== LC 354. Russian Doll Envelopes =====================
int russianDollEnvelopes(vector<pair<ll,ll>> env)
{
    sort(env.begin(), env.end(), [](const pair<ll,ll>& x, const pair<ll,ll>& y){
        if(x.first!=y.first) return x.first<y.first;
        return x.second>y.second; // descending on height for equal width
    });
    vector<ll> tails;
    for(auto& e: env)
    {
        ll h=e.second;
        auto it=lower_bound(tails.begin(), tails.end(), h);
        if(it==tails.end()) tails.push_back(h);
        else *it=h;
    }
    return tails.size();
}

// ===================== LC 1671. Min Removals to Make Mountain Array =====================
int minimumMountainRemovals(vector<ll>& a)
{
    int n=a.size();
    vector<int> lisLeft(n,1), lisRight(n,1);
    for(int i=0;i<n;i++)
        for(int j=0;j<i;j++)
            if(a[j]<a[i]) lisLeft[i]=max(lisLeft[i], lisLeft[j]+1);
    for(int i=n-1;i>=0;i--)
        for(int j=n-1;j>i;j--)
            if(a[j]<a[i]) lisRight[i]=max(lisRight[i], lisRight[j]+1);
    int best=0;
    for(int i=0;i<n;i++)
        if(lisLeft[i]>1 && lisRight[i]>1)
            best=max(best, lisLeft[i]+lisRight[i]-1);
    return n-best;
}

void muhtasim()
{
    int n;
    cin>>n;
    vector<ll> a(n);
    for(auto &x: a) cin>>x;

    cout<<"===== LC 300. LIS (O(n^2), with reconstruction) =====\n";
    vector<int> parent; int bestEnd;
    int len1=lisON2(a, parent, bestEnd);
    cout<<"LIS length = "<<len1<<"\n";
    vector<ll> seq=reconstructLIS(a, parent, bestEnd);
    cout<<"One valid LIS: ";
    for(ll x: seq) cout<<x<<" ";
    cout<<"\n";

    cout<<"===== LC 300. LIS (O(n log n) patience sorting) =====\n";
    cout<<"LIS length = "<<lisNLogN(a)<<"\n";

    cout<<"===== LC 673. Number of Longest Increasing Subsequences (bundled) =====\n";
    cout<<"Count of LIS = "<<numberOfLIS(a)<<"\n";

    cout<<"===== LC 354. Russian Doll Envelopes (bundled, hardcoded demo) =====\n";
    vector<pair<ll,ll>> envelopes = {{5,4},{6,4},{6,7},{2,3}};
    cout<<"Max envelopes nested = "<<russianDollEnvelopes(envelopes)<<"\n";

    cout<<"===== LC 1671. Min Removals to Make Mountain Array (bundled) =====\n";
    vector<ll> mountainDemo = {2,1,1,5,6,2,3,1};
    cout<<"Min removals = "<<minimumMountainRemovals(mountainDemo)<<"\n";
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
