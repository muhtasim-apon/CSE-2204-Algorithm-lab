#include<bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// GLOBAL GRAPH
//////////////////////////////////////////////////////////////////
vector<vector<int>> g;

//////////////////////////////////////////////////////////////////
// 1. BASIC DFS TRAVERSAL
//////////////////////////////////////////////////////////////////
void dfs(int u, vector<int>&vis){
    vis[u]=1;
    cout<<u<<" ";

    for(int v:g[u]){
        if(!vis[v]) dfs(v,vis);
    }
}

//////////////////////////////////////////////////////////////////
// 2. DFS TREE EDGES (PARENT TRACKING)
//////////////////////////////////////////////////////////////////
void dfsTree(int u, vector<int>&vis, vector<int>&parent){
    vis[u]=1;

    for(int v:g[u]){
        if(!vis[v]){
            parent[v]=u;
            dfsTree(v,vis,parent);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 3. CONNECTED COMPONENTS
//////////////////////////////////////////////////////////////////
void connectedComponents(int n){
    vector<int> vis(n,0);

    for(int i=0;i<n;i++){
        if(!vis[i]){
            cout<<"Component: ";
            dfs(i,vis);
            cout<<"\n";
        }
    }
}

//////////////////////////////////////////////////////////////////
// 4. ALL PATHS FROM u TO v (BACKTRACKING DFS)
//////////////////////////////////////////////////////////////////
void allPaths(int u, int dst,
              vector<int>&vis,
              vector<int>&path){

    if(u==dst){
        for(int x:path) cout<<x<<" ";
        cout<<dst<<"\n";
        return;
    }

    vis[u]=1;

    for(int v:g[u]){
        if(!vis[v]){
            path.push_back(u);
            allPaths(v,dst,vis,path);
            path.pop_back();
        }
    }

    vis[u]=0;
}

//////////////////////////////////////////////////////////////////
// 5. ALL DFS ORDERS (BACKTRACK STYLE)
//////////////////////////////////////////////////////////////////
void allDFS(int u,
            vector<int>&vis,
            vector<int>&order){

    vis[u]=1;
    order.push_back(u);

    bool leaf=true;

    for(int v:g[u]){
        if(!vis[v]){
            leaf=false;
            allDFS(v,vis,order);
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
// 6. CYCLE DETECTION (DIRECTED GRAPH)
//////////////////////////////////////////////////////////////////
bool dfsCycleDirected(int u,
                      vector<int>&vis,
                      vector<int>&pathVis){

    vis[u]=1;
    pathVis[u]=1;

    for(int v:g[u]){
        if(!vis[v]){
            if(dfsCycleDirected(v,vis,pathVis))
                return true;
        }
        else if(pathVis[v]){
            return true;
        }
    }

    pathVis[u]=0;
    return false;
}

//////////////////////////////////////////////////////////////////
// 7. CYCLE DETECTION (UNDIRECTED GRAPH)
//////////////////////////////////////////////////////////////////
bool dfsCycleUndirected(int u, int p,
                        vector<int>&vis){

    vis[u]=1;

    for(int v:g[u]){
        if(!vis[v]){
            if(dfsCycleUndirected(v,u,vis))
                return true;
        }
        else if(v!=p){
            return true;
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////////
// 8. FLOOD FILL (GRID DFS)
//////////////////////////////////////////////////////////////////
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

void floodFill(vector<vector<int>>&grid,
               int x,int y,
               vector<vector<int>>&vis){

    int n=grid.size(), m=grid[0].size();

    vis[x][y]=1;

    for(int i=0;i<4;i++){
        int nx=x+dx[i];
        int ny=y+dy[i];

        if(nx>=0 && ny>=0 && nx<n && ny<m){
            if(!vis[nx][ny] && grid[nx][ny]==1){
                floodFill(grid,nx,ny,vis);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////
// 9. HAMILTONIAN PATH (VISIT ALL NODES ONCE)
//////////////////////////////////////////////////////////////////
void hamiltonian(int u,
                 vector<int>&vis,
                 vector<int>&path,
                 int n){

    if(path.size()==n){
        for(int x:path) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    for(int v:g[u]){
        if(!vis[v]){
            vis[v]=1;
            path.push_back(v);

            hamiltonian(v,vis,path,n);

            path.pop_back();
            vis[v]=0;
        }
    }
}

//////////////////////////////////////////////////////////////////
// 10. DFS SUBSET GENERATION (STATE TREE)
//////////////////////////////////////////////////////////////////
void subsetDFS(int i,
               vector<int>&arr,
               vector<int>&curr){

    if(i==arr.size()){
        for(int x:curr) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    // include
    curr.push_back(arr[i]);
    subsetDFS(i+1,arr,curr);
    curr.pop_back();

    // exclude
    subsetDFS(i+1,arr,curr);
}

//////////////////////////////////////////////////////////////////
// 11. DFS SPANNING TREE EDGES
//////////////////////////////////////////////////////////////////
void dfsSpanning(int u,
                 vector<int>&vis,
                 vector<pair<int,int>>&treeEdges){

    vis[u]=1;

    for(int v:g[u]){
        if(!vis[v]){
            treeEdges.push_back({u,v});
            dfsSpanning(v,vis,treeEdges);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 12. MAIN
//////////////////////////////////////////////////////////////////
int main(){

    int n,m;
    cin>>n>>m;

    g.assign(n,{});

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;

        g[u].push_back(v);
        g[v].push_back(u); // undirected (change for directed)
    }

    vector<int> vis(n,0);

    cout<<"DFS Traversal:\n";
    dfs(0,vis);
    cout<<"\n";

    return 0;
}