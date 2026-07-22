include<bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector<pair<ll,int>>>adj(n);
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u-1].push_back({v-1,w});
        adj[v-1].push_back({u-1,w});
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>pq;
    int src;
    cin>>src;
    src--;
    vector<ll>dist(n,1e18);
    dist[src]=0;
    pq.push({0,src});
    while(!pq.empty())
    {
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u])
        {
            if(dist[v]>dist[u]+w)
            {dist[v]=dist[u]+w;
            pq.push({dist[v],v});
        }
    }
    }
    for(int i=0;i<n;i++)
    {
        if(dist[i]==1e18)cout<<"Unreachable\n";
        else cout<<dist[i]<<"\n";
    }
}