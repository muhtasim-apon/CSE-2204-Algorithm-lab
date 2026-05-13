#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,m,src;
    cin>>n>>m;
    vector<vector<pair<int,int>>>adj(n+1);
    vector<vector<int>>times;
       priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
       vector<int>dist(n,INT_MAX);
       vector<bool>visited(n,false);
       while(m--)
       {
        int u,v,w;
        cin>>u>>v>>w;
        times.push_back({u,v,w});
        if(w<0)
        {
            cout<<"Negative Edge Detected.Dijsktra Algo Failed.\n";
            return 0;
        }
       }
       for(int i=0;i<times.size();i++)
       {
        adj[times[i][0]].push_back({times[i][1],times[i][2]});
        //adj[times[i][1]].push_back({times[i][0],times[i][2]});
       }
       cin>>src;
        dist[src]=0;
         int ans=0;
        pq.push({dist[src],src});
        while(!pq.empty())
        {
            int d=pq.top().first;
            int u=pq.top().second;
            pq.pop();
            if(d>dist[u])continue;
            visited[u]=true;
            for(auto v:adj[u])
            {
                int v1=v.first;
                int w=v.second;
                if(!visited[v1] && dist[u]+w<dist[v1])
                {
                dist[v1]=d+w;
                pq.push({dist[v1],v1});
            }
        }
        }
        for(auto x:dist)cout<<x<<" ";
       } 
//        #include<bits/stdc++.h>
// using namespace std;

// #define ll long long
// const ll INF=1e18;

// /* ================= EDGE STRUCT ================= */
// struct Edge
// {
//     int v;
//     ll w;
// };

// /* ================= CORE CLASS ================= */
// class Dijkstra
// {
// public:
//     int n;
//     vector<vector<Edge>> adj;

//     vector<ll> dist;
//     vector<int> parent;

//     Dijkstra(int n)
//     {
//         this->n=n;
//         adj.resize(n+1);
//     }

//     void addEdge(int u,int v,ll w)
//     {
//         adj[u].push_back({v,w});
//     }

//     /* ================= 1. STANDARD DIJKSTRA ================= */
//     void run(int src)
//     {
//         dist.assign(n+1,INF);
//         parent.assign(n+1,-1);

//         priority_queue<pair<ll,int>,
//                        vector<pair<ll,int>>,
//                        greater<pair<ll,int>>> pq;

//         dist[src]=0;
//         pq.push({0,src});

//         while(!pq.empty())
//         {
//             auto [d,u]=pq.top();
//             pq.pop();

//             if(d!=dist[u]) continue;

//             for(auto e:adj[u])
//             {
//                 if(dist[u]+e.w<dist[e.v])
//                 {
//                     dist[e.v]=dist[u]+e.w;
//                     parent[e.v]=u;
//                     pq.push({dist[e.v],e.v});
//                 }
//             }
//         }
//     }

//     /* ================= 2. PATH RECONSTRUCTION ================= */
//     vector<int> getPath(int src,int dest)
//     {
//         vector<int> path;
//         if(dist[dest]==INF) return path;

//         for(int v=dest;v!=-1;v=parent[v])
//             path.push_back(v);

//         reverse(path.begin(),path.end());

//         if(path[0]!=src) return {};
//         return path;
//     }

//     /* ================= 3. MULTI-SOURCE ================= */
//     void multiSource(vector<int>& sources)
//     {
//         dist.assign(n+1,INF);
//         parent.assign(n+1,-1);

//         priority_queue<pair<ll,int>,
//                        vector<pair<ll,int>>,
//                        greater<pair<ll,int>>> pq;

//         for(int s:sources)
//         {
//             dist[s]=0;
//             pq.push({0,s});
//         }

//         while(!pq.empty())
//         {
//             auto [d,u]=pq.top();
//             pq.pop();

//             if(d!=dist[u]) continue;

//             for(auto e:adj[u])
//             {
//                 if(dist[u]+e.w<dist[e.v])
//                 {
//                     dist[e.v]=dist[u]+e.w;
//                     parent[e.v]=u;
//                     pq.push({dist[e.v],e.v});
//                 }
//             }
//         }
//     }

//     /* ================= 4. COUNT SHORTEST PATHS ================= */
//     vector<ll> ways;

//     void countShortestPaths(int src)
//     {
//         dist.assign(n+1,INF);
//         ways.assign(n+1,0);

//         priority_queue<pair<ll,int>,
//                        vector<pair<ll,int>>,
//                        greater<pair<ll,int>>> pq;

//         dist[src]=0;
//         ways[src]=1;
//         pq.push({0,src});

//         while(!pq.empty())
//         {
//             auto [d,u]=pq.top();
//             pq.pop();

//             if(d!=dist[u]) continue;

//             for(auto e:adj[u])
//             {
//                 if(dist[u]+e.w<dist[e.v])
//                 {
//                     dist[e.v]=dist[u]+e.w;
//                     ways[e.v]=ways[u];
//                     pq.push({dist[e.v],e.v});
//                 }
//                 else if(dist[u]+e.w==dist[e.v])
//                 {
//                     ways[e.v]+=ways[u];
//                 }
//             }
//         }
//     }

//     /* ================= 5. SECOND SHORTEST PATH ================= */
//     ll secondShortest(int src,int dest)
//     {
//         vector<ll> d1(n+1,INF), d2(n+1,INF);

//         priority_queue<pair<ll,int>,
//                        vector<pair<ll,int>>,
//                        greater<pair<ll,int>>> pq;

//         d1[src]=0;
//         pq.push({0,src});

//         while(!pq.empty())
//         {
//             auto [d,u]=pq.top();
//             pq.pop();

//             for(auto e:adj[u])
//             {
//                 ll nd=d+e.w;

//                 if(nd<d1[e.v])
//                 {
//                     d2[e.v]=d1[e.v];
//                     d1[e.v]=nd;
//                     pq.push({nd,e.v});
//                 }
//                 else if(nd>d1[e.v] && nd<d2[e.v])
//                 {
//                     d2[e.v]=nd;
//                     pq.push({nd,e.v});
//                 }
//             }
//         }

//         return d2[dest]==INF?-1:d2[dest];
//     }

//     /* ================= 6. WIDEST PATH ================= */
//     ll widestPath(int src,int dest)
//     {
//         vector<ll> best(n+1,-1);

//         priority_queue<pair<ll,int>> pq;

//         best[src]=INF;
//         pq.push({INF,src});

//         while(!pq.empty())
//         {
//             auto [w,u]=pq.top();
//             pq.pop();

//             for(auto e:adj[u])
//             {
//                 ll nw=min(w,e.w);

//                 if(nw>best[e.v])
//                 {
//                     best[e.v]=nw;
//                     pq.push({nw,e.v});
//                 }
//             }
//         }

//         return best[dest];
//     }

//     /* ================= 7. PROBABILITY PATH ================= */
//     double maxProbability(int src,int dest)
//     {
//         vector<double> prob(n+1,0.0);

//         priority_queue<pair<double,int>> pq;

//         prob[src]=1.0;
//         pq.push({1.0,src});

//         while(!pq.empty())
//         {
//             auto [p,u]=pq.top();
//             pq.pop();

//             if(p<prob[u]) continue;

//             for(auto e:adj[u])
//             {
//                 double np=p*e.w;

//                 if(np>prob[e.v])
//                 {
//                     prob[e.v]=np;
//                     pq.push({np,e.v});
//                 }
//             }
//         }

//         return prob[dest];
//     }
// };
// #include<bits/stdc++.h>
// using namespace std;

// #define ll long long
// const ll INF = 1e18;

// /* ================= NODE ================= */
// struct Node
// {
//     ll dist;
//     int v;

//     Node* left;
//     Node* right;
//     Node* parent;

//     Node(ll d,int v)
//     {
//         dist=d;
//         this->v=v;
//         left=right=parent=nullptr;
//     }
// };

// /* ================= POINTER MIN HEAP ================= */
// class MinHeap
// {
// public:
//     Node* root;
//     int size;

//     MinHeap()
//     {
//         root=nullptr;
//         size=0;
//     }

//     void swapNode(Node* a,Node* b)
//     {
//         swap(a->dist,b->dist);
//         swap(a->v,b->v);
//     }

//     /* ---------- INSERT ---------- */
//     void push(ll dist,int v)
//     {
//         Node* newNode=new Node(dist,v);
//         size++;

//         if(!root)
//         {
//             root=newNode;
//             return;
//         }

//         queue<Node*> q;
//         q.push(root);

//         while(!q.empty())
//         {
//             Node* cur=q.front();
//             q.pop();

//             if(!cur->left)
//             {
//                 cur->left=newNode;
//                 newNode->parent=cur;
//                 heapifyUp(newNode);
//                 return;
//             }
//             else q.push(cur->left);

//             if(!cur->right)
//             {
//                 cur->right=newNode;
//                 newNode->parent=cur;
//                 heapifyUp(newNode);
//                 return;
//             }
//             else q.push(cur->right);
//         }
//     }

//     /* ---------- HEAPIFY UP ---------- */
//     void heapifyUp(Node* node)
//     {
//         while(node->parent && node->parent->dist > node->dist)
//         {
//             swapNode(node,node->parent);
//             node=node->parent;
//         }
//     }

//     /* ---------- FIND LAST NODE ---------- */
//     Node* getLastNode()
//     {
//         queue<Node*> q;
//         q.push(root);

//         Node* last=nullptr;

//         while(!q.empty())
//         {
//             last=q.front();
//             q.pop();

//             if(last->left) q.push(last->left);
//             if(last->right) q.push(last->right);
//         }

//         return last;
//     }

//     /* ---------- HEAPIFY DOWN ---------- */
//     void heapifyDown(Node* node)
//     {
//         while(node)
//         {
//             Node* smallest=node;

//             if(node->left && node->left->dist < smallest->dist)
//                 smallest=node->left;

//             if(node->right && node->right->dist < smallest->dist)
//                 smallest=node->right;

//             if(smallest==node) break;

//             swapNode(node,smallest);
//             node=smallest;
//         }
//     }

//     /* ---------- POP MIN ---------- */
//     void pop()
//     {
//         if(!root) return;

//         if(size==1)
//         {
//             delete root;
//             root=nullptr;
//             size--;
//             return;
//         }

//         Node* last=getLastNode();

//         swapNode(root,last);

//         Node* p=last->parent;
//         if(p)
//         {
//             if(p->right==last) p->right=nullptr;
//             else p->left=nullptr;
//         }

//         delete last;
//         size--;

//         heapifyDown(root);
//     }

//     Node* top()
//     {
//         return root;
//     }

//     bool empty()
//     {
//         return root==nullptr;
//     }
// };

// /* ================= GRAPH ================= */
// class Graph
// {
// public:
//     int n;
//     vector<vector<pair<int,int>>> adj;
//     vector<ll> dist;

//     Graph(int n)
//     {
//         this->n=n;
//         adj.resize(n+1);
//     }

//     void addEdge(int u,int v,int w)
//     {
//         adj[u].push_back({v,w});
//     }

//     /* ================= DIJKSTRA ================= */
//     void dijkstra(int src)
//     {
//         dist.assign(n+1,INF);

//         MinHeap pq;

//         dist[src]=0;
//         pq.push(0,src);

//         while(!pq.empty())
//         {
//             Node* cur=pq.top();
//             pq.pop();

//             ll d=cur->dist;
//             int u=cur->v;

//             if(d!=dist[u]) continue;

//             for(auto [v,w]:adj[u])
//             {
//                 if(dist[u]+w < dist[v])
//                 {
//                     dist[v]=dist[u]+w;
//                     pq.push(dist[v],v);
//                 }
//             }
//         }
//     }

//     /* ================= PRINT DISTANCES ================= */
//     void printDistances()
//     {
//         for(int i=1;i<=n;i++)
//         {
//             if(dist[i]==INF) cout<<"INF\n";
//             else cout<<dist[i]<<"\n";
//         }
//     }
// };

// /* ================= MAIN ================= */
// int main()
// {
//     int n,m;
//     cin>>n>>m;

//     Graph g(n);

//     for(int i=0;i<m;i++)
//     {
//         int u,v,w;
//         cin>>u>>v>>w;
//         g.addEdge(u,v,w);
//         g.addEdge(v,u,w); // remove if directed
//     }

//     int src;
//     cin>>src;

//     g.dijkstra(src);

//     g.printDistances();

//     return 0;
// }