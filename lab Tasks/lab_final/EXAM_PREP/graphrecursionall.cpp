#include<bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////////////
vector<vector<pair<int,int>>> g;   // weighted graph: {to, weight}
vector<int> vis, disc, low;
int timer;

//////////////////////////////////////////////////////////////////
// 1. BASIC DFS (TRAVERSAL)
//////////////////////////////////////////////////////////////////
void dfs(int u){
    vis[u]=1;
    cout<<u<<" ";

    for(auto [v,w]:g[u]){
        if(!vis[v]) dfs(v);
    }
}

//////////////////////////////////////////////////////////////////
// 2. ALL PATHS u -> dst (BACKTRACKING)
//////////////////////////////////////////////////////////////////
void allPaths(int u,int dst,vector<int>&path){
    if(u==dst){
        for(int x:path) cout<<x<<" ";
        cout<<dst<<"\n";
        return;
    }

    vis[u]=1;

    for(auto [v,w]:g[u]){
        if(!vis[v]){
            path.push_back(u);
            allPaths(v,dst,path);
            path.pop_back();
        }
    }

    vis[u]=0;
}

//////////////////////////////////////////////////////////////////
// 3. HAMILTONIAN PATH
//////////////////////////////////////////////////////////////////
void hamiltonian(int u, vector<int>&path, int n){
    if(path.size()==n){
        for(int x:path) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    for(auto [v,w]:g[u]){
        if(!vis[v]){
            vis[v]=1;
            path.push_back(v);

            hamiltonian(v,path,n);

            path.pop_back();
            vis[v]=0;
        }
    }
}

//////////////////////////////////////////////////////////////////
// 4. ALL TOPOLOGICAL SORTS (DAG)
//////////////////////////////////////////////////////////////////
void allTopo(vector<int>&indeg, vector<int>&res, int n){
    bool found=false;

    for(int i=0;i<n;i++){
        if(indeg[i]==0 && !vis[i]){
            found=true;

            vis[i]=1;
            res.push_back(i);

            for(auto [v,w]:g[i]) indeg[v]--;

            allTopo(indeg,res,n);

            for(auto [v,w]:g[i]) indeg[v]++;
            res.pop_back();
            vis[i]=0;
        }
    }

    if(!found){
        for(int x:res) cout<<x<<" ";
        cout<<"\n";
    }
}

//////////////////////////////////////////////////////////////////
// 5. BRIDGES (TARJAN)
//////////////////////////////////////////////////////////////////
vector<pair<int,int>> bridges;

void bridgeDFS(int u,int p){
    vis[u]=1;
    disc[u]=low[u]=++timer;

    for(auto [v,w]:g[u]){
        if(v==p) continue;

        if(!vis[v]){
            bridgeDFS(v,u);
            low[u]=min(low[u],low[v]);

            if(low[v] > disc[u]){
                bridges.push_back({u,v});
            }
        }
        else{
            low[u]=min(low[u],disc[v]);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 6. BICONNECTED COMPONENTS (EDGE STACK)
//////////////////////////////////////////////////////////////////
stack<pair<int,int>> edgeStack;
vector<vector<pair<int,int>>> bcc;

void bccDFS(int u,int p){
    vis[u]=1;
    disc[u]=low[u]=++timer;

    for(auto [v,w]:g[u]){
        if(v==p) continue;

        if(!vis[v]){
            edgeStack.push({u,v});

            bccDFS(v,u);

            low[u]=min(low[u],low[v]);

            if(low[v] >= disc[u]){
                vector<pair<int,int>> comp;

                while(true){
                    auto e=edgeStack.top();
                    edgeStack.pop();
                    comp.push_back(e);

                    if(e.first==u && e.second==v) break;
                }

                bcc.push_back(comp);
            }
        }
        else if(disc[v] < disc[u]){
            edgeStack.push({u,v});
            low[u]=min(low[u],disc[v]);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 7. SCC (KOSARAJU)
//////////////////////////////////////////////////////////////////
void dfs1(int u, vector<int>&order){
    vis[u]=1;

    for(auto [v,w]:g[u]){
        if(!vis[v]) dfs1(v,order);
    }

    order.push_back(u);
}

void dfs2(int u, vector<vector<int>>&rg, vector<int>&component){
    vis[u]=1;
    component.push_back(u);

    for(int v:rg[u]){
        if(!vis[v]) dfs2(v,rg,component);
    }
}

void kosaraju(int n){
    vector<int> order;
    fill(vis.begin(), vis.end(), 0);

    for(int i=0;i<n;i++){
        if(!vis[i]) dfs1(i,order);
    }

    vector<vector<int>> rg(n);
    for(int u=0;u<n;u++){
        for(auto [v,w]:g[u]){
            rg[v].push_back(u);
        }
    }

    fill(vis.begin(), vis.end(), 0);
    reverse(order.begin(), order.end());

    for(int u:order){
        if(!vis[u]){
            vector<int> comp;
            dfs2(u,rg,comp);

            cout<<"SCC: ";
            for(int x:comp) cout<<x<<" ";
            cout<<"\n";
        }
    }
}

//////////////////////////////////////////////////////////////////
// 8. GENERATE ALL DFS ORDERS
//////////////////////////////////////////////////////////////////
void allDFS(int u, vector<int>&order){
    vis[u]=1;
    order.push_back(u);

    bool leaf=true;

    for(auto [v,w]:g[u]){
        if(!vis[v]){
            leaf=false;
            allDFS(v,order);
        }
    }

    if(leaf){
        for(int x:order) cout<<x<<" ";
        cout<<"\n";
    }

    order.pop_back();
    vis[u]=0;
}

//////////////////////////////////////////////////////////////////
// 9. DIJKSTRA + PRINT ALL SHORTEST PATHS
//////////////////////////////////////////////////////////////////
vector<long long> dijkstra(int src, vector<vector<int>>&parent){
    int n=g.size();
    const long long INF=4e18;

    vector<long long> dist(n,INF);
    parent.assign(n,{});

    priority_queue<
        pair<long long,int>,
        vector<pair<long long,int>>,
        greater<pair<long long,int>>
    > pq;

    dist[src]=0;
    pq.push({0,src});

    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();

        if(d!=dist[u]) continue;

        for(auto [v,w]:g[u]){
            long long nd=d+w;

            if(nd<dist[v]){
                dist[v]=nd;
                parent[v].clear();
                parent[v].push_back(u);
                pq.push({nd,v});
            }
            else if(nd==dist[v]){
                parent[v].push_back(u);
            }
        }
    }

    return dist;
}

void printAllShortestPaths(int u, int src,
                           vector<vector<int>>&parent,
                           vector<int>&path){
    if(u==src){
        cout<<src<<" ";
        for(int i=(int)path.size()-1;i>=0;i--){
            cout<<path[i]<<" ";
        }
        cout<<"\n";
        return;
    }

    for(int p:parent[u]){
        path.push_back(u);
        printAllShortestPaths(p,src,parent,path);
        path.pop_back();
    }
}

//////////////////////////////////////////////////////////////////
// 10. BELLMAN-FORD + PRINT ALL SHORTEST PATHS
//////////////////////////////////////////////////////////////////
struct Edge{
    int u,v,w;
};

vector<long long> bellmanFord(int n,int src,
                              vector<Edge>&edges,
                              vector<vector<int>>&parent){
    const long long INF=4e18;

    vector<long long> dist(n,INF);
    parent.assign(n,{});

    dist[src]=0;

    for(int i=1;i<=n-1;i++){
        for(auto e:edges){
            if(dist[e.u]==INF) continue;

            long long nd=dist[e.u]+e.w;

            if(nd<dist[e.v]){
                dist[e.v]=nd;
                parent[e.v].clear();
                parent[e.v].push_back(e.u);
            }
            else if(nd==dist[e.v]){
                parent[e.v].push_back(e.u);
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////////////////////
int main(){
    int n,m;
    cin>>n>>m;

    g.assign(n,{});
    vis.assign(n,0);
    disc.assign(n,0);
    low.assign(n,0);

    vector<Edge> edges;

    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;

        // Directed weighted edge
        g[u].push_back({v,w});

        // Uncomment next line for undirected graphs
        // g[v].push_back({u,w});

        edges.push_back({u,v,w});
    }

    // Example usage:
    // dfs(0);
    // allPaths(0,n-1,path);
    // hamiltonian(start,path,n);
    // allTopo(indeg,res,n);
    // bridgeDFS(0,-1);
    // bccDFS(0,-1);
    // kosaraju(n);
    // allDFS(0,order);

    // Dijkstra all shortest paths:
    // vector<vector<int>> parent;
    // auto dist=dijkstra(0,parent);
    // vector<int> path;
    // printAllShortestPaths(destination,0,parent,path);

    // Bellman-Ford all shortest paths:
    // vector<vector<int>> parent;
    // auto dist=bellmanFord(n,0,edges,parent);
    // vector<int> path;
    // printAllShortestPaths(destination,0,parent,path);

    return 0;
}