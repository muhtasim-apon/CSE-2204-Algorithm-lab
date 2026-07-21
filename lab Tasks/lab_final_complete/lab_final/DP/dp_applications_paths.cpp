#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===================== LC 62/63. Unique Paths / Unique Paths II (obstacles) =====================
ll uniquePathsWithObstacles(vector<vector<int>>& grid)
{
    int m=grid.size(), n=grid[0].size();
    vector<vector<ll>> dp(m, vector<ll>(n,0));
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(grid[i][j]==1){ dp[i][j]=0; continue; }
            if(i==0 && j==0){ dp[i][j]=1; continue; }
            ll fromTop = (i>0)? dp[i-1][j] : 0;
            ll fromLeft = (j>0)? dp[i][j-1] : 0;
            dp[i][j]=fromTop+fromLeft;
        }
    }
    return dp[m-1][n-1];
}

// ===================== LC 64. Minimum Path Sum =====================
ll minPathSum(vector<vector<int>>& grid)
{
    int m=grid.size(), n=grid[0].size();
    vector<vector<ll>> dp(m, vector<ll>(n,0));
    dp[0][0]=grid[0][0];
    for(int i=1;i<m;i++) dp[i][0]=dp[i-1][0]+grid[i][0];
    for(int j=1;j<n;j++) dp[0][j]=dp[0][j-1]+grid[0][j];
    for(int i=1;i<m;i++)
        for(int j=1;j<n;j++)
            dp[i][j]=grid[i][j]+min(dp[i-1][j], dp[i][j-1]);
    return dp[m-1][n-1];
}

// ===================== LC 174. Dungeon Game (backward DP) =====================
ll calculateMinimumHP(vector<vector<int>>& dungeon)
{
    int m=dungeon.size(), n=dungeon[0].size();
    vector<vector<ll>> dp(m+1, vector<ll>(n+1, LLONG_MAX));
    dp[m][n-1]=1; dp[m-1][n]=1;
    for(int i=m-1;i>=0;i--)
        for(int j=n-1;j>=0;j--)
        {
            ll need = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
            dp[i][j] = max(1LL, need);
        }
    return dp[0][0];
}

// ===================== LC 741. Cherry Pickup (hardcoded small grid) =====================
int cherryPickup(vector<vector<int>>& grid)
{
    int n=grid.size();
    vector<vector<vector<int>>> memo(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
    function<int(int,int,int)> dp = [&](int r1,int c1,int c2)->int
    {
        int r2 = r1+c1-c2;
        if(r1>=n||c1>=n||r2>=n||c2>=n||grid[r1][c1]==-1||grid[r2][c2]==-1) return INT_MIN;
        if(r1==n-1 && c1==n-1) return grid[r1][c1];
        if(memo[r1][c1][c2]!=INT_MIN) return memo[r1][c1][c2];
        int cherries = grid[r1][c1];
        if(r1!=r2 || c1!=c2) cherries += grid[r2][c2];
        int best=INT_MIN;
        best=max(best, dp(r1+1,c1,c2+1));
        best=max(best, dp(r1+1,c1,c2));
        best=max(best, dp(r1,c1+1,c2+1));
        best=max(best, dp(r1,c1+1,c2));
        if(best==INT_MIN) return memo[r1][c1][c2]=INT_MIN;
        return memo[r1][c1][c2]=cherries+best;
    };
    int res=dp(0,0,0);
    return max(res,0);
}

// ===================== LC 980. Unique Paths III (enumerate actual paths) =====================
int uniquePathsIIICount;
void dfsUniquePathsIII(vector<vector<int>>& grid, int r, int c, int remaining)
{
    int m=grid.size(), n=grid[0].size();
    if(r<0||r>=m||c<0||c>=n||grid[r][c]==-1) return;
    if(grid[r][c]==2)
    {
        if(remaining==0) uniquePathsIIICount++;
        return;
    }
    int backup=grid[r][c];
    grid[r][c]=-1; // mark visited
    int dr[]={0,0,1,-1}, dc[]={1,-1,0,0};
    for(int d=0;d<4;d++)
        dfsUniquePathsIII(grid, r+dr[d], c+dc[d], remaining-1);
    grid[r][c]=backup; // backtrack
}

int uniquePathsIII(vector<vector<int>> grid)
{
    int m=grid.size(), n=grid[0].size();
    int startR=0,startC=0, walkable=0;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
            if(grid[i][j]==1){ startR=i; startC=j; }
            if(grid[i][j]!=-1) walkable++;
        }
    uniquePathsIIICount=0;
    dfsUniquePathsIII(grid, startR, startC, walkable-1);
    return uniquePathsIIICount;
}

// ===================== LC 1301. Number of Paths with Max Score =====================
pair<int,int> pathsWithMaxScore(vector<string>& board)
{
    int n=board.size();
    const ll MOD=1e9+7;
    vector<vector<ll>> dpSum(n, vector<ll>(n,-1));
    vector<vector<ll>> dpCnt(n, vector<ll>(n,0));
    board[0][0]='0'; board[n-1][n-1]='0';
    dpSum[n-1][n-1]=0; dpCnt[n-1][n-1]=1;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=n-1;j>=0;j--)
        {
            if(i==n-1&&j==n-1) continue;
            if(board[i][j]=='X') continue;
            ll best=-1, cnt=0;
            // neighbors are (i+1,j), (i,j+1), (i+1,j+1)
            int ni1=i+1, nj1=j, ni2=i, nj2=j+1, ni3=i+1, nj3=j+1;
            auto consider=[&](int ni,int nj){
                if(ni<n && nj<n && dpSum[ni][nj]>=0)
                {
                    if(dpSum[ni][nj]>best){ best=dpSum[ni][nj]; cnt=dpCnt[ni][nj]; }
                    else if(dpSum[ni][nj]==best) cnt=(cnt+dpCnt[ni][nj])%MOD;
                }
            };
            consider(ni1,nj1); consider(ni2,nj2); consider(ni3,nj3);
            if(best>=0)
            {
                dpSum[i][j]=best+(board[i][j]-'0');
                dpCnt[i][j]=cnt;
            }
        }
    }
    if(dpSum[0][0]<0) return {0,0};
    return {(int)dpSum[0][0], (int)dpCnt[0][0]};
}

void muhtasim()
{
    int m,n;
    cin>>m>>n;
    vector<vector<int>> grid(m, vector<int>(n));
    for(auto& row: grid) for(auto& x: row) cin>>x;

    cout<<"===== LC 63. Unique Paths II (with obstacles) =====\n";
    cout<<"Unique paths = "<<uniquePathsWithObstacles(grid)<<"\n";

    cout<<"===== LC 64. Minimum Path Sum (bundled) =====\n";
    {
        vector<vector<int>> costGrid={{1,3,1},{1,5,1},{4,2,1}};
        cout<<"minPathSum({{1,3,1},{1,5,1},{4,2,1}}) = "<<minPathSum(costGrid)<<"\n";
    }

    cout<<"===== LC 174. Dungeon Game (bundled, backward DP) =====\n";
    {
        vector<vector<int>> dungeon={{-2,-3,3},{-5,-10,1},{10,30,-5}};
        cout<<"calculateMinimumHP = "<<calculateMinimumHP(dungeon)<<"\n";
    }

    cout<<"===== LC 741. Cherry Pickup (bundled, small hardcoded grid) =====\n";
    {
        vector<vector<int>> cherryGrid={{0,1,-1},{1,0,-1},{1,1,1}};
        cout<<"cherryPickup(3x3 demo) = "<<cherryPickup(cherryGrid)<<"\n";
    }

    cout<<"===== LC 980. Unique Paths III (enumerate actual paths, bundled) =====\n";
    {
        vector<vector<int>> pathsGrid={{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
        cout<<"uniquePathsIII(demo) = "<<uniquePathsIII(pathsGrid)<<"\n";
    }

    cout<<"===== LC 1301. Number of Paths with Max Score (bundled) =====\n";
    {
        vector<string> board={"E23","2X2","12S"};
        auto res = pathsWithMaxScore(board);
        cout<<"pathsWithMaxScore = [ "<<res.first<<", "<<res.second<<" ]\n";
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
