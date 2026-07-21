#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== DAG Shortest & Longest Path via Topological Order + DP =====

int n;
vector<vector<pair<int,ll>>> adj;
vector<int> indeg;

vector<int> topoOrder(){
    vector<int> ind=indeg;
    queue<int> q;
    for(int i=0;i<n;i++) if(ind[i]==0) q.push(i);
    vector<int> order;
    while(!q.empty()){
        int u=q.front(); q.pop();
        order.push_back(u);
        for(auto&[v,w]:adj[u]){ if(--ind[v]==0) q.push(v); }
    }
    return order;
}

void muhtasim()
{
    int m; cin>>n>>m;
    adj.assign(n,{});
    indeg.assign(n,0);
    for(int i=0;i<m;i++){
        int u,v; ll w; cin>>u>>v>>w;
        adj[u].push_back({v,w});
        indeg[v]++;
    }
    int src=0;
    auto order=topoOrder();

    // ----- Core: shortest path in DAG from src -----
    vector<ll> dist(n, LLONG_MAX);
    dist[src]=0;
    for(int u:order){
        if(dist[u]==LLONG_MAX) continue;
        for(auto&[v,w]:adj[u]) dist[v]=min(dist[v], dist[u]+w);
    }
    cout<<"DAG Shortest from "<<src<<": ";
    for(int i=0;i<n;i++) cout<<(dist[i]==LLONG_MAX? string("INF"): to_string(dist[i]))<<(i+1<n?" ":"\n");

    // ----- Longest path in DAG from src (critical path) -----
    vector<ll> longest(n, LLONG_MIN);
    longest[src]=0;
    for(int u:order){
        if(longest[u]==LLONG_MIN) continue;
        for(auto&[v,w]:adj[u]) longest[v]=max(longest[v], longest[u]+w);
    }
    cout<<"DAG Longest from "<<src<<": ";
    for(int i=0;i<n;i++) cout<<(longest[i]==LLONG_MIN? string("-INF"): to_string(longest[i]))<<(i+1<n?" ":"\n");

    // ===== LC 1786: Number of Restricted Paths From First to Last Node =====
    // (distances computed from destination node backward; restriction: dist[u] > dist[v] along path)
    // Demo graph (0-indexed, hand-verified): 0-1(1) 0-2(2) 1-2(1) 1-3(1) 2-3(1), src=0, dst=3.
    // Dijkstra from 3 backward: d3=0, d1=1, d2=1, d0=2.
    // Restricted paths (strictly decreasing dist each step): 0->1->3 and 0->2->3 => answer 2.
    {
        int N=4;
        vector<array<ll,3>> edges2={{0,1,1},{0,2,2},{1,2,1},{1,3,1},{2,3,1}};
        vector<vector<pair<int,ll>>> g(N);
        for(auto&e:edges2){ g[e[0]].push_back({(int)e[1],e[2]}); g[e[1]].push_back({(int)e[0],e[2]}); }
        vector<ll> d(N, LLONG_MAX); d[N-1]=0;
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq; pq.push({0,N-1});
        while(!pq.empty()){ auto[dd,u]=pq.top(); pq.pop(); if(dd>d[u]) continue; for(auto&[v,w]:g[u]) if(d[u]+w<d[v]){ d[v]=d[u]+w; pq.push({d[v],v}); } }
        const ll MOD=1e9+7;
        vector<ll> memo(N,-1);
        function<ll(int)> countPaths=[&](int u)->ll{
            if(u==N-1) return 1;
            if(memo[u]!=-1) return memo[u];
            ll res=0;
            for(auto&[v,w]:g[u]) if(d[v]<d[u]) res=(res+countPaths(v))%MOD;
            return memo[u]=res;
        };
        cout<<"LC1786 RestrictedPaths: "<<countPaths(0)<<"\n";
    }

    // ===== LC 329: Longest Increasing Path in a Matrix (DAG longest-path pattern) =====
    {
        vector<vector<int>> mat={{9,9,4},{6,6,8},{2,1,1}};
        int R=mat.size(), C=mat[0].size();
        vector<vector<int>> memo(R, vector<int>(C,-1));
        int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
        function<int(int,int)> dfs=[&](int x,int y)->int{
            if(memo[x][y]!=-1) return memo[x][y];
            int best=1;
            for(int d=0;d<4;d++){ int nx=x+dx[d],ny=y+dy[d];
                if(nx<0||ny<0||nx>=R||ny>=C) continue;
                if(mat[nx][ny]>mat[x][y]) best=max(best,1+dfs(nx,ny));
            }
            return memo[x][y]=best;
        };
        int ans=0;
        for(int i=0;i<R;i++) for(int j=0;j<C;j++) ans=max(ans, dfs(i,j));
        cout<<"LC329 LongestIncreasingPath: "<<ans<<"\n";
    }

    // ===== LC 1494/2050-style: Parallel Courses III (longest completion time over topo DAG) =====
    {
        int N=3;
        vector<int> time={3,2,5}; // 0-indexed course durations
        vector<array<int,2>> rel={{0,1},{1,2}}; // 0-indexed prereq edges
        vector<vector<int>> g2(N); vector<int> ind2(N,0);
        for(auto&r:rel){ g2[r[0]].push_back(r[1]); ind2[r[1]]++; }
        queue<int> q2; for(int i=0;i<N;i++) if(ind2[i]==0) q2.push(i);
        vector<int> finish(N,0);
        for(int i=0;i<N;i++) if(ind2[i]==0) finish[i]=time[i];
        while(!q2.empty()){
            int u=q2.front(); q2.pop();
            for(int v:g2[u]){
                finish[v]=max(finish[v], finish[u]+time[v]);
                if(--ind2[v]==0) q2.push(v);
            }
        }
        cout<<"LC1494 ParallelCoursesIII: "<<*max_element(finish.begin(),finish.end())<<"\n";
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
