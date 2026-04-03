#include<bits/stdc++.h>
using namespace std;
void dfs(int node, vector<vector<int>>&adj, vector<bool>&visited,vector<bool>&inprocess,bool &iscycle)
{
    visited[node]=true;
    //if(inprocess[node])iscycle=true;
    inprocess[node]=true;
    for(auto v: adj[node])
    {
        if(!visited[v])dfs(v,adj,visited,inprocess,iscycle);
        else if(inprocess[v])iscycle=true;
    }
    inprocess[node]=false;
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    vector<bool>visited(n,false);
    vector<bool>inprocess(n,false);
    bool iscycle=false;
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        //adj[v].push_back(u);
    }
    for(auto &it: adj)
    {
        sort(it.begin(),it.end());
    }
    for(int i=0;i<n;i++)
    {
        if(!visited[i])dfs(i,adj,visited,inprocess,iscycle);
    }
    if(iscycle)
    {
        cout<<"Cycle Detected\n";
    }
    else
    {
        cout<<"No Cycle Detected\n";
    }

}