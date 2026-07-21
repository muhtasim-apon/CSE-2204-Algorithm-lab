#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== Rod Cutting helpers =====================
// Top-down memoized rod cutting: max revenue cutting rod of length n
// given price[1..n].
ll rcMemoHelper(vector<ll>& price, int n, vector<ll>& memo)
{
    if(n==0) return 0;
    if(memo[n]!=-1) return memo[n];
    ll best=LLONG_MIN;
    for(int i=1;i<=n;i++)
        best=max(best, price[i]+rcMemoHelper(price,n-i,memo));
    return memo[n]=best;
}

ll rodCuttingMemo(vector<ll>& price, int n)
{
    vector<ll> memo(n+1,-1);
    return rcMemoHelper(price,n,memo);
}

// Bottom-up tabulation, also reconstructs the actual cuts used.
ll rodCuttingBottomUp(vector<ll>& price, int n, vector<int>& firstCut)
{
    vector<ll> dp(n+1,0);
    firstCut.assign(n+1,0);
    for(int len=1; len<=n; len++)
    {
        ll best=LLONG_MIN; int bestCut=len;
        for(int i=1;i<=len;i++)
        {
            if(price[i]+dp[len-i] > best)
            {
                best=price[i]+dp[len-i];
                bestCut=i;
            }
        }
        dp[len]=best;
        firstCut[len]=bestCut;
    }
    return dp[n];
}

void printCuts(vector<int>& firstCut, int n)
{
    cout<<"Cuts used: ";
    int len=n;
    while(len>0)
    {
        cout<<firstCut[len]<<" ";
        len-=firstCut[len];
    }
    cout<<"\n";
}

// ===================== LC 343. Integer Break =====================
// Break integer n into >=2 positive parts to maximize product.
ll integerBreak(int n)
{
    vector<ll> dp(n+1,0);
    dp[1]=0;
    for(int i=2;i<=n;i++)
    {
        ll best=0;
        for(int j=1;j<i;j++)
            best=max({best,(ll)j*(i-j), (ll)j*dp[i-j]});
        dp[i]=best;
    }
    return dp[n];
}

void muhtasim()
{
    int n;
    cin>>n;
    vector<ll> price(n+1);
    for(int i=1;i<=n;i++) cin>>price[i];

    cout<<"===== ROD CUTTING (top-down memo) =====\n";
    cout<<"Max revenue (memo): "<<rodCuttingMemo(price,n)<<"\n";

    cout<<"===== ROD CUTTING (bottom-up + reconstruct cuts) =====\n";
    vector<int> firstCut;
    cout<<"Max revenue (bottom-up): "<<rodCuttingBottomUp(price,n,firstCut)<<"\n";
    printCuts(firstCut,n);

    cout<<"===== LC 343. Integer Break (bundled variant) =====\n";
    for(int test : {2,8,10})
        cout<<"integerBreak("<<test<<") = "<<integerBreak(test)<<"\n";
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
