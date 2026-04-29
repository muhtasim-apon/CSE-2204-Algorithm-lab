#include<bits/stdc++.h>
using namespace std;
void findbridges(int u,vector<vector<int>>&adj,vector<bool>&visited,vector<int>&disc,vector<int>&low,vector<pair<int,int>>&bridges,int &time,vector<int>&parent)
{
    disc[u]=low[u]=time++;
    visited[u]=true;
    for(auto v:adj[u])
    {
        if(!visited[v])
        {
            parent[v]=u;
            findbridges(v,adj,visited,disc,low,bridges,time,parent);
            low[u]=min(low[u],low[v]);
            if(low[v]>disc[u])bridges.push_back({u,v});
        }
        else
        {
            if(v!=parent[u])low[u]=min(low[u],disc[v]);
        }
    }
}
int main()
{
    int N,M;
    cin>>N>>M;
    int time=0;
    vector<vector<int>>adj(N);
    vector<int>disc(N),low(N);
    vector<int>parent(N,-1);
    vector<pair<int,int>>bridges;
    vector<bool>visited(N,false);
    while(M--)
    {
        int U,V;
        cin>>U>>V;
        adj[U].push_back(V);
        adj[V].push_back(U);
    }
    for(int i=0;i<N;i++)
    {
        if(!visited[i])
        {
            findbridges(i,adj,visited,disc,low,bridges,time,parent);
        }
    }
    sort(bridges.begin(),bridges.end());
    for(auto x: bridges)cout<<x.first<<" "<<x.second<<"\n";
    
}