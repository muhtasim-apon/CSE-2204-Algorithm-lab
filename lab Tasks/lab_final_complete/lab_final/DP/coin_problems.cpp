#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== LC 322. Coin Change (min coins) =====================
ll coinChangeMin(vector<ll>& coins, ll amount)
{
    vector<ll> dp(amount+1, LLONG_MAX/2);
    dp[0]=0;
    for(ll i=1;i<=amount;i++)
        for(ll c: coins)
            if(c<=i) dp[i]=min(dp[i], dp[i-c]+1);
    return dp[amount]>=LLONG_MAX/2 ? -1 : dp[amount];
}

// ===================== LC 518. Coin Change II (combinations) =====================
// Order does NOT matter: iterate coins outer, amount inner.
ll coinChangeCombinations(vector<ll>& coins, ll amount)
{
    vector<ll> dp(amount+1,0);
    dp[0]=1;
    for(ll c: coins)
        for(ll i=c;i<=amount;i++)
            dp[i]+=dp[i-c];
    return dp[amount];
}

// ===================== LC 377. Combination Sum IV (permutations, order matters) =====================
// Order DOES matter: iterate amount outer, coins inner.
ll combinationSumIVPermutations(vector<ll>& coins, ll amount)
{
    vector<ll> dp(amount+1,0);
    dp[0]=1;
    for(ll i=1;i<=amount;i++)
        for(ll c: coins)
            if(c<=i) dp[i]+=dp[i-c];
    return dp[amount];
}

// ===================== LC 279. Perfect Squares =====================
ll perfectSquares(ll n)
{
    vector<ll> dp(n+1, LLONG_MAX/2);
    dp[0]=0;
    for(ll i=1;i<=n;i++)
        for(ll j=1;j*j<=i;j++)
            dp[i]=min(dp[i], dp[i-j*j]+1);
    return dp[n];
}

void muhtasim()
{
    ll amount, n;
    cin>>amount>>n;
    vector<ll> coins(n);
    for(auto &c: coins) cin>>c;

    cout<<"===== LC 322. Coin Change (min coins) =====\n";
    cout<<"Min coins for amount="<<amount<<" : "<<coinChangeMin(coins,amount)<<"\n";

    cout<<"===== LC 518. Coin Change II (combinations, order-independent) =====\n";
    ll combos = coinChangeCombinations(coins, amount);
    cout<<"Number of combinations = "<<combos<<"\n";

    cout<<"===== LC 377. Combination Sum IV (permutations, order matters) =====\n";
    ll perms = combinationSumIVPermutations(coins, amount);
    cout<<"Number of ordered sequences = "<<perms<<"\n";

    cout<<"===== Combinations vs Permutations contrast =====\n";
    cout<<"Same coin set/amount -> combinations(order irrelevant)="<<combos
        <<" vs permutations(order relevant)="<<perms
        <<"  (permutations count >= combinations count, since each combination can appear in multiple orders)\n";

    cout<<"===== LC 279. Perfect Squares (bundled variant) =====\n";
    for(ll test : {12LL,13LL,1LL})
        cout<<"perfectSquares("<<test<<") = "<<perfectSquares(test)<<"\n";
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
