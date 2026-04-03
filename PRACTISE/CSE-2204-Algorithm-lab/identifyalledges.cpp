#include<bits/stdc++.h>
using namespace std;
void dfs(int node, vector<vector<int>>&adj, vector<bool>&visited,vector<pair<int,int>>&treeedges,vector<pair<int,int>>&backedges,vector<bool>&inprocess,vector<pair<int,int>>&edges,int &time, vector<int>&start,vector<int>&finish)
{
    visited[node]=true;
    inprocess[node]=true;
    start[node]=time++;
    for(auto v: adj[node])
    {
        if(!visited[v])
        {
            treeedges.push_back({node,v});
            dfs(v,adj,visited,treeedges,backedges,inprocess,edges,time,start,finish);
        }
        else if(inprocess[v])backedges.push_back({node,v});
    }
    finish[node]=time++;
    inprocess[node]=false;
}
int main()
{
    int n,m,time=0;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    vector<bool>visited(n,false),inprocess(n,false);
    vector<int>start(n),finish(n);
    vector<pair<int,int>>treeedges,backedges,frontedges,crossedges,edges;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        //adj[v].push_back(u); --. coz front and cross edges only for the directed graph
        edges.push_back({u,v});
    }
    for(auto &it: adj)
    {
        sort(it.begin(),it.end());
    }
    for(int i=0;i<n;i++)
    {
        if(!visited[i])dfs(i,adj,visited,treeedges,backedges,inprocess,edges,time,start,finish);
    }
    set<pair<int,int>>treeedgeset(treeedges.begin(),treeedges.end());
    set<pair<int,int>>backedgeset(backedges.begin(),backedges.end());
    for(auto x: edges)
    {
        if(treeedgeset.count({x.first,x.second}))continue;
        else if (backedgeset.count({x.first,x.second}))continue;
        if(start[x.first]<start[x.second] && start[x.second]<finish[x.second] && finish[x.second]<finish[x.first])
        {
            frontedges.push_back({x.first,x.second});
        }
        else crossedges.push_back({x.first,x.second});
    }
    cout<<"Treeedges are:\n";
    for(auto x:treeedgeset)cout<<x.first<<" "<<x.second<<"\n";
    cout<<"Backedges are:\n";
    for(auto x:backedgeset)cout<<x.first<<" "<<x.second<<"\n";
    cout<<"Frontedges are:\n";
    for(auto x:frontedges)cout<<x.first<<" "<<x.second<<"\n";
    cout<<"Crossedges are:\n";
    for(auto x:crossedges)cout<<x.first<<" "<<x.second<<"\n";

}