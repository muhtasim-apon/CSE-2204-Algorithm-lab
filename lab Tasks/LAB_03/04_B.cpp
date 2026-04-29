#include<bits/stdc++.h>
using namespace std;
void dfs(int u,vector<vector<int>>&adj,vector<bool>&visited,vector<bool>&inprocess,vector<pair<pair<int,int>,int>>&edges,vector<int>&disc,int &time)
{
    disc[u]=time++;
   inprocess[u]=visited[u]=true;
    for(auto v: adj[u])
    {
        if(!visited[v])
        {edges.push_back({{u,v},1});
        dfs(v,adj,visited,inprocess,edges,disc,time);
    }
    else if(inprocess[v])edges.push_back({{u,v},2});
    else if(disc[u]<disc[v])edges.push_back({{u,v},3});
    else edges.push_back({{u,v},4});
    }
    inprocess[u]=false;
}
int main()
{
    int N,M;
    cin>>N>>M;
    vector<bool>visited(N,false),inprocess(N,false);
    vector<pair<pair<int,int>,int>>edges;
    vector<vector<int>>adj(N);
    vector<int>disc(N);
    int time=0;
    while(M--)
    {
        int U,V;
        cin>>U>>V;
        adj[U].push_back(V);
        //adj[V].push_back(U);
    }
    for(int i=0;i<N;i++)
    {
        if(!visited[i])
        {
            dfs(i,adj,visited,inprocess,edges,disc,time);
        }
    }
    sort(edges.begin(),edges.end());
    for(auto x: edges)
    {
        int u=x.first.first;
        int v=x.first.second;
        if(x.second==1)cout<<u<<" "<<v<<" (T)\n";
        else if(x.second==2)cout<<u<<" "<<v<<" (B)\n";
        else if(x.second==3)cout<<u<<" "<<v<<" (F)\n";
        else cout<<u<<" "<<v<<" (C)\n";
    }
}