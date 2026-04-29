#include<bits/stdc++.h>
using namespace std;
void findarticularpoints(int u,vector<vector<int>>&adj,vector<bool>&visited,vector<int>&disc,vector<int>&low,set<int>&articular_points,int &time,vector<int>&parent,int root)
{
    int child=0;
    disc[u]=low[u]=time++;
    visited[u]=true;
    for(auto v:adj[u])
    {
        if(!visited[v])
        {
            child++;
            parent[v]=u;
            findarticularpoints(v,adj,visited,disc,low,articular_points,time,parent,root);
            low[u]=min(low[u],low[v]);
            if( u!=root && low[v]>=disc[u])articular_points.insert(u);
        }
        else
        {
            if(v!=parent[u])low[u]=min(low[u],disc[v]);
        }
        if(u==root && child>=2)articular_points.insert(u);
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
    //vector<pair<int,int>>articular_points;
    set<int>articular_points;
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
            int root =i;
            findarticularpoints(i,adj,visited,disc,low,articular_points,time,parent,root);
        }
    }
    //sort(articular_points.begin(),articular_points.end());
    for(auto x: articular_points)cout<<x<<"\n";
    
}