#include<bits/stdc++.h>
using namespace std;
void dfs(int node,vector<bool>&visited,vector<bool>&inprocess,vector<vector<int>>&adj,vector<pair<int,int>>&edges,vector<pair<int,int>>&treeedges,vector<pair<int,int>>&backedges,vector<int>&start,vector<int>&finish,int &time)
{
    if(!visited[node])
    {
        visited[node]=true;
        inprocess[node]=true;
        start[node]=time++;
        for(auto v:adj[node])
        {
            if(!visited[v])
            {
                treeedges.push_back({node,v});
                dfs(v,visited,inprocess,adj,edges,treeedges,backedges,start,finish,time);
            }
            else if(inprocess[v])
            {
                backedges.push_back({node,v});
            }
        }
        inprocess[node]=false;
        finish[node]=time++;
    }
}
int main()
{
    int N,m;
    int time=0;
    cin>>N>>m;
    vector<vector<int>>adj(N);
    vector<int>start(N),finish(N);
    vector<bool>visited(N,false);
    vector<bool>inprocess(N,false);
    vector<pair<int,int>>treeedges,backedges,frontedges,crossedges,edges;
    //vector<vector<int>>edges(N,vector<int>(N,-1));
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);//considering it as a 0 based index node and edges
        edges.push_back({u,v});
    }
    for(auto &it: adj)sort(it.begin(),it.end());
    for(int i=0;i<N;i++)
    {
        if(!visited[i])dfs(i,visited,inprocess,adj,edges,treeedges,backedges,start,finish,time);
    }
    set<pair<int,int>>treeedgeset(treeedges.begin(),treeedges.end());
    set<pair<int,int>>backedgeset(backedges.begin(),backedges.end());
    sort(edges.begin(),edges.end());
     for(auto it:edges)
     {
         if(treeedgeset.count({it.first,it.second}))continue;
         else if(backedgeset.count({it.first,it.second}))continue;
         else if(start[it.first]<start[it.second] && start[it.second]<finish[it.second] && finish[it.second]<finish[it.first])
         {
             frontedges.push_back({it.first,it.second});
         }
         else crossedges.push_back({it.first,it.second});
     }
     //for(auto it:treeedges)cout<<it.first<<" "<<it.second<<"\n";
     sort(frontedges.begin(),frontedges.end());
     sort(crossedges.begin(),crossedges.end());
     cout<<"u"<<" "<<"v"<<" "<<"type\n";
     for(auto it:edges)
     {
        if(treeedgeset.count({it.first,it.second}))cout<<it.first<<" "<<it.second<<" "<<"T\n";
        else if(backedgeset.count({it.first,it.second}))cout<<it.first<<" "<<it.second<<" "<<"B\n";
        else if(find(frontedges.begin(),frontedges.end(),it) != frontedges.end())cout<<it.first<<" "<<it.second<<" "<<"F\n";
        else cout<<it.first<<" "<<it.second<<" "<<"C\n";
     }

}