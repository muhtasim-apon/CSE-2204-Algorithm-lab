#include<bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// GLOBAL GRAPH
//////////////////////////////////////////////////////////////////
vector<vector<int>> g;

//////////////////////////////////////////////////////////////////
// 1. KAHN'S ALGORITHM (BFS TOPO SORT)
//////////////////////////////////////////////////////////////////
vector<int> kahnTopo(int n){

    vector<int> indeg(n,0);

    for(int u=0;u<n;u++){
        for(int v:g[u]) indeg[v]++;
    }

    queue<int> q;
    for(int i=0;i<n;i++){
        if(indeg[i]==0) q.push(i);
    }

    vector<int> topo;

    while(!q.empty()){
        int u=q.front(); q.pop();
        topo.push_back(u);

        for(int v:g[u]){
            indeg[v]--;
            if(indeg[v]==0) q.push(v);
        }
    }

    if(topo.size()!=n){
        cout<<"Cycle exists!\n";
        return {};
    }

    return topo;
}

//////////////////////////////////////////////////////////////////
// 2. DFS TOPO SORT
//////////////////////////////////////////////////////////////////
void dfsTopo(int u, vector<int>&vis, vector<int>&res){

    vis[u]=1;

    for(int v:g[u]){
        if(!vis[v]) dfsTopo(v,vis,res);
    }

    res.push_back(u);
}

vector<int> topoDFS(int n){

    vector<int> vis(n,0);
    vector<int> res;

    for(int i=0;i<n;i++){
        if(!vis[i]) dfsTopo(i,vis,res);
    }

    reverse(res.begin(),res.end());
    return res;
}

//////////////////////////////////////////////////////////////////
// 3. ALL TOPOLOGICAL SORTS (BACKTRACKING)
//////////////////////////////////////////////////////////////////
void allTopo(int n, vector<int>&indeg,
             vector<int>&vis,
             vector<int>&res){

    bool found=false;

    for(int i=0;i<n;i++){
        if(indeg[i]==0 && !vis[i]){

            found=true;

            vis[i]=1;
            res.push_back(i);

            for(int v:g[i]) indeg[v]--;

            allTopo(n,indeg,vis,res);

            for(int v:g[i]) indeg[v]++;
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
// 4. LEXICOGRAPHICALLY SMALLEST TOPO ORDER
//////////////////////////////////////////////////////////////////
vector<int> lexicographicTopo(int n){

    vector<int> indeg(n,0);

    for(int u=0;u<n;u++){
        for(int v:g[u]) indeg[v]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i=0;i<n;i++){
        if(indeg[i]==0) pq.push(i);
    }

    vector<int> topo;

    while(!pq.empty()){
        int u=pq.top(); pq.pop();
        topo.push_back(u);

        for(int v:g[u]){
            indeg[v]--;
            if(indeg[v]==0) pq.push(v);
        }
    }

    return topo;
}

//////////////////////////////////////////////////////////////////
// 5. CYCLE DETECTION (KAHN)
//////////////////////////////////////////////////////////////////
bool hasCycle(int n){

    vector<int> indeg(n,0);

    for(int u=0;u<n;u++){
        for(int v:g[u]) indeg[v]++;
    }

    queue<int> q;
    for(int i=0;i<n;i++){
        if(indeg[i]==0) q.push(i);
    }

    int cnt=0;

    while(!q.empty()){
        int u=q.front(); q.pop();
        cnt++;

        for(int v:g[u]){
            if(--indeg[v]==0) q.push(v);
        }
    }

    return cnt!=n;
}

//////////////////////////////////////////////////////////////////
// 6. LONGEST PATH IN DAG (USING TOPO)
//////////////////////////////////////////////////////////////////
vector<int> longestPathDAG(int n, int src){

    vector<int> topo = kahnTopo(n);

    vector<int> dist(n, INT_MIN);
    dist[src]=0;

    for(int u:topo){
        if(dist[u]==INT_MIN) continue;

        for(int v:g[u]){
            dist[v]=max(dist[v], dist[u]+1);
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 7. SHORTEST PATH IN DAG (USING TOPO)
//////////////////////////////////////////////////////////////////
vector<int> shortestPathDAG(int n, int src){

    vector<int> topo = kahnTopo(n);

    vector<int> dist(n, INT_MAX);
    dist[src]=0;

    for(int u:topo){
        if(dist[u]==INT_MAX) continue;

        for(int v:g[u]){
            dist[v]=min(dist[v], dist[u]+1);
        }
    }

    return dist;
}

//////////////////////////////////////////////////////////////////
// 8. TOPO SORT + DP TEMPLATE (MOST IMPORTANT PATTERN)
//////////////////////////////////////////////////////////////////
void topoDP(int n){

    vector<int> topo = kahnTopo(n);

    vector<int> dp(n,0);

    for(int u:topo){
        for(int v:g[u]){
            dp[v]=max(dp[v], dp[u]+1);
        }
    }

    cout<<"DP result:\n";
    for(int i=0;i<n;i++){
        cout<<dp[i]<<" ";
    }
    cout<<"\n";
}

//////////////////////////////////////////////////////////////////
// 9. MAIN
//////////////////////////////////////////////////////////////////
int main(){

    int n,m;
    cin>>n>>m;

    g.assign(n,{});

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v); // directed graph
    }

    // Example usage:

    vector<int> topo1 = kahnTopo(n);

    cout<<"Kahn Topo:\n";
    for(int x:topo1) cout<<x<<" ";
    cout<<"\n";

    vector<int> topo2 = topoDFS(n);

    cout<<"DFS Topo:\n";
    for(int x:topo2) cout<<x<<" ";
    cout<<"\n";

    if(hasCycle(n)){
        cout<<"Cycle exists\n";
    } else {
        cout<<"No cycle\n";
    }

    return 0;
}