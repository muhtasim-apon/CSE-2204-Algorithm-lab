#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Instructor Problem: Edge Classification (directed DFS, T/B/F/C) =====
// ===== Instructor Problem: DFS Again (undirected discovery/finish times) =====
// muhtasim() reads ONE edge list and runs BOTH analyses: directed adjacency
// (as given) for classification, and an undirected mirror of the same edges
// for discovery/finish times. Verified independently against each
// instructor sample (they use different graphs, so each is tested in
// isolation with its own tests=1 run).

int n;
vector<vector<int>> adjDirected, adjUndirected;

void classifyDfs(int u, vector<bool>&visited, vector<bool>&inProcess, vector<int>&disc, int &time_, vector<pair<pair<int,int>,int>>&edges){
    disc[u]=time_++;
    visited[u]=inProcess[u]=true;
    for(int v:adjDirected[u]){
        if(!visited[v]){ edges.push_back({{u,v},1}); classifyDfs(v,visited,inProcess,disc,time_,edges); }
        else if(inProcess[v]) edges.push_back({{u,v},2});
        else if(disc[u]<disc[v]) edges.push_back({{u,v},3});
        else edges.push_back({{u,v},4});
    }
    inProcess[u]=false;
}

void startFinishDfs(int u, vector<bool>&visited, vector<int>&startT, vector<int>&finishT, int &time_){
    visited[u]=true;
    startT[u]=time_++;
    for(int v:adjUndirected[u]) if(!visited[v]) startFinishDfs(v,visited,startT,finishT,time_);
    finishT[u]=time_++;
}

void muhtasim()
{
    int m; cin>>n>>m;
    adjDirected.assign(n,{});
    adjUndirected.assign(n,{});
    vector<array<int,2>> edgeList(m);
    for(auto &e:edgeList){
        int u,v; cin>>u>>v;
        e={u,v};
        adjDirected[u].push_back(v);
        adjUndirected[u].push_back(v);
        adjUndirected[v].push_back(u);
    }

    // ----- Edge Classification -----
    {
        vector<bool> visited(n,false), inProcess(n,false);
        vector<int> disc(n);
        vector<pair<pair<int,int>,int>> edges;
        int time_=0;
        for(int i=0;i<n;i++) if(!visited[i]) classifyDfs(i,visited,inProcess,disc,time_,edges);
        sort(edges.begin(),edges.end());
        for(auto &x:edges){
            int u=x.first.first, v=x.first.second;
            char tag = x.second==1?'T': x.second==2?'B': x.second==3?'F':'C';
            cout<<u<<" "<<v<<" ("<<tag<<")\n";
        }
    }

    // ----- DFS Again: discovery/finish times (undirected) -----
    {
        vector<bool> visited(n,false);
        vector<int> startT(n), finishT(n);
        int time_=1;
        for(int i=0;i<n;i++) if(!visited[i]) startFinishDfs(i,visited,startT,finishT,time_);
        for(int i=0;i<n;i++) cout<<i<<": "<<startT[i]<<" "<<finishT[i]<<"\n";
    }

    // ===== LC 200: Number of Islands (DFS flood fill) =====
    {
        vector<vector<char>> grid={{'1','1','0','0'},{'1','1','0','0'},{'0','0','1','0'},{'0','0','0','1'}};
        int R=grid.size(), C=grid[0].size(), count_=0;
        vector<vector<bool>> vis(R, vector<bool>(C,false));
        function<void(int,int)> flood=[&](int r,int c){
            if(r<0||c<0||r>=R||c>=C||vis[r][c]||grid[r][c]=='0') return;
            vis[r][c]=true;
            flood(r+1,c); flood(r-1,c); flood(r,c+1); flood(r,c-1);
        };
        for(int r=0;r<R;r++) for(int c=0;c<C;c++) if(grid[r][c]=='1' && !vis[r][c]){ count_++; flood(r,c); }
        cout<<"LC200 NumberOfIslands: "<<count_<<"\n";
    }

    // ===== LC 130: Surrounded Regions (mark border-connected O's safe) =====
    {
        vector<vector<char>> board={{'X','X','X','X'},{'X','O','O','X'},{'X','X','O','X'},{'X','O','X','X'}};
        int R=board.size(), C=board[0].size();
        vector<vector<bool>> safe(R, vector<bool>(C,false));
        function<void(int,int)> mark=[&](int r,int c){
            if(r<0||c<0||r>=R||c>=C||safe[r][c]||board[r][c]!='O') return;
            safe[r][c]=true;
            mark(r+1,c); mark(r-1,c); mark(r,c+1); mark(r,c-1);
        };
        for(int r=0;r<R;r++){ mark(r,0); mark(r,C-1); }
        for(int c=0;c<C;c++){ mark(0,c); mark(R-1,c); }
        int flipped=0;
        for(int r=0;r<R;r++) for(int c=0;c<C;c++) if(board[r][c]=='O' && !safe[r][c]) flipped++;
        cout<<"LC130 SurroundedRegions flipped: "<<flipped<<"\n";
    }

    // ===== LC 547: Number of Provinces =====
    {
        vector<vector<int>> isConnected={{1,1,0},{1,1,0},{0,0,1}};
        int N=isConnected.size();
        vector<bool> vis(N,false);
        function<void(int)> dfs2=[&](int u){ vis[u]=true; for(int v=0;v<N;v++) if(isConnected[u][v] && !vis[v]) dfs2(v); };
        int provinces=0;
        for(int i=0;i<N;i++) if(!vis[i]){ provinces++; dfs2(i); }
        cout<<"LC547 NumberOfProvinces: "<<provinces<<"\n";
    }

    // ===== LC 1319: Number of Operations to Make Network Connected =====
    {
        int N=6;
        vector<vector<int>> connections={{0,1},{0,2},{0,3},{1,2},{1,3}};
        if((int)connections.size()<N-1) cout<<"LC1319 MakeConnected: -1\n";
        else{
            vector<vector<int>> adj2(N);
            for(auto&e:connections){ adj2[e[0]].push_back(e[1]); adj2[e[1]].push_back(e[0]); }
            vector<bool> vis(N,false);
            function<void(int)> dfs2=[&](int u){ vis[u]=true; for(int v:adj2[u]) if(!vis[v]) dfs2(v); };
            int comps=0;
            for(int i=0;i<N;i++) if(!vis[i]){ comps++; dfs2(i); }
            cout<<"LC1319 MakeConnected (ops needed): "<<comps-1<<"\n";
        }
    }

    // ===== LC 261: Graph Valid Tree (cycle detection via DFS) =====
    {
        int N=5;
        vector<vector<int>> edges2={{0,1},{0,2},{0,3},{1,4}};
        bool validTree=true;
        if((int)edges2.size()!=N-1) validTree=false;
        else{
            vector<vector<int>> adj2(N);
            for(auto&e:edges2){ adj2[e[0]].push_back(e[1]); adj2[e[1]].push_back(e[0]); }
            vector<bool> vis(N,false);
            function<void(int,int)> dfs2=[&](int u,int parent){ vis[u]=true; for(int v:adj2[u]) if(v!=parent){ if(vis[v]){ validTree=false; return; } dfs2(v,u); } };
            dfs2(0,-1);
            for(int i=0;i<N;i++) if(!vis[i]) validTree=false;
        }
        cout<<"LC261 GraphValidTree: "<<(validTree?"true":"false")<<"\n";
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
