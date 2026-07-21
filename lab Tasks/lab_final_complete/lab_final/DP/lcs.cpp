#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== LC 1143. Longest Common Subsequence =====================
vector<vector<int>> buildLCSTable(const string& a, const string& b)
{
    int n=a.size(), m=b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1,0));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dp[i][j] = (a[i-1]==b[j-1]) ? dp[i-1][j-1]+1 : max(dp[i-1][j], dp[i][j-1]);
    return dp;
}

string reconstructLCS(const string& a, const string& b, vector<vector<int>>& dp)
{
    int i=a.size(), j=b.size();
    string res;
    while(i>0 && j>0)
    {
        if(a[i-1]==b[j-1]){ res+=a[i-1]; i--; j--; }
        else if(dp[i-1][j] >= dp[i][j-1]) i--;
        else j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

// ===================== LC 1092. Shortest Common Supersequence =====================
string shortestCommonSupersequence(const string& a, const string& b, vector<vector<int>>& dp)
{
    int i=a.size(), j=b.size();
    string res;
    while(i>0 && j>0)
    {
        if(a[i-1]==b[j-1]){ res+=a[i-1]; i--; j--; }
        else if(dp[i-1][j] >= dp[i][j-1]) { res+=a[i-1]; i--; }
        else { res+=b[j-1]; j--; }
    }
    while(i>0){ res+=a[i-1]; i--; }
    while(j>0){ res+=b[j-1]; j--; }
    reverse(res.begin(), res.end());
    return res;
}

// ===================== LC 72. Edit Distance =====================
int editDistance(const string& a, const string& b)
{
    int n=a.size(), m=b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1,0));
    for(int i=0;i<=n;i++) dp[i][0]=i;
    for(int j=0;j<=m;j++) dp[0][j]=j;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(a[i-1]==b[j-1]) dp[i][j]=dp[i-1][j-1];
            else dp[i][j]=1+min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
        }
    return dp[n][m];
}

// ===================== LC 115. Distinct Subsequences (counting ways) =====================
ll numDistinctSubsequences(const string& s, const string& t)
{
    int n=s.size(), m=t.size();
    vector<vector<ll>> dp(n+1, vector<ll>(m+1,0));
    for(int i=0;i<=n;i++) dp[i][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            dp[i][j]=dp[i-1][j];
            if(s[i-1]==t[j-1]) dp[i][j]+=dp[i-1][j-1];
        }
    return dp[n][m];
}

// ===================== LC 583. Delete Operation for Two Strings =====================
int minDeleteOperations(const string& a, const string& b, vector<vector<int>>& dp)
{
    int n=a.size(), m=b.size();
    int lcsLen=dp[n][m];
    return (n-lcsLen)+(m-lcsLen);
}

// ===================== LCS of 3 strings extension =====================
int lcsOfThree(const string& a, const string& b, const string& c)
{
    int n=a.size(), m=b.size(), p=c.size();
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(m+1, vector<int>(p+1,0)));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=1;k<=p;k++)
            {
                if(a[i-1]==b[j-1] && b[j-1]==c[k-1]) dp[i][j][k]=dp[i-1][j-1][k-1]+1;
                else dp[i][j][k]=max({dp[i-1][j][k], dp[i][j-1][k], dp[i][j][k-1]});
            }
    return dp[n][m][p];
}

void muhtasim()
{
    string a,b;
    cin>>a>>b;

    auto dp = buildLCSTable(a,b);
    cout<<"===== LC 1143. Longest Common Subsequence =====\n";
    cout<<"LCS length = "<<dp[a.size()][b.size()]<<"\n";
    cout<<"LCS string = "<<reconstructLCS(a,b,dp)<<"\n";

    cout<<"===== LC 1092. Shortest Common Supersequence (bundled) =====\n";
    string scs = shortestCommonSupersequence(a,b,dp);
    cout<<"SCS length = "<<scs.size()<<"  SCS = "<<scs<<"\n";

    cout<<"===== LC 72. Edit Distance (bundled) =====\n";
    cout<<"Edit distance = "<<editDistance(a,b)<<"\n";

    cout<<"===== LC 115. Distinct Subsequences (bundled, counting ways) =====\n";
    cout<<"numDistinct("<<a<<","<<b<<") = "<<numDistinctSubsequences(a,b)<<"\n";

    cout<<"===== LC 583. Delete Operation for Two Strings (bundled) =====\n";
    cout<<"Min deletions to make equal = "<<minDeleteOperations(a,b,dp)<<"\n";

    cout<<"===== LCS of 3 strings extension (bundled, hardcoded demo) =====\n";
    cout<<"lcsOfThree(\"abcbdab\",\"bdcaba\",\"cbadbab\") = "<<lcsOfThree("abcbdab","bdcaba","cbadbab")<<"\n";
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
