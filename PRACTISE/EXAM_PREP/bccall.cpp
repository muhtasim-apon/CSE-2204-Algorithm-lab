#include<bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////////////
vector<vector<int>> g;
vector<int> disc, low, vis;
int timer = 0;

stack<pair<int,int>> st; // edge stack

vector<vector<pair<int,int>>> bcc; // list of components
vector<pair<int,int>> bridges;

//////////////////////////////////////////////////////////////////
// 1. EDGE-BASED BCC (TARJAN CORE)
//////////////////////////////////////////////////////////////////
void dfsBCC(int u, int p){

    vis[u] = 1;
    disc[u] = low[u] = ++timer;

    for(int v : g[u]){

        if(v == p) continue;

        if(!vis[v]){

            st.push({u, v});

            dfsBCC(v, u);

            low[u] = min(low[u], low[v]);

            // BCC FOUND
            if(low[v] >= disc[u]){

                vector<pair<int,int>> comp;

                while(true){
                    auto e = st.top();
                    st.pop();
                    comp.push_back(e);

                    if(e.first == u && e.second == v)
                        break;
                }

                bcc.push_back(comp);
            }

            // BRIDGE CHECK (also part of BCC logic)
            if(low[v] > disc[u]){
                bridges.push_back({u, v});
            }
        }
        else if(disc[v] < disc[u]){

            st.push({u, v});
            low[u] = min(low[u], disc[v]);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 2. INITIALIZATION
//////////////////////////////////////////////////////////////////
void init(int n){
    g.assign(n, {});
    disc.assign(n, 0);
    low.assign(n, 0);
    vis.assign(n, 0);
    timer = 0;

    while(!st.empty()) st.pop();

    bcc.clear();
    bridges.clear();
}

//////////////////////////////////////////////////////////////////
// 3. RUN BCC
//////////////////////////////////////////////////////////////////
void runBCC(int n){
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            dfsBCC(i, -1);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 4. PRINT BCC COMPONENTS
//////////////////////////////////////////////////////////////////
void printBCC(){
    cout << "BICONNECTED COMPONENTS:\n";

    for(int i = 0; i < (int)bcc.size(); i++){
        cout << "Component " << i + 1 << ":\n";
        for(auto &e : bcc[i]){
            cout << e.first << " - " << e.second << "\n";
        }
        cout << "\n";
    }
}

//////////////////////////////////////////////////////////////////
// 5. PRINT BRIDGES
//////////////////////////////////////////////////////////////////
void printBridges(){
    cout << "BRIDGES:\n";
    for(auto &b : bridges){
        cout << b.first << " - " << b.second << "\n";
    }
}

//////////////////////////////////////////////////////////////////
// 6. ARTICULATION-STYLE BCC SPLIT IDEA
//////////////////////////////////////////////////////////////////
/*
If low[v] >= disc[u], then removing u splits components.
Each BCC is a "maximal subgraph without articulation break"
*/

//////////////////////////////////////////////////////////////////
// 7. BLOCK-CUT TREE (ADVANCED IDEA)
//////////////////////////////////////////////////////////////////
/*
We create:
- node for each original vertex
- node for each BCC

Connect:
- vertex → BCC if vertex is inside that component
*/

vector<vector<int>> blockCutTree;
vector<int> nodeBelong; // vertex → BCC id

void buildBlockCutTree(int n){

    int bccCount = bcc.size();
    blockCutTree.assign(n + bccCount, {});
    nodeBelong.assign(n, -1);

    for(int i = 0; i < bccCount; i++){

        set<int> nodes;

        for(auto &e : bcc[i]){
            nodes.insert(e.first);
            nodes.insert(e.second);
        }

        for(int u : nodes){
            blockCutTree[u].push_back(n + i);
            blockCutTree[n + i].push_back(u);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 8. SIMPLE CHECK: IS EDGE A BCC INTERNAL EDGE?
//////////////////////////////////////////////////////////////////
bool isInternalEdge(int u, int v){
    for(auto &comp : bcc){
        for(auto &e : comp){
            if((e.first == u && e.second == v) ||
               (e.first == v && e.second == u))
                return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////
// 9. REMOVE NODE EFFECT (BRUTE BCC SPLIT IDEA)
//////////////////////////////////////////////////////////////////
int countComponentsAfterRemoving(int n, int removed){

    vector<int> vis2(n, 0);

    function<void(int)> dfs = [&](int u){
        vis2[u] = 1;

        for(int v : g[u]){
            if(v == removed) continue;
            if(!vis2[v]) dfs(v);
        }
    };

    int cnt = 0;

    for(int i = 0; i < n; i++){
        if(i == removed) continue;
        if(!vis2[i]){
            dfs(i);
            cnt++;
        }
    }

    return cnt;
}

//////////////////////////////////////////////////////////////////
// 10. MAIN
//////////////////////////////////////////////////////////////////
int main(){

    int n, m;
    cin >> n >> m;

    init(n);

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u); // undirected graph
    }

    runBCC(n);

    printBCC();
    printBridges();

    buildBlockCutTree(n);

    return 0;
}