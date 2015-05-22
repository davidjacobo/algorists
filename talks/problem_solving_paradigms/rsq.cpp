#include <iostream>
#include <vector>
#define N 8

using namespace std;
int st[N<<2], A[] = {2,3,5,1,3,7,3,8};

int build_tree(int ind,int p,int q){
    if(p==q){
        return st[ind] = A[p];
    } else {
        int m = (p+q)>>1;
        int left = ind<<1;
        int right = left+1;

        int sum = build_tree(left  ,p  ,m);
        sum +=    build_tree(right ,m+1,q);

        return st[ind] = sum;
    }
}

int query(int ind,int p,int q,int i,int j){
    if(p==i && q==j) return st[ind];
    
    int m = (p+q)>>1;
    int left = ind<<1;
    int right = left+1;

    if(i>m) {
        return query(right,  m+1, q, i, j);
    } else if(j<=m) {
        return query(left ,    p, m, i, j);
    } else {
        return query(right,  m+1, q, m+1, j)\
             + query(left ,    p, m,   i, m);
    }
}

int main(){
    int i,j;
    build_tree(1, 0, N-1);

    while(1){
        cout<<"insert query ";
        cin>>i>>j;

        cout<<query(1, 0, N-1, i, j)<<endl;
    }
    return 0;
}
