#include <iostream>
#include <vector>
#include <algorithm>
#define MAX_V 1000
#define INF (1<<29)
#define INV -1
#define CYCLE 1
#define OK 0

using namespace std;
typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;

void insert(vii (&graph)[MAX_V],int x,int y,int w) {
	graph[x].push_back(ii(y,w));
}

void capture_input(vii (&graph)[MAX_V],int& v,int& e,int& source) {
	int x,y,w;
	cin>>v>>e;
	for(int i=0;i<e;++i) {
		cin>>x>>y>>w;
		insert(graph, x, y, w);
	}
	cin>>source;

}

int cycle_present(const vii (&graph)[MAX_V], int* distances,int v) {
	//I don't need to modify/compute distances again
	//Running a single cycle (thats the main difference agains bellman_ford func)

	for(int j=0;j<v;++j) {
		for(int k=0;k<graph[j].size();++k) {
			int y = graph[j][k].first;
			int w = graph[j][k].second;
			int total_dist = distances[j] + w;
			if(total_dist < distances[y]) {
				//There shouldn't be another relaxation in here
				return y;
			}
		}
	}

	return INV;
}

void dfs(const vii (&graph)[MAX_V],int source,bool* wrong) {
	wrong[source] = true;

	for(int j=0;j<graph[source].size();++j) {
		int y = graph[source][j].first;

		if(!wrong[y]) dfs(graph, y, wrong);
	}
}

int bellman_ford(const vii (&graph)[MAX_V],int source,int* distances,int* parent,bool* wrong,int v) {
	fill(distances, distances+v, INF);
	fill(parent, parent+v, INV);
	fill(wrong, wrong+v, false);

	distances[source] = 0;
	for(int i=0;i<v-1;++i) {
		for(int j=0;j<v;++j) {
			for(int k=0;k<graph[j].size();++k) {
				int y = graph[j][k].first;
				int w = graph[j][k].second;
				int total_dist = distances[j] + w;
				if(total_dist < distances[y]) {
					//RELAX!!!
					distances[y] = total_dist;
					parent[y] = j;
				}
			}
		}
	}

	//Alright, if there are no negative cycles we are good to go!
	//doesn't hurt to check tho

	int cycle_start = cycle_present(graph, distances, v);
	if(cycle_start!=INV) {
		//We already know there is a cycle, another interesting question is:
		//Which vertices in the graph are being afected by the cycle?
		dfs(graph, cycle_start, wrong);

		return CYCLE;
	} else {
		return OK;
	}
}

int main() {
	int v,e,source,distances[MAX_V],parent[MAX_V];
	bool wrong[MAX_V];
	vii graph[MAX_V];

	capture_input(graph, v, e, source);
	bellman_ford(graph, source,distances,parent,wrong,v);
	return 0;
} 