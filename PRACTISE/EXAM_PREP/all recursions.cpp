#include<bits/stdc++.h>
using namespace std;

/////////////////////////////////////////////////////////////////
// UTIL
/////////////////////////////////////////////////////////////////
int abs2(int x){ return x<0?-x:x; }

/////////////////////////////////////////////////////////////////
// PRINT 1 TO N
/////////////////////////////////////////////////////////////////
void print1toN(int n){
    if(n==0) return;
    print1toN(n-1);
    cout<<n<<" ";
}

/////////////////////////////////////////////////////////////////
// PRINT N TO 1
/////////////////////////////////////////////////////////////////
void printNto1(int n){
    if(n==0) return;
    cout<<n<<" ";
    printNto1(n-1);
}

/////////////////////////////////////////////////////////////////
// PERMUTATION 1..n
/////////////////////////////////////////////////////////////////
void perm(int n, vector<int>&curr, vector<int>&vis){
    if(curr.size()==n){
        for(int x:curr) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    for(int i=1;i<=n;i++){
        if(!vis[i]){
            vis[i]=1;
            curr.push_back(i);

            perm(n,curr,vis);

            curr.pop_back();
            vis[i]=0;
        }
    }
}

/////////////////////////////////////////////////////////////////
// PROBLEM A / D TYPE
// even index -> even digit, odd index -> odd digit
/////////////////////////////////////////////////////////////////
void pattern_even_odd(int idx, int n, vector<int>&curr){
    if(idx==n){
        for(int x:curr) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    if(idx%2==0){
        for(int d:{0,2,4}){
            curr.push_back(d);
            pattern_even_odd(idx+1,n,curr);
            curr.pop_back();
        }
    }else{
        for(int d:{1,3}){
            curr.push_back(d);
            pattern_even_odd(idx+1,n,curr);
            curr.pop_back();
        }
    }
}

/////////////////////////////////////////////////////////////////
// PROBLEM C TYPE
// even index -> odd digit
// odd index -> even digit
/////////////////////////////////////////////////////////////////
void pattern_swap(int idx,int n,vector<int>&curr){
    if(idx==n){
        for(int x:curr) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    if(idx%2==0){
        for(int d:{1,3}){
            curr.push_back(d);
            pattern_swap(idx+1,n,curr);
            curr.pop_back();
        }
    }else{
        for(int d:{0,2,4}){
            curr.push_back(d);
            pattern_swap(idx+1,n,curr);
            curr.pop_back();
        }
    }
}

/////////////////////////////////////////////////////////////////
// COMBINATIONS DESCENDING
/////////////////////////////////////////////////////////////////
void comb(int start,int k,int n,vector<int>&curr){
    if(curr.size()==k){
        for(int x:curr) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    for(int i=start;i>=0;i--){
        curr.push_back(i);
        comb(i-1,k,n,curr);
        curr.pop_back();
    }
}

/////////////////////////////////////////////////////////////////
// CONSTRAINT CHECK
/////////////////////////////////////////////////////////////////
bool ok(int last,int cur){
    if(last==-1) return true;
    if(last%2==cur%2) return false;
    if(abs2(last-cur)>=5) return false;
    return true;
}

/////////////////////////////////////////////////////////////////
// SPECIAL PERMUTATION
/////////////////////////////////////////////////////////////////
void special(int n,vector<int>&curr,vector<int>&vis){
    if(curr.size()==n){
        for(int x:curr) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int last = curr.empty() ? -1 : curr.back();

            if(!ok(last,i)) continue;

            vis[i]=1;
            curr.push_back(i);

            special(n,curr,vis);

            curr.pop_back();
            vis[i]=0;
        }
    }
}

/////////////////////////////////////////////////////////////////
// SPECIAL SUM < 30
/////////////////////////////////////////////////////////////////
void specialSum(int n,vector<int>&curr,vector<int>&vis,int sum){
    if(sum>=30) return;

    if(curr.size()==n){
        for(int x:curr) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int last = curr.empty() ? -1 : curr.back();

            if(!ok(last,i)) continue;

            vis[i]=1;
            curr.push_back(i);

            specialSum(n,curr,vis,sum+i);

            curr.pop_back();
            vis[i]=0;
        }
    }
}

/////////////////////////////////////////////////////////////////
// MENU
/////////////////////////////////////////////////////////////////
int main(){

    cout<<"1 Print 1 to N\n";
    cout<<"2 Print N to 1\n";
    cout<<"3 Permutation\n";
    cout<<"4 Pattern (even idx even, odd idx odd)\n";
    cout<<"5 Pattern swap\n";
    cout<<"6 Combinations\n";
    cout<<"7 Special perm\n";
    cout<<"8 Special sum < 30\n";

    int choice;
    cin>>choice;

    if(choice==1){
        int n;cin>>n;
        print1toN(n);
    }

    else if(choice==2){
        int n;cin>>n;
        printNto1(n);
    }

    else if(choice==3){
        int n;cin>>n;
        vector<int>curr,vis(n+1,0);
        perm(n,curr,vis);
    }

    else if(choice==4){
        int n;cin>>n;
        vector<int>curr;
        pattern_even_odd(0,n,curr);
    }

    else if(choice==5){
        int n;cin>>n;
        vector<int>curr;
        pattern_swap(0,n,curr);
    }

    else if(choice==6){
        int n,k;cin>>n>>k;
        vector<int>curr;
        comb(n-1,k,n,curr);
    }

    else if(choice==7){
        int n;cin>>n;
        vector<int>curr,vis(n+1,0);
        special(n,curr,vis);
    }

    else if(choice==8){
        int n;cin>>n;
        vector<int>curr,vis(n+1,0);
        specialSum(n,curr,vis,0);
    }

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> path;

vector<int> evenDigits = {0,2,4};
vector<int> oddDigits  = {1,3};

void dfs(int idx){

    if(idx == n){
        for(int x:path) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    if(idx % 2 == 0){
        for(int d : evenDigits){
            path.push_back(d);
            dfs(idx+1);
            path.pop_back();
        }
    }
    else{
        for(int d : oddDigits){
            path.push_back(d);
            dfs(idx+1);
            path.pop_back();
        }
    }
}

int main(){
    cin>>n;
    dfs(0);
}
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> path;

void dfs(int idx){

    if(idx == n){
        for(int x:path) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    if(idx % 2 == 0){
        for(int d : {1,3}){
            path.push_back(d);
            dfs(idx+1);
            path.pop_back();
        }
    }
    else{
        for(int d : {0,2,4}){
            path.push_back(d);
            dfs(idx+1);
            path.pop_back();
        }
    }
}

int main(){
    cin>>n;
    dfs(0);
}
#include<bits/stdc++.h>
using namespace std;

int n,k;
vector<int> path;

void dfs(int start){

    if(path.size() == k){
        for(int x:path) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    for(int i=start;i>=0;i--){
        path.push_back(i);
        dfs(i-1);
        path.pop_back();
    }
}

int main(){
    cin>>n>>k;
    dfs(n-1);
}
#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> path;

void dfs(int idx){

    if(idx == n){
        for(int x:path) cout<<x<<" ";
        cout<<"\n";
        return;
    }

    if(idx % 2 == 0){
        for(int d : {0,2,4}){
            path.push_back(d);
            dfs(idx+1);
            path.pop_back();
        }
    }
    else{
        for(int d : {1,3}){
            path.push_back(d);
            dfs(idx+1);
            path.pop_back();
        }
    }
}

int main(){
    cin>>n;
    dfs(0);
}