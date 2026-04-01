#include<bits/stdc++.h>
using namespace std;
void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &start, vector<int> &finish, int &time)
{
    visited[node]=true;
    start[node]=time++;
    for(auto v: adj[node])
    {
        if(!visited[v])
        {
            dfs(v,adj,visited,start,finish,time);
        }
    }
    finish[node]=time++;
}
int main()
{
    cout<<"Number of Nodes in the graph:\n";
    int n;
    cin>>n;
    cout<<"Number of Edges in the graph:\n";
    int m;
    cin>>m;
    vector<vector<int>> adj(n);
    cout<<"Enter the edges in the graph:\n";
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int time=0;
    vector<int> start(n),finish(n);
    vector<bool>visited(n,false);
    dfs(0,adj,visited,start,finish,time);
    cout<<"Start Time:\n";
    for(int i=0;i<n;i++)
    {
        cout<<i<<" "<<start[i]<<"\n";
    }
    cout<<"Finish Time:\n";
    for(int i=0;i<n;i++)
    {
        cout<<i<<" "<<finish[i]<<"\n";
    }
}