#include<bits/stdc++.h>
using namespace std;
    void dfs(int node, vector<bool>&visited,vector<vector<int>>&edges,int &time,vector<int>&start,vector<int>&low,int parent,set<int>&articularpoint)
    {
        visited[node]=true;
        start[node]=time;
        low[node]=time;
        time++;
        int child=0;
        for(auto it : edges[node])
        {
            if(it==parent)continue;
            if(!visited[it] && it!=parent)
            {
                child++;
                dfs(it,visited,edges,time,start,low,node,articularpoint);
                low[node]=min(low[node],low[it]);
                if(low[it]>=start[node] && parent!=-1)articularpoint.insert(node);
            }
            else
            {
                low[node]=min(low[node],start[it]);
            }

        }
        if(child>1 && parent==-1)articularpoint.insert(node);
    }
    int main()
    {
        int n,m;
        cin>>n>>m;
        vector<vector<int>>edges(n);
        while(m--)
        {
         int u,v;
         cin>>u>>v;
         edges[u].push_back(v);
         edges[v].push_back(u);
        }
       // vector<vector<int>>edges(n);
       // vector<vector<int>>bridges;
        vector<int>start(n),low(n);
        vector<bool>visited(n,false);
        set<int>articularpoint;
        int time=0;
        // for(int i=0;i<connections.size();i++)
        // {
        //     edges[connections[i][0]].push_back(connections[i][1]);
        //     edges[connections[i][1]].push_back(connections[i][0]);
        // }
        for(auto &it:edges)sort(it.begin(),it.end());
        int parent=-1;
        for(int i=0;i<n;i++)
        {
            if(!visited[i])dfs(i,visited,edges,time,start,low,parent,articularpoint);
        }
        for(auto x: articularpoint)cout<<x<<" ";
    }