#include <iostream>
using namespace std;
typedef unsigned long long integer;
struct trie{
    trie* child[2];
};

integer query(trie* t,integer value,int mask,integer r = 0){
    if(t && mask >= 0){
        integer b = (value & (1 << mask)) >> mask;
        if(t->child[!b]){
            r |= 1 << mask | query(t->child[!b],value,--mask,r);
        }else{
            r |= query(t->child[b],value,--mask,r);
        }
    }
    return r;
}

void add(trie* t,integer value,int mask){
    if(t && mask >= 0){
        integer b = (value & (1 << mask)) >> mask;
        if(!t->child[b]){
            t->child[b] = new trie;
        }
        add(t->child[b],value,--mask);
    }
}

integer maxXor(int l,int r){
    integer x = 0,y,mask = r;
    trie* root = new trie;
    integer n = r;
    int k = 0;
    while(n >>= 1) k++;
    for(integer i = l; i <= r; i++){
        y = query(root,i,k);
        if(y > x){
            x = y;
        }
        add(root,i,k);
    }
    return x;
}

int main(){
    unsigned int l,r;
    cin >> l >> r;
    cout << maxXor(l,r);
    return 0;
}