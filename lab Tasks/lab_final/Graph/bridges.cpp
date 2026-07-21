#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Instructor Problem: Bridges (undirected, Tarjan low-link) =====
int n, timer_;
vector<vector<int>> g;
vector<int> disc, low_;
vector<bool> visited_;
set<pair<int,int>> bridgeEdges;

void dfsBridge(int u,int parent){
    visited_[u]=true;
    disc[u]=low_[u]=timer_++;
    for(int v:g[u]){
        if(v==parent) continue;
        if(visited_[v]){
            low_[u]=min(low_[u],disc[v]);
        } else {
            dfsBridge(v,u);
            low_[u]=min(low_[u],low_[v]);
            if(low_[v]>disc[u]) bridgeEdges.insert({min(u,v),max(u,v)});
        }
    }
}

void muhtasim()
{
    int m; cin>>n>>m;
    g.assign(n,{});
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        g[u].push_back(v); g[v].push_back(u);
    }

    disc.assign(n,0); low_.assign(n,0); visited_.assign(n,false);
    bridgeEdges.clear(); timer_=0;
    for(int i=0;i<n;i++) if(!visited_[i]) dfsBridge(i,-1);

    for(auto &e:bridgeEdges) cout<<e.first<<" "<<e.second<<"\n";

    // ===== LC 1192: Critical Connections in a Network (LeetCode function signature) =====
    {
        int N=4;
        vector<vector<int>> connections={{0,1},{1,2},{2,0},{1,3}};
        vector<vector<int>> adj2(N);
        for(auto&c:connections){ adj2[c[0]].push_back(c[1]); adj2[c[1]].push_back(c[0]); }
        vector<int> d2(N,-1), l2(N,-1);
        vector<vector<int>> ans;
        int t2=0;
        function<void(int,int)> dfs2=[&](int u,int parent){
            d2[u]=l2[u]=t2++;
            for(int v:adj2[u]){
                if(v==parent) continue;
                if(d2[v]==-1){ dfs2(v,u); l2[u]=min(l2[u],l2[v]); if(l2[v]>d2[u]) ans.push_back({u,v}); }
                else l2[u]=min(l2[u],d2[v]);
            }
        };
        dfs2(0,-1);
        // known expected answer for this classic example: [[1,3]]
        cout<<"LC1192 CriticalConnections (expected [[1,3]]): ";
        for(auto&e:ans) cout<<"["<<e[0]<<","<<e[1]<<"] ";
        cout<<"\n";
    }

    // ===== GfG classic: two triangles joined by a single bridge edge =====
    {
        int N=6;
        vector<vector<int>> edges2={{0,1},{1,2},{2,0},{2,3},{3,4},{4,5},{5,3}};
        vector<vector<int>> adj2(N);
        for(auto&e:edges2){ adj2[e[0]].push_back(e[1]); adj2[e[1]].push_back(e[0]); }
        vector<int> d2(N,-1), l2(N,-1);
        vector<pair<int,int>> ans;
        int t2=0;
        function<void(int,int)> dfs2=[&](int u,int parent){
            d2[u]=l2[u]=t2++;
            for(int v:adj2[u]){
                if(v==parent) continue;
                if(d2[v]==-1){ dfs2(v,u); l2[u]=min(l2[u],l2[v]); if(l2[v]>d2[u]) ans.push_back({min(u,v),max(u,v)}); }
                else l2[u]=min(l2[u],d2[v]);
            }
        };
        dfs2(0,-1);
        cout<<"GfG two-triangles-one-bridge (expected 2-3): ";
        for(auto&e:ans) cout<<e.first<<"-"<<e.second<<" ";
        cout<<"\n";
    }
}

int main()
{
ios::sync_with_stdio(false);
cin.tie(nullptr);
ll tests;
cin>>tests;
while(tests--)
{
muhtasim();
}
}
