#include<bits/stdc++.h>
#define ll long long
using namespace std;

// ===== Euler Path/Circuit: existence check + Hierholzer's algorithm =====
// Input: N, M, then M undirected edges "U V".

vector<multiset<int>> g;
vector<int> hierholzerUndirected(int n,int start){
    vector<multiset<int>> adj=g;
    vector<int> circuit, stackPath{start};
    while(!stackPath.empty()){
        int v=stackPath.back();
        if(!adj[v].empty()){
            int u=*adj[v].begin();
            adj[v].erase(adj[v].find(u));
            adj[u].erase(adj[u].find(v));
            stackPath.push_back(u);
        } else {
            circuit.push_back(v);
            stackPath.pop_back();
        }
    }
    reverse(circuit.begin(),circuit.end());
    return circuit;
}

void muhtasim()
{
    int n,m; cin>>n>>m;
    g.assign(n,{});
    vector<int> deg(n,0);
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        g[u].insert(v); g[v].insert(u);
        deg[u]++; deg[v]++;
    }

    int oddCount=0, oddNode=-1, anyEdgeNode=-1;
    for(int i=0;i<n;i++){ if(deg[i]&1){ oddCount++; oddNode=i; } if(deg[i]>0 && anyEdgeNode==-1) anyEdgeNode=i; }

    cout<<"Undirected Euler check: ";
    if(m==0){ cout<<"No edges (trivially has an Euler circuit of length 0)\n"; }
    else if(oddCount==0){
        cout<<"Euler CIRCUIT exists. Path: ";
        for(int x:hierholzerUndirected(n,anyEdgeNode)) cout<<x<<" ";
        cout<<"\n";
    } else if(oddCount==2){
        cout<<"Euler PATH exists (not circuit). Path: ";
        for(int x:hierholzerUndirected(n,oddNode)) cout<<x<<" ";
        cout<<"\n";
    } else {
        cout<<"No Euler path/circuit ("<<oddCount<<" odd-degree vertices)\n";
    }

    // ===== Directed Euler path/circuit existence check (in-degree vs out-degree) =====
    {
        int N=4;
        vector<array<int,2>> dedges={{0,1},{1,2},{2,3},{3,0}};
        vector<int> indeg(N,0), outdeg(N,0);
        for(auto&e:dedges){ outdeg[e[0]]++; indeg[e[1]]++; }
        bool circuit=true, path=true; int startDiff=0,endDiff=0;
        for(int i=0;i<N;i++){
            int d=outdeg[i]-indeg[i];
            if(d!=0) circuit=false;
            if(d==1) startDiff++; else if(d==-1) endDiff++; else if(d!=0) path=false;
        }
        path = path && ((startDiff==0&&endDiff==0) || (startDiff==1&&endDiff==1));
        cout<<"Directed demo graph (0->1->2->3->0): Euler circuit="<<(circuit?"true":"false")<<", Euler path="<<(path?"true":"false")<<"\n";
    }

    // ===== LC 332: Reconstruct Itinerary (Hierholzer's, lexicographic tie-break) =====
    {
        vector<vector<string>> tickets={{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
        map<string, multiset<string>> adj2;
        for(auto&t:tickets) adj2[t[0]].insert(t[1]);
        vector<string> route;
        function<void(string)> visit=[&](string u){
            while(!adj2[u].empty()){
                string v=*adj2[u].begin();
                adj2[u].erase(adj2[u].begin());
                visit(v);
            }
            route.push_back(u);
        };
        visit("JFK");
        reverse(route.begin(),route.end());
        cout<<"LC332 ReconstructItinerary: ";
        for(auto&s:route) cout<<s<<" ";
        cout<<"\n";
    }

    // ===== LC 2097: Valid Arrangement of Pairs (Eulerian path over directed pairs) =====
    {
        vector<vector<int>> pairs={{5,1},{4,5},{11,9},{9,4}};
        map<int, multiset<int>> adj2;
        map<int,int> indeg, outdeg;
        for(auto&p:pairs){ adj2[p[0]].insert(p[1]); outdeg[p[0]]++; indeg[p[1]]++; }
        int start=pairs[0][0];
        for(auto&p:pairs) if(outdeg[p[0]]-indeg[p[0]]==1){ start=p[0]; break; }
        vector<int> route;
        function<void(int)> visit=[&](int u){
            while(!adj2[u].empty()){
                int v=*adj2[u].begin();
                adj2[u].erase(adj2[u].begin());
                visit(v);
            }
            route.push_back(u);
        };
        visit(start);
        reverse(route.begin(),route.end());
        cout<<"LC2097 ValidArrangementOfPairs route: ";
        for(int x:route) cout<<x<<" ";
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
