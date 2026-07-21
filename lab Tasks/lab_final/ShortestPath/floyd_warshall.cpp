#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll INF = LLONG_MAX/4;

// ===== Floyd-Warshall: all-pairs shortest paths + path reconstruction + negative-cycle detection =====

int n;
vector<vector<ll>> dist_;
vector<vector<int>> nxt;

void floydWarshall(){
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dist_[i][k]+dist_[k][j] < dist_[i][j]){
                    dist_[i][j]=dist_[i][k]+dist_[k][j];
                    nxt[i][j]=nxt[i][k];
                }
}

vector<int> reconstructPath(int u,int v){
    if(dist_[u][v]>=INF) return {};
    vector<int> path={u};
    while(u!=v){
        u=nxt[u][v];
        if(u==-1) return {};
        path.push_back(u);
    }
    return path;
}

void muhtasim()
{
    int m; cin>>n>>m;
    dist_.assign(n, vector<ll>(n, INF));
    nxt.assign(n, vector<int>(n, -1));
    for(int i=0;i<n;i++){ dist_[i][i]=0; nxt[i][i]=i; }
    for(int i=0;i<m;i++){
        int u,v; ll w; cin>>u>>v>>w;
        if(w<dist_[u][v]){ dist_[u][v]=w; nxt[u][v]=v; }
    }

    floydWarshall();

    // negative-cycle check
    bool negCycle=false;
    for(int i=0;i<n;i++) if(dist_[i][i]<0) negCycle=true;

    cout<<"Floyd-Warshall all-pairs distances:\n";
    if(negCycle) cout<<"Negative Cycle Detected\n";
    else{
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++) cout<<(dist_[i][j]>=INF? string("INF"): to_string(dist_[i][j]))<<(j+1<n?" ":"\n");
        }
        // path reconstruction demo: 0 -> n-1
        auto path=reconstructPath(0,n-1);
        cout<<"Path 0->"<<n-1<<": ";
        if(path.empty()) cout<<"None\n";
        else{ for(int x:path) cout<<x<<" "; cout<<"\n"; }
    }

    // ===== LC 1334: Find the City With the Smallest Number of Neighbors Within Threshold =====
    {
        int N=4, threshold=4;
        vector<array<int,3>> edges2={{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
        vector<vector<ll>> d(N, vector<ll>(N, INF));
        for(int i=0;i<N;i++) d[i][i]=0;
        for(auto&e:edges2){ d[e[0]][e[1]]=min((ll)d[e[0]][e[1]],(ll)e[2]); d[e[1]][e[0]]=min((ll)d[e[1]][e[0]],(ll)e[2]); }
        for(int k=0;k<N;k++) for(int i=0;i<N;i++) for(int j=0;j<N;j++) d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
        int bestCity=-1, bestCount=INT_MAX;
        for(int i=0;i<N;i++){
            int cnt=0;
            for(int j=0;j<N;j++) if(i!=j && d[i][j]<=threshold) cnt++;
            if(cnt<=bestCount){ bestCount=cnt; bestCity=i; } // tie -> larger index wins since we scan ascending with <=
        }
        cout<<"LC1334 SmallestNeighborsCity: "<<bestCity<<"\n";
    }

    // ===== LC 1462: Course Schedule IV (reachability via transitive closure) =====
    {
        int N=4;
        vector<array<int,2>> prereq={{0,1},{1,2},{1,3},{2,3}};
        vector<vector<bool>> reach(N, vector<bool>(N,false));
        for(auto&p:prereq) reach[p[0]][p[1]]=true;
        for(int k=0;k<N;k++) for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(reach[i][k]&&reach[k][j]) reach[i][j]=true;
        vector<array<int,2>> queries={{0,3},{3,0},{0,2}};
        cout<<"LC1462 CourseScheduleIV: ";
        for(auto&q:queries) cout<<(reach[q[0]][q[1]]?"T":"F")<<" ";
        cout<<"\n";
    }

    // ===== LC 2101: Detonate the Maximum Bombs (reachability via directed containment graph) =====
    {
        vector<array<ll,3>> bombs={{2,1,3},{6,1,4}}; // x,y,r
        int N=bombs.size();
        vector<vector<bool>> canDetonate(N, vector<bool>(N,false));
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) if(i!=j){
            ll dx=bombs[i][0]-bombs[j][0], dy=bombs[i][1]-bombs[j][1], r=bombs[i][2];
            if(dx*dx+dy*dy <= r*r) canDetonate[i][j]=true;
        }
        int best=0;
        for(int i=0;i<N;i++){
            vector<bool> vis(N,false);
            function<void(int)> dfs=[&](int u){ vis[u]=true; for(int v=0;v<N;v++) if(canDetonate[u][v] && !vis[v]) dfs(v); };
            dfs(i);
            best=max(best,(int)count(vis.begin(),vis.end(),true));
        }
        cout<<"LC2101 MaxBombsDetonated: "<<best<<"\n";
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
