#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>>adj(n);
    vector<bool>visited(n,false);
    vector<int>dist(n,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    vector<int>parent(n,-1);
    vector<int>path;
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    for(int i=0;i<n;i++)
    {
        sort(adj[i].begin(),adj[i].end());
    }
    dist[0]=0;
    pq.push({0,0});
    while(!pq.empty())
    {
        int d=pq.top().first;
        int node=pq.top().second;
        pq.pop();
        if(d>dist[node])continue;
        visited[node]=true;
        for(auto v: adj[node])
        {
            int d1=v.second;
            int node1=v.first;
            if(!visited[node1])
            {
                if(d1+dist[node]<dist[node1])
                {
                    pq.push({d1+dist[node1],node1});\
                    dist[node1]=d1+dist[node];
                    parent[node1]=node;
                }
                else if (d1+dist[node]==dist[node1] && node1<node )
                {
                    parent[node1]=min(parent[node1],node);
                }
            }
        }
    }
    if(dist[1]==INT_MAX)cout<<"Not Reachable\n";
    else 
    {
        int cur=1;
        path.push_back(1);
        while(parent[cur]!=-1)
        {
            path.push_back(parent[cur]);
            cur=parent[cur];
        }
        reverse(path.begin(),path.end());
        for(auto x: path)cout<<x<<"\n";
    }

}