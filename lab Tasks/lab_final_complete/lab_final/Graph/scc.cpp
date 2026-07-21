#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Instructor Problem: Strongly Connected Components (Kosaraju's) =====
int n;
vector<vector<int>> g, rg;
vector<int> order_, comp;
vector<bool> vis;

void dfs1(int u){
    vis[u]=true;
    for(int v:g[u]) if(!vis[v]) dfs1(v);
    order_.push_back(u);
}
void dfs2(int u,int c){
    comp[u]=c;
    for(int v:rg[u]) if(comp[v]==-1) dfs2(v,c);
}

vector<vector<int>> kosaraju(){
    vis.assign(n,false); order_.clear();
    for(int i=0;i<n;i++) if(!vis[i]) dfs1(i);
    comp.assign(n,-1);
    int c=0;
    for(int i=n-1;i>=0;i--){
        int u=order_[i];
        if(comp[u]==-1){ dfs2(u,c); c++; }
    }
    vector<vector<int>> sccs(c);
    for(int i=0;i<n;i++) sccs[comp[i]].push_back(i);
    return sccs;
}

// ===== Tarjan's SCC (single-pass low-link), cross-checked against Kosaraju =====
vector<int> disc, low_;
vector<bool> onStack;
stack<int> stk;
int timer_;
vector<vector<int>> tarjanSCCs;

void tarjanDfs(int u){
    disc[u]=low_[u]=timer_++;
    stk.push(u); onStack[u]=true;
    for(int v:g[u]){
        if(disc[v]==-1){ tarjanDfs(v); low_[u]=min(low_[u],low_[v]); }
        else if(onStack[v]) low_[u]=min(low_[u],disc[v]);
    }
    if(low_[u]==disc[u]){
        vector<int> comp_;
        while(true){
            int v=stk.top(); stk.pop(); onStack[v]=false;
            comp_.push_back(v);
            if(v==u) break;
        }
        tarjanSCCs.push_back(comp_);
    }
}

void muhtasim()
{
    int m; cin>>n>>m;
    g.assign(n,{}); rg.assign(n,{});
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    auto sccs = kosaraju();
    for(auto &c:sccs){
        for(int i=0;i<(int)c.size();i++) cout<<c[i]<<" \n"[i+1==(int)c.size()];
    }

    // ===== Tarjan's SCC cross-check (order may differ from Kosaraju's) =====
    disc.assign(n,-1); low_.assign(n,-1); onStack.assign(n,false);
    timer_=0; tarjanSCCs.clear();
    for(int i=0;i<n;i++) if(disc[i]==-1) tarjanDfs(i);
    cout<<"Tarjan SCC count: "<<tarjanSCCs.size()<<" (Kosaraju also found "<<sccs.size()<<")\n";

    // ===== Condensation graph (DAG of SCCs) =====
    {
        set<pair<int,int>> condEdges;
        for(int u=0;u<n;u++) for(int v:g[u]) if(comp[u]!=comp[v]) condEdges.insert({comp[u],comp[v]});
        cout<<"Condensation graph edges: "<<condEdges.size()<<"\n";
    }

    // ===== GfG-style: count of SCCs =====
    cout<<"Number of SCCs: "<<sccs.size()<<"\n";

    // ===== LC 1557: Minimum Number of Vertices to Reach All Nodes (DAG, indegree==0) =====
    {
        int N=6;
        vector<vector<int>> edges={{0,1},{0,2},{2,5},{3,4},{4,2}};
        vector<int> indeg(N,0);
        for(auto&e:edges) indeg[e[1]]++;
        vector<int> res;
        for(int i=0;i<N;i++) if(indeg[i]==0) res.push_back(i);
        cout<<"LC1557 MinVerticesToReachAll: ";
        for(int x:res) cout<<x<<" ";
        cout<<"\n";
    }

    // ===== LC 2360: Longest Cycle in a Functional Graph =====
    {
        vector<int> edges={3,3,4,2,3};
        int N=edges.size();
        vector<int> visitTime(N,-1);
        int ans=-1, t=0;
        for(int i=0;i<N;i++){
            if(visitTime[i]!=-1) continue;
            int u=i, start=t;
            while(u!=-1 && visitTime[u]==-1){ visitTime[u]=t++; u=edges[u]; }
            if(u!=-1 && visitTime[u]>=start) ans=max(ans, t-visitTime[u]);
        }
        cout<<"LC2360 LongestCycle: "<<ans<<"\n";
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
