#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll INF = LLONG_MAX/4;

// ===== Johnson's Algorithm: Bellman-Ford reweighting + per-source Dijkstra for all-pairs SP =====
// (rare as a direct LeetCode problem; included as GfG-style reference, cross-checked against
//  a Floyd-Warshall run on the same input as a correctness sanity check.)

int n;
vector<array<ll,3>> edges; // u,v,w directed

// returns {ok,h[]}; ok=false if a negative cycle is detected from the virtual source
pair<bool,vector<ll>> computePotentials(){
    vector<ll> h(n+1, 0); // node n is the virtual source, connected to all with weight 0
    vector<array<ll,3>> ext=edges;
    for(int i=0;i<n;i++) ext.push_back({n,i,0});
    for(int i=0;i<n;i++){
        for(auto&e:ext){ ll u=e[0],v=e[1],w=e[2]; if(h[u]!=INF && h[u]+w<h[v]) h[v]=h[u]+w; }
    }
    for(auto&e:ext){ ll u=e[0],v=e[1],w=e[2]; if(h[u]!=INF && h[u]+w<h[v]) return {false,{}}; }
    return {true,h};
}

vector<vector<ll>> johnsons(bool &ok){
    auto [good,h] = computePotentials();
    ok=good;
    vector<vector<ll>> result(n, vector<ll>(n, INF));
    if(!good) return result;

    vector<vector<pair<int,ll>>> adj(n);
    for(auto&e:edges){
        ll u=e[0],v=e[1],w=e[2];
        adj[u].push_back({(int)v, w + h[u] - h[v]}); // reweighted, guaranteed >= 0
    }
    for(int src=0;src<n;src++){
        vector<ll> dist(n, INF);
        dist[src]=0;
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq;
        pq.push({0,src});
        while(!pq.empty()){
            auto [d,u]=pq.top(); pq.pop();
            if(d>dist[u]) continue;
            for(auto&[v,w]:adj[u]) if(dist[u]+w<dist[v]){ dist[v]=dist[u]+w; pq.push({dist[v],v}); }
        }
        for(int v=0;v<n;v++) if(dist[v]<INF) result[src][v]=dist[v]-h[src]+h[v];
    }
    return result;
}

// Floyd-Warshall cross-check on the same edge list
vector<vector<ll>> floydCrossCheck(){
    vector<vector<ll>> d(n, vector<ll>(n, INF));
    for(int i=0;i<n;i++) d[i][i]=0;
    for(auto&e:edges){ ll u=e[0],v=e[1],w=e[2]; if(w<d[u][v]) d[u][v]=w; }
    for(int k=0;k<n;k++) for(int i=0;i<n;i++) for(int j=0;j<n;j++)
        if(d[i][k]<INF && d[k][j]<INF && d[i][k]+d[k][j]<d[i][j]) d[i][j]=d[i][k]+d[k][j];
    return d;
}

void muhtasim()
{
    int m; cin>>n>>m;
    edges.assign(m,{});
    for(auto &e:edges){ ll u,v,w; cin>>u>>v>>w; e={u,v,w}; }

    bool ok;
    auto jd = johnsons(ok);
    cout<<"Johnson's all-pairs distances:\n";
    if(!ok){ cout<<"Negative Cycle Detected\n"; return; }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) cout<<(jd[i][j]>=INF? string("INF"): to_string(jd[i][j]))<<(j+1<n?" ":"\n");
    }

    // ===== Cross-check against Floyd-Warshall on the same graph =====
    auto fw = floydCrossCheck();
    bool match=true;
    for(int i=0;i<n && match;i++) for(int j=0;j<n;j++) if(jd[i][j]!=fw[i][j]){ match=false; break; }
    cout<<"CrossCheck vs Floyd-Warshall: "<<(match? "MATCH" : "MISMATCH")<<"\n";
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
