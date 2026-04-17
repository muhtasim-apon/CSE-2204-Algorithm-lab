#include<bits/stdc++.h>
using namespace std;
void dfs1(int node, vector<vector<int>>&adj,vector<bool>&visited1,stack<int>&st)
{
    visited1[node]=true;
    for(auto v: adj[node])
    {
        if(!visited1[v])dfs1(v,adj,visited1,st);
    }
    st.push(node);
}
void dfs2(int node, vector<vector<int>>&adjT,vector<bool>&visited2)
{
    visited2[node]=true;
    for(auto v: adjT[node])
    {
        if(!visited2[v])dfs2(v,adjT,visited2);
    }
    //st.push(node);
}
int main()
{
    int n,m,ans=0;
    cin>>n>>m;
    vector<vector<int>>adj(n),adjT(n);
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adj[u-1].push_back(v-1);
        adjT[v-1].push_back(u-1);
    }
    // for(auto it:adj)sort(it.begin(),it.end());
    // for(auto it:adjT)sort(it.begin(),it.end());
    vector<bool>visited1(n,false),visited2(n,false);
    stack<int>st;
    for(int i=0;i<n;i++)
    {
    if(!visited1[i])dfs1(i,adj,visited1,st);
    }
    while(!st.empty())
    {
        int u=st.top();
        st.pop();
        if(!visited2[u])
        {
            ans++;
            dfs2(u,adjT,visited2);
    }
}
cout<<ans<<"\n";
}
