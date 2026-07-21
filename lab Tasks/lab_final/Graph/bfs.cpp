#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== BFS: traversal order, shortest hop-distance from source 0, bipartite check =====
// Input: N, M, then M undirected edges "U V".

void muhtasim()
{
    int n,m; cin>>n>>m;
    vector<vector<int>> g(n);
    for(int i=0;i<m;i++){ int u,v; cin>>u>>v; g[u].push_back(v); g[v].push_back(u); }

    // ----- Standard BFS from 0: order + hop-distances -----
    {
        vector<int> dist(n,-1);
        vector<int> order_;
        queue<int> q; q.push(0); dist[0]=0;
        while(!q.empty()){
            int u=q.front(); q.pop(); order_.push_back(u);
            for(int v:g[u]) if(dist[v]==-1){ dist[v]=dist[u]+1; q.push(v); }
        }
        cout<<"BFS order from 0: "; for(int x:order_) cout<<x<<" "; cout<<"\n";
        cout<<"Hop-distances from 0: "; for(int i=0;i<n;i++) cout<<i<<":"<<dist[i]<<" "; cout<<"\n";
    }

    // ===== LC 785: Is Graph Bipartite (2-coloring BFS) =====
    {
        vector<int> color(n,-1);
        bool bipartite=true;
        for(int s=0;s<n && bipartite;s++){
            if(color[s]!=-1) continue;
            color[s]=0;
            queue<int> q; q.push(s);
            while(!q.empty() && bipartite){
                int u=q.front(); q.pop();
                for(int v:g[u]){
                    if(color[v]==-1){ color[v]=color[u]^1; q.push(v); }
                    else if(color[v]==color[u]){ bipartite=false; break; }
                }
            }
        }
        cout<<"LC785 IsBipartite: "<<(bipartite?"true":"false")<<"\n";
    }

    // ===== LC 200: Number of Islands (BFS variant) =====
    {
        vector<vector<char>> grid={{'1','1','0','0'},{'1','1','0','0'},{'0','0','1','0'},{'0','0','0','1'}};
        int R=grid.size(), C=grid[0].size(), count_=0;
        vector<vector<bool>> vis(R, vector<bool>(C,false));
        int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
        for(int r=0;r<R;r++) for(int c=0;c<C;c++){
            if(grid[r][c]=='1' && !vis[r][c]){
                count_++; vis[r][c]=true;
                queue<pair<int,int>> q; q.push({r,c});
                while(!q.empty()){
                    auto [cr,cc]=q.front(); q.pop();
                    for(int d=0;d<4;d++){
                        int nr=cr+dx[d], nc=cc+dy[d];
                        if(nr>=0&&nc>=0&&nr<R&&nc<C&&grid[nr][nc]=='1'&&!vis[nr][nc]){ vis[nr][nc]=true; q.push({nr,nc}); }
                    }
                }
            }
        }
        cout<<"LC200 NumberOfIslands(BFS): "<<count_<<"\n";
    }

    // ===== LC 994: Rotting Oranges (multi-source BFS) =====
    {
        vector<vector<int>> grid={{2,1,1},{1,1,0},{0,1,1}};
        int R=grid.size(), C=grid[0].size(), fresh=0, minutes=0;
        queue<pair<int,int>> q;
        for(int r=0;r<R;r++) for(int c=0;c<C;c++){ if(grid[r][c]==2) q.push({r,c}); else if(grid[r][c]==1) fresh++; }
        int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
        while(!q.empty() && fresh>0){
            int sz=q.size(); minutes++;
            while(sz--){
                auto [r,c]=q.front(); q.pop();
                for(int d=0;d<4;d++){
                    int nr=r+dx[d], nc=c+dy[d];
                    if(nr>=0&&nc>=0&&nr<R&&nc<C&&grid[nr][nc]==1){ grid[nr][nc]=2; fresh--; q.push({nr,nc}); }
                }
            }
        }
        cout<<"LC994 RottingOranges minutes: "<<(fresh==0? minutes : -1)<<"\n";
    }

    // ===== LC 542: 01 Matrix (multi-source BFS from all 0s) =====
    {
        vector<vector<int>> mat={{0,0,0},{0,1,0},{1,1,1}};
        int R=mat.size(), C=mat[0].size();
        vector<vector<int>> dist(R, vector<int>(C,-1));
        queue<pair<int,int>> q;
        for(int r=0;r<R;r++) for(int c=0;c<C;c++) if(mat[r][c]==0){ dist[r][c]=0; q.push({r,c}); }
        int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
        while(!q.empty()){
            auto [r,c]=q.front(); q.pop();
            for(int d=0;d<4;d++){
                int nr=r+dx[d], nc=c+dy[d];
                if(nr>=0&&nc>=0&&nr<R&&nc<C&&dist[nr][nc]==-1){ dist[nr][nc]=dist[r][c]+1; q.push({nr,nc}); }
            }
        }
        cout<<"LC542 01Matrix dist[2][2]: "<<dist[2][2]<<"\n";
    }

    // ===== LC 127: Word Ladder (small demo word list) =====
    {
        string beginWord="hit", endWord="cog";
        set<string> wordList={"hot","dot","dog","lot","log","cog"};
        queue<pair<string,int>> q; q.push({beginWord,1});
        int result=0;
        while(!q.empty()){
            auto [w,steps]=q.front(); q.pop();
            if(w==endWord){ result=steps; break; }
            for(int i=0;i<(int)w.size();i++){
                string t=w;
                for(char c='a';c<='z';c++){
                    t[i]=c;
                    if(wordList.count(t)){ wordList.erase(t); q.push({t,steps+1}); }
                }
            }
        }
        cout<<"LC127 WordLadder length: "<<result<<"\n";
    }

    // ===== LC 1091: Shortest Path in Binary Matrix (8-directional BFS) =====
    {
        vector<vector<int>> grid={{0,0,0},{1,1,0},{1,1,0}};
        int N=grid.size();
        vector<vector<bool>> vis(N, vector<bool>(N,false));
        int result=-1;
        if(grid[0][0]==0 && grid[N-1][N-1]==0){
            queue<pair<int,int>> q; q.push({0,0}); vis[0][0]=true;
            int steps=1;
            while(!q.empty()){
                int sz=q.size();
                while(sz--){
                    auto [r,c]=q.front(); q.pop();
                    if(r==N-1&&c==N-1){ result=steps; }
                    for(int dr=-1;dr<=1;dr++) for(int dc=-1;dc<=1;dc++){
                        if(dr==0&&dc==0) continue;
                        int nr=r+dr,nc=c+dc;
                        if(nr>=0&&nc>=0&&nr<N&&nc<N&&!vis[nr][nc]&&grid[nr][nc]==0){ vis[nr][nc]=true; q.push({nr,nc}); }
                    }
                }
                if(result!=-1) break;
                steps++;
            }
        }
        cout<<"LC1091 ShortestPathBinaryMatrix: "<<result<<"\n";
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
