#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Biconnected Components (BCC): edge-stack + Tarjan low-link =====
// Note: BCC has no direct popular LeetCode problem (it's a GfG/CLRS staple);
// this file cross-references it against articulation points found in the
// same pass, since AP == vertices shared by >=2 BCCs.

int n, timer_;
vector<vector<pair<int,int>>> g; // (neighbor, edge id)
vector<int> disc, low_;
vector<bool> visited_;
stack<pair<int,int>> edgeStack;
vector<vector<pair<int,int>>> bccs;
set<int> articulationPoints;

void dfsBCC(int u,int parentEdge){
    visited_[u]=true;
    disc[u]=low_[u]=timer_++;
    int children=0;
    for(auto [v,eid]:g[u]){
        if(eid==parentEdge) continue;
        if(!visited_[v]){
            children++;
            edgeStack.push({u,v});
            dfsBCC(v,eid);
            low_[u]=min(low_[u],low_[v]);
            if((disc[u]==0 && children>1) || (disc[u]!=0 && low_[v]>=disc[u])){
                if(disc[u]==0 ? children>1 : true) if(disc[u]!=0) articulationPoints.insert(u);
                vector<pair<int,int>> comp;
                while(!edgeStack.empty() && edgeStack.top()!=make_pair(u,v)){
                    comp.push_back(edgeStack.top()); edgeStack.pop();
                }
                if(!edgeStack.empty()){ comp.push_back(edgeStack.top()); edgeStack.pop(); }
                bccs.push_back(comp);
            }
        } else if(disc[v]<disc[u]){
            edgeStack.push({u,v});
            low_[u]=min(low_[u],disc[v]);
        }
    }
    if(disc[u]==0 && children>1) articulationPoints.insert(u);
}

void muhtasim()
{
    int m; cin>>n>>m;
    g.assign(n,{});
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        g[u].push_back({v,i});
        g[v].push_back({u,i});
    }

    disc.assign(n,0); low_.assign(n,0); visited_.assign(n,false);
    timer_=0; bccs.clear(); articulationPoints.clear();
    while(!edgeStack.empty()) edgeStack.pop();

    for(int i=0;i<n;i++){
        if(!visited_[i]){
            dfsBCC(i,-1);
            if(!edgeStack.empty()){
                vector<pair<int,int>> comp;
                while(!edgeStack.empty()){ comp.push_back(edgeStack.top()); edgeStack.pop(); }
                bccs.push_back(comp);
            }
        }
    }

    cout<<"Number of biconnected components: "<<bccs.size()<<"\n";
    for(int i=0;i<(int)bccs.size();i++){
        cout<<"BCC "<<i<<": ";
        for(auto&e:bccs[i]) cout<<"("<<e.first<<"-"<<e.second<<") ";
        cout<<"\n";
    }
    cout<<"Articulation points (shared by >=2 BCCs): ";
    for(int x:articulationPoints) cout<<x<<" ";
    cout<<"\n";

    // ===== GfG classic example: one articulation point splitting graph into 2 BCCs =====
    // Graph: triangle {0,1,2} joined at vertex 2 to a second triangle {2,3,4}.
    // Expected: 2 biconnected components, articulation point = {2}.
    {
        int N=5;
        vector<vector<pair<int,int>>> g2(N);
        vector<array<int,2>> edges2={{0,1},{1,2},{2,0},{2,3},{3,4},{4,2}};
        for(int i=0;i<(int)edges2.size();i++){ g2[edges2[i][0]].push_back({edges2[i][1],i}); g2[edges2[i][1]].push_back({edges2[i][0],i}); }
        vector<int> d2(N,-1), l2(N,-1);
        int t2=0;
        set<int> ap2;
        function<void(int,int,int)> dfs2=[&](int u,int parentEdge,int depth)->void{
            d2[u]=l2[u]=t2++;
            int children=0;
            for(auto [v,eid]:g2[u]){
                if(eid==parentEdge) continue;
                if(d2[v]==-1){
                    children++;
                    dfs2(v,eid,depth+1);
                    l2[u]=min(l2[u],l2[v]);
                    if(depth>0 && l2[v]>=d2[u]) ap2.insert(u);
                } else l2[u]=min(l2[u],d2[v]);
            }
            if(depth==0 && children>1) ap2.insert(u);
        };
        dfs2(0,-1,0);
        cout<<"GfG two-triangles-sharing-vertex-2 articulation points (expected {2}): ";
        for(int x:ap2) cout<<x<<" ";
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
