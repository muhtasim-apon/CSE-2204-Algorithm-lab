#include<bits/stdc++.h>
#define ll long long
using namespace std;
int knapsackrecur(int start, vector<int>&value,vector<int>&weight, int cap,int n)
{
    int taken=0;
    if(start==n || cap<=0)return 0;
    if(weight[start]<=cap)taken=value[start]+knapsackrecur(start+1,value,weight,cap-weight[start],n);
    int notaken=knapsackrecur(start+1,value,weight,cap,n);
    return max(taken ,notaken);
}
int knapsackdp(int start, vector<int>&value,vector<int>&weight, int cap,int n, vector<vector<int>>&mem)
{
    if(start==n || cap<=0)return 0;
    if(mem[start][cap]!=-1)return mem[start][cap];
    int taken =0;
    if(weight[start]<=cap)taken=value[start]+knapsackdp(start+1,value,weight,cap-weight[start],n,mem);
    int notaken=knapsackdp(start+1,value,weight,cap,n,mem);
    return mem[start][cap]=max(taken,notaken);

}
void generateItems(int n, vector<int>&value,vector<int>&weight)
{
    mt19937 rng(42+n);
    uniform_int_distribution<int>wtdist(1,50);
    uniform_int_distribution<int>valdist(10,100);
    for(int start=0;start<n;start++)
    {
        value.push_back(valdist(rng));
        weight.push_back(wtdist(rng));
    }
}
int main()
{
ios::sync_with_stdio(false);
cin.tie(nullptr);
{
     int n,cap;
    // cin>>n>>cap;
    // int start=0;
    // vector<int>value(n);
    // vector<int>weight(n);
     //vector<vector<int>>mem(n,vector<int>(cap+1,-1));
    // int recur=knapsackrecur(start,value,weight,cap,n);
    // int mem=knapsackdp(start,value,weight,cap,n,mem);
    vector<pair<int,int>>tests=
    {
    {5,20},
    {8,30},
    {10,40},
    {12,50},
    {15,70},
    {18,90},
    {20,100},
    {24,120},
    {28,150},
    {32,180}
    };

    // ofstream fout("knapsack_results.csv");
    // fout<<"Test,Items,Capacity,Recursive(ms),Memoization(ms),Answer\n";
    cout<<fixed<<setprecision(6);
    cout<<"\n";
    cout<<"=============================================================\n";
    cout<<" Test | Items | Capacity | Recursive(us) | Memo(us) | Result\n";
    cout<<"=============================================================\n";
    int test_nums=1;
    for(auto x:tests)
{
    int n=x.first;
    int capacity=x.second;
        vector<int>weight;
        vector<int>value;

        generateItems(
            n,
            value,
            weight
        );
        auto start =
        chrono::high_resolution_clock::now();


        int recursiveAnswer =
        knapsackrecur(
            0,
            value,
            weight,
            capacity,
            n
        );


        auto end =
        chrono::high_resolution_clock::now();


        double recursiveTime =
        chrono::duration<double,milli>
        (end-start).count();

        vector<vector<int>>dp(
            n,
            vector<int>(
                capacity+1,
                -1
            )
        );


        start =
        chrono::high_resolution_clock::now();


        int memoAnswer =
        knapsackdp(
            0,
            value,
            weight,
            capacity,
            n,
            dp
        );


        end =
        chrono::high_resolution_clock::now();



        double memoTime =
        chrono::duration<double,milli>
        (end-start).count();




        cout
        <<setw(5)<<test_nums<<" | "
        <<setw(5)<<n<<" | "
        <<setw(8)<<capacity<<" | "
        <<setw(13)<<recursiveTime<<" | "
        <<setw(8)<<memoTime<<" | "
        <<setw(6)<<memoAnswer
        <<"\n";



        // fout
        // <<test_nums<<","
        // <<n<<","
        // <<capacity<<","
        // <<recursiveTime<<","
        // <<memoTime<<","
        // <<memoAnswer<<"\n";


        test_nums++;

    }


    // fout.close();
    //cout<<"\nResults saved to knapsack_results.csv\n";

}
}
