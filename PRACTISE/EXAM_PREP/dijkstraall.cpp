#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)4e18;

//////////////////////////////////////////////////////////////////
// GRAPH REPRESENTATION
//////////////////////////////////////////////////////////////////
// adj[u] = {v, w}
vector<vector<pair<int,int>>> adj;

//////////////////////////////////////////////////////////////////
// 1. STANDARD DIJKSTRA (DISTANCE ONLY)
//////////////////////////////////////////////////////////////////
vector<ll> dijkstra(int n, int src){
    vector<ll> dist(n, INF);

    priority_queue<
        pair<ll,int>,
        vector<pair<ll,int>>,
        greater<pair<ll,int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d != dist[u]) continue;

        for(auto [v, w] : adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 2. DIJKSTRA WITH PATH RECONSTRUCTION
//////////////////////////////////////////////////////////////////
vector<ll> dijkstraPath(int n, int src, vector<int>& parent){
    vector<ll> dist(n, INF);
    parent.assign(n, -1);

    priority_queue<
        pair<ll,int>,
        vector<pair<ll,int>>,
        greater<pair<ll,int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d != dist[u]) continue;

        for(auto [v, w] : adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

vector<int> getPath(int src, int dst, vector<int>& parent){
    vector<int> path;

    if(src == dst && parent[src] == -1){
        path.push_back(src);
        return path;
    }

    if(parent[dst] == -1) return path;

    for(int v = dst; v != -1; v = parent[v]){
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

//////////////////////////////////////////////////////////////////
// 3. MULTI-SOURCE DIJKSTRA
//////////////////////////////////////////////////////////////////
vector<ll> multiSourceDijkstra(int n, vector<int>& sources){
    vector<ll> dist(n, INF);

    priority_queue<
        pair<ll,int>,
        vector<pair<ll,int>>,
        greater<pair<ll,int>>
    > pq;

    for(int s : sources){
        dist[s] = 0;
        pq.push({0, s});
    }

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d != dist[u]) continue;

        for(auto [v, w] : adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 4. COUNT NUMBER OF SHORTEST PATHS
//////////////////////////////////////////////////////////////////
vector<ll> dijkstraCountPaths(int n, int src, vector<ll>& ways){
    vector<ll> dist(n, INF);
    ways.assign(n, 0);

    priority_queue<
        pair<ll,int>,
        vector<pair<ll,int>>,
        greater<pair<ll,int>>
    > pq;

    dist[src] = 0;
    ways[src] = 1;
    pq.push({0, src});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d != dist[u]) continue;

        for(auto [v, w] : adj[u]){
            ll nd = dist[u] + w;

            if(nd < dist[v]){
                dist[v] = nd;
                ways[v] = ways[u];
                pq.push({dist[v], v});
            }
            else if(nd == dist[v]){
                ways[v] += ways[u];
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 5. MIN/MAX EDGES AMONG SHORTEST PATHS
//////////////////////////////////////////////////////////////////
vector<ll> dijkstraMinMaxEdges(
    int n,
    int src,
    vector<int>& minEdges,
    vector<int>& maxEdges
){
    vector<ll> dist(n, INF);
    minEdges.assign(n, INT_MAX);
    maxEdges.assign(n, INT_MIN);

    priority_queue<
        pair<ll,int>,
        vector<pair<ll,int>>,
        greater<pair<ll,int>>
    > pq;

    dist[src] = 0;
    minEdges[src] = 0;
    maxEdges[src] = 0;
    pq.push({0, src});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d != dist[u]) continue;

        for(auto [v, w] : adj[u]){
            ll nd = dist[u] + w;

            if(nd < dist[v]){
                dist[v] = nd;
                minEdges[v] = minEdges[u] + 1;
                maxEdges[v] = maxEdges[u] + 1;
                pq.push({dist[v], v});
            }
            else if(nd == dist[v]){
                minEdges[v] = min(minEdges[v], minEdges[u] + 1);
                maxEdges[v] = max(maxEdges[v], maxEdges[u] + 1);
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 6. PRINT ALL SHORTEST PATHS (MULTI-PARENT DAG)
//////////////////////////////////////////////////////////////////
vector<ll> dijkstraAllParents(
    int n,
    int src,
    vector<vector<int>>& parents
){
    vector<ll> dist(n, INF);
    parents.assign(n, {});

    priority_queue<
        pair<ll,int>,
        vector<pair<ll,int>>,
        greater<pair<ll,int>>
    > pq;

    dist[src] = 0;
    pq.push({0, src});

    while(!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if(d != dist[u]) continue;

        for(auto [v, w] : adj[u]){
            ll nd = dist[u] + w;

            if(nd < dist[v]){
                dist[v] = nd;
                parents[v].clear();
                parents[v].push_back(u);
                pq.push({dist[v], v});
            }
            else if(nd == dist[v]){
                parents[v].push_back(u);
            }
        }
    }

    return dist;
}

void printAllShortestPaths(
    int u,
    int src,
    vector<vector<int>>& parents,
    vector<int>& path
){
    if(u == src){
        cout << src << " ";
        for(int i = (int)path.size() - 1; i >= 0; i--){
            cout << path[i] << " ";
        }
        cout << "\n";
        return;
    }

    for(int p : parents[u]){
        path.push_back(u);
        printAllShortestPaths(p, src, parents, path);
        path.pop_back();
    }
}

//////////////////////////////////////////////////////////////////
// 7. 0-1 BFS (weights 0 or 1 only)
//////////////////////////////////////////////////////////////////
vector<ll> zeroOneBFS(int n, int src){
    vector<ll> dist(n, INF);
    deque<int> dq;

    dist[src] = 0;
    dq.push_front(src);

    while(!dq.empty()){
        int u = dq.front();
        dq.pop_front();

        for(auto [v, w] : adj[u]){
            if(dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;

                if(w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// MAIN (EXAMPLE INPUT)
//////////////////////////////////////////////////////////////////
int main(){
    int n, m;
    cin >> n >> m;

    adj.assign(n, {});

    for(int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;

        // Directed graph:
        adj[u].push_back({v, w});

        // Uncomment for undirected graph:
        // adj[v].push_back({u, w});
    }

    // Example: Standard Dijkstra from node 0
    vector<ll> dist = dijkstra(n, 0);

    for(int i = 0; i < n; i++){
        if(dist[i] == INF) cout << "INF\n";
        else cout << "dist["
                  << i
                  << "] = "
                  << dist[i]
                  << "\n";
    }

    return 0;
}