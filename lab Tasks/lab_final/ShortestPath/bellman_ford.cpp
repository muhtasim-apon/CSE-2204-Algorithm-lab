#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Bellman-Ford: relaxation + negative-cycle detection =====

int n;
vector<array<ll,3>> edges; // u,v,w (directed)

// returns {ok, dist}; ok=false means a negative cycle reachable from src exists
pair<bool,vector<ll>> bellmanFord(int src){
    vector<ll> dist(n, LLONG_MAX);
    dist[src]=0;
    for(int i=0;i<n-1;i++){
        for(auto &e:edges){
            ll u=e[0],v=e[1],w=e[2];
            if(dist[u]!=LLONG_MAX && dist[u]+w<dist[v]) dist[v]=dist[u]+w;
        }
    }
    bool ok=true;
    for(auto &e:edges){
        ll u=e[0],v=e[1],w=e[2];
        if(dist[u]!=LLONG_MAX && dist[u]+w<dist[v]){ ok=false; break; }
    }
    return {ok,dist};
}

void muhtasim()
{
    int m; cin>>n>>m;
    edges.assign(m,{});
    for(auto &e:edges){ ll u,v,w; cin>>u>>v>>w; e={u,v,w}; }
    int src=0;

    // ----- Core: standard relaxation from src -----
    auto [ok,dist] = bellmanFord(src);
    cout<<"Bellman-Ford from "<<src<<": ";
    if(!ok) cout<<"Negative Cycle Detected\n";
    else{
        for(int i=0;i<n;i++) cout<<(dist[i]==LLONG_MAX? string("INF"): to_string(dist[i]))<<(i+1<n?" ":"\n");
    }

    // ===== Explicit negative-cycle demo (hand-verified) =====
    // Graph: 0->1 (w=1), 1->2 (w=-3), 2->0 (w=1)  cycle sum = 1-3+1 = -1 < 0
    {
        int N=3;
        vector<array<ll,3>> e={{0,1,1},{1,2,-3},{2,0,1}};
        vector<ll> d(N,LLONG_MAX); d[0]=0;
        bool neg=false;
        for(int i=0;i<N-1;i++) for(auto&ed:e){ ll u=ed[0],v=ed[1],w=ed[2]; if(d[u]!=LLONG_MAX && d[u]+w<d[v]) d[v]=d[u]+w; }
        for(auto&ed:e){ ll u=ed[0],v=ed[1],w=ed[2]; if(d[u]!=LLONG_MAX && d[u]+w<d[v]){ neg=true; break; } }
        cout<<"NegativeCycleDemo: "<<(neg? "Negative Cycle Detected" : "No Negative Cycle")<<"\n";
    }

    // ===== LC 787: Cheapest Flights Within K Stops =====
    {
        int N=4,src2=0,dst2=3,K=1;
        vector<array<int,3>> flights={{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
        vector<ll> d(N, LLONG_MAX); d[src2]=0;
        for(int i=0;i<=K;i++){
            vector<ll> nd=d;
            for(auto&f:flights){ int u=f[0],v=f[1],w=f[2]; if(d[u]!=LLONG_MAX && d[u]+w<nd[v]) nd[v]=d[u]+w; }
            d=nd;
        }
        cout<<"LC787 CheapestFlightsKStops: "<<(d[dst2]==LLONG_MAX? -1 : d[dst2])<<"\n";
    }

    // ===== GfG-style: negative-weight shortest path (LC743-with-negative-weights) =====
    {
        int N=5;
        vector<array<ll,3>> e={{0,1,4},{0,2,1},{2,1,-2},{1,3,3},{2,3,5},{3,4,2}};
        vector<ll> d(N,LLONG_MAX); d[0]=0;
        for(int i=0;i<N-1;i++) for(auto&ed:e){ ll u=ed[0],v=ed[1],w=ed[2]; if(d[u]!=LLONG_MAX && d[u]+w<d[v]) d[v]=d[u]+w; }
        cout<<"NegativeWeightDemo dist[4]: "<<d[4]<<"\n";
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
