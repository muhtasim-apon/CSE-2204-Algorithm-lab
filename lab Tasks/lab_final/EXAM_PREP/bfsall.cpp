#include<bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// GRAPH
//////////////////////////////////////////////////////////////////
vector<vector<int>> g;

//////////////////////////////////////////////////////////////////
// 1. BASIC BFS TRAVERSAL
//////////////////////////////////////////////////////////////////
void bfs(int src){
    int n=g.size();
    vector<int> vis(n,0);

    queue<int> q;
    q.push(src);
    vis[src]=1;

    while(!q.empty()){
        int u=q.front(); q.pop();
        cout<<u<<" ";

        for(int v:g[u]){
            if(!vis[v]){
                vis[v]=1;
                q.push(v);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////
// 2. LEVEL ORDER BFS
//////////////////////////////////////////////////////////////////
void bfsLevel(int src){
    int n=g.size();
    vector<int> vis(n,0);

    queue<int> q;
    q.push(src);
    vis[src]=1;

    while(!q.empty()){
        int sz=q.size();

        while(sz--){
            int u=q.front(); q.pop();
            cout<<u<<" ";

            for(int v:g[u]){
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
        cout<<"\n";
    }
}

//////////////////////////////////////////////////////////////////
// 3. SHORTEST PATH (UNWEIGHTED GRAPH)
//////////////////////////////////////////////////////////////////
vector<int> bfsShortestPath(int src){
    int n=g.size();

    vector<int> dist(n,INT_MAX);
    queue<int> q;

    dist[src]=0;
    q.push(src);

    while(!q.empty()){
        int u=q.front(); q.pop();

        for(int v:g[u]){
            if(dist[v]==INT_MAX){
                dist[v]=dist[u]+1;
                q.push(v);
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 4. MULTI-SOURCE BFS
//////////////////////////////////////////////////////////////////
vector<int> multiSourceBFS(vector<int>&sources){
    int n=g.size();

    vector<int> dist(n,INT_MAX);
    queue<int> q;

    for(int s:sources){
        dist[s]=0;
        q.push(s);
    }

    while(!q.empty()){
        int u=q.front(); q.pop();

        for(int v:g[u]){
            if(dist[v]==INT_MAX){
                dist[v]=dist[u]+1;
                q.push(v);
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 5. 0-1 BFS (VERY IMPORTANT)
//////////////////////////////////////////////////////////////////
vector<int> zeroOneBFS(int src, vector<vector<pair<int,int>>>&adj){
    int n=adj.size();

    vector<int> dist(n,INT_MAX);
    deque<int> dq;

    dist[src]=0;
    dq.push_front(src);

    while(!dq.empty()){
        int u=dq.front();
        dq.pop_front();

        for(auto [v,w]:adj[u]){
            if(dist[u]+w < dist[v]){
                dist[v]=dist[u]+w;

                if(w==0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 6. CYCLE DETECTION (UNDIRECTED BFS)
//////////////////////////////////////////////////////////////////
bool bfsCycleUndirected(int src){
    int n=g.size();

    vector<int> vis(n,0), parent(n,-1);
    queue<int> q;

    q.push(src);
    vis[src]=1;

    while(!q.empty()){
        int u=q.front(); q.pop();

        for(int v:g[u]){
            if(!vis[v]){
                vis[v]=1;
                parent[v]=u;
                q.push(v);
            }
            else if(parent[u]!=v){
                return true;
            }
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////////
// 7. BIPARTITE GRAPH CHECK
//////////////////////////////////////////////////////////////////
bool isBipartite(int src){
    int n=g.size();

    vector<int> color(n,-1);
    queue<int> q;

    q.push(src);
    color[src]=0;

    while(!q.empty()){
        int u=q.front(); q.pop();

        for(int v:g[u]){
            if(color[v]==-1){
                color[v]=1-color[u];
                q.push(v);
            }
            else if(color[v]==color[u]){
                return false;
            }
        }
    }

    return true;
}

//////////////////////////////////////////////////////////////////
// 8. BFS IN GRID (FLOOD FILL)
//////////////////////////////////////////////////////////////////
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

int bfsGrid(vector<vector<int>>&grid, int sx,int sy){
    int n=grid.size(), m=grid[0].size();

    vector<vector<int>> vis(n,vector<int>(m,0));
    queue<pair<int,int>> q;

    q.push({sx,sy});
    vis[sx][sy]=1;

    while(!q.empty()){
        auto [x,y]=q.front(); q.pop();

        for(int i=0;i<4;i++){
            int nx=x+dx[i];
            int ny=y+dy[i];

            if(nx>=0 && ny>=0 && nx<n && ny<m){
                if(!vis[nx][ny] && grid[nx][ny]==1){
                    vis[nx][ny]=1;
                    q.push({nx,ny});
                }
            }
        }
    }

    return 1;
}

//////////////////////////////////////////////////////////////////
// 9. BFS WITH PATH RECONSTRUCTION
//////////////////////////////////////////////////////////////////
vector<int> bfsPath(int src, int dst){
    int n=g.size();

    vector<int> vis(n,0), parent(n,-1);
    queue<int> q;

    q.push(src);
    vis[src]=1;

    while(!q.empty()){
        int u=q.front(); q.pop();

        for(int v:g[u]){
            if(!vis[v]){
                vis[v]=1;
                parent[v]=u;
                q.push(v);
            }
        }
    }

    vector<int> path;

    if(!vis[dst]) return path;

    for(int v=dst; v!=-1; v=parent[v])
        path.push_back(v);

    reverse(path.begin(),path.end());

    return path;
}

//////////////////////////////////////////////////////////////////
// 10. MAIN
//////////////////////////////////////////////////////////////////
int main(){

    int n,m;
    cin>>n>>m;

    g.assign(n,{});

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;

        g[u].push_back(v);
        g[v].push_back(u); // undirected
    }

    cout<<"BFS Traversal:\n";
    bfs(0);

    return 0;
}