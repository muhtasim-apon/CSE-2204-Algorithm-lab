#include<bits/stdc++.h>
using namespace std;

//////////////////////////////////////////////////////////////////
// GLOBALS
//////////////////////////////////////////////////////////////////
vector<vector<int>> g;
vector<int> disc, low, vis, isAP;
vector<pair<int,int>> bridges;

int timer = 0;

//////////////////////////////////////////////////////////////////
// 1. BRIDGES (TARJAN ALGORITHM)
//////////////////////////////////////////////////////////////////
void bridgeDFS(int u, int p){
    vis[u] = 1;
    disc[u] = low[u] = ++timer;

    for(int v : g[u]){
        if(v == p) continue;

        if(!vis[v]){
            bridgeDFS(v, u);

            low[u] = min(low[u], low[v]);

            // BRIDGE CONDITION
            if(low[v] > disc[u]){
                bridges.push_back({u, v});
            }
        }
        else{
            low[u] = min(low[u], disc[v]);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 2. ARTICULATION POINTS (TARJAN)
//////////////////////////////////////////////////////////////////
void apDFS(int u, int p){
    vis[u] = 1;
    disc[u] = low[u] = ++timer;

    int children = 0;

    for(int v : g[u]){
        if(v == p) continue;

        if(!vis[v]){
            children++;

            apDFS(v, u);

            low[u] = min(low[u], low[v]);

            // CASE 1: root articulation point
            if(p == -1 && children > 1)
                isAP[u] = 1;

            // CASE 2: non-root articulation point
            if(p != -1 && low[v] >= disc[u])
                isAP[u] = 1;
        }
        else{
            low[u] = min(low[u], disc[v]);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 3. BICONNECTED COMPONENTS (EDGE STACK METHOD)
//////////////////////////////////////////////////////////////////
stack<pair<int,int>> st;
vector<vector<pair<int,int>>> bcc;

void bccDFS(int u, int p){
    vis[u] = 1;
    disc[u] = low[u] = ++timer;

    for(int v : g[u]){
        if(v == p) continue;

        if(!vis[v]){
            st.push({u, v});

            bccDFS(v, u);

            low[u] = min(low[u], low[v]);

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
        }
        else if(disc[v] < disc[u]){
            st.push({u, v});
            low[u] = min(low[u], disc[v]);
        }
    }
}

//////////////////////////////////////////////////////////////////
// 4. REMOVE EDGE AND CHECK CONNECTIVITY (BRUTE FORCE)
//////////////////////////////////////////////////////////////////
bool dfsCheck(int u, int target, int banU, int banV, vector<int>&vis2){
    if(u == target) return true;

    vis2[u] = 1;

    for(int v : g[u]){
        if((u == banU && v == banV) || (u == banV && v == banU))
            continue;

        if(!vis2[v]){
            if(dfsCheck(v, target, banU, banV, vis2))
                return true;
        }
    }

    return false;
}

bool isBridgeBrute(int u, int v, int n){
    vector<int> vis2(n, 0);
    return !dfsCheck(u, v, u, v, vis2);
}

//////////////////////////////////////////////////////////////////
// 5. BRIDGE TREE (CONCEPTUAL BUILDING IDEA)
//////////////////////////////////////////////////////////////////
/*
After finding bridges:
- Remove bridges
- Remaining graph splits into components
- Each component becomes a node in a tree (bridge tree)
*/

vector<int> compId;
int compCnt = 0;

void markComponent(int u){
    compId[u] = compCnt;

    for(int v : g[u]){
        if(compId[v] == -1){
            bool isBridge = false;

            for(auto b : bridges){
                if((b.first == u && b.second == v) ||
                   (b.first == v && b.second == u)){
                    isBridge = true;
                }
            }

            if(!isBridge){
                markComponent(v);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////
// 6. INIT FUNCTION
//////////////////////////////////////////////////////////////////
void init(int n){
    g.assign(n, {});
    vis.assign(n, 0);
    disc.assign(n, 0);
    low.assign(n, 0);
    isAP.assign(n, 0);
    timer = 0;
}

//////////////////////////////////////////////////////////////////
// 7. RUN ALL
//////////////////////////////////////////////////////////////////
void runBridgeAP(int n){
    for(int i = 0; i < n; i++){
        if(!vis[i])
            bridgeDFS(i, -1);
    }

    fill(vis.begin(), vis.end(), 0);
    timer = 0;

    for(int i = 0; i < n; i++){
        if(!vis[i])
            apDFS(i, -1);
    }
}

//////////////////////////////////////////////////////////////////
// 8. PRINT RESULTS
//////////////////////////////////////////////////////////////////
void printResults(){
    cout << "BRIDGES:\n";
    for(auto &b : bridges){
        cout << b.first << " - " << b.second << "\n";
    }

    cout << "\nARTICULATION POINTS:\n";
    for(int i = 0; i < isAP.size(); i++){
        if(isAP[i])
            cout << i << " ";
    }
    cout << "\n";
}

//////////////////////////////////////////////////////////////////
// MAIN
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

    runBridgeAP(n);
    printResults();

    return 0;
}