#include <cstdio>
#include <vector>
#include <cstring>
#define MAX_V 1000000

using namespace std;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

bool seen[MAX_V];
vi graph[MAX_V];

void dfs(int u){
    //We are located at u, we should visit all
    //u's direct neighboors, let's try to visit
    //one at the time iff we haven't seen it 
    //before (call this neighboors v)
    seen[u] = true;
    int v;

    for(int i=0;i<graph[u].size();++i){
        v = graph[u][i];
        if(!seen[v]) dfs(v);
    }
}

int main(){
    int V,E;
    int x,y;
    //V = Amount of vertices in the graph
    //E = Amount of edges in the graph
    scanf("%d %d",&V,&E);
    memset(seen, false, sizeof seen);

    for(int i=0;i<E;++i){
        //On an undirected graph, a conection 
        //from x->y implies that y->x exists too!
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    int source;
    scanf("%d",&source);
    dfs(source);
    return 0;
}
