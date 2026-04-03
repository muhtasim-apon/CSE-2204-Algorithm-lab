#include<bits/stdc++.h>
using namespace std;
void dfs(int node, vector<vector<int>>&adj, vector<bool>&visited,vector<vector<int>>&edges)
{
    visited[node]=true;
    for(auto v: adj[node])
    {
        if(!visited[v])
        {
            edges[node][v]=1;
            edges[v][node]=1;
            dfs(v,adj,visited,edges);
        }
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>adj(n);
    vector<vector<int>>edges(n,vector<int>(n,-1));
    vector<bool>visited(n,false);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[u][v]=0;
    }
    for(auto &it: adj)
    {
        sort(it.begin(),it.end());
    }
    for(int i=0;i<n;i++)
    {
        if(!visited[i])dfs(i,adj,visited,edges);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(edges[i][j]==0)
            {
                auto it1=find(adj[i].begin(),adj[i].end(),j);
                if(it1!=adj[i].end())adj[i].erase(it1);
                auto it2=find(adj[j].begin(),adj[j].end(),i);
                if(it2!=adj[j].end())adj[j].erase(it2);

            }
        }
    }

}