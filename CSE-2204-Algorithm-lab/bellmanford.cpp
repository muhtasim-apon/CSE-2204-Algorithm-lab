```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const ll INF=1e18;

struct Edge
{
    int u,v;
    ll w;
};

vector<Edge> edges;
vector<ll> dist;
vector<int> parent;

// Add a directed edge u -> v with weight w
void addEdge(int u,int v,ll w)
{
    edges.push_back({u,v,w});
}

// Initialize distance and parent arrays
void initialize(int n,int src)
{
    dist.assign(n+1,INF);
    parent.assign(n+1,-1);
    dist[src]=0;
}

// 1. Standard Bellman-Ford
// Returns true if at least one relaxation happened in the last pass.
bool bellmanFord(int n,int src)
{
    initialize(n,src);

    bool updated=false;

    for(int i=1;i<=n-1;i++)
    {
        updated=false;

        for(auto e:edges)
        {
            if(dist[e.u]==INF) continue;

            if(dist[e.u]+e.w<dist[e.v])
            {
                dist[e.v]=dist[e.u]+e.w;
                parent[e.v]=e.u;
                updated=true;
            }
        }

        if(!updated) break;
    }

    return updated;
}

// 2. Detect negative cycle reachable from source
bool hasNegativeCycleFromSource()
{
    for(auto e:edges)
    {
        if(dist[e.u]==INF) continue;

        if(dist[e.u]+e.w<dist[e.v])
        {
            parent[e.v]=e.u;
            return true;
        }
    }

    return false;
}

// 3. Return one actual negative cycle anywhere in the graph
vector<int> getNegativeCycle(int n)
{
    vector<ll> d(n+1,0);
    vector<int> p(n+1,-1);

    int x=-1;

    for(int i=1;i<=n;i++)
    {
        x=-1;

        for(auto e:edges)
        {
            if(d[e.u]+e.w<d[e.v])
            {
                d[e.v]=d[e.u]+e.w;
                p[e.v]=e.u;
                x=e.v;
            }
        }
    }

    if(x==-1) return {};

    for(int i=1;i<=n;i++)
        x=p[x];

    vector<int> cycle;
    int cur=x;

    do
    {
        cycle.push_back(cur);
        cur=p[cur];
    }
    while(cur!=x);

    cycle.push_back(x);
    reverse(cycle.begin(),cycle.end());

    return cycle;
}

// 4. Detect any negative cycle in the whole graph
bool hasAnyNegativeCycle(int n)
{
    return !getNegativeCycle(n).empty();
}

// 5. Reconstruct shortest path after bellmanFord()
vector<int> getPath(int src,int dest)
{
    vector<int> path;

    if(dist[dest]==INF) return path;

    for(int v=dest;v!=-1;v=parent[v])
        path.push_back(v);

    reverse(path.begin(),path.end());

    if(path.empty() || path[0]!=src)
        return {};

    return path;
}

// 6. Shortest path using at most k edges
ll shortestPathWithKEdges(int n,int src,int dest,int k)
{
    vector<ll> d(n+1,INF);
    d[src]=0;

    for(int i=1;i<=k;i++)
    {
        vector<ll> temp=d;

        for(auto e:edges)
        {
            if(d[e.u]==INF) continue;

            temp[e.v]=min(temp[e.v],d[e.u]+e.w);
        }

        d=temp;
    }

    if(d[dest]==INF) return -1;
    return d[dest];
}

// 7. Longest path by negating all edge weights
// Valid only when no positive cycle affects destination.
ll longestPath(int n,int src,int dest)
{
    vector<Edge> backup=edges;

    for(auto &e:edges)
        e.w=-e.w;

    bellmanFord(n,src);

    ll ans=(dist[dest]==INF?INF:-dist[dest]);

    edges=backup;

    if(ans==INF) return -1;
    return ans;
}

int main()
{
    int n,m;
    cin>>n>>m;

    edges.clear();

    while(m--)
    {
        int u,v;
        ll w;
        cin>>u>>v>>w;
        addEdge(u,v,w);
    }

    int src;
    cin>>src;

    // 1. Run Bellman-Ford
    bellmanFord(n,src);

    // Print shortest distances
    for(int i=1;i<=n;i++)
    {
        if(dist[i]==INF) cout<<"INF\n";
        else cout<<dist[i]<<"\n";
    }

    // 2. Negative cycle reachable from source
    if(hasNegativeCycleFromSource())
        cout<<"Negative Weight Cycle Detected\n";
    else
        cout<<"NO\n";

    // 3. Print actual negative cycle anywhere in graph
    vector<int> cycle=getNegativeCycle(n);
    if(!cycle.empty())
    {
        for(auto x:cycle)
            cout<<x<<" ";
        cout<<"\n";
    }

    // 5. Example path from src to n
    vector<int> path=getPath(src,n);
    if(!path.empty())
    {
        for(auto x:path)
            cout<<x<<" ";
        cout<<"\n";
    }

    // 6. Example: shortest path from src to n using at most 3 edges
    cout<<shortestPathWithKEdges(n,src,n,3)<<"\n";

    // 7. Example longest path from src to n
    cout<<longestPath(n,src,n)<<"\n";

    return 0;
}
```
