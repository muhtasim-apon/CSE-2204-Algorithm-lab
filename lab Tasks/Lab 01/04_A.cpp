#include<bits/stdc++.h>
using namespace std;
bool checkadj(int lastnumber,int currentnumber)
{
    if(lastnumber==-1)return true;
    if((lastnumber%2==0 && currentnumber%2==0) || (lastnumber%2!=0 && currentnumber%2!=0))return false;
    if(abs(lastnumber-currentnumber)>=5)return false;
    return true;
}
void generatepermutation(vector<int>&permutation, vector<bool>&visited, int &n)
{
    if(permutation.size()==n)
    {
        for(int i=0;i<permutation.size();i++)
        {
            cout<<permutation[i]<<" ";
        }
        cout<<"\n";
        return;
    }
    //return;
    for(int i=1;i<=n;i++)
    {
        int lastnumber;
        if(permutation.size()==0)
        {
            lastnumber=-1;
        }
         else lastnumber=permutation.back();
       if(!visited[i] && checkadj(lastnumber,i))
       {
        visited[i]=true;
        permutation.push_back(i);
        generatepermutation(permutation,visited,n);
        visited[i]=false;
        permutation.pop_back();        
       } 
    }
}
int main()
{
    int n;
    cin>>n;
    if(n==0)
    {
        cout<<"Less Than 1.Permutation can't be printed"<<"\n";
    }
    else
    {
        vector<int>permutation;
        vector<bool>visited(n+1,false);
        generatepermutation(permutation,visited,n);
    }
}

// #include<bits/stdc++.h>
// using namespace std;

// bool ok(int last,int cur){
//     if(last==-1) return true;

//     if(last%2==cur%2) return false;

//     if(abs(last-cur)>=5) return false;

//     return true;
// }

// void solve(vector<int>&curr, vector<bool>&vis, int n){

//     if(curr.size()==n){
//         for(int x:curr) cout<<x<<" ";
//         cout<<"\n";
//         return;
//     }

//     for(int i=1;i<=n;i++){
//         if(vis[i]) continue;

//         if(!ok(curr.empty() ? -1 : curr.back(), i)) continue;

//         // PUSH
//         vis[i]=1;
//         curr.push_back(i);

//         solve(curr,vis,n);

//         // POP
//         curr.pop_back();
//         vis[i]=0;
//     }
// }

// int main(){
//     int n;
//     cin>>n;

//     if(n<1){
//         cout<<"No permutation\n";
//         return 0;
//     }

//     vector<int>curr;
//     vector<bool>vis(n+1,0);

//     solve(curr,vis,n);
// }