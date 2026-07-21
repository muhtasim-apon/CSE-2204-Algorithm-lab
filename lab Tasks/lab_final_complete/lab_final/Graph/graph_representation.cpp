#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Graph Representation: Adjacency List <-> Adjacency Matrix =====
// Input: N, M, then M lines "U V" (undirected, unweighted) for this demo.

void muhtasim()
{
    int n,m; cin>>n>>m;
    vector<vector<int>> adjList(n);
    vector<vector<int>> adjMatrix(n, vector<int>(n,0));
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
        adjMatrix[u][v]=1;
        adjMatrix[v][u]=1;
    }

    cout<<"Adjacency List:\n";
    for(int i=0;i<n;i++){
        cout<<i<<": ";
        for(int v:adjList[i]) cout<<v<<" ";
        cout<<"\n";
    }

    cout<<"Adjacency Matrix:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cout<<adjMatrix[i][j]<<" ";
        cout<<"\n";
    }

    // ----- Convert matrix -> list (round trip check) -----
    vector<vector<int>> rebuiltList(n);
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(adjMatrix[i][j]) rebuiltList[i].push_back(j);
    bool same=true;
    for(int i=0;i<n;i++){
        vector<int> a=adjList[i], b=rebuiltList[i];
        sort(a.begin(),a.end()); sort(b.begin(),b.end());
        if(a!=b) same=false;
    }
    cout<<"Matrix->List round-trip matches original list: "<<(same?"true":"false")<<"\n";

    // ===== Weighted directed adjacency-list demo =====
    {
        int N=4;
        vector<vector<pair<int,int>>> wadj(N);
        vector<array<int,3>> wedges={{0,1,5},{1,2,3},{0,2,10},{2,3,1}};
        for(auto&e:wedges) wadj[e[0]].push_back({e[1],e[2]});
        cout<<"Weighted directed adjacency list demo:\n";
        for(int i=0;i<N;i++){
            cout<<i<<": ";
            for(auto&[v,w]:wadj[i]) cout<<"("<<v<<","<<w<<") ";
            cout<<"\n";
        }
    }

    // ===== LC 133: Clone Graph (BFS clone) =====
    {
        int N=4;
        vector<vector<int>> adj2={{1,3},{0,2},{1,3},{0,2}}; // 0-indexed square
        vector<vector<int>> clone(N);
        vector<bool> visited(N,false);
        queue<int> q; q.push(0); visited[0]=true;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:adj2[u]){ clone[u].push_back(v); if(!visited[v]){ visited[v]=true; q.push(v); } }
        }
        cout<<"LC133 CloneGraph adjacency reproduced correctly: "<<(clone==adj2?"true":"false")<<"\n";
    }

    // ===== LC 997: Find the Town Judge =====
    {
        int N=3;
        vector<vector<int>> trust={{1,3},{2,3}};
        vector<int> trustsCount(N+1,0), trustedBy(N+1,0);
        for(auto&t:trust){ trustsCount[t[0]]++; trustedBy[t[1]]++; }
        int judge=-1;
        for(int i=1;i<=N;i++) if(trustsCount[i]==0 && trustedBy[i]==N-1) judge=i;
        cout<<"LC997 TownJudge: "<<judge<<"\n";
    }

    // ===== LC 1042: Flower Planting With No Adjacent (greedy 4-coloring) =====
    {
        int N=4;
        vector<vector<int>> paths={{1,2},{2,3},{3,4},{4,1},{1,3},{2,4}};
        vector<vector<int>> adj2(N+1);
        for(auto&p:paths){ adj2[p[0]].push_back(p[1]); adj2[p[1]].push_back(p[0]); }
        vector<int> color(N+1,0);
        for(int i=1;i<=N;i++){
            vector<bool> used(5,false);
            for(int v:adj2[i]) if(color[v]) used[color[v]]=true;
            for(int c=1;c<=4;c++) if(!used[c]){ color[i]=c; break; }
        }
        cout<<"LC1042 FlowerPlanting colors: ";
        for(int i=1;i<=N;i++) cout<<color[i]<<" ";
        cout<<"\n";
    }

    // ===== LC 1557: Minimum Number of Vertices to Reach All Nodes (indegree==0) =====
    {
        int N=6;
        vector<vector<int>> edges2={{0,1},{0,2},{2,5},{3,4},{4,2}};
        vector<int> indeg(N,0);
        for(auto&e:edges2) indeg[e[1]]++;
        cout<<"LC1557 MinVertices: ";
        for(int i=0;i<N;i++) if(indeg[i]==0) cout<<i<<" ";
        cout<<"\n";
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
