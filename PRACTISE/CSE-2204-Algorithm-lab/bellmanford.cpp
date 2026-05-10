#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>edges;
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w});
    }
    vector<int>dist(n+1,INT_MAX);
    int src;
    cin>>src;
    dist[src]=0;
    for(int i=0;i<n-1;i++)
    {
    for(auto it:edges)
    {
        int u=it[0];
        int v=it[1];
        int w=it[2];
        if(dist[u]!=INT_MAX && dist[u]+w<dist[v])
        {
            dist[v]=dist[u]+w;
        }
    }
}
 for(auto it:edges)
    {
        int u=it[0];
        int v=it[1];
        int w=it[2];
        if(dist[u]!=INT_MAX && dist[u]+w<dist[v])
        {
            cout<<"Negative Cycle Detected.BellMan Ford Failed\n";
            return 0;
        }
    }
for(auto x: dist)cout<<x<<"\n";
}