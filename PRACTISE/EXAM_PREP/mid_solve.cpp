#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> disc, low, vis;
int timer;

vector<pair<int,int>> edges;

vector<pair<int,int>> bridges;

void dfsBridge(int u,int p){
    vis[u]=1;
    disc[u]=low[u]=++timer;

    for(int v:g[u]){

        if(v==p) continue;

        if(!vis[v]){
            dfsBridge(v,u);
            low[u]=min(low[u],low[v]);

            if(low[v]>disc[u]){
                bridges.push_back({u,v});
            }
        }
        else{
            low[u]=min(low[u],disc[v]);
        }
    }
}

void reset(int n){
    vis.assign(n,0);
    disc.assign(n,0);
    low.assign(n,0);
    timer=0;
}

bool hasBridge(int n){
    bridges.clear();
    reset(n);

    for(int i=0;i<n;i++){
        if(!vis[i]) dfsBridge(i,-1);
    }

    return !bridges.empty();
}

vector<pair<int,int>> criticalEdges(int n){

    vector<pair<int,int>> ans;

    for(auto [u,v]:edges){

        // remove edge u-v
        g[u].erase(remove(g[u].begin(),g[u].end(),v),g[u].end());
        g[v].erase(remove(g[v].begin(),g[v].end(),u),g[v].end());

        if(hasBridge(n)){
            ans.push_back({u,v});
        }

        // restore edge
        g[u].push_back(v);
        g[v].push_back(u);
    }

    return ans;
}

int main(){
    int n,m;
    cin>>n>>m;

    g.assign(n,{});

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;

        g[u].push_back(v);
        g[v].push_back(u);

        edges.push_back({u,v});
    }

    auto res = criticalEdges(n);

    cout<<"Edges whose removal creates at least one bridge:\n";
    for(auto [u,v]:res){
        cout<<u<<" "<<v<<"\n";
    }
}
#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> g;

void allTopo(int n,
             vector<int>&indeg,
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

int main(){

    int n,m;
    cin>>n>>m;

    g.assign(n,{});

    vector<int> indeg(n,0);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        indeg[v]++;
    }

    vector<int> vis(n,0), res;

    cout<<"All Topological Sort Orders:\n";
    allTopo(n,indeg,vis,res);
}