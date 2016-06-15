#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
typedef vector<int> vi;
typedef pair<int,double> id;

class Graph{
public:
	Graph(int v,int e) : V{v} , E{e} , graph{new vi[V]}{}

	void insert(int u,int v) {
		graph[u].push_back(v);
	}

	vi top_sort() {
		//We will need a temporal array to keep track of the indegree
		//A vector for the linearized order = output and 
		//A vector for the outgoing edges per each vertex
		int indegree[V];
		vi output, neighbours;

		memset(indegree, 0, sizeof indegree);

		//Alright, lets count the indegree
		for(auto i=0;i<V;++i) {
			neighbours = local_neighbours(i);
			for(auto j:neighbours) {
				++indegree[j];
			}
		}

		//Which indegrees ended in 0?
		//These are the initial tasks which can be started right away
		for(auto i=0;i<V;++i) {
			if(indegree[i]==0) {
				output.push_back(i);
			}
		}

		//Lets relax each task wich indegree == 0
		for(auto i=0;i<output.size();++i) {
			auto u = output[i];
			neighbours = local_neighbours(u);
			for(auto v:neighbours) {
				--indegree[v];
				if(indegree[v]==0) {
					output.push_back(v);
				}
			}
		}

		return output;
	}

	int v_size() {
		return V;
	}

	const vi local_neighbours(int u) {
		return graph[u];
	}

	~Graph() {
		delete[] graph;
	}
private:
	int V,E;
	vector<int> *graph;
};

Graph* read_graph() {
	int V,E;
	int x,y;
	cin>>V>>E;
	Graph *graph = new Graph(V,E);
	for(auto i=0;i<E;++i) {
		cin>>x>>y;
		graph->insert(x,y);
	}

	return graph;
}

int main() {
	Graph *graph = read_graph();
	vi output = graph->top_sort();

	if(output.size()!=graph->v_size()) {
		cout<<"These tasks cannot be linearized"<<endl;
	} else {
		cout<<"At least one sort exists"<<endl;
		for(auto i:output) {
			cout<<i<<" ";
		}
		cout<<endl;
	}

	delete graph;
	return 0;
}