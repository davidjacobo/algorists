#include <iostream>
#include <vector>
#include <cstring>
#define MAX_V 1001
#define BLACK 0
#define GRAY 1
#define WHITE 2
#define INV -1

using namespace std;
typedef vector<int> vi;
int state[MAX_V], parent[MAX_V];
int V,E;
bool cycle;
vi graph[MAX_V];

void dfs_cycle(int u){
    state[u] = GRAY;

    for(int i=0;i<graph[u].size();++i){
        int v = graph[u][i];

        if(BLACK==state[v]){
            parent[v] = u;
            dfs_cycle(v);
        }else if(GRAY==state[v] && parent[u]!=v){
            cycle = true;
        }
    }

    state[u] = WHITE;
}

int main(){
    int x,y;
    cin>>V>>E;
    memset(state, BLACK, sizeof(state));
    memset(parent, INV, sizeof(parent));
    for(int i=0;i<E;++i){
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    cycle = false;
    for(int i=0;i<V;++i){
        if(BLACK==state[i]){
            dfs_cycle(i);
        }
    }

    cout<<"The given graph does"<<((cycle)?"":" NOT")<<" contain a cycle"<<endl;
    return 0;
}
