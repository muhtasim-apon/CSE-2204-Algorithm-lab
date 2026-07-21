#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Instructor Problem: Articulation Points (undirected, Tarjan low-link) =====
int n, timer_;
vector<vector<int>> g;
vector<int> disc, low_;
vector<bool> visited_;
set<int> articulationPoints;
set<pair<int,int>> bridgeEdges;

void dfsAP(int u,int parent){
    visited_[u]=true;
    disc[u]=low_[u]=timer_++;
    int children=0;
    for(int v:g[u]){
        if(v==parent) continue;
        if(visited_[v]){
            low_[u]=min(low_[u],disc[v]);
        } else {
            children++;
            dfsAP(v,u);
            low_[u]=min(low_[u],low_[v]);
            if(low_[v]>disc[u]) bridgeEdges.insert({min(u,v),max(u,v)});
            if(parent!=-1 && low_[v]>=disc[u]) articulationPoints.insert(u);
            if(parent==-1 && children>1) articulationPoints.insert(u);
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
    articulationPoints.clear(); bridgeEdges.clear(); timer_=0;
    for(int i=0;i<n;i++) if(!visited_[i]) dfsAP(i,-1);

    for(int x:articulationPoints) cout<<x<<"\n";

    // ===== Shared low-link machinery: bridges found for free in same pass =====
    cout<<"Bridges found in the same pass: ";
    for(auto &e:bridgeEdges) cout<<e.first<<"-"<<e.second<<" ";
    cout<<"\n";

    // ===== Root-vs-non-root articulation rule demo =====
    cout<<"(Root is an articulation point only if it has >1 DFS-tree children; "
          "non-root u is one if some child v has low[v] >= disc[u].)\n";

    // ===== LC 1192: Critical Connections in a Network (bridges via same algorithm) =====
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
        cout<<"LC1192 CriticalConnections: ";
        for(auto&e:ans) cout<<"["<<e[0]<<","<<e[1]<<"] ";
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
