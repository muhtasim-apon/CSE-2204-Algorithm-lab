#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Instructor Problem A: Dijkstra (distances from node 0) =====
// ===== Instructor Problem B: Path of Dijkstra (lexicographically smallest shortest path 0->1) =====

int n;
vector<vector<pair<int,int>>> adj;

vector<ll> dijkstraDist(int src){
    vector<ll> dist(n, LLONG_MAX);
    dist[src]=0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0,src});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist[u]) continue;
        for(auto [v,w]:adj[u]){
            if(dist[u]!=LLONG_MAX && dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

// lexicographically smallest shortest path: among equal-distance predecessors pick smallest node id
vector<int> dijkstraLexPath(int src,int dst){
    vector<ll> dist(n, LLONG_MAX);
    vector<int> parent(n,-1);
    dist[src]=0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0,src});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist[u]) continue;
        for(auto [v,w]:adj[u]){
            ll nd=dist[u]+w;
            if(nd<dist[v] || (nd==dist[v] && (parent[v]==-1 || u<parent[v]))){
                if(nd<dist[v]){
                    dist[v]=nd;
                    parent[v]=u;
                    pq.push({nd,v});
                } else if(u<parent[v]){
                    parent[v]=u;
                }
            }
        }
    }
    if(dist[dst]==LLONG_MAX) return {};
    vector<int> path;
    int cur=dst;
    while(cur!=-1){ path.push_back(cur); cur = (cur==src? -1 : parent[cur]); }
    reverse(path.begin(),path.end());
    return path;
}

void muhtasim()
{
    int m;
    cin>>n>>m;
    adj.assign(n,{});
    vector<array<int,3>> edges(m);
    for(auto &e:edges){
        int u,v,w; cin>>u>>v>>w;
        e={u,v,w};
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    // ----- Problem A: distances from 0 -----
    auto dist = dijkstraDist(0);
    for(int i=0;i<n;i++){
        cout<<i<<": "<<(dist[i]==LLONG_MAX? string("Infinity") : to_string(dist[i]))<<"\n";
    }

    // ----- Problem B: lexicographically smallest shortest path 0->1 -----
    if(n>1){
        auto path = dijkstraLexPath(0,1);
        if(path.empty()) cout<<"Not Reachable\n";
        else for(int x:path) cout<<x<<"\n";
    }

    // ===== LC 743: Network Delay Time =====
    {
        int N=4,K=2;
        vector<vector<int>> times={{2,1,1},{2,3,1},{3,4,1}};
        vector<vector<pair<int,int>>> g(N+1);
        for(auto&t:times) g[t[0]].push_back({t[1],t[2]});
        vector<ll> d(N+1,LLONG_MAX); d[K]=0;
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq; pq.push({0,K});
        while(!pq.empty()){auto[dd,u]=pq.top();pq.pop(); if(dd>d[u])continue; for(auto[v,w]:g[u]) if(d[u]+w<d[v]){d[v]=d[u]+w;pq.push({d[v],v});}}
        ll mx=0; bool ok=true;
        for(int i=1;i<=N;i++){ if(d[i]==LLONG_MAX){ok=false;break;} mx=max(mx,d[i]); }
        cout<<"LC743 NetworkDelayTime: "<<(ok? to_string(mx): string("-1"))<<"\n";
    }

    // ===== LC 1514: Path with Maximum Probability =====
    {
        int N=3;
        vector<array<int,2>> e={{0,1},{1,2},{0,2}};
        vector<double> prob={0.5,0.5,0.3};
        vector<vector<pair<int,double>>> g(N);
        for(int i=0;i<(int)e.size();i++){ g[e[i][0]].push_back({e[i][1],prob[i]}); g[e[i][1]].push_back({e[i][0],prob[i]}); }
        vector<double> best(N,0.0); best[0]=1.0;
        priority_queue<pair<double,int>> pq; pq.push({1.0,0});
        while(!pq.empty()){ auto[p,u]=pq.top(); pq.pop(); if(p<best[u]) continue; for(auto[v,w]:g[u]) if(best[u]*w>best[v]){ best[v]=best[u]*w; pq.push({best[v],v}); } }
        cout<<"LC1514 MaxProbability(0->2): "<<best[2]<<"\n";
    }

    // ===== LC 1631: Path With Minimum Effort =====
    {
        vector<vector<int>> heights={{1,2,2},{3,8,2},{5,3,5}};
        int R=heights.size(), C=heights[0].size();
        vector<vector<int>> effort(R, vector<int>(C, INT_MAX));
        effort[0][0]=0;
        priority_queue<array<int,3>, vector<array<int,3>>, greater<>> pq; pq.push({0,0,0});
        int dx[]={0,0,1,-1}, dy[]={1,-1,0,0};
        while(!pq.empty()){
            auto top=pq.top(); pq.pop(); int e=top[0],x=top[1],y=top[2];
            if(e>effort[x][y]) continue;
            for(int d=0;d<4;d++){ int nx=x+dx[d],ny=y+dy[d];
                if(nx<0||ny<0||nx>=R||ny>=C) continue;
                int ne=max(e, abs(heights[nx][ny]-heights[x][y]));
                if(ne<effort[nx][ny]){ effort[nx][ny]=ne; pq.push({ne,nx,ny}); }
            }
        }
        cout<<"LC1631 MinimumEffort: "<<effort[R-1][C-1]<<"\n";
    }

    // ===== LC 1976: Number of Ways to Arrive at Destination (count shortest paths) =====
    {
        int N=7;
        vector<array<int,3>> roads={{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};
        vector<vector<pair<int,ll>>> g(N);
        for(auto&r:roads){ g[r[0]].push_back({r[1],r[2]}); g[r[1]].push_back({r[0],r[2]}); }
        vector<ll> d(N,LLONG_MAX); vector<ll> ways(N,0); d[0]=0; ways[0]=1;
        const ll MOD=1e9+7;
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq; pq.push({0,0});
        while(!pq.empty()){
            auto[dd,u]=pq.top(); pq.pop(); if(dd>d[u]) continue;
            for(auto[v,w]:g[u]){
                if(d[u]+w<d[v]){ d[v]=d[u]+w; ways[v]=ways[u]; pq.push({d[v],v}); }
                else if(d[u]+w==d[v]){ ways[v]=(ways[v]+ways[u])%MOD; }
            }
        }
        cout<<"LC1976 WaysToArrive(0->N-1): "<<ways[N-1]<<"\n";
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
