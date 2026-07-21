#include<bits/stdc++.h>
#define ll long long

using namespace std;


//------------------------------------------------
// Simple Recursive 0/1 Knapsack
//------------------------------------------------

int knapsackrecur(
    int start,
    vector<int>& value,
    vector<int>& weight,
    int cap,
    int n
)
{

    if(start==n || cap<=0)
        return 0;


    int taken=0;


    if(weight[start]<=cap)
    {
        taken =
        value[start] +
        knapsackrecur(
            start+1,
            value,
            weight,
            cap-weight[start],
            n
        );
    }


    int notaken =
    knapsackrecur(
        start+1,
        value,
        weight,
        cap,
        n
    );


    return max(taken,notaken);
}



//------------------------------------------------
// Top Down DP Memoization
//------------------------------------------------

int knapsackdp(
    int start,
    vector<int>& value,
    vector<int>& weight,
    int cap,
    int n,
    vector<vector<int>>& mem
)
{

    if(start==n || cap<=0)
        return 0;


    if(mem[start][cap]!=-1)
        return mem[start][cap];



    int taken=0;


    if(weight[start]<=cap)
    {
        taken =
        value[start] +
        knapsackdp(
            start+1,
            value,
            weight,
            cap-weight[start],
            n,
            mem
        );
    }



    int notaken =
    knapsackdp(
        start+1,
        value,
        weight,
        cap,
        n,
        mem
    );


    return mem[start][cap] =
            max(taken,notaken);

}



//------------------------------------------------
// Random Item Generator
//------------------------------------------------

void generatecases(
    int n,
    vector<int>& value,
    vector<int>& weight
)
{

    mt19937 rng(42+n);


    uniform_int_distribution<int>
    wtdist(1,50);


    uniform_int_distribution<int>
    valdist(10,100);



    for(int i=0;i<n;i++)
    {
        weight.push_back(wtdist(rng));
        value.push_back(valdist(rng));
    }

}



//------------------------------------------------
// MAIN
//------------------------------------------------

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);



    vector<pair<int,int>>tests =
    {

        {5,10},
        {8,15},
        {10,20},
        {12,30},
        {15,40},
        {18,50},
        {20,60},
        {22,70},
        {25,80},
        {28,100}

    };



    ofstream csv("knapsack_results.csv");

    ofstream graph("knapsack_graph.dat");



    csv<<"Test,Items,Capacity,Recursive(ms),Memoization(ms),Answer\n";


    graph<<"Items Recursive Memoization\n";



    cout<<fixed<<setprecision(6);



    cout<<"\n";
    cout<<"=============================================================\n";
    cout<<" Test  Items Capacity Recursive(ms) Memo(ms) Answer\n";
    cout<<"=============================================================\n";



    int test=1;



    for(auto [n,capacity]:tests)
    {


        vector<int>value;
        vector<int>weight;



        generatecases(
            n,
            value,
            weight
        );



        //-----------------------------
        // Recursive Timing
        //-----------------------------

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



        auto stop =
        chrono::high_resolution_clock::now();



        double recursiveTime =
        chrono::duration<double,milli>
        (stop-start).count();



        //-----------------------------
        // DP Timing
        //-----------------------------


        vector<vector<int>>mem(
            n,
            vector<int>(
                capacity+1,
                -1
            )
        );



        start =
        chrono::high_resolution_clock::now();



        int dpAnswer =
        knapsackdp(
            0,
            value,
            weight,
            capacity,
            n,
            mem
        );



        stop =
        chrono::high_resolution_clock::now();



        double dpTime =
        chrono::duration<double,milli>
        (stop-start).count();



        //-----------------------------
        // Display
        //-----------------------------


        cout
        <<setw(5)<<test
        <<setw(7)<<n
        <<setw(10)<<capacity
        <<setw(16)<<recursiveTime
        <<setw(12)<<dpTime
        <<setw(10)<<dpAnswer
        <<"\n";




        //-----------------------------
        // Save CSV
        //-----------------------------


        csv
        <<test<<","
        <<n<<","
        <<capacity<<","
        <<recursiveTime<<","
        <<dpTime<<","
        <<dpAnswer<<"\n";



        //-----------------------------
        // Save graph data
        //-----------------------------


        graph
        <<n<<" "
        <<recursiveTime<<" "
        <<dpTime<<"\n";



        test++;

    }



    csv.close();
    graph.close();



    cout<<"\nFiles Generated:\n";
    cout<<"1. knapsack_results.csv\n";
    cout<<"2. knapsack_graph.dat\n";


    return 0;
}