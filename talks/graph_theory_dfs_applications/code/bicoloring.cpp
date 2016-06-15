#include <iostream>
#include <vector>
#include <cstring>
#define MAX_V 1001
#define INVALID -1
using namespace std;

typedef vector<int> vi;
int color[MAX_V];
int V,E;
bool bipartite, seen[MAX_V];
vi graph[MAX_V];

void dfs_bicolor(int u){
    seen[u] = true;

    for(int i=0;i<graph[u].size();++i){
        int v = graph[u][i];

        if(!seen[v]){
            color[v] = 1-color[u];
            dfs_bicolor(v);
        }else if(color[v]==color[u]){
            //Game over man, game over!
            bipartite = false;
        }
    }
}

int main(){
    int x,y;
    cin>>V>>E;
    memset(color, INVALID, sizeof(color));
    memset(seen, false, sizeof(seen));
    for(int i=0;i<E;++i){
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    bipartite = true;
    for(int i=0;i<V;++i){
        if(!seen[i]){
            color[i] = 1;
            dfs_bicolor(i);
        }
    }

    cout<<"The given graph is"<<((bipartite)?"":" NOT")<<" bipartite"<<endl;
    return 0;
}
