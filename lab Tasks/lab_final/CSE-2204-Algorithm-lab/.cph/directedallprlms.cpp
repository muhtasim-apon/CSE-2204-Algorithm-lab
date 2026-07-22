#include<bits/stdc++.h>
using namespace std;
#define ll long long
void dfs(int u,vector<vector<int>>&adj,vector<bool>&visited,bool &iscycle,int &time,vector<pair<int,int>>&treeedge,vector<pair<int,int>>&backedge,vector<pair<int,int>>&frontedge,vector<pair<int,int>>&crossedge,vector<int>&disco,vector<int>&finish,vector<bool>&inprocess,stack<int>&st)
{
    //low[u]=disco[u]=time++;
    disco[u]=time++;
    visited[u]=true;
    inprocess[u]=true;
    //int child=0;
    for(auto v:adj[u])
    {
        if(!visited[v])
        {
            //child++;
            //parent[v]=u;
            treeedge.push_back({u,v});
            dfs(v,adj,visited,iscycle,time,treeedge,backedge,frontedge,crossedge,disco,finish,inprocess,st);
           // low[u]=min(low[u],low[v]);
            //if(low[v]>=disco[u] && u!=root)articulation_point.insert(u);
       // else if(u==root && child>=2)articulation_point.push_back(u);
        //if(low[v]>disco[u])bridges.push_back({u,v});
       // else if(u==root && child>=2)bridges.push_back({u,v});//bridge does not depend on loop
        }
       else if(inprocess[v])
        {
            iscycle=true;
            if(disco[v]<disco[u])backedge.push_back({u,v});
            //low[u]=min(low[u],disco[v]);
        }
        else if(disco[u]<disco[v])frontedge.push_back({u,v});
        else crossedge.push_back({u,v});
       // if(u==root && child>=2)articulation_point.insert(u);
    }
    inprocess[u]=false;
    finish[u]=time++;
    //if(u==root && child>=2)articulation_point.insert(u);
    st.push(u);
}
void dfs1(int u,vector<vector<int>>&adjT,vector<bool>&visited1)
{
    visited1[u]=true;
    for(auto v: adjT[u])
    {
        if(!visited1[v])dfs1(v,adjT,visited1);
    }
}

int main()
{
    int n,m;
    cin>>n>>m;
    stack<int>st;
    vector<vector<int>>adj(n),adjT(n);
    int num_scc=0;
    vector<pair<int,int>>treeedge,backedge,frontedge,crossedge;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adjT[v-1].push_back(u-1);
       // adj[v-1].push_back(u-1);
        //bridges.push_back({u-1,v-1});
    }
    for(auto &it:adj)sort(it.begin(),it.end());
    vector<bool>visited(n,false),inprocess(n,false),visited1(n,false);
   // map<int,int>parent;
    bool iscycle=false;
    int time=0;
    //set<int>articulation_point;
    vector<int>disco(n),finish(n);
    for(int i=0;i<n;i++)
    {
        //num_cc++;
       //int root=i;
        if(!visited[i])
        {
            //num_scc++;
            //int root=i;
            //parent[i]=-1;
        dfs(i,adj,visited,iscycle,time,treeedge,backedge,frontedge,crossedge,disco,finish,inprocess,st);
    }
}
        //num_cc++;
       //int root=i;
        while(!st.empty())
        {
            int u=st.top();
            st.pop();
            //num_scc++;
            //int root=i;
            //parent[i]=-1;
        if(!visited1[u])
        {
            num_scc++;   
            dfs1(u,adjT,visited1);
    }
}
    cout<<"number of strongly connected components: "<<num_scc<<"\n";
    if(iscycle)cout<<"Cycle Detected\n";
    sort(treeedge.begin(),treeedge.end());
    cout<<"Treeedges are:\n";
    for(auto x: treeedge)cout<<x.first<<" "<<x.second<<"\n";
    cout<<"Backedges are:\n";
    for(auto x: backedge)cout<<x.first<<" "<<x.second<<"\n";
    cout<<"Frontedges are:\n";
    sort(frontedge.begin(),frontedge.end());
    for(auto x: frontedge)cout<<x.first<<" "<<x.second<<"\n";
    //for(auto x: articulation_point)cout<<x<<" ";
    //cout<<"\n";
    cout<<"Crossedges are:\n";
    sort(crossedge.begin(),crossedge.end());
    //sort(bridges.begin(),bridges.end());
    for(auto x: crossedge)cout<<x.first<<" "<<x.second<<"\n";
} 