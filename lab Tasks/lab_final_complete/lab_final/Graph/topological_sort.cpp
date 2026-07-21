#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Instructor Problem: Topological Order (DFS finish-order based) =====
int n;
vector<vector<int>> g;

void dfsTopo(int u, vector<bool>&visited, vector<int>&order_){
    visited[u]=true;
    for(int v:g[u]) if(!visited[v]) dfsTopo(v,visited,order_);
    order_.push_back(u);
}

// ===== Kahn's algorithm (BFS, in-degree based) =====
vector<int> kahnTopo(){
    vector<int> indeg(n,0);
    for(int u=0;u<n;u++) for(int v:g[u]) indeg[v]++;
    queue<int> q;
    for(int i=0;i<n;i++) if(indeg[i]==0) q.push(i);
    vector<int> topo;
    while(!q.empty()){
        int u=q.front(); q.pop();
        topo.push_back(u);
        for(int v:g[u]) if(--indeg[v]==0) q.push(v);
    }
    return topo;
}

// ===== Lexicographically smallest topological order (min-heap Kahn's) =====
vector<int> lexSmallestTopo(){
    vector<int> indeg(n,0);
    for(int u=0;u<n;u++) for(int v:g[u]) indeg[v]++;
    priority_queue<int, vector<int>, greater<>> pq;
    for(int i=0;i<n;i++) if(indeg[i]==0) pq.push(i);
    vector<int> topo;
    while(!pq.empty()){
        int u=pq.top(); pq.pop();
        topo.push_back(u);
        for(int v:g[u]) if(--indeg[v]==0) pq.push(v);
    }
    return topo;
}

// ===== Print ALL valid topological orderings (backtracking) =====
void allTopoOrders(vector<int>&indeg, vector<bool>&used, vector<int>&path, vector<vector<int>>&results){
    if((int)path.size()==n){ results.push_back(path); return; }
    for(int i=0;i<n;i++){
        if(!used[i] && indeg[i]==0){
            used[i]=true;
            for(int v:g[i]) indeg[v]--;
            path.push_back(i);
            allTopoOrders(indeg,used,path,results);
            path.pop_back();
            for(int v:g[i]) indeg[v]++;
            used[i]=false;
        }
    }
}

void muhtasim()
{
    int m; cin>>n>>m;
    g.assign(n,{});
    for(int i=0;i<m;i++){ int u,v; cin>>u>>v; g[u].push_back(v); }

    // ----- Instructor: DFS finish-order topological order -----
    {
        vector<bool> visited(n,false);
        vector<int> order_;
        for(int i=0;i<n;i++) if(!visited[i]) dfsTopo(i,visited,order_);
        reverse(order_.begin(),order_.end());
        for(int x:order_) cout<<x<<"\n";
    }

    // ===== Kahn's algorithm (alternate valid order on same input) =====
    {
        auto topo = kahnTopo();
        cout<<"Kahn's order: ";
        for(int x:topo) cout<<x<<" ";
        cout<<"\n";
    }

    // ===== Lexicographically smallest topological order =====
    {
        auto topo = lexSmallestTopo();
        cout<<"Lexicographically smallest order: ";
        for(int x:topo) cout<<x<<" ";
        cout<<"\n";
    }

    // ===== Print all valid topological orderings (small graphs only) =====
    if(n<=8){
        vector<int> indeg(n,0);
        for(int u=0;u<n;u++) for(int v:g[u]) indeg[v]++;
        vector<bool> used(n,false);
        vector<int> path;
        vector<vector<int>> results;
        allTopoOrders(indeg,used,path,results);
        cout<<"Total valid topological orderings: "<<results.size()<<"\n";
    }

    // ===== LC 207/210: Course Schedule I/II (hardcoded prerequisites) =====
    {
        int numCourses=4;
        vector<vector<int>> prereq={{1,0},{2,0},{3,1},{3,2}};
        vector<vector<int>> adj2(numCourses);
        vector<int> indeg(numCourses,0);
        for(auto&p:prereq){ adj2[p[1]].push_back(p[0]); indeg[p[0]]++; }
        queue<int> q; for(int i=0;i<numCourses;i++) if(indeg[i]==0) q.push(i);
        vector<int> order_; while(!q.empty()){ int u=q.front(); q.pop(); order_.push_back(u); for(int v:adj2[u]) if(--indeg[v]==0) q.push(v); }
        cout<<"LC207/210 CourseSchedule possible: "<<(order_.size()==(size_t)numCourses?"true":"false")<<", order: ";
        for(int x:order_) cout<<x<<" ";
        cout<<"\n";
    }

    // ===== LC 802: Find Eventual Safe States (topo on reversed terminal-reachability) =====
    {
        vector<vector<int>> graph={{1,2},{2,3},{5},{0},{5},{},{}};
        int N=graph.size();
        vector<int> color(N,0); // 0=unvisited,1=visiting,2=safe
        function<bool(int)> isSafe=[&](int u)->bool{
            if(color[u]>0) return color[u]==2;
            color[u]=1;
            for(int v:graph[u]) if(!isSafe(v)) return false;
            color[u]=2; return true;
        };
        vector<int> safeNodes;
        for(int i=0;i<N;i++) if(isSafe(i)) safeNodes.push_back(i);
        cout<<"LC802 SafeStates: ";
        for(int x:safeNodes) cout<<x<<" ";
        cout<<"\n";
    }

    // ===== LC 1136-style: Parallel Courses (minimum semesters via BFS levels) =====
    {
        int N=5; // courses 1..5
        vector<vector<int>> rel={{1,3},{2,3},{3,4},{4,5}};
        vector<vector<int>> adj2(N+1);
        vector<int> indeg(N+1,0);
        for(auto&r:rel){ adj2[r[0]].push_back(r[1]); indeg[r[1]]++; }
        queue<int> q; for(int i=1;i<=N;i++) if(indeg[i]==0) q.push(i);
        int studied=0, semesters=0;
        while(!q.empty()){
            semesters++;
            int sz=q.size();
            while(sz--){ int u=q.front(); q.pop(); studied++; for(int v:adj2[u]) if(--indeg[v]==0) q.push(v); }
        }
        cout<<"LC1136 ParallelCourses min semesters: "<<(studied==N? to_string(semesters): string("-1"))<<"\n";
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
