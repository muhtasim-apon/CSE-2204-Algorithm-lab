#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,src;
    cin>>n>>m;
    vector<vector<pair<int,int>>>adj(n+1);
    vector<vector<int>>times;
       priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
       vector<int>dist(n,INT_MAX);
       vector<bool>visited(n,false);
       while(m--)
       {
        int u,v,w;
        cin>>u>>v>>w;
        times.push_back({u,v,w});
        if(w<0)
        {
            cout<<"Negative Edge Detected.Dijsktra Algo Failed.\n";
            return 0;
        }
       }
       for(int i=0;i<times.size();i++)
       {
        adj[times[i][0]].push_back({times[i][1],times[i][2]});
        //adj[times[i][1]].push_back({times[i][0],times[i][2]});
       }
       cin>>src;
        dist[src]=0;
         int ans=0;
        pq.push({dist[src],src});
        while(!pq.empty())
        {
            int d=pq.top().first;
            int u=pq.top().second;
            pq.pop();
            if(d>dist[u])continue;
            visited[u]=true;
            for(auto v:adj[u])
            {
                int v1=v.first;
                int w=v.second;
                if(!visited[v1] && dist[u]+w<dist[v1])
                {
                dist[v1]=d+w;
                pq.push({dist[v1],v1});
            }
        }
        }
        for(auto x:dist)cout<<x<<" ";
       } 