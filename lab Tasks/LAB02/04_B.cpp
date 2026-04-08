#include<bits/stdc++.h>
using namespace std;
void topologicalsort(int node, vector<bool>&visited,vector<vector<int>>&adj,stack<int>&st)
{
    if(!visited[node])visited[node]=true;
    for(auto v: adj[node])
    {
        if(!visited[v])topologicalsort(v,visited,adj,st);
    }
    st.push(node);
}
int main()
{
    int N,m;
    cin>>N>>m;
    vector<vector<int>>adj(N);
    vector<bool>visited(N,false);
    stack<int>st;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);//considering it as a 0 based index of nodes and edges
    }
    for(auto &it:adj)sort(it.begin(),it.end());
    // int src;
    // cin>>src;
    for(int i=0;i<N;i++)
    {
        if(!visited[i])topologicalsort(i5,visited,adj,st);
    }
    //if i want any type of odering , then i have to comment out the upper line in here. so no ascending order is needed btw.
    cout<<"Topological Order is:\n";
    while(!st.empty())
    {
        int node=st.top();
        cout<<node<<" ";
        st.pop();
    }
}