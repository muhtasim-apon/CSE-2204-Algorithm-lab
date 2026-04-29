#include<bits/stdc++.h>
using namespace std;
void dfs1(int u,vector<vector<int>>&adj,vector<bool>&visited1,stack<int>&st)
{
    visited1[u]=true;
    for(auto v: adj[u])
    {
        if(!visited1[v])dfs1(v,adj,visited1,st);
    }
    st.push(u);
}
// void dfs2(int u, vector<vector<int>>&adjT,vector<bool>&visited2,vector<int>&nodes)
// {
//     visited2[u]=true;
//     nodes.push_back(u);
//     for(auto v:adjT[u])
//     {
//         if(!visited2[v])dfs2(v,adjT,visited2,nodes);
//     }
// }
int main()
{
    int N,M;
    cin>>N>>M;
    stack<int>st;
    vector<bool>visited1(N,false);//,visited2(N,false);
    vector<vector<int>>adj(N);//adjT(N);
    vector<int>nodes;
    while(M--)
    {
        int U,V;
        cin>>U>>V;
        adj[U].push_back(V);
       // adjT[V].push_back(U);
    }
    //for(auto &it: adj)sort(it.begin(),it.end());
    for(int i=0;i<N;i++)
    {
        if(!visited1[i])
        {
            dfs1(i,adj,visited1,st);
        }
    }
    while(!st.empty())
    {
      //int node=st.top();
     // nodes.push_back(st.top());
     cout<<st.top()<<"\n";
      st.pop();
    //   if(!visited2[node])
    //   {
    //     dfs2(node,adjT,visited2,nodes);
    //   for(auto x: nodes)cout<<x<<" ";
    //   cout<<"\n";
    // }
}
//reverse(nodes.begin(),nodes.end());
//for(auto x: nodes)cout<<x<<"\n";
}