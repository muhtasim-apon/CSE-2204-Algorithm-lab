#include<bits/stdc++.h>
using namespace std;
#define ll long long
void dfs(int u,vector<vector<int>>&adj,vector<bool>&visited,bool &iscycle,map<int,int>&parent,vector<pair<int,int>>&bridges,int &time,vector<pair<int,int>>&treeedge,vector<pair<int,int>>&backedge,set<int>&articulation_point,vector<int>&disco,vector<int>&low,int root)
{
    low[u]=disco[u]=time++;
    visited[u]=true;
    int child=0;
    for(auto v:adj[u])
    {
        if(!visited[v])
        {
            child++;
            parent[v]=u;
            treeedge.push_back({u,v});
            dfs(v,adj,visited,iscycle,parent,bridges,time,treeedge,backedge,articulation_point,disco,low,root);
            low[u]=min(low[u],low[v]);
            if(low[v]>=disco[u] && u!=root)articulation_point.insert(u);
       // else if(u==root && child>=2)articulation_point.push_back(u);
        if(low[v]>disco[u])bridges.push_back({u,v});
       // else if(u==root && child>=2)bridges.push_back({u,v});//bridge does not depend on loop
        }
       else if(visited[v] && parent[u]!=v )
        {
            iscycle=true;
            if(disco[v]<disco[u])backedge.push_back({u,v});
            low[u]=min(low[u],disco[v]);
        }
       // if(u==root && child>=2)articulation_point.insert(u);
    }
    if(u==root && child>=2)articulation_point.insert(u);
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    int num_cc=0;
    vector<pair<int,int>>bridges,treeedge,backedge;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adj[v-1].push_back(u-1);
        //bridges.push_back({u-1,v-1});
    }
    for(auto &it:adj)sort(it.begin(),it.end());
    vector<bool>visited(n,false);
    map<int ,int>parent;
    bool iscycle=false;
    int time=0;
    set<int>articulation_point;
    vector<int>disco(n),low(n);
    for(int i=0;i<n;i++)
    {
        //num_cc++;
       //int root=i;
        if(!visited[i])
        {
            num_cc++;
            int root=i;
            parent[i]=-1;
        dfs(i,adj,visited,iscycle,parent,bridges,time,treeedge,backedge,articulation_point,disco,low,root);
    }
}
    cout<<"number of connected components: "<<num_cc<<"\n";
    if(iscycle)cout<<"Cycle Detected\n";
    sort(treeedge.begin(),treeedge.end());
    cout<<"Treeedges are:\n";
    for(auto x: treeedge)cout<<x.first<<" "<<x.second<<"\n";
    cout<<"Backedges are:\n";
    for(auto x: backedge)cout<<x.first<<" "<<x.second<<"\n";
    cout<<"Articulation point:\n";
    for(auto x: articulation_point)cout<<x<<" ";
    cout<<"\n";
    cout<<"Bridges are:\n";
    sort(bridges.begin(),bridges.end());
    for(auto x: bridges)cout<<x.first<<" "<<x.second<<"\n";
    
}