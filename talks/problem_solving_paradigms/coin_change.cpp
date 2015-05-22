#include <iostream>
#define MAX_N 200  
#define INF (1<<30)
using namespace std;
//int coins[] = {1,2,5,10};
int coins[] = {1,3,4,10};

int get_coins_complete_search(int N){
    int min = MAX_N;

    for(int w=0;w<MAX_N;++w){
        for(int x=0;x<MAX_N;++x){
            for(int y=0;y<MAX_N;++y){
                for(int z=0;z<MAX_N;++z){
                    if(w*coins[0] + x*coins[1] + y*coins[2] + z*coins[3] == N \
                        && w + x + y + z < min){  
                        min = w + x + y + z;
                    }
                }
            }
        }
    }
    
    return min;
}

int get_coins_dp_bottom_up(int N){
    int  memo[N+1];
    int coin_types = sizeof(coins) / sizeof(int);

    for(int i=1;i<=N;++i) memo[i] = INF;
    memo[0] = 0;

    for(int i=0;i<coin_types;++i){
        for(int j=1;j<=N;++j){
            if(j>=coins[i]) {
                memo[j] = min(memo[j] , memo[j-coins[i]]+1);
            }
        }
    }

    return memo[N];
}

int top_down(int N,int *memo,int coin_types){
    if(N<0) return INF;
    if(INF!=memo[N]) return memo[N];
    
    int min = INF;
    for(int i=0;i<coin_types;++i){
        int temp = top_down(N-coins[i], memo, coin_types)+1;
        if(temp < min) 
            min = temp;
    }
 
   return memo[N] = min;
}

int get_coins_dp_top_down(int N){
    int coin_types = sizeof(coins) / sizeof(int);
    int memo[N+1];

    for(int i=0;i<=N;++i) 
        memo[i] = INF;
    memo[0] = 0;

    top_down(N, memo, coin_types);
    return memo[N];
}

int get_coins_greedy(int N){
    int coins_counter = 0;
    int coin_types = sizeof(coins) / sizeof(int);

    for(int i=--coin_types;i>=0;--i){
        while(N>=coins[i]){
            ++coins_counter;
            N-= coins[i];
        }
    }

    return coins_counter;
}

int main(){
    int N;
    cin>>N;
    cout<<"Complete Search: "<<get_coins_complete_search(N)<<endl;
    cout<<"DP Bottom Up:    "<<get_coins_dp_bottom_up(N)<<endl;
    cout<<"DP Top Down:     "<<get_coins_dp_top_down(N)<<endl;
    cout<<"Greedy:          "<<get_coins_greedy(N)<<endl;
}
