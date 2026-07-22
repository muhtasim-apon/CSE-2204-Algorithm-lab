#include<bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////////////
vector<vector<int>> g, rg;
vector<int> vis, comp, order, disc, low;
stack<int> st;
vector<bool> inStack;

int timer = 0;
int compCnt = 0;

//////////////////////////////////////////////////////////////////
// 1. KOSARAJU STEP 1: DFS ORDER
//////////////////////////////////////////////////////////////////
void dfs1(int u){
    vis[u] = 1;

    for(int v : g[u]){
        if(!vis[v]) dfs1(v);
    }

    order.push_back(u);
}

//////////////////////////////////////////////////////////////////
// 2. KOSARAJU STEP 2: REVERSE GRAPH DFS
//////////////////////////////////////////////////////////////////
void dfs2(int u, int c){
    comp[u] = c;

    for(int v : rg[u]){
        if(comp[v] == -1){
            dfs2(v, c);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 3. KOSARAJU SCC
//////////////////////////////////////////////////////////////////
int kosaraju(int n){

    vis.assign(n, 0);
    order.clear();

    for(int i = 0; i < n; i++){
        if(!vis[i]) dfs1(i);
    }

    comp.assign(n, -1);

    int c = 0;

    for(int i = n - 1; i >= 0; i--){
        int v = order[i];

        if(comp[v] == -1){
            dfs2(v, c++);
        }
    }

    compCnt = c;
    return c;
}

//////////////////////////////////////////////////////////////////
// 4. TARJAN SCC
//////////////////////////////////////////////////////////////////
void tarjan(int u){

    disc[u] = low[u] = ++timer;
    st.push(u);
    inStack[u] = true;

    for(int v : g[u]){

        if(!disc[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(inStack[v]){
            low[u] = min(low[u], disc[v]);
        }
    }

    if(low[u] == disc[u]){

        while(true){
            int v = st.top();
            st.pop();
            inStack[v] = false;
            comp[v] = compCnt;

            if(v == u) break;
        }

        compCnt++;
    }
}

//////////////////////////////////////////////////////////////////
// 5. RUN TARJAN SCC
//////////////////////////////////////////////////////////////////
void runTarjan(int n){
    disc.assign(n, 0);
    low.assign(n, 0);
    inStack.assign(n, false);
    comp.assign(n, -1);

    while(!st.empty()) st.pop();

    timer = 0;
    compCnt = 0;

    for(int i = 0; i < n; i++){
        if(!disc[i]) tarjan(i);
    }
}

//////////////////////////////////////////////////////////////////
// 6. BUILD SCC CONDENSATION GRAPH (DAG)
//////////////////////////////////////////////////////////////////
vector<vector<int>> buildSCCGraph(int n, int c){

    vector<vector<int>> dag(c);

    set<pair<int,int>> edges;

    for(int u = 0; u < n; u++){
        for(int v : g[u]){
            if(comp[u] != comp[v]){
                if(!edges.count({comp[u], comp[v]})){
                    dag[comp[u]].push_back(comp[v]);
                    edges.insert({comp[u], comp[v]});
                }
            }
        }
    }

    return dag;
}

//////////////////////////////////////////////////////////////////
// 7. CHECK CYCLE USING SCC
//////////////////////////////////////////////////////////////////
bool hasCycleSCC(int n){
    for(int i = 0; i < n; i++){
        if(comp[i] == comp[0]) continue;
    }

    // If any SCC size > 1 OR self loop exists → cycle exists
    unordered_map<int,int> freq;

    for(int i = 0; i < n; i++){
        freq[comp[i]]++;
    }

    for(auto &p : freq){
        if(p.second > 1) return true;
    }

    return false;
}

//////////////////////////////////////////////////////////////////
// 8. TOPO SORT ON SCC DAG
//////////////////////////////////////////////////////////////////
void topoDFS(int u, vector<vector<int>>&dag, vector<int>&vis2, vector<int>&res){
    vis2[u] = 1;

    for(int v : dag[u]){
        if(!vis2[v]) topoDFS(v, dag, vis2, res);
    }

    res.push_back(u);
}

vector<int> topoSCC(int c, vector<vector<int>>&dag){
    vector<int> vis2(c, 0), res;

    for(int i = 0; i < c; i++){
        if(!vis2[i]) topoDFS(i, dag, vis2, res);
    }

    reverse(res.begin(), res.end());
    return res;
}

//////////////////////////////////////////////////////////////////
// 9. PRINT COMPONENTS
//////////////////////////////////////////////////////////////////
void printSCC(int n){
    unordered_map<int, vector<int>> groups;

    for(int i = 0; i < n; i++){
        groups[comp[i]].push_back(i);
    }

    cout << "SCC Components:\n";
    for(auto &p : groups){
        cout << "Component " << p.first << ": ";
        for(int x : p.second) cout << x << " ";
        cout << "\n";
    }
}

//////////////////////////////////////////////////////////////////
// 10. 2-SAT CORE (IMPORTANT SCC APPLICATION)
//////////////////////////////////////////////////////////////////
/*
Variable x → node x
NOT x → node x+n
*/

int opp(int x, int n){
    return (x < n ? x + n : x - n);
}

bool twoSAT(int n, vector<pair<int,int>>&implications){

    g.assign(2*n, {});
    rg.assign(2*n, {});

    for(auto [a,b] : implications){
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    kosaraju(2*n);

    for(int i = 0; i < n; i++){
        if(comp[i] == comp[i+n]){
            return false;
        }
    }

    return true;
}

//////////////////////////////////////////////////////////////////
// MAIN
//////////////////////////////////////////////////////////////////
int main(){

    int n, m;
    cin >> n >> m;

    g.assign(n, {});
    rg.assign(n, {});

    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        rg[v].push_back(u);
    }

    int c = kosaraju(n);

    printSCC(n);

    vector<vector<int>> dag = buildSCCGraph(n, c);

    vector<int> topo = topoSCC(c, dag);

    cout << "SCC Topological Order:\n";
    for(int x : topo) cout << x << " ";

    cout << "\n";

    return 0;
}