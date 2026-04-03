#include<bits/stdc++.h>
using namespace std;
void dfs(int node,vector<bool>&visited,vector<vector<int>>&adj,vector<int>&start,vector<int>&finish, int &time)
{
    visited[node]=true;
    //int m=1e9;
    start[node]=time++;
    for(auto v: adj[node])
    {
        if(!visited[v])
        {
    //         m=min(m,v);
    //     }
    // }
    // bool test=false;
    // if(m!=1e9)
    // {
        dfs(v,visited,adj,start,finish,time);
    }
}
    // else
    // {
        finish[node]=time++;
        //test=true;

    }
  // if(!test) finish[node]=time++;
int main()
{
    int n,m;
    cin>>n>>m;
    int time=1;
    vector<vector<int>>adj(n);
    vector<int>start(n);
    vector<int>finish(n);
    vector<bool>visited(n,false);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
         for(auto it:adj)
         {
             sort(it.begin(),it.end());
         }
    for(int i=0;i<n;i++)
    {
        if(!visited[i])
        {
        dfs(i,visited,adj,start,finish,time);
    }
}
    for(int i=0;i<n;i++)
    {
        cout<<i<<": "<<start[i]<<" "<<finish[i]<<"\n";
    }
}
