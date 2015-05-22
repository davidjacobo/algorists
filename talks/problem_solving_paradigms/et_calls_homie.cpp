#include <iostream>
using namespace std;

bool valid(int must_sum,int sum){
    return must_sum==sum;
}

void list_numbers(int state[],int k,int digits,int must_sum,int sum){
    if(k==digits){
        if(valid(must_sum, sum)){
            for(int i=1;i<=digits;i++){
                cout<<state[i];
            }
            cout<<endl;
        }
    } else {
        ++k;
        int temp_sum;
        
        for(int i=0;i<10;++i){
            state[k] = i;
            temp_sum = sum + i;
            if(temp_sum > must_sum) continue;
            list_numbers(state, k, digits, must_sum, temp_sum);
        }
    }
}

int main(){
    int digits, must_sum;
    cin>>digits>>must_sum;
    int state[digits+1];

    list_numbers(state, 0, digits, must_sum,0);
    return 0;
}
