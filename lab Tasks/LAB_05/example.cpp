#include<bits/stdc++.h>
#define ll long long
using namespace std;


int knapsackrecur(int start, vector<int>&value,vector<int>&weight, int cap,int n)
{
    int taken=0;
    if(start==n || cap<=0)return 0;

    if(weight[start]<=cap)
        taken=value[start]+knapsackrecur(start+1,value,weight,cap-weight[start],n);

    int notaken=knapsackrecur(start+1,value,weight,cap,n);

    return max(taken ,notaken);
}



int knapsackdp(int start, vector<int>&value,vector<int>&weight, int cap,int n, vector<vector<int>>&mem)
{
    if(start==n || cap<=0)return 0;

    if(mem[start][cap]!=-1)
        return mem[start][cap];

    int taken =0;

    if(weight[start]<=cap)
        taken=value[start]+knapsackdp(start+1,value,weight,cap-weight[start],n,mem);

    int notaken=knapsackdp(start+1,value,weight,cap,n,mem);

    return mem[start][cap]=max(taken,notaken);

}



void generatecase(int n, vector<int>&value,vector<int>&weight)
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



    ofstream graph("knapsack_graph.dat");

    graph<<"Items Recursive(us) Memo(us)\n";



    cout<<fixed<<setprecision(3);


    cout<<"\n";
    cout<<"=================================================================\n";
    cout<<" Test | Items | Capacity | Recursive(us) | Memo(us) | Result\n";
    cout<<"=================================================================\n";


    int test_nums=1;



    for(auto x:tests)
    {

        int n=x.first;
        int capacity=x.second;


        vector<int>weight;
        vector<int>value;


        generatecase(n,value,weight);



        auto start1 =
        chrono::high_resolution_clock::now();



        int ans1 =
        knapsackrecur(
            0,
            value,
            weight,
            capacity,
            n
        );



        auto end1 =
        chrono::high_resolution_clock::now();



        double recurtime =
        chrono::duration<double,micro>
        (end1-start1).count();





        vector<vector<int>>mem(
            n,
            vector<int>(capacity+1,-1)
        );



        auto start2 =
        chrono::high_resolution_clock::now();



        int ans2 =
        knapsackdp(
            0,
            value,
            weight,
            capacity,
            n,
            mem
        );



        auto end2 =
        chrono::high_resolution_clock::now();



        double dptime =
        chrono::duration<double,micro>
        (end2-start2).count();





        cout
        <<setw(5)<<test_nums
        <<" | "
        <<setw(5)<<n
        <<" | "
        <<setw(8)<<capacity
        <<" | "
        <<setw(13)<<recurtime
        <<" | "
        <<setw(8)<<dptime
        <<" | "
        <<setw(6)<<ans2
        <<"\n";



        // graph data

        graph
        <<n<<" "
        <<recurtime<<" "
        <<dptime
        <<"\n";



        test_nums++;

    }



    graph.close();



    cout<<"\nGraph data generated: knapsack_graph.dat\n";


}

return 0;
}